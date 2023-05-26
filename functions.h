#pragma once

#include<string>
#include<vector>
#include<iostream>
#include<sstream>
#include<regex>

#define TESTVALUE 2
#define TESTSTRING "test st st deo deom"


using std::cin;
using std::cout;
using std::endl;

enum class mainMenuChoice{ manual = 1, file, test, exit};
enum class postParseMenuChoice { returnToSrc = 1, startAgain, exit };
enum class decryptChoice {Yes = 1, No};

std::string launchAll(bool isTest);
std::string decrypt(std::string encryptedString);
std::vector<std::string> splitString(const std::string s, std::vector<std::string> wordPartVec, int input);
std::string setInitialString();
std::string findRepeats(std::vector<std::string> allChars, std::string s);
std::string launchMainMenu(std::string& fileName);
std::string stringOutput(std::string input);
std::string stringInput();
bool launchPostParseMenu(std::string& parsedString, std::string initialString);
int checkInputInt();
int checkInputInt(int lowerLimit);
int enterPartSize();