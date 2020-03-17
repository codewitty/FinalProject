#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Node.h"
#include "LinkedList.h"
#include "BNTree.h"
#include "BSTNode.h"


using namespace std;

// Forward Declarations
int ValidateTempInput(int tempInt);
void DeleteEmptyLines(string &Path);
string trim(string s);
string ltrim(string s);
string rtrim(string s);
const string WHITESPACE = " \n\r\t\f\v";
const int ARRAY_SIZE{ 20 };
bool exitFunction(int);

int ValidateTempInput(int tempInt) {
	while (cin.fail() || (tempInt < 0 && tempInt > 2147483647)) {
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "Please enter a valid value between 0 to 2147483647" << endl;
		cin >> tempInt;
	}
	return tempInt;
}

void DeleteEmptyLines(string &Path)
{
	ifstream inF(Path);
	string line, text;
	while (std::getline(inF, line))
		if (!(line.empty() || line.find_first_not_of(' ') == std::string::npos))
			text += line + "\n";
	inF.close();
	ofstream out(Path);
	out << text;
}


string ltrim(string s)
{
	size_t start = s.find_first_not_of(WHITESPACE);
	return (start == string::npos) ? "" : s.substr(start);
}

string rtrim(string s)
{
	size_t end = s.find_last_not_of(WHITESPACE);
	return (end == string::npos) ? "" : s.substr(0, end + 1);
}

string trim(string s)
{
	return rtrim(ltrim(s));
}


bool exitFunction(int choice) {
	bool retVal;
	char rem_choice;
	if (choice == 1) {
		cout << "\nWould you like to add another Genome Assembly? \n"
			 << "Enter Y for \"Yes\" or any other key for \"No\"\n";
	}
	else if (choice == 2) {
		cout << "\nWould you like to remove another Genome Assembly? \n"
			 << "Enter Y for \"Yes\" or any other key for \"No\"\n";
	}
	else if (choice == 3) {
		cout << "\nWould you like to search for another Genome Assembly? \n"
			 << "Enter Y for \"Yes\" or any other key for \"No\"\n";
	}
	cin >> rem_choice;
	cin.ignore(32767, '\n');
	if (cin.fail()) {
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "\nExiting to main menu" << endl;
		retVal = false;
	}
	if (rem_choice == 'Y' || rem_choice == 'y') {
		retVal = true;
	}
	else {
		cout << "\nExiting to main menu" << endl;
		retVal = false;
	}
	return retVal;
}
