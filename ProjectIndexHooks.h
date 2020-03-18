#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
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


// Our 4 indexes
BNTree<Assembly> assemblyTree;                  // Our binary search tree.
LinkedList<Assembly> assemblyList(DESCENDING);  // Our Linked List.
CTree<Assembly> assemblyCTree;                  // Our 2-3 Tree.
HashTable table;                                // Our hash table.

// We use this to print records in name.
BNTree<Assembly> BST_NameOrder;                 


// THis is for keeping track dynamically allocated Assemblies.
const int       MAX_ASSEMBLIES = 500;              // Maximum persons in our database
Array<Assembly *> assemblyByName(MAX_ASSEMBLIES);  // An array of type 'Assembly' using Array Template

// Covering function for generic add.
bool addItem(Assembly * anItem) {
	// 1. Simple validation
	// 2. Add to all 3 data structures

	// HASH ADD CODE tbd
	table.add(*anItem);

	// TREE ADD CODE
	anItem->setOrdering(assemblyAttribute::SIZE);
	assemblyTree.add(*anItem);

	// 2-3 tree...
	anItem->setOrdering(assemblyAttribute::NUM_CONTIGS);
	assemblyCTree.insert(anItem);

	// LINKED LIST ADD CODE
	anItem->setOrdering(assemblyAttribute::N50);
	assemblyList.insert(*anItem);

	// Extra by name BST index.  Used save file in name order.
	anItem->setOrdering(assemblyAttribute::NAME);
	BST_NameOrder.add(*anItem);

	return true;
}

bool searchItem(Assembly searchGenome) {
	bool retVal{ false };
	if (table.search(searchGenome)) {
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

bool deleteItem(Assembly genome_to_delete) {
	bool retVal{ false };
	if (!table.search(genome_to_delete)) {
		cout << "\n!!!!!! ASSEMBLY GENOME NOT FOUND !!!!!!!";
		retVal = false;
	}
	else {

		// 1.  Remove from Hash Table (keyed by NAME).
		Assembly deleteGenome = table.getObject(genome_to_delete);  // ...get the record...

		cout << string(141, '=');                                   // Some hashtable output formatting (??)
		cout << "\nData item removed from the Hash Table : ";
		table.printObj(deleteGenome);
		table.remove(deleteGenome);                                 // ...remove the item from the hash table.

		// 2.  Remove from BST (oredered by SIZE).
		deleteGenome.setOrdering(assemblyAttribute::SIZE);          // ...Set the ordering attruibute to 'SIZE'.
		cout << "\nData item removed from the BST        : ";
		Assembly dTreeGenome = assemblyTree.find(deleteGenome);
		cout << dTreeGenome;
		assemblyTree.remove(deleteGenome);                          // ...remove the item from the binary search tree.

		// 3.  Remove from 2-3 Tree (ordered by number of contigs (NUM_CONTIGS))
		deleteGenome.setOrdering(assemblyAttribute::NUM_CONTIGS);   // ...Set the ordering attruibute to 'NUM_CONTIGS'.
		cout << "\nData item removed from the 2-3 Tree   : ";
		const Assembly * dcTreeGenome = assemblyCTree.find(&deleteGenome);
		cout << *dcTreeGenome;
		assemblyCTree.deleteItem(&deleteGenome);                    // ...remove the item from the 2-3 tree.

		// 4.  Remove from the Linked List (ordered by N50).
		cout << "\nData item removed from the Linked List: ";
		deleteGenome.setOrdering(assemblyAttribute::N50);           // ...Set the ordering attruibute to 'N50'.
		Assembly listDeleteGenome = assemblyList.findItem(deleteGenome);
		cout << listDeleteGenome;
		assemblyList.remove(listDeleteGenome);
		cout << endl << string(141, '=') << endl;

		// 5.  Remove from name ordering BST (our utility BST index for convenient
		// NAME ordering access.)  Used for writing out the file.
		deleteGenome.setOrdering(assemblyAttribute::NAME);          // Set the ordering attruibute to 'NAME'.
		Assembly BSTreeNameOrderGenome = BST_NameOrder.find(deleteGenome); // First find the item....
		BST_NameOrder.remove(BSTreeNameOrderGenome);                // ...remove the item from the secondary BSTree.

		retVal = true;
	}
	// 3. Report results
	return retVal;
}