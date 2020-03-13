#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "ArrayTemplateClass.h"
#include "Assembly.h"
using namespace std;

// Skips the Byte Order Mark (BOM) that defines UTF-8 in some text files.
// Ref: https://stackoverflow.com/questions/10417613/c-reading-from-file-puts-three-weird-characters
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

int main()
{
	const int ASSEMBLY_NAME{ 0 };
	const int ASSEMBLY_METHOD{ 1 };
	const int NUMBER_CONTIGS{ 2 };
	const int SIZE_bases{ 3 };
	const int N50_kbp{ 4 };
	const int GC_CONTENT{ 5 };
	const int PERCENT_UNKNOWN{ 6 };

	const int       MAX_ASSEMBLIES = 500;              // Maximum persons in our database
	Array<Assembly *> assemblyByName(MAX_ASSEMBLIES);		// An array of type 'Person' using Array Template
	Array<Assembly *> assemblyByContigs(MAX_ASSEMBLIES);		// An array of type 'Person' using Array Template
	Array<Assembly *> assemblyByN50(MAX_ASSEMBLIES);
	Array<Assembly *> assemblyBySize(MAX_ASSEMBLIES);

	// basic string trim
	string thello{ " hello " };
	cout << "[" << celltrim(thello) << "]" << endl;

	// first the basic csv row split....
	std::string str = "contig-20.fa,pilon+idba,2637,2182179,306,0.1573,0.1964";
	Array<string> row(10);

	rowsplit(str, row, ',');

	for (int ndx = 0; ndx < 7; ndx++)
		std::cout << row[ndx] << std::endl;


	// lets read and dump
	// our global file handles
	ofstream namefh;  // file handle for the name ordered traversals.
	ofstream bdayfh;  // file handle for the birthday ordered traversals.

	std::string csvLine{ "" };
	int         number_of_lines{ 0 };
	int         count{ 0 };

	ifstream inFile("faux_assemblies.csv");
	SkipBOM(inFile);

	// This if block creates Person objects and seeds them into the array.
	if (inFile) {
		cin.clear();
		while (getline(inFile, csvLine)) {
			++number_of_lines;
		}

		inFile.clear();
		inFile.seekg(0, ios::beg);

		SkipBOM(inFile);
		while (!inFile.eof() && count < number_of_lines) {
			// skip the csv header
			if (count == 0)
				getline(inFile, csvLine);

			const int GNomeCSVCols = 7;              // Maximum persons in our database

			Array<string> aRow(GNomeCSVCols);
			// Get the name and birthday...
			getline(inFile, csvLine);
			cout << "Processing this line : [" << csvLine << "]" << endl;

			// ok here we go...
			rowsplit(csvLine, aRow, ',');

			string aName(aRow[ASSEMBLY_NAME]);
			string aMethod(aRow[ASSEMBLY_METHOD]);
			int    aNumContigs(stoi(aRow[NUMBER_CONTIGS]));
			int    aSizeBases(stoi(aRow[SIZE_bases]));
			int    aN50kbp(stoi(aRow[N50_kbp]));
			double aGCContent(stod(aRow[GC_CONTENT]));
			double aPercentUnknown(stod(aRow[PERCENT_UNKNOWN]));

			assemblyByName[count]    = new Assembly(aName, aMethod, aNumContigs, aSizeBases, aN50kbp, aGCContent, aPercentUnknown, NAME);
			assemblyByContigs[count] = new Assembly(aName, aMethod, aNumContigs, aSizeBases, aN50kbp, aGCContent, aPercentUnknown, NUM_CONTIGS);
			assemblyByN50[count]     = new Assembly(aName, aMethod, aNumContigs, aSizeBases, aN50kbp, aGCContent, aPercentUnknown, N50);
			assemblyBySize[count]    = new Assembly(aName, aMethod, aNumContigs, aSizeBases, aN50kbp, aGCContent, aPercentUnknown, SIZE);

			//getline(inFile, bday);
			//// Normalize the name and birthday...
			//string tname = trim(name);
			//string tbday = trim(bday);
			//// Add the person to the name and birthday arrays...
			//aPersonByName[count] = new Person(tname, tbday, NAME);
			//aPersonByBday[count] = new Person(tname, tbday, BDAY);
			//// Add to person to name and birthday BST's
			//nameTree.add(*aPersonByName[count]);
			//bdayTree.add(*aPersonByBday[count]);

			count++;
		}
		inFile.close();
	}
	else {
		cout << "   Error!!!" << endl;
	}

	return 0;
}