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

//
void SkipBOM(std::ifstream &in)
{
	char test[3] = { 0 };
	in.read(test, 3);
	if ((unsigned char)test[0] == 0xEF &&
		(unsigned char)test[1] == 0xBB &&
		(unsigned char)test[2] == 0xBF)
	{
		return;
	}
	in.seekg(0);
}

// pre     : a string that has spaces in from of or after it.  
//           EX: "hello " -OR- " hello" -OR- " hello "...
// post    : Our array has a string based CSV row that can now be converted
//           to assemblies.
// returns : By reference our row array is updated.
string celltrim(const string& str)
{
	size_t first = str.find_first_not_of(' ');
	if (string::npos == first)
	{
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

// pre     : validated 7 item string list with 6 comma (',') delimiters
//           EX: "contig-20.fa,pilon+idba,2637,2182179,306,0.1573,0.1964"
// post    : Our array has a string based CSV row that can now be converted
//           to assemblies.
// returns : By reference our row array is updated.
void rowsplit(const std::string& str, Array<string>& row, char delim = ',')
{
	// string indexes for .find
	std::size_t prev{ 0 };
	std::size_t curr{ str.find(delim) };

	// our value index
	int ndx{ 0 };
	// while not end of string
	while (curr != std::string::npos) {
		std::string tcell = celltrim(str.substr(prev, curr - prev));
		row[ndx] = tcell;
		prev = curr + 1;
		curr = str.find(delim, prev);
		ndx++;
	}
	row[ndx] = celltrim(str.substr(prev, curr - prev));
}
