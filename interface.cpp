#include"interface.h"

void giveGreeting() {
	cout << "===================================================================================================================" << endl;
	cout << "Welcome!" << endl << "Made by Orekhov Daniil, group 423, task #4, variant 15" << endl;
	cout << "===================================================================================================================" << endl;
	cout << "Task: Develop a program that finds al repeating substrings in a given string that are more or equal to the input number" << endl <<
		"Replace all repeating substrings, except for the first one with a special signature:" << endl <<
		"{ index of the first symbol of the original substring, the length of a substring }" << endl;
}

void giveMainMenu() {
	cout << "===================================================================================================================" << endl;
	cout << "1. Manual input" << endl
		<< "2. File input" << endl
		<< "3. Test" << endl
		<< "4. Exit" << endl;
	cout << "===================================================================================================================" << endl;
}

void givePostParseMenu() {
	cout << "===================================================================================================================" << endl;
	cout << "1. Use the same input string again" << endl
		<< "2. Start again" << endl
		<< "3. Exit" << endl;
	cout << "===================================================================================================================" << endl;
}

void giveResult(std::string srcString, std::string parsedString) {
	cout << "===================================================================================================================" << endl;
	cout << "Input string: " << endl;
	cout << "===================================================================================================================" << endl;
	cout << srcString << endl;
	cout << "===================================================================================================================" << endl;
	cout << "Parsed string: " << endl;
	cout << "===================================================================================================================" << endl;
	cout << parsedString << endl;
	cout << "===================================================================================================================" << endl;
}