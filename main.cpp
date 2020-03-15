#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "ArrayTemplateClass.h"
#include "HandyUtils.h"
#include "BSTNode.h"
#include "BNTree.h"
#include "2-3BTreeError.h"
#include "2-3BTreeNode.h"
#include "2-3BTree.h"
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
//void displayAssemblyName(Assembly & anItem);
//void displayAssemblyBday(Assembly & anItem);
template<class T> void printOrders(CTree<T>* pTree);
void displayAssembly(Assembly & anItem);
int objectCount = 0;

BNTree<Assembly> assemblyTree;
BNTree<Assembly> assemblyTreeName;
LinkedList<Assembly> assemblyList;
CTree<Assembly> assemblyCTree;

// Covering function for generic add.
bool addItem(Assembly * anItem){
	// 1. Simple validation
	// 2. Add to all 3 data structures

	// TREE ADD CODE
	//assemblyTreeName.add(anItem);
	//anItem->setOrdering(NUM_CONTIGS);
	//assemblyTree.add(anItem);
	// 2-3 tree...
	//assemblyCTree.insert(anItem);

	// HASH ADD CODE tbd
	// Ex. BdayHash.add(*name)
	
	// LINKED LIST ADD CODE
//	else if (keyType == N50)
//	anItem->setOrdering(N50);
//	assemblyList.insert(*anItem);
	// 3. Report results
	return true;
}

