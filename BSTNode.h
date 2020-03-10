#pragma once

using namespace std;

template<typename T>
class BSTNode {
private:
	T item;
	BSTNode <T> *left;
	BSTNode <T> *right;
public:
	BSTNode();
	BSTNode(const T &anItem);
	BSTNode(const T &anItem,
		BSTNode <T> *leftPtr,
		BSTNode <T> *rightPtr);

	void setItem(const T &anItem);
	T  getItem() const;

	bool isLeaf() const;

	BSTNode<T> *getLeftPtr() const;
	BSTNode<T> *getRightPtr() const;

	void setLeftPtr(BSTNode <T> *leftPtr);
	void setRightPtr(BSTNode <T> *rightPtr);
};

template<typename T>
inline BSTNode<T>::BSTNode()
{
	left = nullptr;
	right = nullptr;
}

template<typename T>
inline BSTNode<T>::BSTNode(const T & anItem)
{
	item = anItem;
	left = nullptr;
	right = nullptr;
}

template<typename T>
inline BSTNode<T>::BSTNode(const T & anItem, BSTNode<T>* leftPtr, BSTNode<T>* rightPtr)
{
	item = anItem;
	left = leftPtr;
	right = rightPtr;
}

template<typename T>
inline void BSTNode<T>::setItem(const T & anItem)
{
	item = anItem;
}

template<typename T>
inline T BSTNode<T>::getItem() const
{
	return item;
}

template<typename T>
inline bool BSTNode<T>::isLeaf() const
{
	return false;
}

template<typename T>
inline BSTNode<T>* BSTNode<T>::getLeftPtr() const
{
	return left;
}

template<typename T>
inline BSTNode<T>* BSTNode<T>::getRightPtr() const
{
	return right;
}

template<typename T>
inline void BSTNode<T>::setLeftPtr(BSTNode<T>* leftPtr)
{
	left = leftPtr;
}

template<typename T>
inline void BSTNode<T>::setRightPtr(BSTNode<T>* rightPtr)
{
	right = rightPtr;
}
