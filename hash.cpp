#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <string>
#include "hash.h"

using namespace std;

HashTable::HashTable()
{
}

/*
DESTRUCTOR - removes all the data items in the hash table
Pre - N/A
Post - clears all data items in the hash table
Returns - N/A
*/
HashTable::~HashTable()
{
	clear();
}

/*
Hashing function to turn inputted key into a table index position
Pre - key string
Post - N/A
Returns - index position calculated by the hashing function
*/
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

/*
Add function to add assembly objects into hash table
Pre - assembly object
Post - assembly object added to hash table
Returns - N/A
*/
void HashTable::add(Assembly assemblyObj)
{
	int index = hashFunc(assemblyObj.getName());
	table[index].append(assemblyObj);
}

/*
Remove function to remove inputted assembly objects from hash table
Pre - assembly object
Post - assembly object removed from hash table
Returns - N/A
*/
void HashTable::remove(Assembly assemblyObj)
{
	int index = hashFunc(assemblyObj.getName());
	table[index].remove(assemblyObj);
}

/*
Prints all assembly objects's properties currently in hash table
Pre - N/A
Post - prints table's assembly objects
Returns - N/A
*/
void HashTable::printTable()
{
	for (int i = 0; i < tableSize; i++) {
		if (table[i].isEmpty() == false) {
			table[i].print();
		}
	}
}

/*
Removes all the assembly objects in the table
Pre - N/A
Post - Table is cleared of assembly objects
Returns - N/A
*/
void HashTable::clear()
{
	for (int i = 0; i < tableSize; i++) {
		table[i].clear();
	}
}

/*
Finds individual given assembly object properties
Pre - assembly object
Post - N/A 
Return - Returns found assembly object 
*/
Assembly HashTable::getObject(Assembly assemblyObj)
{
	Assembly tempItem;
	int index = hashFunc(assemblyObj.getName());
	tempItem = table[index].findItem(assemblyObj);
	return tempItem;
}

/*
Prints individual given assembly object properties
Pre - assembly object
Post - prints given assembly object properties
Returns - N/A
*/
void HashTable::printObj(Assembly assemblyObj)
{
	Assembly temp = getObject(assemblyObj);
	cout << temp;
}

/*
Function to check if given assembly object exists. 
Pre - key string
Post - print object's properties if object exist
Returns - true if item exists, false if item doesn't exist
*/
bool HashTable::search(Assembly assemblyObj)
{
	int index = hashFunc(assemblyObj.getName());
	if (table[index].find(assemblyObj)) {
		return true;;
	}
	else {
		return false;
	}
}


/*
Getter for number of assembly objects in the hash table
Pre - N/A
Post - returns number of assembly objects count in the table
Returns - number of assembly objects currently in the hash table
*/
int HashTable::getnumberOfItems()
{
	int amount = 0;
	for (int i = 0; i < tableSize; i++) {
		amount += table[i].length();
	}
	numberOfItems = amount;
	return amount;
}

/*
Getter for load factor of the hash table
Pre - N/A
Post - returns load factor
Returns - load factor value
*/
double HashTable::getLoadFactor()
{
	int filled = 0;
	for (int i = 0; i < tableSize; i++) {
		if (table[i].isEmpty() == false) {
			filled++;
		}
	}
	loadFactor = ((double)filled / tableSize) * 100;
	return loadFactor;

}

/*
Getter for amount of collisions that exist in the hash table
Pre - N/A
Post - returns number of collisions in hash table
Returns - amount of collisions
*/
int HashTable::getCollisionsCount()
{
	int amount = 0;
	for (int i = 0; i < tableSize; i++) {
		if (table[i].length() >= 2) {
			amount++;
		}
	}
	collisions = amount;
	return amount;
}

/*
Function to print hash table statistics to fulfill menu item 7
Pre - N/A
Post - prints hash table statistics
Returns - N/A
*/
void HashTable::printStats()
{
	cout << "Here are the statistics of the hash table:" << endl;
	cout << "Table size: " << tableSize << endl;
	cout << "Number of items in table: " << getnumberOfItems() << endl;
	cout << fixed;
	cout << setprecision(2);
	cout << "Load Factor: " << getLoadFactor() << "%" << endl;

	cout << "Number of collisions: " << getCollisionsCount() << endl;
}