bool searchItem(Assembly searchGenome) {
	bool retVal{false};
	if (assemblyTreeName.contains(searchGenome)) {
		cout << "\nHere is the Data item found in the BST" << endl;
		Assembly foundGenome = assemblyTreeName.find(searchGenome);
		foundGenome.setOrdering(NUM_CONTIGS);
		if (assemblyTree.contains(foundGenome))
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
	if (!assemblyTreeName.contains(genome_to_delete)) {
		cout << "\n Data item not found" << endl;
		retVal = false;
	}
	else {
		// ==> foundAssemblyRecord found by name, get the record.
		Assembly deleteGenome = assemblyTreeName.find(genome_to_delete);
		deleteGenome.setOrdering(NUM_CONTIGS);
		cout << " We are deleting this genome" << endl;
		cout << " " << deleteGenome;
		assemblyTree.remove(deleteGenome);
		cout << "\nHere is the Data item to be removed from the Linked List" << endl;
		deleteGenome.setOrdering(N50);
		Assembly listDeleteGenome = assemblyList.findItem(deleteGenome);
		cout << listDeleteGenome;
		assemblyList.remove(listDeleteGenome);
		cout << "\nGenome removed from the Linked List" << endl;
		retVal = true;
		}
/*
	// HASH DELETE CODE tbd
	// Ex. BdayHash.delete(*name)


	*/
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
	const int GC_CONTENT{ 5 };
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

	std::string csvLine{ "" };
	int         number_of_lines{ 0 };
	int         count{ 0 };

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
		while (!inFile.eof() && count < number_of_lines) {
			// skip the csv header
			if (count == 0) {
				getline(inFile, csvLine);
				count++;
			}

			const int GNomeCSVCols = 7;     // Maximum data fields in our database

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

			//// Add to Linked List, Hash Table and BST
			addItem(assemblyByName[count]);

			count++;
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
			string new_genome;
			string Name;
			string Method;
			int    NumContigs;
			int    SizeBases;
			int    N50kbp;
			double GCContent;
			double PercentUnknown;
			while (flag) {
				cout << " Enter the name for the new Genome. " << endl;
				getline(cin, new_genome);
				string Name = trim(new_genome);
				cout << " Enter the method for the new Genome. " << endl;
				getline(cin, new_genome);
				string aMethod = trim(new_genome);
				cout << " Enter the number of contigs for the new Genome. " << endl;
				cin >> NumContigs;
				cout << " \nEnter the size of bases for the new Genome. " << endl;
				cin >> SizeBases;
				cout << " \nEnter the N50 for the new Genome. " << endl;
				cin >> N50kbp;
				cout << " \nEnter the GC Content for the new Genome. " << endl;
				cin >> GCContent;
				cout << " \nEnter the percent unknown for the new Genome. " << endl;
				cin >> PercentUnknown;
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
				// inc object count...
				objectCount += 1;

				*/
				// Set flag using exit function
				flag = exitFunction();
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

			//Assembly * del3 = &AssemblyByName03;
			//if (deleteItem(AssemblyByName03)) // DELETE entrypoint!
			//	cout << "Deleting done" << endl;


			 //loop allows you to keep deleting items to your hearts content...
			while (removingDataItems) {
				cout << " Enter the name of the Genome Assembly to be deleted.\n";
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
		// case 3 SEARCHES for a user specified node.				  //
		//************************************************************//
		case 3: // Search for a particular Genome by Name 
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
		// case 4 PRINTS data in hash table sequence 
		//************************************************************//
		case 4:
		{
			cout << endl << endl << "~~~~~~~~~~~~EFFICIENCY~~~~~~~~~~~~~" << endl;
			break;
		}

		//************************************************************//
		// case 5 PRINTS data in sorted key sequence using 2 data	  // 
		//	structures, Linked List and BST.						  //
		// Linked List is printed by the N50 key.					  //
		// BST is printed by the Num_Contigs key.					  //
		//************************************************************//
		case 5:
		{
			cout << endl << endl << "~~~~~~~~~~~~PRINTING BY N50~~~~~~~~~~~~~" << endl;
			cout << string(160, '=') << endl;
			cout << setw(80) << left << "GENOME NAME" << setw(20) << "GENOME TYPE" << setw(15) << "NUM_CONTIGS" 
				<< setw(10) << "Size" << setw(10) << "n50" << setw(10) << "GC Count" << setw(10) << "Percent UNKNOWN" << endl;
			cout << string(160, '=') << endl;
			assemblyList.print();
			cout << endl << endl << "~~~~~~~~~~~~PRINTING BY NUM CONTIGS~~~~~~~~~~~~~" << endl;
			cout << string(160, '=') << endl;
			cout << setw(80) << left << "GENOME NAME" << setw(20) << "GENOME TYPE" << setw(15) << "NUM_CONTIGS" 
				<< setw(10) << "Size" << setw(10) << "n50" << setw(10) << "GC Count" << setw(10) << "Percent UNKNOWN" << endl;
			cout << string(160, '=') << endl;
			assemblyTree.inorderTraverse(displayAssembly);
			//assemblyByN50.print();
		break;
		}

		//************************************************************//
		// case 6 PRINTS the indented tree 
		//************************************************************//
		case 6:
		{
			printOrders(&assemblyCTree);
			cout << endl << endl << "~~~~~~~~~~~~EFFICIENCY~~~~~~~~~~~~~" << endl;
			break;
		}

		//************************************************************//
		// case 7 PRINTS all efficiency statistics.					  //
		//************************************************************//
		case 7:
		{
			cout << endl << endl << "~~~~~~~~~~~~EFFICIENCY~~~~~~~~~~~~~" << endl;
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
			cout << endl << endl << "~~~~~~~~~~~~EXITING PROGRAM~~~~~~~~~~~~~~~~" << endl;
			loop = false;
			break;
		} // End Case 6
		default:
			cout << "   Please enter a valid choice between"
				<< "   1-8" << endl;
		} // End Switch for Menu
	} // End While loop for Menu

	// size variable is same for both arrays because of parallel arrays.
	//int personCount = aAssemblyByName.GetLength();

	// Clean up allocated memory for Assembly Objects.
	/*
	for (int index = 0; index < objectCount; ++index) {
		delete aAssemblyByName[index];
		delete aAssemblyByBday[index];
	}
	*/

	return 0;
}

void displayAssembly(Assembly & anItem)
{
	cout << anItem << endl;
}

template<class T>
void printOrders(CTree<T>* pTree)
{
	int iItemCnt = 0;
	pTree->print(preorder, &iItemCnt);
	std::cout << "**preorder[" << iItemCnt << "]" << std::endl << std::endl;
	pTree->print(inorder, &iItemCnt);
	std::cout << "**inorder[" << iItemCnt << "]" << std::endl << std::endl;
	pTree->print(postorder, &iItemCnt);
	std::cout << "**postorder[" << iItemCnt << "]" << std::endl << std::endl;
}

// EOF Lab05BST_main.cpp
