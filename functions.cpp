#include "functions.h"
#include "interface.h"
#include "fileIO.h"
#include "tester.h"

std::string launchAll(bool isTest) {
    std::string fileName{};
    std::string srcString{};
    bool isStringKept = false;
    std::vector<std::string> lines;
    std::vector<std::string> allChars;
    std::multimap<std::string, int> wordParts;
    std::string s;
    do {
        if (!isStringKept && !isTest) {
            lines.clear();
            allChars.clear();
            wordParts.clear();
            srcString = launchMainMenu(lines, fileName);
        }
        int input = 0;
        if (isTest) {
            srcString = TESTSTRING;
            lines.push_back(srcString);
            input = TESTVALUE;
        }
        else{
            input = enterPartSize();

        }
        //создание временной s дл€ дальнейшего восстановлени€ строки, если потребуетс€
        s = srcString;
        wordParts = splitString(lines, allChars, input);
        s = findRepeats(allChars, wordParts, s);
        if (!isTest) {
            giveResult(srcString, s);
            saveToFile(fileName, s);
            givePostParseMenu();
            isStringKept = launchPostParseMenu(s, srcString);
        }
        else{
            return s;
        }
    } while (true);
    return s;
}

std::string launchMainMenu(std::vector<std::string>& lines, std::string& fileName) {
    std::string srcString{};
    bool exitFlag = true;

    do {
        giveMainMenu();
        mainMenuChoice choice = static_cast<mainMenuChoice>(checkInputInt());
        exitFlag = true;
        switch (choice)
        {
        case mainMenuChoice::manual:
            srcString = setSrcString(lines);
            break;
        case mainMenuChoice::file:
            std::tie(fileName, exitFlag) = openFile();
            if (exitFlag) {
                srcString = setSrcString(lines, fileName);
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
    return srcString;
}

bool launchPostParseMenu(std::string& parsedString, std::string srcString) {
    bool exitFlag = true;
    bool keepString = false;
    do {
        postParseMenuChoice choice = static_cast<postParseMenuChoice>(checkInputInt());
        exitFlag = true;
        keepString = false;
        switch (choice) {
        case postParseMenuChoice::returnToSrc:
            parsedString = srcString;
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
std::string setSrcString(std::vector<std::string>& lines) {
    std::string s;
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
                lines.push_back(temp);
                s += temp + '\n';
            }
        }
        if (s.empty()) {
            cout << "ERR. An empty string has been entered. Try again: " << endl;
        }
    } while (s.empty());
    //cout << s << endl;
    //cout << "==============" << endl;

    return s;
}



//заполение хэш таблицы: ключ - подстрока; знчаение - позици€ в исходной строке
std::multimap<std::string, int> splitString(const std::vector<std::string>& lines, std::vector<std::string>& wordPartVec, int input) {

    //разделение на слова
    std::vector<std::string> words;
    std::multimap<std::string, int> wordParts;
    for (int i = 0; i < lines.size(); i++) {
        std::stringstream ssin(lines[i]);
        std::string temp;
        while (ssin >> temp) {
            words.push_back(temp);
        }
    }

    //разделение на все возможные подстроки
    for (int i = 0, num = 0; i < words.size(); i++) {
        int partSize = static_cast<int>(words[i].size());
        while (partSize >= input) {
            for (int j = 0; j < words[i].size(); j++) {
                std::string temp;
                temp = words[i].substr(j, partSize);

                if (temp.size() >= partSize) {
                    //заполнение массива подстрок дл€ дальнейших сравнений
                    wordPartVec.push_back(temp);       
                    
                    wordParts.insert(std::pair<std::string, int>(temp, num + j));   
                                                                                    
                    //cout << num + j << ": " << temp << endl;
                }
            }
            partSize--;
        }
        num += static_cast<int>(words[i].size()) + 1;
    }
    return wordParts;
}

//удаление повтор€ющихс€ частей слов из словар€ сравнений 
void delRepeat(std::vector<std::string>& allChars) {
    std::sort(allChars.begin(), allChars.end());
    allChars.erase(std::unique(allChars.begin(), allChars.end()), allChars.end());
}

//поиск и замена повтор€ющихс€ символов
std::string findRepeats(std::vector<std::string> allChars, std::multimap<std::string, int>& wordParts, std::string s) {
    std::multimap<std::string, int>::iterator itr;

    delRepeat(allChars);

    //—ортировка массива подсрок по убыванию их длины дл€ того, чтобы замен€ть сначала самые длинные подстроки
    std::sort(allChars.begin(), allChars.end(), [](std::string& a1, std::string& a2) { return a1.size() > a2.size(); });

    for (auto& w : allChars) {
        std::string st = w;
        //std::string st = "st";
        //cout <<"---> " << st << endl;
        int n = static_cast<int>(st.size());
        //cout << st << ": " << n << endl;
        int min = INT_MAX;
        //cin >> st;
        //cout << "============================" << endl;
        if (wordParts.count(st) > 1) {
            auto search = wordParts.find(st);
            for (itr = search; itr != wordParts.end(); itr++) {
                if (itr->first == st) {
                    if (itr->second < min) {
                        min = itr->second;
                    }
                }

            }
            //cout << "============================" << endl;
            for (itr = wordParts.begin(); itr != wordParts.end(); itr++) {
                std::string temp;
                if (itr->second != min && itr->first == st) {
                    temp = "{" + std::to_string(min + 1) + ',' + std::to_string(n) + "}";
                    //cout << min << endl;
                    std::string str1 = s.substr(0, min + st.size());
                    //cout <<"1. " << str1 << " ";
                    std::string str2 = s.substr(min + st.size());
                    //cout <<"2. "<< str2 << " ";
                    str2 = std::regex_replace(str2, std::regex(st), temp);
                    s = str1 + str2;
                    //cout <<"3. "<< s << endl;
                }
            }
        }
    }
    return s;
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