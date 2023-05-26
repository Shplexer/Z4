#include "functions.h"
#include "interface.h"
#include "fileIO.h"
#include "tester.h"

struct Cipher {
    int firstInd = 0;
    int len = 0;
    std::string cipherString{};
};

std::vector<Cipher> findEncryptions(std::string encryptedString) {
    const char brackL = '{';
    const char brackR = '}';
    const char comma = ',';
    std::vector<Cipher>ciphers;
    //std::vector<int>firstSymbolIndexes;
    //std::vector<int>substrLen;
    for (int i = 0; i < encryptedString.size(); i++) {
        std::string num1{};
        std::string num2{};
        //cout << i << " " << encryptedString[i] << endl;
        //Проходим по всем символам до '{'
        if (encryptedString[i] == brackL) {
            //cout << encryptedString[i] << endl;
            i++;
            //После 
            while (isdigit(encryptedString[i])) {
                num1 += encryptedString[i];
                //cout << encryptedString[i] << endl;
                i++;
            }

            if (encryptedString[i] == comma) {
                i++;
                while (isdigit(encryptedString[i])) {
                    num2 += encryptedString[i];
                    i++;
                }
                if (encryptedString[i] == brackR) {
                    //firstSymbolIndexes.push_back(stoi(num1));
                    //substrLen.push_back(stoi(num2));
                    Cipher temp;
                    temp.firstInd = stoi(num1) - 1;
                    temp.len = stoi(num2);
                    //cipher.insert(std::pair<int,int>(stoi(num1), stoi(num2)));
                    //std::string newS = brackL + num1 + comma + num2 + brackR;
                    temp.cipherString = brackL + num1 + comma + num2 + brackR;
                    ciphers.push_back(temp);
                    //cout << newS << endl;
                }
            }
        }
    }
    return ciphers;
}

std::string decrypt(std::string encryptedString) {
    std::vector<Cipher>ciphers = findEncryptions(encryptedString);
    std::string decryptedString = encryptedString;
    std::sort(ciphers.begin(), ciphers.end(), [](Cipher& a, Cipher& b) { return a.firstInd < b.firstInd; });
    for (auto i : ciphers) {
        int indexToReplace = static_cast<int>(decryptedString.find(i.cipherString));
        std::string decryptedPart = decryptedString.substr(i.firstInd, i.len);
        decryptedString.replace(indexToReplace, i.cipherString.size(), decryptedPart);
        //cout << decryptedString << endl;
    }
    return decryptedString;
}

std::string launchAll(bool isTest) {
    std::string fileName{};
    std::string initialString{};
    bool isStringKept = false;
    std::vector<std::string> allChars;
    std::string resultString{};
    do {
        if (!isStringKept && !isTest) {
            allChars.clear();
            initialString = launchMainMenu(fileName);
        }
        int inputSubstrSize = 0;
        if (isTest) {
            initialString = TESTSTRING;
            inputSubstrSize = TESTVALUE;
        }
        else{
            inputSubstrSize = enterPartSize();
        }

        //создание временной для дальнейшего восстановления строки, если потребуется
        resultString = initialString;
        allChars = splitString(initialString, allChars, inputSubstrSize);
        resultString = findRepeats(allChars, resultString);
        if (!isTest) {
            giveResult(initialString, resultString);
            saveToFile(fileName, resultString);
            givePostParseMenu();
            isStringKept = launchPostParseMenu(resultString, initialString);
        }
        else{
            return resultString;
        }
    } while (true);
    return resultString;
}

std::string launchMainMenu(std::string& fileName) {
    std::string initialString{};
    bool exitFlag = true;

    do {
        giveMainMenu();
        mainMenuChoice choice = static_cast<mainMenuChoice>(checkInputInt());
        exitFlag = true;
        switch (choice)
        {
        case mainMenuChoice::manual:
            initialString = setInitialString();
            break;
        case mainMenuChoice::file:
            fileName = openFile();
            //cout << fileName;
            if (!fileName.empty()) {
                initialString = setInitialString(fileName);
            }
            else{
                exitFlag = false;
            }
            break;
        case mainMenuChoice::test:
            launchTest();
            exitFlag = false;
            break;
        case mainMenuChoice::exit:
            cout << "Exiting..." << endl;
            std::exit(0);
        default:
            cout << "ERR. Wrong input, try again" << endl;
            exitFlag = false;
            break;
        }
    } while (!exitFlag);
    std::vector<Cipher> encryptions = findEncryptions(initialString);
    if (!encryptions.empty()) {
        cout << "Intput text: " << endl << initialString << endl;
        cout << "Found encryptions: " << endl;
        for (int i = 0; i < encryptions.size(); i++) {
            cout << i + 1 << ": " << encryptions[i].cipherString << endl;
        }
        do {
            exitFlag = true;
            cout << "Would you like to decrypt the text?" << endl << "1. Yes" << endl << "2. No" << endl;
            decryptChoice choice = static_cast<decryptChoice>(checkInputInt());
            switch (choice)
            {
            case decryptChoice::Yes:

                initialString = decrypt(initialString);
                cout << "Decrypted string:" << endl << initialString << endl;
                break;
            case decryptChoice::No:

                break;
            default:
                cout << "ERR. Wrong input, try again" << endl;
                exitFlag = false;
                break;
            }
        } while (!exitFlag);
    }
    return initialString;
}

