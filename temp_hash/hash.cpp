
#include <cstdlib>
#include <iostream>
#include <string>
#include "hash.h"

using namespace std;

HashTable::HashTable()
{
	
}

unsigned int HashTable::hashFunc(std::string key)
{
	unsigned int result = 0;
	unsigned int n;

	n = key.length();

	for (unsigned int i = 0; i < n; i++) {
		result = (result + (int)key[i]) * 7;
	}

	unsigned int toReturn = result % tableSize;
	return toReturn;

}

void HashTable::add(Assembly assemblyObj)
{
	int index = hashFunc(assemblyObj.getName());
	table[index].append(assemblyObj);
}

void HashTable::remove(Assembly assemblyObj)
{
	int index = hashFunc(assemblyObj.getName());
	//cout << index << endl;
	table[index].remove(assemblyObj);


}


void HashTable::printTable()
{
	for (int i = 0; i < tableSize; i++) {
		if (table[i].isEmpty() == false) {
			table[i].print();
		}
	}
}

void HashTable::clear()
{
	for (int i = 0; i < tableSize; i++) {
		table[i].clear();
	}
}

void HashTable::printObj(Assembly assemblyObj)
{
	int index = hashFunc(assemblyObj.getName());
	table[index].print();
}

bool HashTable::search(Assembly assemblyObj)
{
	bool retVal = false;
	int index = hashFunc(assemblyObj.getName());
	if (table[index].find(assemblyObj)) {
		cout << "Item exists!" << endl;
		printObj(assemblyObj);
		retVal = true;
	}
	else {
		cout << "Item does not exist!" << endl;
	}
	return retVal;
}

void HashTable::getLength()
{
	int length = 0;
	for (int i = 0; i < tableSize; i++) {
		length += table[i].length();
	}
	cout << length << endl;
}


