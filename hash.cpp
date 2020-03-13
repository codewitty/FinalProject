#include <cstdlib>
#include <iostream>
#include <string>

#include "hash.h"

HashTable::HashTable()
{
	for (int i = 0; i < tableSize; i++) {
		Table[i] = new Assembly;
		Table[i]->setName("");
		Table[i]-> = NULL; //set next linked list function needed
	}
}

unsigned int HashTable::hashFunc(std::string key)
{
	int result = 0;
	int n;

	n = key.length();

	for (unsigned int i = 0; i < n; i++) {
		result = (result + (int)key[i]) * 7;
	}

	return result % tableSize;

}

void HashTable::addItem(std::string name)
{
	int index = hashFunc(name);

	if (Table[index]->getName == "") {
		Table[index]->setName("name");
	}
	else {
		Assembly* ptr = Table[index];
		item* n = new item;
		n->name = name;
		n->next = NULL;
		while (ptr->next != NULL)
		{
			// gets to last item of linked list
			ptr = ptr->next;
		}
		ptr->next = n;

	}
}

int HashTable::numberofItemsInIndex(int index)
{
	int count = 0;

	if (Table[index]->getName() == "empty") {
		return count;
	}
	else
	{
		count++;
		Assembly* ptr = Table[index];
		while (ptr->next != NULL) {
			count++;
			ptr = ptr->next;
		}
	}

}

void HashTable::printTable()
{
	int number;
	for (int i = 0; i < tableSize; i++) {
		number = numberofItemsInIndex(i);
		std::cout << "-------------------\n";
		std::cout << "index = " << i << std::endl;
		std::cout << Table[i]->getName() << std::endl;
		std::cout << "Number of items: " << number << std::endl;
		std::cout << "-------------------\n";
	}
}

void HashTable::printItemsInIndex(int index)
{
	Assembly* ptr = Table[index];

	if (ptr->name == "empty") {
		std::cout << "index is empty" << std::endl;
	}
	else {
		std::cout << "index " << index << " contains the following" << std::endl;

		while (ptr != NULL)
		{
			std::cout << "----------------\n";
			std::cout << ptr->name << std::endl;
			std::cout << "----------------\n";
			ptr = ptr->next;
		}
	}

}
