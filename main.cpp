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

// Forward Declarations
//void displayPersonName(Person & anItem);
//void displayPersonBday(Person & anItem);
//void displayPerson(Person & anItem);
int objectCount = 0;

BNTree<Assembly> assemblyTree;
LinkedList<Assembly> assemblyList;
Assembly AssemblyByName01("contig-20.fa", "pilon+idba", 2637, 2182179, 306, 0.1573, 0.1964, NAME);
Assembly AssemblyByName02("contig-30.fa", "Spades", 2130, 1660411, 321, 0.5292, 0.3762, NAME);
Assembly AssemblyByName03("contig-40.fa", "MosaicFLye", 2309, 2463148, 265, 0.8489, 0.759, NAME);

// Covering function for generic add.
bool addItem(Assembly * anItem){
	// 1. Simple validation
	// 2. Add to all 3 data structures

	// TREE ADD CODE
	assemblyTree.add(*anItem);
	// HASH ADD CODE tbd
	// Ex. BdayHash.add(*name)

	// MRU LINKED LIST ADD CODE tbd
	assemblyList.insert(*anItem);
	// 3. Report results
	return true;
}

bool searchItem(Assembly * searchItem) {
	bool retVal{true};
	assemblyList.find(*searchItem);
	/*
	if (order == NAME) {
		if (nameTree.contains(searchItem))
		{
			cout << "\nData item found" << endl;
			cout << nameTree.find(searchItem);
			retVal = true;
		}
	}
	else if (order == BDAY)
	{
		if (bdayTree.contains(searchItem))
		{
			cout << "\nData item found" << endl;
			cout << bdayTree.find(searchItem);
			retVal = true;
		}
	}
	return retVal;

	// HASH DELETE CODE tbd
	// Ex. BdayHash.delete(*name)

	// MRU LINKED LIST DELETE CODE tbd

	// 3. Report results
	*/
	return retVal;
}

