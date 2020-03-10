/* Node.h - Our node class template. */
#pragma once

//**********************************************************************//
// template class Node - This is our Node class for our linked list.    // 
//**********************************************************************//
template<class T>
class Node
{
private:
	// Our member variables are the item data and a pointer to the next items
	// in the list.
	T        item;
	Node<T>* next;
public:
	// Constructors
	Node();
	Node(const T& anItem);
	Node(const T& anItem, Node<T>* nextNode);
	// Destructor
	~Node();
	// Mutators
	void setItem(const T& anItem);
	void setNext(Node<T>* nextNode);
	// Accessors
	T getItem() const;
	Node<T>* getNext() const;
};

//**********************************************************************//
// Node Constructor														// 
// pre:  N/A.															//
// post: Node with next pointer initialized to nullptr					//
//**********************************************************************//
template<class T>
inline Node<T>::Node() : next(nullptr)
{
	// Bsically just initilizes the member variables.
	// alternatively next = nullptr;
}

//**********************************************************************//
// Node Constructor														// 
// pre:  User provided item data.										//
// post: A Node with the user provided data and the						//
//		 next pointer initialized to nullptr							//
//**********************************************************************//
template<class T>
inline Node<T>::Node(const T & anItem) : item(anItem), next(nullptr)
{
	// Bsically just initilizes the member variables.
	// alternatively item = anItem; next = nullptr;
}

//**********************************************************************//
// Node Constructor														// 
// pre:  User provided item data and address of next node.				//
// post: A Node with the user provided data and the						//
//		 next pointer initialized to user provided node address.		//
//**********************************************************************//
template<class T>
inline Node<T>::Node(const T & anItem, Node<T>* nextNode) : item(anItem), next(nextNode)
{
	// Bsically just initilizes the member variables.
	// alternatively item = anItem; next = nextNode;
}

template<class T>
inline Node<T>::~Node()
{
	// point not dangling
	next = nullptr;
}

//**********************************************************************//
// This is the set item mutator.										// 
// pre:  User provided item data.										//
// post: A Node item is set to user provided data.						//
//**********************************************************************//
template<class T>
inline void Node<T>::setItem(const T & anItem)
{
	item = anItem;
}

//**********************************************************************//
// This is the set next node pointer mutator.							// 
// pre:  User provided item pointer.									//
// post: The Node item pointer is set to user provided address.			//
//**********************************************************************//
template<class T>
inline void Node<T>::setNext(Node<T>* nextNode)
{
	next = nextNode;
}

//**********************************************************************//
// This is the get item accessor.										// 
// return: Returns the value of item.									//
//**********************************************************************//
template<class T>
inline T Node<T>::getItem() const
{
	return item;
}

//**********************************************************************//
// This is the get next pointer accessor.								// 
// return: Returns the address of the next node.						//
//**********************************************************************//
template<class T>
inline Node<T>* Node<T>::getNext() const
{
	return next;
}
#pragma once
