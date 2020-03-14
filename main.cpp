#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "ArrayTemplateClass.h"
#include "HandyUtils.h"
#include "BSTNode.h"
#include "BNTree.h"
#include "LinkedList.h"
#include "Node.h"
#include "Assembly.h"

using namespace std;

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
// Forward Declarations
//void displayPersonName(Person & anItem);
//void displayPersonBday(Person & anItem);
void displayPerson(Assembly & anItem);
int objectCount = 0;

BNTree<Assembly> assemblyTree;
LinkedList<Assembly> assemblyList;
/*
Assembly AssemblyByName01("contig-20.fa", "pilon+idba", 2637, 2182179, 306, 0.1573, 0.1964, NAME);
Assembly AssemblyByName02("contig-30.fa", "Spades", 2130, 1660411, 321, 0.5292, 0.3762, NAME);
Assembly AssemblyByName03("contig-40.fa", "MosaicFLye", 2309, 2463148, 265, 0.8489, 0.759, NAME);
*/

// Covering function for generic add.
bool addItem(Assembly * anItem, assemblyAttribute keyType){
	// 1. Simple validation
	// 2. Add to all 3 data structures

	// TREE ADD CODE
	if (keyType == NAME)
		assemblyTree.add(*anItem);

	// HASH ADD CODE tbd
	// Ex. BdayHash.add(*name)

	// LINKED LIST ADD CODE
	else if (keyType == N50)
		assemblyList.insert(*anItem);
	// 3. Report results
	return true;
}

bool searchItem(Assembly searchGenome) {
	bool retVal{false};
	if (assemblyTree.contains(searchGenome)) {
		cout << "\nHere is the Data item found in the BST" << endl;
		Assembly foundGenome = assemblyTree.find(searchGenome);
		cout << foundGenome;
		cout << "\nHere is the Data item found in the Linked List" << endl;
		foundGenome.setOrdering(N50);
		Assembly listGenome = assemblyList.findItem(foundGenome);
		cout << listGenome;
		retVal = true;
	}
	return retVal;
}

bool deleteItem(Assembly genome_to_delete){
	bool retVal{false};
	if (!assemblyTree.contains(genome_to_delete)) {
		cout << "\n Data item not found" << endl;
		retVal = false;
	}
	else {
		// ==> foundPersonRecord found by name, get the record.
		Assembly deleteGenome = assemblyTree.find(genome_to_delete);
		cout << " We are deleting this genome" << endl;
		cout << " " << deleteGenome;
		assemblyTree.remove(deleteGenome);
		cout << "\nHere is the Data item to be removed from the Linked List" << endl;
		deleteGenome.setOrdering(N50);
		Assembly listDeleteGenome = assemblyList.findItem(deleteGenome);
		cout << listDeleteGenome;
		cout << "\nGenome removed from the Linked List" << endl;
		retVal = true;
		}
/*
	// HASH DELETE CODE tbd
	// Ex. BdayHash.delete(*name)

	// MRU LINKED LIST DELETE CODE tbd

	// 3. Report results
	*/
	return retVal;
}


//****************************************************************************
// int main() - Main is our menu driven system for BST Tree based Person DB.
//				Our DB has a record type that allows you to sort record types
//				based on a persons name or birthday.
//				
// You can add, delete or find persons. You can also print the DB using tree
// options that display preorder, postorder, inorder and breadthfirst displays
// from the tree structure.
// 
// PSEUDOCODE: 
// 
// While not done
//	  select action from list of menu options for DB manipulation 
//	  executes action from method list 
//	  ask if done
//	  	  exit
//	  else continue
//	  
//***************************************************************************
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
	const int       MAX_PERSONS = 500;              // Maximum persons in our database
	//Array<Person *> aPersonByName(MAX_PERSONS);		// An array of type 'Person' using Array Template
