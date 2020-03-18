#ifndef HASH_H
#define HASH_H

#include <cstdlib>
#include <iostream>
#include <string>
#include "Assembly.h"
#include "LinkedList.h"


class HashTable {
private:
	// table size
	static const int tableSize = 11;

	// setting a hash table array of linked lists of Assembly objects
	LinkedList<Assembly> table[tableSize];

	int numberOfItems = 0;
	int collisions = 0;
	double loadFactor;

public:
	HashTable();
	~HashTable(); 

	// hashing function
	unsigned int hashFunc(std::string key);
	
	// function to add assembly objects
	void add(Assembly assemblyObj);

	// function to remove assembly objects
	void remove(Assembly assemblyObj);

	// prints all the assembly objects in the hash table
	void printTable();

	// remove all assembly objects in the hash table
	void clear();

	// prints one assembly object given in as a parameter
	void printObj(Assembly assemblyObj);

	// search the hash table
	bool search(Assembly assemblyObj);

	// search the hash table and return object found
	Assembly getObject(Assembly assemblyObj);
	
	// getters for table stats
	int getnumberOfItems();
	double getLoadFactor();
	int getCollisionsCount();

	// function to print table statistics for option 7(efficiency)
	void printStats(); 
};





#endif // !HASH_H
