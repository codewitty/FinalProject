#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "ArrayTemplateClass.h"
#include "HandyUtils.h"
#include "LinkedList.h"
#include "Assembly.h"
#include "BSTNode.h"
#include "BNTree.h"
#include "2-3BTreeError.h"
#include "2-3BTreeNode.h"
#include "2-3BTree.h"
#include "Node.h"
#include "hash.h"


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
//void displayAssemblyName(Assembly & anItem);
//void displayAssemblyBday(Assembly & anItem);
template<class T> void printOrders(CTree<T>* pTree);
void displayPretty(Assembly & anItem);
void displayAssembly(Assembly & anItem);
int objectCount = 0;

BNTree<Assembly> assemblyTree;
//BNTree<Assembly> assemblyTreeName;
LinkedList<Assembly> assemblyList(DESCENDING);
CTree<Assembly> assemblyCTree;
HashTable table;

// Covering function for generic add.
bool addItem(Assembly * anItem){
	// 1. Simple validation
	// 2. Add to all 3 data structures

	// HASH ADD CODE tbd
	table.add(*anItem);

	// TREE ADD CODE
//	assemblyTreeName.add(*anItem);
	anItem->setOrdering(assemblyAttribute::SIZE);
	assemblyTree.add(*anItem);
	// 2-3 tree...
	anItem->setOrdering(assemblyAttribute::NUM_CONTIGS);
	assemblyCTree.insert(anItem);


	
	// LINKED LIST ADD CODE
	anItem->setOrdering(assemblyAttribute::N50);
	assemblyList.insert(*anItem);
	// 3. Report results
	return true;
}

bool searchItem(Assembly searchGenome) {
	bool retVal{false};
	if (table.search(searchGenome)){
		Assembly foundGenome = table.getObject(searchGenome);
		cout << string(138, '=');
		cout << "\nData item found in the Hash Table  : ";
		table.printObj(foundGenome);
		cout << "\nData item found in the BST         : ";
		// Change key for BST
		foundGenome.setOrdering(assemblyAttribute::SIZE);
		Assembly treeGenome = assemblyTree.find(foundGenome);
		cout << treeGenome;
		cout << "\nData item found in the Linked List : ";
		// Change key for Linked List
		foundGenome.setOrdering(assemblyAttribute::N50);
		Assembly listGenome = assemblyList.findItem(foundGenome);
		cout << listGenome;
		cout << "\nData item found in the 2-3 Tree    : ";
		// Change key for 2-3 Tree
		foundGenome.setOrdering(assemblyAttribute::NUM_CONTIGS);
		const Assembly * cTreeGenome = assemblyCTree.find(&foundGenome);
		cout << *cTreeGenome << endl;
		cout << string(138, '=') << endl;
		retVal = true;
	}
	else
		cout << "!!!!!! ASSEMBLY GENOME NOT FOUND !!!!!!!";
	return retVal;
}

bool deleteItem(Assembly genome_to_delete){
	bool retVal{false};
	if (!table.search(genome_to_delete)) {
		cout << "\n!!!!!! ASSEMBLY GENOME NOT FOUND !!!!!!!";
		retVal = false;
	}
	else {
		// ==> foundAssemblyRecord found by name, get the record.
		Assembly deleteGenome = table.getObject(genome_to_delete);
		// Remove from Hash Table
		cout << string(141, '=');
		cout << "\nData item removed from the Hash Table : ";
		table.printObj(deleteGenome);
		table.remove(deleteGenome);
		// Remove from BST
		deleteGenome.setOrdering(assemblyAttribute::SIZE);
		cout << "\nData item removed from the BST        : ";
		Assembly dTreeGenome = assemblyTree.find(deleteGenome);
		cout << dTreeGenome;
		assemblyTree.remove(deleteGenome);
		// Remove from 2-3 Tree 
		deleteGenome.setOrdering(assemblyAttribute::NUM_CONTIGS);
		cout << "\nData item removed from the 2-3 Tree   : ";
		const Assembly * dcTreeGenome = assemblyCTree.find(&deleteGenome);
		cout << *dcTreeGenome;
		assemblyCTree.deleteItem(&deleteGenome);
		cout << "\nData item removed from the Linked List: ";
		deleteGenome.setOrdering(assemblyAttribute::N50);
		Assembly listDeleteGenome = assemblyList.findItem(deleteGenome);
		cout << listDeleteGenome;
		assemblyList.remove(listDeleteGenome);
		cout << endl << string(141, '=') << endl;
		retVal = true;
		}
	// 3. Report results
	return retVal;
}