bool deleteItem(Assembly genome_to_delete){
	bool retVal{false};
	if (assemblyList.remove(genome_to_delete))
		retVal = true;
	/*
	if (order == NAME)
	{
		if (!nameTree.contains(person_to_delete))
		{
			cout << "\n Data item not found" << endl;
			retVal = false;
		}
		else {
			// ==> foundPersonRecord found by name, get the record.
			Person foundPersonRecord = nameTree.find(person_to_delete);
			cout << " We are deleting this person" << endl;
			cout << " " << foundPersonRecord;
			nameTree.remove(foundPersonRecord);
			// reset search criteria so we can delete from the birthday tree
			foundPersonRecord.setOrdering(BDAY);
			bdayTree.remove(foundPersonRecord);
		}
	}

	else if (order == BDAY)
	{
		if (!bdayTree.contains(person_to_delete))
		{
			cout << "\n Data item not found" << endl;
			retVal = false;
		}
		else {
			// ==> foundPersonRecord found by name, get the record.
			Person foundPersonRecord = bdayTree.find(person_to_delete);
			cout << " We are deleting this person" << endl;
			cout << " " << foundPersonRecord;
			bdayTree.remove(foundPersonRecord);
			// reset search criteria so we can delete from the name tree
			foundPersonRecord.setOrdering(NAME);
			nameTree.remove(foundPersonRecord);
		}
	}
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
	fstream inFile;
	int number_of_lines = 0;
	int count = 0;
	string name;

	inFile.open("faux_assemblies.csv", ios::in);

	// This if block creates Person objects and seeds them into the array.
	if (inFile) {
		while (getline(inFile, name)) {
			++number_of_lines;
		}

		inFile.clear();
		inFile.seekg(0, ios::beg);


		while (!inFile.eof() && count < number_of_lines) {
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
		cout << "   2: Search for a Node by Name" << endl;
		cout << "   3: Search for a Node by Birthday" << endl;
		cout << "   4: Delete a Node by Name" << endl;
		cout << "   5: Delete a Node by Birthday" << endl;
		cout << "   6: Print data" << endl;
		cout << "   7: EXIT" << endl << endl;
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

				Assembly * temp1 = &AssemblyByName01;
				Assembly * temp2 = &AssemblyByName02;
				Assembly * temp3 = &AssemblyByName03;
				addItem(temp1);
				addItem(temp2);
				addItem(temp3);
				/*
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
		case 2: // Search for a particular Node by Name 
		{
			bool sflag = true;
			string name;
			while (sflag)
			{
				cout << " Enter the name of the person you would like to look for.\n";
				Assembly * temp3 = &AssemblyByName03;
				if (searchItem(temp3))
					cout << "\nData item found" << endl;
				/*j
				getline(cin, name);
				string tname = trim(name);
				Person search_name(tname, "000-00-00", NAME);

				if (searchItem(search_name, NAME))
					cout << "\nData item found" << endl;
				else
					cout << "\nData item not found" << endl;
				// Set flag using exit function
				*/
				sflag = exitFunction();
			}
			break;
		}
		//************************************************************//
		// case 3 SEARCHES for a user specified node.				  //
		//************************************************************//
		case 3: // Search for a particular Node by Bday
		{
			bool sflag = true;
			string bday;
			while (sflag)
			{
				cout << " Enter the birthday of the person you would like to look for.\n";
				/*
				getline(cin, bday);
				string tbday = trim(bday);
				Person search_bday("", tbday, BDAY);

				if (searchItem(search_bday, BDAY))
					cout << "\nData item found" << endl;
				else
					cout << "\nData item not found" << endl;
					*/
				// Set flag using exit function
				sflag = exitFunction();
			}
			break;
		}

		//************************************************************//
		// case 4 DELETES a node from both existing trees by Name.	  //
		//************************************************************//
		case 4: // Delete a particular Node by Name
		{
			bool removingDataItems = false;

			//Assembly * del3 = &AssemblyByName03;
			if (deleteItem(AssemblyByName03)) // DELETE entrypoint!
				cout << "Deleting done" << endl;


			// loop allows you to keep deleting items to your hearts content...
			/*
			while (removingDataItems) {
				cout << " Enter the name of the person item to be deleted.\n";
				cout << " ";
				getline(cin, r_name);
				Person name_to_delete(r_name, "", NAME);  // sparse record wtih user entered name
				// deleteItem is the entry point to delete the item from ALL data structures.
				if (deleteItem(name_to_delete, NAME)) // DELETE entrypoint!
				{
					cout << "Deleting done" << endl;
				}
				else 
				{
					cout << "Item not found or deleted." << endl;
				}
			}
			*/
			// Set flag using exit function
			removingDataItems = exitFunction();
		break;
	} // End switch

		//************************************************************//
		// case 5 DELETES a node from both existing trees by Birthday.//
		//************************************************************//
		case 5: // Delete a particular Node by Birthday
		{
			bool removingDataItems = true;
			string r_bday;
/*
			// loop allows you to keep deleting items to your hearts content...
			while (removingDataItems) {
				cout << " Enter the birthday of the person item to be deleted.\n";
				cout << " ";
				getline(cin, r_bday);
				Person bday_to_delete("", r_bday, BDAY);  // sparse record wtih user entered name
				// deleteItem is the entry point to delete the item from ALL data structures.
				if (deleteItem(bday_to_delete, BDAY)) // DELETE entrypoint!
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
			*/
		break;
		} // End switch case 5
		//************************************************************//
		// case 6 PRINTS all node from both existing trees.			  //
		// Name Tree is printed in Preorder and Postorder modes.	  //
		// Birthday Tree is printed in Inorder and BreadthFirst mode. //
		//************************************************************//
		case 6:
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
		}
		break;

		//************************************************************//
		// case 7 PRINTS all node from both existing trees and		  //
		//		 exits the menu.									  //
		// Name Tree is printed in Preorder and Postorder modes.	  //
		// Birthday Tree is printed in Inorder and BreadthFirst mode. //
		//************************************************************//
		case 7:
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
			assemblyList.print();
			cout << endl << endl << "~~~~~~~~~~~~EXITING PROGRAM~~~~~~~~~~~~~~~~" << endl;
			loop = false;
			break;
		} // End Case 5
		default:
			cout << "   Please enter a valid choice between"
				<< "   1-7" << endl;
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
