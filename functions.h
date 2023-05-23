#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<sstream>
#include<map>
#include<regex>

#define TESTVALUE 2
#define TESTSTRING "test st st deo deom"


using std::cin;
using std::cout;
using std::endl;

enum class mainMenuChoice{ manual = 1, file, test, exit};
enum class postParseMenuChoice { returnToSrc = 1, startAgain, exit };

std::string launchAll(bool isTest);
std::multimap<std::string, int> splitString(const std::vector<std::string>& lines, std::vector<std::string>& wordPartVec, int input);
std::string setSrcString(std::vector<std::string>& lines);
std::string findRepeats(std::vector<std::string> allChars, std::multimap<std::string, int>& wordParts, std::string s);
std::string launchMainMenu(std::vector<std::string>& lines, std::string& fileName);
std::string stringOutput(std::string input);
std::string stringInput();
bool launchPostParseMenu(std::string& parsedString, std::string srcString);
int checkInputInt();
int checkInputInt(int lowerLimit);
int enterPartSize();