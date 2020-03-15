#ifndef HASHBUCKET_H
#define HASHBUCKET_H



#include <iostream>
#include <string>
#include "ArrayTemplateClass.h"
#include "Node.h"
#include "Assembly.h"
#include "LinkedList.h"
using namespace std;

template<class T>
class HashBucket {
private:
	LinkedList<Assembly> list;
public:
	HashBucket();
	void insert(Assembly item);
	void remove(Assembly item);
	bool contains(Assembly item);
};

template<class T>
HashBucket<T>::HashBucket()
{

}

template<class T>
void HashBucket<T>::insert(Assembly item)
{

}

template<class T>
void HashBucket<T>::remove(Assembly item)
{
}

template<class T>
bool HashBucket<T>::contains(Assembly item)
{
	return false;
}

#endif // !HASHBUCKET_H