//****************************************************************************
// int main() - Main is our menu driven system for BST Tree based Assembly DB.
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
	const int SIZE_CONTENT{ 5 };
	const int PERCENT_UNKNOWN{ 6 };

	const int       MAX_ASSEMBLIES = 500;              // Maximum persons in our database
	Array<Assembly *> assemblyByName(MAX_ASSEMBLIES);		// An array of type 'Assembly' using Array Template

	//   Print Header
	cout << "\n\nFinal Project\n"
		<< "Names : Joseph Saunders, Joshua Gomes, Minh Truong and Kavya Aswadhati\n"
		<< "Class : CIS22C61Y"
		<< endl << endl;

	// Working Variables for Menu Processing
	int choice = 0;
	bool loop = true;

	// line by line processing variable...
	std::string csvLine{ "" };
	// existing CSV header...
	std::string csvFileHeader{ "" };
	int         number_of_lines{ 0 };
	int         objectCount{ 0 };

	// default CSV file name
	ifstream inFile("faux_assemblies.csv");
	SkipBOM(inFile);

	// This if block creates Assembly objects and seeds them into the array.
	if (inFile) {
		cin.clear();
		while (getline(inFile, csvLine)) {
			++number_of_lines;
		}

		inFile.clear();
		inFile.seekg(0, ios::beg);

		SkipBOM(inFile);
		while (!inFile.eof() && objectCount < number_of_lines) {
			// skip the csv header in processing...
			if (objectCount == 0) {
				// ...but save it off for reuse when saving...
				getline(inFile, csvFileHeader);
				objectCount++;
			}

			const int GNomeCSVCols = 7;     // Maximum data fields in our database

			Array<string> aRow(GNomeCSVCols);
			// Get the name and birthday...
			getline(inFile, csvLine);

			// ok here we go...
			rowsplit(csvLine, aRow, ',');

			string aName(aRow[ASSEMBLY_NAME]);
			string aMethod(aRow[ASSEMBLY_METHOD]);
			int    aNumContigs(stoi(aRow[NUMBER_CONTIGS]));
			int    aSizeBases(stoi(aRow[SIZE_bases]));
			int    aN50kbp(stoi(aRow[N50_kbp]));
			double aSIZEContent(stod(aRow[SIZE_CONTENT]));
			double aPercentUnknown(stod(aRow[PERCENT_UNKNOWN]));

			assemblyByName[objectCount]    = new Assembly(aName, aMethod, aNumContigs, aSizeBases, aN50kbp, aSIZEContent, aPercentUnknown, assemblyAttribute::NAME);

			//// Add to Linked List, Hash Table and BST
			addItem(assemblyByName[objectCount]);

			objectCount++;
		}
		inFile.close();
	}
	else {
		cout << "   Error!!!" << endl;
	}


	//**********************************************************************//
	// Main menu Loop.														//
	// pre: Successfully seeded all data structures.						//
	// post: Updated Database per User Request.								// 
	//**********************************************************************//
	while (loop)
	{
		// Output User Menu
		cout << endl
			 << "   What operation would you like to carry out?" << endl;
		cout << "   1: Add a Genome Assembly" << endl;
		cout << "   2: Delete a Genome Assembly" << endl;
		cout << "   3: Search for a Genome Assembly by Name" << endl;
		cout << "   4: List Genome Assemblies in Hash Table Sequence" << endl;
		cout << "   5: List Genome Assemblies in Sorted Key Sequence" << endl;
		cout << "   6: Print indented Tree" << endl; 
		cout << "   7: Display Efficiency Statistics" << endl; 
		cout << "   8: Display Genome Assemblies in 2-3 Binary Tree Format" << endl; 
		cout << "   9: EXIT" << endl << endl;
		cout << "   Your Choice: ";
		// User response recorded
		cin >> choice;
		cin.ignore(32767, '\n');
		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "\n   !!!INVALID INPUT DETECTED!!!!Exiting Program!!" << endl;
			loop = false;
		}

		// This switch will execute all actions from the menu
		switch (choice)
		{
			//************************************************************//
			// case 1 ADDS a node to both existing trees.				  //
			//************************************************************//
		case 1: // Add a Node to both Trees 
		{
			bool flag = true;
			string new_genome;
			string new_method;
			string Name;
			string Method;
			int tempInt;
			int    NumContigs;
			int    SizeBases;
			int    N50kbp;
			double tempDouble;
			double SIZEContent;
			double PercentUnknown;
			while (flag) {
				cout << "Enter the name for the new Genome. " << endl;
				getline(cin, new_genome);
				Name = trim(new_genome);
				cout << "Enter the method for the new Genome. " << endl;
				getline(cin, new_method);
				Method = trim(new_method);
				cout << "Enter the number of contigs for the new Genome. " << endl;
				cin >> tempInt;
				NumContigs = ValidateTempInput(tempInt);
				cout << "Enter the size of bases for the new Genome. " << endl;
				cin >> tempInt;
				SizeBases = ValidateTempInput(tempInt);
				cout << "Enter the N50 for the new Genome. " << endl;
				cin >> tempInt;
				N50kbp = ValidateTempInput(tempInt);
				cout << "Enter the SIZE Content for the new Genome. " << endl;
				cin >> SIZEContent;
				cout << "Enter the percent unknown for the new Genome. " << endl;
				cin >> PercentUnknown;
				assemblyByName[objectCount]    = new Assembly(Name, Method, NumContigs, SizeBases, N50kbp, SIZEContent, PercentUnknown, assemblyAttribute::NAME);
				//// Add to Linked List, Hash Table and BST
				addItem(assemblyByName[objectCount]);

				objectCount++;

				/*
					 < " A genome assembly consists of the following data items "
					 << " A name, a type, the number of contigs( whole number only), 
					 << " size( whole number only), N50 (whole number only), "
					 << " gc, number of unknown). "
					 << "\n  Please enter all data in one line separated by spaces."
					 << endl;
				Assembly * temp1 = &AssemblyByName01;
				Assembly * temp2 = &AssemblyByName02;
				Assembly * temp3 = &AssemblyByName03;
				addItem(temp1);
				addItem(temp2);
				addItem(temp3);
				
				// dynamicallyy allocate & assign to array to keep track of memory
				Assembly * personByName = new Assembly(tname, tbday, NAME); 
				Assembly * personByBday = new Assembly(tname, tbday, BDAY); 
				// Add to all data structures, BST, Hash Table, Linked List.
				addItem(personByName, personByBday);
				// save for later deallocation
				aAssemblyByName[objectCount] = personByName;
				aAssemblyByBday[objectCount] = personByBday; 
				// inc object objectCount...
				objectCount += 1;

				*/
				// Set flag using exit function
				int num = 1;
				flag = exitFunction(num);
			}
			break;
		}

		//************************************************************//
		// case 2 DELETES a genome from both all data structures. 	  //
		//************************************************************//
		case 2: // Delete a particular Node by Name
		{
			bool removingDataItems = true;
			string r_name;

			 //loop allows you to keep deleting items to your hearts content...
			while (removingDataItems) {
				cout << "Enter the name of the Genome Assembly to be deleted.\n";
				getline(cin, r_name);
				string tname = trim(r_name);
				Assembly delete_genome(tname, "", 0, 0, 0, 0.0, 0.0, assemblyAttribute::NAME);
				// deleteItem is the entry point to delete the item from ALL data structures.
				deleteItem(delete_genome); // DELETE entrypoint!
			// Set flag using exit function
			int num = 2;
			removingDataItems = exitFunction(num);
			}
		break;
		} // End switch

		//************************************************************//
		// case 3 SEARCHES for a user specified node.				  //
		//************************************************************//
		case 3: // Search for a particular Genome by Name 
		{
			bool sflag = true;
			string name;
			while (sflag)
			{
				cout << "Enter the name of the genome assembly you would like to look for.\n";
				getline(cin, name);
				string tname = trim(name);
				Assembly search_genome(tname, "", 0, 0, 0, 0.0, 0.0, assemblyAttribute::NAME);
				// Search for Genome Assembly in all data structures
				searchItem(search_genome);
				// Set flag using exit function
				int num = 3;
				sflag = exitFunction(num);
			}
			break;
		}

		//************************************************************//
		// case 4 PRINTS data in hash table sequence 
		//************************************************************//
		case 4:
		{
			cout << endl << string(40, '~') << "PRINTING BY HASH TABLE SEQUENCE~~~~~~~~~~~~~" << string (40, '~') << endl;
			cout << string(110, '=') << endl;
			cout << setw(30) << left << "GENOME NAME" << setw(20) << "GENOME TYPE" << setw(15) << "NUM_CONTIGS" 
				<< setw(10) << "Size" << setw(10) << "n50" << setw(10) << "GC Count" << setw(10) << "Percent UNKNOWN" << endl;
			cout << string(110, '=') << endl;
			table.printTable();
			break;
		}

		//************************************************************//
		// case 5 PRINTS data in sorted key sequence using 2 data	  // 
		//	structures, Linked List and BST.						  //
		// 2-3 Tree is printed by the Num_Contigs key.				  //
		// BST is printed by the Size key.					   		  //
		// Linked List is printed by the N50 key.					  //
		//************************************************************//
		case 5:
		{
			cout << endl << string(39, '~') << "PRINTING 2-3 Tree BY NUM_CONTIGS" << string(39, '~') << endl;
			cout << string(110, '=') << endl;
			cout << setw(30) << left << "GENOME NAME" << setw(20) << "GENOME TYPE" << setw(15) << "NUM_CONTIGS" 
				<< setw(10) << "Size" << setw(10) << "n50" << setw(10) << "GC Count" << setw(10) << "Percent UNKNOWN" << endl;
			cout << string(110, '=') << endl;
			int num = 0;
			assemblyCTree.print(inorder, &num);
			cout << endl << string(45, '~') << "PRINTING BST BY SIZE" << string(45, '~') << endl;
			cout << string(110, '=') << endl;
			cout << setw(30) << left << "GENOME NAME" << setw(20) << "GENOME TYPE" << setw(15) << "NUM_CONTIGS" 
				<< setw(10) << "Size" << setw(10) << "n50" << setw(10) << "GC Count" << setw(10) << "Percent UNKNOWN" << endl;
			cout << string(110, '=') << endl;
			assemblyTree.inorderTraverse(displayAssembly);
			cout << endl << string(41, '~') << "PRINTING LINKED LIST BY N50" << string(41,'~')  << endl;
			cout << string(110, '=') << endl;
			cout << setw(30) << left << "GENOME NAME" << setw(20) << "GENOME TYPE" << setw(15) << "NUM_CONTIGS" 
				<< setw(10) << "Size" << setw(10) << "n50" << setw(10) << "GC Count" << setw(10) << "Percent UNKNOWN" << endl;
			cout << string(110, '=') << endl;
			assemblyList.print();
		break;
		}

		//************************************************************//
		// case 6 PRINTS the indented tree 
		//************************************************************//
		case 6:
		{
			//printOrders(&assemblyCTree);
			cout << string(110, '=');
			cout << endl << "~~~~~~~~~~~~PRINTING INDENTED BST~~~~~~~~~~~~~" << endl;
			cout << string(110, '=') << endl;
			assemblyTree.prettyPrint(displayPretty);
			cout << endl << string(110, '=') << endl;
			break;
		}

		//************************************************************//
		// case 7 PRINTS all efficiency statistics.					  //
		//************************************************************//
		case 7:
		{
			cout << string(110, '=') << endl;
			cout << string(20, '~') << "EFFICIENCY" << string(20,'~') << endl;
			cout << string(110, '=') << endl;
			table.printStats();
			cout << string(110, '=') << endl;
			break;
		}

		//************************************************************//
		// case 8 PRINTS all node from both existing trees.			  //
		// Name Tree is printed in Preorder and Postorder modes.	  //
		// Birthday Tree is printed in Inorder and BreadthFirst mode. //
		//************************************************************//
		case 8:
		{
			cout << endl << endl << "~~~~~~~~~~~~Special Menu Option~~~~~~~~~~~~~" << endl;
			break;
		}

		//************************************************************//
		// case 9 Exits the menu and QUITS the program.				  //
		//************************************************************//
		case 9:
		{
			cout << endl << "~~~~~~~~~~~~EXITING PROGRAM~~~~~~~~~~~~~~~~" << endl << endl << endl;
			loop = false;
			break;
		} // End Case 6
		default:
			cout << "   Please enter a valid choice between"
				<< "   1-8" << endl;
		} // End Switch for Menu
	} // End While loop for Menu

