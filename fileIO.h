#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

enum class fileNameChoice { change = 1, exit };
enum class errChoice { change = 1, keep };
enum class saveChoice { save = 1, discard };

std::string openFile();
std::string fileNameCheck(std::string inputName);
std::string setInitialString(std::string fileName);

std::string saveFileCheck(std::string saveFileName);
void saveToFile(std::string saveFileName, std::string saveString);