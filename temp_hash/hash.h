

#ifndef HASH_H
#define HASH_H

#include <cstdlib>
#include <iostream>
#include <string>
#include "Assembly.h"


class HashTable {
private:
	static const int tableSize = 97;
	// this would be our object class
	Assembly* Table[tableSize];

public:
	HashTable();
	unsigned int hashFunc(std::string key);
	void addItem(std::string name);
	int numberofItemsInIndex(int index);
	void printTable();
	void printItemsInIndex(int index);
	// still need search and other basic functions
};












#endif // !HASH_H
