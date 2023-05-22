#include "functions.h"

//прием ввода до "~"
std::string enterSrcString(std::vector<std::string>& lines) {
    cout << "Enter your text. To stop, start a new line and press \"~\"" << endl;
    std::string s;
    while (true) {
        std::string temp;
        std::getline(cin, temp);
        if (temp == "~")
            break;
        else {
            //разбитие всего ввода на все строки 
            lines.push_back(temp);
            s += temp += "\n";
        }
    }
    //cout << s << endl;
    //cout << "==============" << endl;

    return s;
}

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
        int partSize = words[i].size();
        while (partSize >= input) {
            for (int j = 0; j < words[i].size(); j++) {
                std::string temp;
                temp = words[i].substr(j, partSize);

                if (temp.size() >= partSize) {
                    //заполнение массива подстрок для дальнейших сравнений
                    wordPartVec.push_back(temp);       
                    //заполение хэш таблицы: ключ - подстрока; знчаение - позиция в исходной строке
                    wordParts.insert(std::pair<std::string, int>(temp, num + j));   
                                                                                    
                    //cout << num + j << ": " << temp << endl;
                }
            }
            partSize--;
        }
        num += words[i].size() + 1;
    }
    return wordParts;
}