/*
	// SAVE THE OUTPUT FILE...
	// default CSV file name
	ofstream outFile("faux_assemblies.csv");
	// 
	for (int index = 0; index < objectCount; ++index) {
		// Get the 7-tuple of GNome assembly data as typed values...
		std::string rGNAName           = assemblyByName[index]->getName();
		std::string rGNAType           = assemblyByName[index]->getType();
		int         rGNANumContigs     = assemblyByName[index]->getNumContigs();
		int         rGNASize           = assemblyByName[index]->getNumContigs();
		int         rGNANumN50         = assemblyByName[index]->getN50();
		double      rGNAGCContent      = assemblyByName[index]->getGc();
		double      rGNAPercentUnknown = assemblyByName[index]->getGc();

		outFile << rGNAName << ',' << rGNAType << ',' << rGNANumContigs << ',' << rGNASize << ',' <<
			rGNANumN50 << ',' << rGNAGCContent << ',' << rGNAPercentUnknown << endl;
	}
	// done lets close the file
	outFile.close();
	*/

	// Clean up allocated memory for Assembly Objects.
	for (int index = 0; index < objectCount; ++index) {
		delete assemblyByName[index];
	}

	return 0;
}

void displayAssembly(Assembly & anItem)
{
	cout << anItem << endl;
}

void displayPretty(Assembly & anItem) {
	anItem.printItemKey();
}

template<class T>
void printOrders(CTree<T>* pTree)
{
	int iItemCnt = 0;
	pTree->print(inorder, &iItemCnt);
	std::cout << "**inorder[" << iItemCnt << "]" << std::endl << std::endl;
}

// EOF Lab05BST_main.cpp
