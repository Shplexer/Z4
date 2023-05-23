#include "tester.h"
#include "functions.h"
void launchTest() {
	std::string testString = launchAll(true);
	cout << "Substring replacer: ";
	const std::string controlString = "test {3,2} {3,2} deo {12,3}m";
	if (testString == controlString) {
		cout << "\033[36m" << "GOOD" << "\033[0m" << endl;
	}
	else {
		cout << "\033[31m" << "BAD" << "\033[0m" << endl;
		cout << "INPUT MATRIX" << endl;
		cout << testString << endl;
		cout << "CONTROL MATRIX" << endl;
		cout << controlString << endl;
	}
}