//	Array<Person *> aPersonByBday(MAX_PERSONS);		// An array of type 'Person' using Array Template

	//   Print Header
	cout << "\n\nFinal Project\n"
		<< "Names : Joseph Saunders, Joshua Gomes, Minh Truong and Kavya Aswadhati\n"
		<< "Class : CIS22C61Y"
		<< endl << endl;

	// Working Variables for Menu Processing
	int choice = 0;
	bool loop = true;
	string name;

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
			if (count == 0) {
				getline(inFile, csvLine);
				count++;
			}

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

			//// Add to Linked List, Hash Table and BST
			addItem(assemblyByName[count], NAME);
			addItem(assemblyByContigs[count], NUM_CONTIGS);
			addItem(assemblyByN50[count], N50);
			addItem(assemblyBySize[count], SIZE);

			count++;
		}
		inFile.close();
	}
	else {
		cout << "   Error!!!" << endl;
	}


	//**********************************************************************//
	// Main menu Loop.														//
	// pre: Successfully seeded Binary Trees.								//
	// post: Updated Database per User Request.								// 
	//**********************************************************************//
	while (loop)
	{
		// Output User Menu
		cout << endl
			 << "   What operation would you like to carry out?" << endl;
		cout << "   1: Add a Node item" << endl;
		cout << "   2: Search for a Genome" << endl;
		cout << "   3: Delete a Genome" << endl;
		cout << "   4: Print data" << endl;
		cout << "   5: EXIT" << endl << endl;
		cout << "   Your Choice: ";
		// User response recorded
		cin >> choice;
		cin.ignore(32767, '\n');
		cout << endl << endl;

		// This switch will execute all actions from the menu
		switch (choice)
		{
			//************************************************************//
			// case 1 ADDS a node to both existing trees.				  //
			//************************************************************//
		case 1: // Add a Node to both Trees 
		{
			bool flag = true;
			string new_name;
			string new_bday;
			while (flag) {
				cout << " Enter the name data item for the new node.\n" << " ";

				/*
				Assembly * temp1 = &AssemblyByName01;
				Assembly * temp2 = &AssemblyByName02;
				Assembly * temp3 = &AssemblyByName03;
				addItem(temp1);
				addItem(temp2);
				addItem(temp3);
				getline(cin, new_name);
				cout << " Enter the birthday data item for the new node. "
					<< "Format is yyy-mm-dd.\n";
				getline(cin, new_bday);
				// Normalize the name and birthday...
				string tname = trim(new_name);
				string tbday = trim(new_bday);
				// dynamicallyy allocate & assign to array to keep track of memory
				Person * personByName = new Person(tname, tbday, NAME); 
				Person * personByBday = new Person(tname, tbday, BDAY); 
				// Add to all data structures, BST, Hash Table, Linked List.
				addItem(personByName, personByBday);
				// save for later deallocation
				aPersonByName[objectCount] = personByName;
				aPersonByBday[objectCount] = personByBday; 
				// inc object count...
				objectCount += 1;
				*/

				// Set flag using exit function
				flag = exitFunction();
			}
			break;
		}
		//************************************************************//
		// case 2 SEARCHES for a user specified node.				  //
		//************************************************************//
		case 2: // Search for a particular Genome by Name 
		{
			bool sflag = true;
			string name;
			while (sflag)
			{
				cout << " Enter the name of the genome assembly you would like to look for.\n";
				getline(cin, name);
				string tname = trim(name);
				Assembly search_genome(tname, "", 0, 0, 0, 0.0, 0.0, NAME);

				if (searchItem(search_genome)) {
					cout << "\nData item found" << endl;
				}
				else
					cout << "\nData item not found" << endl;
				// Set flag using exit function
				sflag = exitFunction();
			}
			break;
		}

		//************************************************************//
		// case 3 DELETES a genome from both all data structures. 	  //
		//************************************************************//
		case 3: // Delete a particular Node by Name
		{
			bool removingDataItems = true;
			string r_name;

			//Assembly * del3 = &AssemblyByName03;
			//if (deleteItem(AssemblyByName03)) // DELETE entrypoint!
			//	cout << "Deleting done" << endl;


			 //loop allows you to keep deleting items to your hearts content...
			while (removingDataItems) {
				cout << " Enter the name of the person item to be deleted.\n";
				cout << " ";
				getline(cin, r_name);
				string tname = trim(r_name);
				Assembly delete_genome(tname, "", 0, 0, 0, 0.0, 0.0, NAME);
				// deleteItem is the entry point to delete the item from ALL data structures.
				if (deleteItem(delete_genome)) // DELETE entrypoint!
				{
					cout << "Deleting done" << endl;
				}
				else 
				{
					cout << "Item not found or deleted." << endl;
				}
			// Set flag using exit function
			removingDataItems = exitFunction();
			}
		break;
		} // End switch

		//************************************************************//
		// case 4 PRINTS all node from both existing trees.			  //
		// Name Tree is printed in Preorder and Postorder modes.	  //
		// Birthday Tree is printed in Inorder and BreadthFirst mode. //
		//************************************************************//
		case 4:
		{
			/*

			nameOut << endl << "...!!!!...DISPLAYING NAME TREE...!!!!..." << endl;
			nameOut << endl << endl << "Nametree in PREORDER" << endl;
			nameOut << string(80, '=') << endl;
			nameOut << left << setw(60) << "NAME" << right << setw(20) << "BIRTHDAY" << endl;
			nameOut << string(80, '=') << endl;
			nameTree.preorderTraverse(displayPersonName);
			nameOut << endl << endl << "Nametree in POSTORDER" << endl;
			nameOut << string(80, '=') << endl;
			nameOut << left << setw(60) << "NAME" << right << setw(20) << "BIRTHDAY" << endl;
			nameOut << string(80, '=') << endl;
			nameTree.postorderTraverse(displayPersonName);
			bdayOut << endl << endl << "...!!!!...DISPLAYING BIRTHDAY TREE...!!!!..." << endl;
			bdayOut << endl << endl << "Birthday Tree in INORDER" << endl;
			bdayOut << string(80, '=') << endl;
			bdayOut << left << setw(60) << "NAME" << right << setw(20) << "BIRTHDAY" << endl;
			bdayOut << string(80, '=') << endl;
			bdayTree.inorderTraverse(displayPersonBday);
			bdayOut << endl << endl << "Birthday Tree in BREADTHFIRST ORDER" << endl;
			bdayOut << string(80, '=') << endl;
			bdayOut << left << setw(60) << "NAME" << right << setw(20) << "BIRTHDAY" << endl;
			bdayOut << string(80, '=') << endl;
			bdayTree.breadthfirstTraverse(displayPersonBday);
			*/
			assemblyList.print();
			cout << endl << endl << "~~~~~~~~~~~~PRINTING BY N50~~~~~~~~COL 4~~~~~" << endl;
			//assemblyByN50.print();
		}
		break;

		//************************************************************//
		// case 5 PRINTS all node from both existing trees and		  //
		//		 exits the menu.									  //
		// Name Tree is printed in Preorder and Postorder modes.	  //
		// Birthday Tree is printed in Inorder and BreadthFirst mode. //
		//************************************************************//
		case 5:
		{
			/*
			nameOut << endl << "...!!!!...DISPLAYING NAME TREE...!!!!..." << endl;
			nameOut << endl << endl << "Nametree in PREORDER" << endl;
			nameOut << string(80, '=') << endl;
			nameOut << left << setw(60) << "NAME" << right << setw(20) << "BIRTHDAY" << endl;
			nameOut << string(80, '=') << endl;
			nameTree.preorderTraverse(displayPersonName);
			nameOut << endl << endl << "Nametree in POSTORDER" << endl;
			nameOut << string(80, '=') << endl;
			nameOut << left << setw(60) << "NAME" << right << setw(20) << "BIRTHDAY" << endl;
			nameOut << string(80, '=') << endl;
			nameTree.postorderTraverse(displayPersonName);
			bdayOut << endl << endl << "...!!!!...DISPLAYING BIRTHDAY TREE...!!!!..." << endl;
			bdayOut << endl << endl << "Birthday Tree in INORDER" << endl;
			bdayOut << string(80, '=') << endl;
			bdayOut << left << setw(60) << "NAME" << right << setw(20) << "BIRTHDAY" << endl;
			bdayOut << string(80, '=') << endl;
			bdayTree.inorderTraverse(displayPersonBday);
			bdayOut << endl << endl << "Birthday Tree in BREADTHFIRST ORDER" << endl;
			bdayOut << string(80, '=') << endl;
			bdayOut << left << setw(60) << "NAME" << right << setw(20) << "BIRTHDAY" << endl;
			bdayOut << string(80, '=') << endl;
			bdayTree.breadthfirstTraverse(displayPersonBday);
			cout << endl;
			*/
			cout << endl << endl << "~~~~~~~~~~~~PRINTING BY N50~~~~~~~~COL 4~~~~~" << endl;
			assemblyList.print();
			cout << endl << endl << "~~~~~~~~~~~~PRINTING BY Name~~~~~~~~COL 1~~~~~" << endl;
			assemblyTree.inorderTraverse(displayPerson);
			cout << endl << endl << "~~~~~~~~~~~~EXITING PROGRAM~~~~~~~~~~~~~~~~" << endl;
			loop = false;
			break;
		} // End Case 6
		default:
			cout << "   Please enter a valid choice between"
				<< "   1-5" << endl;
		} // End Switch for Menu
	} // End While loop for Menu

	// size variable is same for both arrays because of parallel arrays.
	//int personCount = aPersonByName.GetLength();

	// Clean up allocated memory for Person Objects.
	/*
	for (int index = 0; index < objectCount; ++index) {
		delete aPersonByName[index];
		delete aPersonByBday[index];
	}
	*/

	return 0;
}
/*
void displayPersonName(Person & anItem)
{
	nameOut << anItem << endl;
}

void displayPersonBday(Person & anItem)
{
	bdayOut << anItem << endl;
}
*/

void displayPerson(Assembly & anItem)
{
	cout << anItem << endl;
}

// EOF Lab05BST_main.cpp
