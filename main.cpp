#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <regex>

#include "functions.h"

using std::cin;
using std::cout;
using std::endl;

    //РАЗБИТЬ ВСЕ В ОТДЕЛЬНЫЕ ФУНКЦИИ!
    //СДЕЛАТЬ ДРАЙВЕР КОДА
    //СДЕЛАТЬ ПРОВЕРКИ ВВОДА input И ПУСТОЙ СТРОКИ
    //НЕ УМЕРЕТЬ

int main() {
    std::vector<std::string> lines;
    std::vector<std::string> allChars;
    std::multimap<std::string, int> wordParts;
    std::multimap<std::string, int>::iterator itr;

    //прием и разбитие ввода на массив строк и сборка одной целой строки до ввода "~"
    std::string srcString = enterSrcString(lines);
    std::string s = srcString;
    int input = 0;
    cout << "Enter minimal length of a substring: ";
    cin >> input;

    wordParts = splitString(lines, allChars, input);


    std::sort(allChars.begin(), allChars.end());
    allChars.erase(std::unique(allChars.begin(), allChars.end()), allChars.end());
    std::sort(allChars.begin(), allChars.end(), [](std::string& a1, std::string& a2) { return a1.size() > a2.size(); });
    
    for(auto& w : allChars) {
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
                    std::string str1 = s.substr(0, min+st.size());
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
    cout << s;
    return 0;
}