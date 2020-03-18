#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "ProjectIndexHooks.h"
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

// Forward Declarations
//void displayAssemblyName(Assembly & anItem);
//void displayAssemblyBday(Assembly & anItem);
template<class T> void printOrders(CTree<T>* pTree);
void displayPretty(Assembly & anItem);
void displayAssembly(Assembly & anItem);
void csvRowOutput(Assembly & anItem);

// our global file handles
ofstream csvSaveFh;  // file handle for the name ordered traversals.

int objectCount = 0;


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
				// Add  an empty record to make up for the CSV header...
				Assembly *newAssemblyPtr = new Assembly();
				assemblyByName[objectCount] = newAssemblyPtr;

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

			Assembly *newAssemblyPtr    = new Assembly(aName, aMethod, aNumContigs, aSizeBases, aN50kbp, aSIZEContent, aPercentUnknown, assemblyAttribute::NAME);
 			assemblyByName[objectCount] = newAssemblyPtr;

			//// Add to Linked List, Hash Table and BST
			addItem(newAssemblyPtr);

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

	// SAVE THE OUTPUT FILE...
	// Open the default CSV file name.
	csvSaveFh.open("faux_assemblies.csv");
	// prepend the CSV header row...
	csvSaveFh << csvFileHeader << endl;

	// Add all records to the CSV
	BST_NameOrder.inorderTraverse(csvRowOutput);

	// done lets close the file
	csvSaveFh.close();

	// Clean up allocated memory for Assembly Objects.
	// index is valid @ 1 not 0
	for (int index = 1; index < objectCount; ++index) {
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

void csvRowOutput(Assembly & anItem) {

	// Get the 7-tuple of GNome assembly data as typed values...
	std::string rGNAName           = anItem.getName();
	std::string rGNAType           = anItem.getType();
	int         rGNANumContigs     = anItem.getNumContigs();
	int         rGNASize           = anItem.getSize();
	int         rGNANumN50         = anItem.getN50();
	double      rGNAGCContent      = anItem.getGc();
	double      rGNAPercentUnknown = anItem.getUnknown();

	csvSaveFh << rGNAName << ',' << rGNAType << ',' << rGNANumContigs << ',' << rGNASize << ',' <<
		rGNANumN50 << ',' << rGNAGCContent << ',' << rGNAPercentUnknown << endl;
}


// EOF Lab05BST_main.cpp
