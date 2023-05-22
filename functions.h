#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<sstream>
#include<map>

using std::cin;
using std::cout;
using std::endl;

std::string enterSrcString(std::vector<std::string>& lines);
std::multimap<std::string, int> splitString(const std::vector<std::string>& lines, std::vector<std::string>& wordPartVec, int input);