bool launchPostParseMenu(std::string& parsedString, std::string initialString) {
    bool exitFlag = true;
    bool keepString = false;
    do {
        postParseMenuChoice choice = static_cast<postParseMenuChoice>(checkInputInt());
        exitFlag = true;
        keepString = false;
        switch (choice) {
        case postParseMenuChoice::returnToSrc:
            parsedString = initialString;
            keepString = true;
            break;
        case postParseMenuChoice::startAgain:
            keepString = false;
            break;
        case postParseMenuChoice::exit:
            std::exit(0);
        default:
            cout << "ERR. Wrong input, try again" << endl;
            exitFlag = false;
            break;
        }
    } while (!exitFlag);
    return keepString;
}

//прием и разбитие ввода на массив строк и сборка одной целой строки до ввода "~"
std::string setInitialString() {
    std::string initialString;
    cout << "Enter your text. To stop, start a new line and press \"~\"" << endl;
    do {
        while (true) {
            std::string temp;
            std::getline(cin, temp);
            //прием ввода до "~"
            if (temp == "~")
                break;
            else if (!temp.empty()) {
                //разбитие всего ввода на все строки 
                initialString += temp + '\n';
            }
        }
        if (initialString.empty()) {
            cout << "ERR. An empty string has been entered. Try again: " << endl;
        }
    } while (initialString.empty());
    //cout << initialString << endl;
    //cout << "==============" << endl;

    return initialString;
}



//заполение хэш таблицы: ключ - подстрока; значение - позиция начала подстроки в исходной строке
std::vector<std::string> splitString(const std::string initialString, std::vector<std::string> wordPartVec, int inputSubstrSize) {

    //разделение на слова
    std::vector<std::string> words;
        std::stringstream ssin(initialString);
        std::string temp;
        while (ssin >> temp) {
            words.push_back(temp);
        }
    //tester
    //
    // 
    //разделение на все возможные подстроки
    for (int i = 0; i < words.size(); i++) {
        int partSize = static_cast<int>(words[i].size());
        while (partSize >= inputSubstrSize) {
            for (int j = 0; j < words[i].size(); j++) {
                //std::string temp;
                temp = words[i].substr(j, partSize);

                if (temp.size() >= partSize) {
                    //заполнение массива подстрок для дальнейших сравнений
                    wordPartVec.push_back(temp);       
                                                                                                       
                    //cout << num + j << ": " << temp << endl;
                }
            }
            partSize--;
        }
    }
    //for (auto i : wordPartVec) {
    //    cout << i << endl;
    //}
    //system("pause");
    return wordPartVec;
}

//удаление повторяющихся частей слов из словаря сравнений 
void delRepeat(std::vector<std::string>& allChars) {
    std::sort(allChars.begin(), allChars.end());
    allChars.erase(std::unique(allChars.begin(), allChars.end()), allChars.end());
}

//поиск и замена повторяющихся символов
std::string findRepeats(std::vector<std::string> allChars, std::string mainString) {
    std::string uneditedString = mainString;
    delRepeat(allChars);

    //Сортировка массива подсрок по убыванию их длины для того, чтобы заменять сначала самые длинные подстроки
    std::sort(allChars.begin(), allChars.end(), [](std::string& a1, std::string& a2) { return a1.size() > a2.size(); });

    int minIndex = 0;
    for (auto& substr : allChars) {
        int occurrences = 0;
        std::string::size_type pos = 0;
        while ((pos = mainString.find(substr, pos)) != std::string::npos) {
            ++occurrences;
            pos += substr.length();
        }
        if (occurrences > 1) {
            std::string temp;
            minIndex = static_cast<int>(mainString.find(substr));
            cout << "minInd: " << minIndex << endl << " substr: " << substr << endl;
            temp = "{" + std::to_string(uneditedString.find(substr) + 1) + ',' + std::to_string(static_cast<int>(substr.size())) + "}";
            std::string str1 = mainString.substr(0, minIndex + substr.size());
            cout << "1. " << str1 << " " << endl;
            std::string str2 = mainString.substr(minIndex + substr.size());
            cout << "2. " << str2 << " " << endl;
            str2 = std::regex_replace(str2, std::regex(substr), temp);
            mainString = str1 + str2;
            cout << "3. " << mainString << endl;   
        }
    }
    return mainString;
}

template<typename T>
T checkInput() {
    T userInput{};
    while (!(cin >> userInput)) {
        cin.clear();											//discard err flag
        cin.ignore(INT_MAX, '\n');								//clear buffer for INT_MAX characters or until '\n'
        cout << "ERR. Wrong input, try again" << endl;
    }
    cin.ignore(INT_MAX, '\n');
    return userInput;
}
template<typename T>
T checkInput(int lowerLimit) {
    T userInput{};
    while (!(cin >> userInput) || userInput <= lowerLimit) {
        cin.clear();											//discard err flag
        cin.ignore(INT_MAX, '\n');								//clear buffer for INT_MAX characters or until '\n'
        cout << "ERR. Wrong input, try again" << endl;
    }
    cin.ignore(INT_MAX, '\n');
    return userInput;
}

int checkInputInt() {
    return checkInput<int>();
}

int checkInputInt(int lowerLimit) {
    return checkInput<int>(lowerLimit);
}

std::string stringInput() {
    std::string input{ "==" };
    std::getline(cin >> std::ws, input);
    for (auto i = 0; i < input.size(); i++) {
        if (input[i] == ' ') {
            input[i] = '_';
        }
    }
    return input;
}

std::string stringOutput(std::string input) {
    std::string temp = input;
    for (auto i = 0; i < temp.size(); i++) {
        if (temp[i] == '_') {
            temp[i] = ' ';
        }
    }
    return temp;
}

int enterPartSize() {
    cout << "Enter minimal length of a substring: ";
    int input = checkInputInt(0);
    return input;
}