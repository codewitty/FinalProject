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
BNTree<Assembly> assemblyTree;                  // Our binary search tree template.
LinkedList<Assembly> assemblyList(DESCENDING);  // Our Linked List template.
CTree<Assembly> assemblyCTree;                  // Our 2-3 Tree open source template.
HashTable table;                                // Our hash table.

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
	// 3. Report results
	anItem->setOrdering(assemblyAttribute::NAME);

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