/**
 * @file
 * @author  Mohamed Kalmoua <Mohamed.Kalmoua@gmail.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * The Node class represents a node which build a 2-3 self balancing tree.
 */
#pragma once

#include "2-3BTreeError.h"

#define MAX_CHILDREN 3

 //enum eNodeSize
 //{
 //    empty = 0,
 //    twoNode,
 //    threeNode
 //};
 //
enum eTraverseDirection
{
	leftChild = 0,
	middleChild,
	rightChild
};

enum class eNodeSize
{
	empty = 0,
	twoNode,
	threeNode
};

//enum class eTraverseDirection
//{
//	leftChild = 0,
//	middleChild,
//	rightChild
//};

template<class T>
class CNode
{
public:
	CNode(CNode<T>* pLeftChild, CNode<T>* pRightChild, const T* const pSmallKey);
	CNode(void);
	~CNode(void);
	CNode* getChild(eTraverseDirection eIndex) const;
	void setChild(eTraverseDirection eIndex, CNode<T>* pChild = 0);
	void setParent(CNode<T>* pNode);
	CNode<T>* getParent(void) const;
	const T* const getSmallKey(void) const;
	void setSmallKey(const T* const tSmallKey);
	const T* const getBigKey(void) const;
	void setBigKey(const T* const pBigKey);
	eNodeSize getSize(void) const;
	bool isLeaf(void) const;
private:
	T m_tSmallKey;
	T m_tBigKey;
	CNode<T>* m_pParent;
	bool m_bBigKeyIsSet;
	bool m_bSmallKeyIsSet;
	CNode<T>* m_pChildren[MAX_CHILDREN];
};

/**
 * Overload constructor taking three arguments.
 * Left and right child are set for this node. Small key is also set.
 * @param[in] pLeftChild: address to node which will be set as left child of this node.
 * @param[in] pRightChild: address to node which will be set as right child of this node.
 * @param[in] pSmallKey: address to small key.
 * @return none
 */
template<class T>
CNode<T>::CNode(CNode<T>* pLeftChild, CNode<T>* pRightChild, const T* const pSmallKey)
{
	m_pChildren[leftChild] = pLeftChild;
	m_pChildren[middleChild] = 0;
	m_pChildren[rightChild] = pRightChild;
	m_bBigKeyIsSet = false;
	m_pParent = 0;

	if (pLeftChild != 0)
	{
		pLeftChild->setParent(this);
	}

	if (pRightChild != 0)
	{
		pRightChild->setParent(this);
	}

	if (pSmallKey != 0)
	{
		m_tSmallKey = *pSmallKey;
		m_bSmallKeyIsSet = true;
	}
	else
	{
		m_bSmallKeyIsSet = false;
	}
}

/**
 * Constructor initializes variables.
 */
template<class T>
CNode<T>::CNode(void)
{
	m_pChildren[leftChild] = 0;
	m_pChildren[middleChild] = 0;
	m_pChildren[rightChild] = 0;
	m_pParent = 0;
	m_bSmallKeyIsSet = false;
	m_bBigKeyIsSet = false;
}

/**
 * Destructor nothing to do.
 */
template<class T>
CNode<T>::~CNode(void)
{
}

/**
 * Member function taking one argument and returning node address.
 * Function returns the node address to the requested child.
 * @param[in] eIndex: child index { leftChild, middleChild, rightChild }.
 * @return Node address
 */
template<class T>
inline CNode<T>* CNode<T>::getChild(eTraverseDirection eIndex) const
{
	return m_pChildren[eIndex];
}

/**
 * Member function taking two arguments and returning none.
 * Function sets child node for a given node.
 * @param[in] eIndex: child index {leftChild,middleChild,rightChild}
 * @param[in] pChild: Node address
 * @return none
 */
template<class T>
inline void CNode<T>::setChild(eTraverseDirection eIndex, CNode<T>* pChild)
{
	m_pChildren[eIndex] = pChild;
	if (pChild != 0)
	{
		pChild->setParent(this);
	}
}

/**
 * Member function taking one argument and returning none.
 * Sets the parent of node.
 * @return none.
 */
template<class T>
inline void CNode<T>::setParent(CNode* pNode)
{
	m_pParent = pNode;
}

/**
 * Member function taking no arguments and returning a pointer to parent node.
 * @return pointer to parent node.
 */
template<class T>
inline CNode<T>* CNode<T>::getParent(void) const
{
	return m_pParent;
}

/**
 * Member function taking no arguments and returning small key address.
 * Small key is a template type.
 * @return small key address.
 */
template<class T>
inline const T* const CNode<T>::getSmallKey(void) const
{
	return &m_tSmallKey;
}

/**
 * Member function taking one argument and returning none.
 * Small key value of node is set. Small key is a template type.
 * Flag m_bSmallKeyIsSet is used to keep track whether the value is set.
 * Flag is used because template variables cannot easily be checked for zero.
 * @param[in] address to small key.
 * @return none
 */
template<class T>
inline void CNode<T>::setSmallKey(const T* const pSmallKey)
{
	if (pSmallKey == 0)
	{
		m_bSmallKeyIsSet = false;
	}
	else
	{
		m_tSmallKey = *pSmallKey;
		m_bSmallKeyIsSet = true;
	}
}

/**
 * Member function taking no arguments and returning address of big key.
 * @return address of big key
 */
template<class T>
inline const T* const CNode<T>::getBigKey(void) const
{
	return &m_tBigKey;
}

/**
 * Member function taking one argument and returning none.
 * Big key value of the node is set. Big key is a template type.
 * Flag m_bBigKeyIsSet is used to to keep track whether value is set.
 * Flag is used because template variables cannot easily be checked for zero.
 * @param[in] address to big key.
 * @return none
 */
template<class T>
inline void CNode<T>::setBigKey(const T* const pBigKey)
{
	if (pBigKey == 0)
	{
		m_bBigKeyIsSet = false;
	}
	else
	{
		m_tBigKey = *pBigKey;
		m_bBigKeyIsSet = true;
	}
}

/**
 * Member function taking no arguments and returning the size of the node.
 * Node size: { empty, twoNode, threeNode }
 * @return node size (enum)
 */
template<class T>
eNodeSize CNode<T>::getSize(void) const
{
	eNodeSize eSize = eNodeSize::empty;
	if (m_bBigKeyIsSet == true && m_bSmallKeyIsSet == true)
	{
		eSize = eNodeSize::threeNode;
	}
	else if (m_bSmallKeyIsSet == true)
	{
		eSize = eNodeSize::twoNode;
	}
	return eSize;
}

/**
 * Member function taking no arguments and returning a boolean.
 * true if node is a leaf, false otherwise.
 * @return boolean.
 */
template<class T>
bool CNode<T>::isLeaf(void) const
{
	if (m_pChildren[leftChild] == 0 &&
		m_pChildren[middleChild] == 0 &&
		m_pChildren[middleChild] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}