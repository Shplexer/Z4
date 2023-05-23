#include "fileIO.h"
#include "functions.h"
#include <tuple>

std::tuple<std::string, bool> openFile() {
	std::ifstream fileIn;
	bool exitFlag = false;
	bool returnExit = false;
	fileNameChoice choice;
	cout << "Enter the name of a source file: ";
	std::string fileName = stringInput();
	do {
		exitFlag = false;
		fileName = fileNameCheck(fileName);
		fileIn.open(fileName);
		if (!fileIn.is_open()) {
			cout << endl << "The name of the file you have entered does not exist." << endl
				<< "1. Change the name of the file" << endl
				<< "2. Exit" << endl;
			choice = static_cast<fileNameChoice>(checkInputInt());
			switch (choice)
			{
			case fileNameChoice::change:
				cout << "Enter the name of a source file: ";
				fileName = fileNameCheck(stringInput());
				break;
			case fileNameChoice::exit:
				cout << "Exiting..." << endl;
				returnExit = false;
				exitFlag = true;
				break;
			default:
				cout << "ERR. Wrong input, try again" << endl;
				break;
			}
		}
		else {
			cout << "Your file is open!" << endl;
			//cout << fileName;
			exitFlag = true;
			returnExit = true;
		}
	} while (!exitFlag);
	fileIn.close();

	return std::make_tuple(fileName, returnExit);
}

//проверка корректности введенного названия файла
std::string fileNameCheck(std::string inputName) {
	std::string temp;
	const std::string errName = "<>:\"/\\|?*";
	const std::vector<std::string> errName2{ "CON", "PRN", "AUX", "NUL",
  "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9",
  "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9" };
	bool exitFlag = false;
	do {
		exitFlag = true;
		for (int i = 0; i < inputName.size(); i++) {
			for (int j = 0, k = 0; j < std::max(errName.size(), errName2.size()); j++, k++) {
				//cout << inputName[i] << " == " << errName[k] << " | " << inputName << " == " << errName2[j] << endl;
				if (inputName[i] == errName[k] || inputName == errName2[j]) {
					cout << "ERR. File name contains illegal characters. Try again." << endl;
					inputName = stringInput();
					exitFlag = false;
					break;
				}
				if (k >= errName.size() - 1)
					k = 0;
			}
			if (!exitFlag)
				break;
		}
	} while (!exitFlag);
	for (auto i = inputName.size() - 4; i < inputName.size(); i++) {
		temp = temp + inputName[i];
	}
	if (temp != ".txt") {
		inputName = inputName + ".txt";
	}

	return inputName;
}

//прием и разбитие ввода из файла на массив строк и сборка одной целой строки
std::string setSrcString(std::vector<std::string>& lines, std::string fileName) {
	std::string s;
	std::ifstream fileIn(fileName);
	do {
		std::string temp;
		std::getline(fileIn, temp);
		if (!temp.empty()) {
			//разбитие всего ввода на все строки 
			lines.push_back(temp);
			s += temp + '\n';
		}
		if (s.empty()) {
			cout << "ERR. An empty string has been entered. Try again: " << endl;
		}
		if (fileIn.eof())
			break;
	} while (true);
	//cout << s << endl;
	//cout << "==============" << endl;
	return s;
}

std::string saveFileCheck(std::string saveFileName) {
	std::ifstream checkStream;
	bool exitFlag;
	bool exitAllFlag;
	do {
		exitAllFlag = false;
		checkStream.open(saveFileName);
		std::error_code ec{};
		if (!checkStream.is_open()) {
			cout << "Please enter a path to the file you wish to save your project to: ";
			saveFileName = fileNameCheck(stringInput());
			//if (!std::filesystem::is_regular_file(saveFileName, ec)) {
			//	cout << "Invalid data." << endl;
			//	continue;
			//}
		}
		else {
			cout << "The name of an open file: " << saveFileName << endl <<
				"Whould you like to make a new one or save into this one?" << endl <<
				"1. Save to another file" << endl <<
				"2. Save here" << endl;
			do {
				exitFlag = true;
				errChoice choice = static_cast<errChoice>(checkInputInt());
				switch (choice)
				{
				case errChoice::change:
					cout << "Enter a path to the file: ";
					//saveFileName = stringInput();
					saveFileName = fileNameCheck(stringInput());
					break;
				case errChoice::keep:
					exitAllFlag = true;
					break;
				default:
					exitFlag = false;
					break;
				}
			} while (!exitFlag);
		}
		checkStream.close();
		checkStream.open(saveFileName);
		if (!checkStream.is_open() || exitAllFlag)
			break;
		checkStream.close();
	} while (true);
	return saveFileName;
}

void saveToFile(std::string saveFileName, std::string savingString) {
	bool exitFlag = true;
	do {
		cout << "Would you like to save the info?" << endl << "1.Yes" << endl << "2.No" << endl;
		saveChoice saveCh = static_cast<saveChoice>(checkInputInt());
		std::ofstream save;
		if (saveCh == saveChoice::save) {
			saveFileName = saveFileCheck(saveFileName);
			save.open(saveFileName, std::ios::out);
			save << savingString;
			save.close();
		}
		else if (saveCh != saveChoice::discard && saveCh != saveChoice::save) {
			cout << "ERR. Wrong input." << endl;
			saveCh = static_cast<saveChoice>(checkInputInt());
			if (saveCh == saveChoice::save || saveCh == saveChoice::discard)
				exitFlag = true;
		}
	} while (!exitFlag);
}