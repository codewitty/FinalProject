#ifndef HASH_H
#define HASH_H

#include <cstdlib>
#include <iostream>
#include <string>
#include "Assembly.h"
#include "ArrayTemplateClass.h"
#include "HashBucket.h"
#include "LinkedList.h"


class HashTable {
private:
	static const int tableSize = 500;
	LinkedList<Assembly> table[tableSize];

public:
	HashTable();
	unsigned int hashFunc(std::string key);
	void add(Assembly assemblyObj);
	void remove(Assembly assemblyObj);
	void printTable();
	void clear();
	void printObj(Assembly assemblyObj); //prints one obj info
	bool search(Assembly assemblyObj);
	void getLength();
	// still need search and other basic functions
};












#endif // !HASH_H
