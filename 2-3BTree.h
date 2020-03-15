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
 * The Tree class represents a 2-3 self balancing tree.
 * Template objects can be stored in the 2-3 tree. Comparison between objects can be accomplished
 * by overloading the > operator in the template class.
 */
#pragma once

#include "2-3BTreeError.h"
#include "2-3BtreeNode.h"

 /* Three tree traversal methods supported. */
enum eTreeTraversal
{
	inorder = 0,
	preorder,
	postorder
};

template<class T>
class CTree
{
public:
	CTree(void);
	~CTree(void);
	int insert(const T* const pKey);
	const T* const find(const T* const);
	int deleteItem(const T* const pKey);
	int print(eTreeTraversal eTraversalMethod, int *pNrOfItemsPrinted) const;
	int removeAll(void);
private:
	int add(CNode<T>* const pNode, const T* const pKey);
	int split(T* pKey,
		CNode<T>* const pNode2Split,
		CNode<T>** const ppAddedNode);
	int search(const T* const,
		CNode<T>** ppNodeFound,
		bool *bFound) const;
	CNode<T>* getMinNode(CNode<T>* pNode) const;
	CNode<T>* getMaxNode(CNode<T>* pNode) const;
	CNode<T>* m_pRoot;
	CNode<T>* getNextInorderKey(CNode<T>* pNode, T* pKey) const;
	CNode<T>* getNextPreorderKey(CNode<T>* pNode, T* pKey) const;
	CNode<T>* getNextPostorderKey(CNode<T>* pNode, T* pKey) const;
	int removeFromLeaf(CNode<T>* pNode, const T* const pKey);
	int localRotation(CNode<T>* pNode);
	int globalRotation(CNode<T>* pNode);
	int localNodeMerger(CNode<T>* pNode);
	int globalNodeMerger(CNode<T>* pNode, CNode<T>** ppNextNode2Fix);
	int swapWithInOrderSuccessor(CNode<T>* pNode, const T* const pKey, CNode<T>** ppLeafNode);
	int TCompare(const T* const pObject1, const T* const pObject2) const;
};

/**
 * Constructor that sets variables to zero.
 */
template<class T>
CTree<T>::CTree(void) : m_pRoot(0)
{
}

/**
 * Destructor cleanup the tree. Delete all nodes.
 */
template<class T>
CTree<T>::~CTree(void)
{
	if (m_pRoot != 0)
	{
		removeAll();
	}
}

/** @brief     Member function taking no argument and returning an error code.
 *             Deletes all the nodes of the tree. Error codes are specified in "CTreeError.h".
 *  @param[in] None.
 *  @return    SUCCESS when no error encountered.
 */
template<class T>
int CTree<T>::removeAll(void)
{
	int iReturnCode = FAILURE;
	CNode<T> *pNodeIterator = 0;
	CNode<T> *pParentNode = 0;
	CNode<T> *pRightNode = 0;
	CNode<T> *pMiddleNode = 0;
	CNode<T> *pLeftNode = 0;

	/* If no root present, no need to delete nodes. */
	if (m_pRoot == 0)
	{
		iReturnCode = IS_EMPTY;
	}
	else
	{
		pNodeIterator = getMinNode(m_pRoot);

		while ((pParentNode = pNodeIterator->getParent()) != 0)
		{
			pRightNode = pParentNode->getChild(rightChild);
			pMiddleNode = pParentNode->getChild(middleChild);
			pLeftNode = pParentNode->getChild(leftChild);

			if ((pNodeIterator == pLeftNode &&
				pMiddleNode == 0) ||
				(pNodeIterator == pMiddleNode))
			{
				delete pNodeIterator;
				pNodeIterator = getMinNode(pRightNode);
			}
			else if (pNodeIterator == pLeftNode)
			{
				delete pNodeIterator;
				pNodeIterator = getMinNode(pMiddleNode);
			}
			else if (pNodeIterator == pRightNode)
			{
				delete pNodeIterator;
				pNodeIterator = pParentNode;
			}
		}
		/* Finally delete root. */
		delete m_pRoot;
		m_pRoot = 0;
		iReturnCode = SUCCESS;
	}
	return iReturnCode;
}

/** @brief     Member function taking one argument and returning an error code.
 *             Adds a key value to tree. Error codes are specified in "CTreeError.h".
 *  @param[in] pKey: address of key value to be added to tree.
 *  @return    SUCCESS when no error encountered.
 */
template<class T>
int CTree<T>::insert(const T* const pKey)
{
	int iReturnCode = FAILURE;
	CNode<T>* pNodeFound = 0;
	CNode<T>* pAddedNode = 0;
	bool bTreeIsFixed = false;
	bool bFound = false;

	/* If no root present, create one. */
	if (m_pRoot == 0)
	{
		m_pRoot = new CNode<T>();
		add(m_pRoot, pKey);
		iReturnCode = SUCCESS;
	}
	else
	{   /* Find place in tree to insert key.*/
		iReturnCode = search(pKey,
			&pNodeFound,
			&bFound);
	}

	if (iReturnCode == SUCCESS &&
		pNodeFound != 0)
	{
		/* Error duplicate value. */
		if (bFound == true)
		{
			iReturnCode = DUPLICATE_VALUE;
		}
		/* Unique Key value, add it to tree (straightforward).*/
		else if (pNodeFound->getSize() == eNodeSize::twoNode)
		{
			add(pNodeFound, pKey);
			iReturnCode = SUCCESS;
		}
		/* In case of three node we need to split node. */
		else if (pNodeFound->getSize() == eNodeSize::threeNode)
		{
			/* Template key variable needed for iteration purposes. */
			/* Node splitting can propagate up the tree using tKey as output. */
			T tKey = *pKey;
			do
			{
				/* Split node. */
				iReturnCode = split(&tKey,
					pNodeFound,
					&pAddedNode);

				if (iReturnCode == SUCCESS)
				{
					/* Node splitting has propagated up to root node, create new root. */
					if (pNodeFound->getParent() == 0)
					{
						CNode<T>* pNewRoot = new CNode<T>(pAddedNode, pNodeFound, &tKey);
						m_pRoot = pNewRoot;
						bTreeIsFixed = true;
						iReturnCode = SUCCESS;
					}
					else
					{
						pNodeFound = pNodeFound->getParent();
						if (pNodeFound->getSize() == eNodeSize::twoNode)
						{
							if (TCompare(&tKey, pNodeFound->getSmallKey()) == LESS)
							{
								add(pNodeFound, &tKey);
								pNodeFound->setChild(middleChild, pNodeFound->getChild(leftChild));
								pNodeFound->setChild(leftChild, pAddedNode);
								bTreeIsFixed = true;
								iReturnCode = SUCCESS;
							}
							else if (TCompare(&tKey, pNodeFound->getSmallKey()) == GREATER)
							{
								add(pNodeFound, &tKey);
								pNodeFound->setChild(middleChild, pAddedNode);
								bTreeIsFixed = true;
								iReturnCode = SUCCESS;
							}
						}
					}
				}
			} while (bTreeIsFixed == false && iReturnCode == SUCCESS);
		}
	}
	return iReturnCode;
}

/** @brief     Member function taking one argument and returning the address of key object.
 *             Searches the tree for the specified key.
 *  @param[in] pKey: address of key value to look for in tree.
 *  @return    address of key object, 0 if key object can not be found in tree.
 */
template<class T>
const T* const CTree<T>::find(const T* const pKey)
{
	CNode<T> *pNodeFound = 0;
	bool bKeyFound = false;

	search(pKey, &pNodeFound, &bKeyFound);
	if (bKeyFound == true &&
		TCompare(pKey, pNodeFound->getSmallKey()) == EQUAL)
	{
		return pNodeFound->getSmallKey();
	}
	else if (bKeyFound == true &&
		pNodeFound->getSize() == eNodeSize::threeNode &&
		TCompare(pKey, pNodeFound->getBigKey()) == EQUAL)
	{
		return pNodeFound->getBigKey();
	}
	else
	{
		return 0;
	}
}

/** @brief      Member function taking three arguments and returning an error code.
 *              Function searches the tree to find a leaf node where the new key value should be inserted.
 *  @param[in]  pKey: address of key value to search for.
 *  @param[out] ppNodeFound: address of node pointer which points to a leaf node where the new key value should be inserted.
 *  @param[out] bFound: If key value already present in tree then bool value at address bFound will be set to true, false otherwise.
 *  @return     SUCCESS when no error encountered.
 */
template<class T>
int CTree<T>::search(const T* const pKey,
	CNode<T>** ppNodeFound,
	bool* bFound) const
{
	eTraverseDirection eSearchDirection;
	CNode<T> *pNodeIterator = 0;
	int iReturnCode = FAILURE;
	*bFound = false;
	*ppNodeFound = 0;

	if (m_pRoot == 0)
	{
		iReturnCode = IS_EMPTY;
	}
	else
	{
		pNodeIterator = m_pRoot;

		do
		{
			/* Key found in tree, DUPLICATE_VALUE. */
			if (TCompare(pKey, pNodeIterator->getSmallKey()) == EQUAL ||
				(pNodeIterator->getSize() == eNodeSize::threeNode &&
					TCompare(pKey, pNodeIterator->getBigKey()) == EQUAL))
			{
				*bFound = true;
				*ppNodeFound = pNodeIterator;
				iReturnCode = SUCCESS;
			}
			/* If (search) key is smaller than smallkey node, traverse to the left child. */
			else if (TCompare(pKey, pNodeIterator->getSmallKey()) == LESS)
			{
				eSearchDirection = leftChild;
			}
			/* If (search) key is larger than bigkey node, traverse to the right child. */
			else if (pNodeIterator->getSize() == eNodeSize::threeNode &&
				TCompare(pKey, pNodeIterator->getBigKey()) == GREATER ||
				(pNodeIterator->getSize() == eNodeSize::twoNode &&
					TCompare(pKey, pNodeIterator->getSmallKey()) == GREATER))
			{
				eSearchDirection = rightChild;
			}
			/* Else traverse to the middle child. */
			else
			{
				eSearchDirection = middleChild;
			}

			/* Move to child. */
			if (*bFound == false && pNodeIterator->getChild(eSearchDirection) == 0)
			{
				*ppNodeFound = pNodeIterator;
				iReturnCode = SUCCESS;
			}
			else if (*bFound == false)
			{
				pNodeIterator = pNodeIterator->getChild(eSearchDirection);
			}
		} while (*ppNodeFound == 0);
	}
	return iReturnCode;
}

/** @brief      Member function taking two arguments and returning an error code.
 *              Function adds a key value to an empty or a two node.
 *  @param[in]  pNode: address of node to which the key value will be added.
 *  @param[in]  pKey: address of key value which will be added to node.
 *  @return     SUCCESS when no error encountered.
 */
template<class T>
int CTree<T>::add(CNode<T>* const pNode,
	const T* const pKey)
{
	int iReturnCode = FAILURE;
	eNodeSize eSize = pNode->getSize();

	if (eSize == eNodeSize::empty)
	{
		pNode->setSmallKey(pKey);
		iReturnCode = SUCCESS;
	}
	else if (eSize == eNodeSize::twoNode && TCompare(pKey, pNode->getSmallKey()) == GREATER)
	{
		pNode->setBigKey(pKey);
		iReturnCode = SUCCESS;
	}
	else if (eSize == eNodeSize::twoNode && TCompare(pKey, pNode->getSmallKey()) == LESS)
	{
		pNode->setBigKey(pNode->getSmallKey());
		pNode->setSmallKey(pKey);
		iReturnCode = SUCCESS;
	}

	return iReturnCode;
}

/** @brief        Member function taking three arguments and returning an error code.
 *                Function splits a three node in order to add a key.
 *                Node Splitting can propagate all the way up to the root node.
 *                Due to this propagation effect a key value will be written to address pKey.
 * @param[in/out] pKey: address of key value which will be added to three node.
 * @param[in/out] pNode2Split: address of three node to which the key will be added.
 * @param[in/out] ppAddedNode: address of node pointer to newly created node.
 * @return        SUCCESS when no error encountered.
 */
template<class T>
int CTree<T>::split(T* const pKey,
	CNode<T>* const pNode2Split,
	CNode<T>** ppAddedNode)
{
	int iReturnCode = FAILURE;
	CNode<T>* pNode = 0;

	if (pNode2Split == 0)
	{
		iReturnCode = IS_EMPTY;
	}
	else
	{
		/* Three ways to split a node, depending on key value. */
		if (TCompare(pKey, pNode2Split->getBigKey()) == GREATER)
		{
			pNode = new CNode<T>(pNode2Split->getChild(leftChild),
				pNode2Split->getChild(middleChild),
				pNode2Split->getSmallKey());
			pNode2Split->setSmallKey(pKey);
			*pKey = *pNode2Split->getBigKey();
			pNode2Split->setChild(leftChild, *ppAddedNode);
			iReturnCode = SUCCESS;
		}
		else if (TCompare(pKey, pNode2Split->getSmallKey()) == LESS)
		{
			pNode = new CNode<T>(*ppAddedNode,
				pNode2Split->getChild(leftChild),
				pKey);
			*pKey = *pNode2Split->getSmallKey();
			pNode2Split->setSmallKey(pNode2Split->getBigKey());
			pNode2Split->setChild(leftChild, pNode2Split->getChild(middleChild));
			iReturnCode = SUCCESS;
		}
		else /* Split in the middle. */
		{
			pNode = new CNode<T>(pNode2Split->getChild(leftChild),
				*ppAddedNode,
				pNode2Split->getSmallKey());
			pNode2Split->setSmallKey(pNode2Split->getBigKey());
			pNode2Split->setChild(leftChild, pNode2Split->getChild(middleChild));
			iReturnCode = SUCCESS;
		}

		pNode2Split->setBigKey(0);
		pNode2Split->setChild(middleChild, 0);
		*ppAddedNode = pNode;
	}
	return iReturnCode;
}

/** @brief        Member function taking one arguments and returning the address of a node.
 *                Function finds and returns the node with the smallest key value for a given tree entry.
 *  @param[in]    pNode: node address of tree entry (where search starts from).
 *  @return       address of a node holding smallest key value.
 */
template<class T>
CNode<T>* CTree<T>::getMinNode(CNode<T>* pNode) const
{
	CNode<T>* pNodeIterator = pNode;
	while (pNodeIterator->getChild(leftChild) != 0)
	{
		pNodeIterator = pNodeIterator->getChild(leftChild);
	}
	return pNodeIterator;
}

/** @brief        Member function taking one arguments and returning the address of a node.
 *                Function finds and returns the node with the largest key value for a given tree entry.
 *  @param[in]    pNode: node address of tree entry (where search starts from).
 *  @return       address of a node holding largest key value.
 */
template<class T>
CNode<T>* CTree<T>::getMaxNode(CNode<T>* pNode) const
{
	CNode<T>* pNodeIterator = pNode;
	while (pNodeIterator->getChild(rightChild) != 0)
	{
		pNodeIterator = pNodeIterator->getChild(rightChild);
	}
	return pNodeIterator;
}

/** @brief        Member function taking one arguments and returning an error code.
 *                Function deletes the specified key value from tree.
 *  @param[in]    pKey: address of key value which needs to be deleted from tree.
 *  @return       SUCCESS when no error encountered.
 */
template<class T>
int CTree<T>::deleteItem(const T* const pKey)
{
	CNode<T>* pNode = 0;
	CNode<T>* pNextNode2Fix = 0;
	int iReturnCode = FAILURE;
	bool bTreeIsFixed = false;
	bool bFound = false;

	if (m_pRoot == 0) /* Tree is empty*/
	{
		iReturnCode = IS_EMPTY;
	}
	else /* Find key value. */
	{
		iReturnCode = search(pKey, &pNode, &bFound);
	}

	/* Key not found in Tree. */
	if (iReturnCode == SUCCESS && !bFound)
	{
		iReturnCode = NOT_FOUND;
	}

	/* Key found in Tree. */
	if (iReturnCode == SUCCESS)
	{
		/* If pNode is internal node swap with in order successor. */
		if (!pNode->isLeaf())
		{
			iReturnCode = swapWithInOrderSuccessor(pNode, pKey, &pNode);
		}

		/* Leaf is three node, delete is straightforward. */
		if (iReturnCode == SUCCESS && pNode->getSize() == eNodeSize::threeNode)
		{
			iReturnCode = removeFromLeaf(pNode, pKey);
		}
		else if (iReturnCode == SUCCESS) /* Delete can propagate up to the root. */
		{
			do
			{
				if (pNode == m_pRoot)
				{
					m_pRoot = pNode->getChild(leftChild);
					/* If tree is empty, no need to reset parent root. */
					if (m_pRoot != 0)
					{
						m_pRoot->setParent(0);
					}
					delete pNode;
					bTreeIsFixed = true;
				}
				/* Check if local rotation is possible. */
				/* Check if global rotation is possible. */
				/* Check if local node merger is possible. */
				else if (localRotation(pNode) == SUCCESS ||
					globalRotation(pNode) == SUCCESS ||
					localNodeMerger(pNode) == SUCCESS)
				{
					bTreeIsFixed = true;
				}
				else if (globalNodeMerger(pNode, &pNextNode2Fix) == SUCCESS)
				{
					pNode = pNextNode2Fix;
					iReturnCode = SUCCESS;
				}
				else
				{
					iReturnCode = FAILURE;
				}
			} while (!bTreeIsFixed && iReturnCode == SUCCESS);
		}
	}
	return iReturnCode;
}

/** @brief     Member function taking two arguments and returning an error code.
 *             Function deletes the specified key value from the specified three node.
 *             Delete is straightforward.
 * @param[in]  pNode: address of three node containing key value to be deleted.
 * @param[in]  pKey: address of key value to be deleted.
 * @return     SUCCESS when no error encountered.
 */
template<class T>
int CTree<T>::removeFromLeaf(CNode<T>* pNode,
	const T* const pKey)
{
	int iReturnCode = FAILURE;

	if (pNode == 0)
	{
		iReturnCode = IS_EMPTY;
	}
	else
	{
		if (TCompare(pKey, pNode->getSmallKey()) == EQUAL)
		{
			pNode->setSmallKey(pNode->getBigKey());
			pNode->setBigKey(0);
			iReturnCode = SUCCESS;
		}
		else if (TCompare(pKey, pNode->getBigKey()) == EQUAL)
		{
			pNode->setBigKey(0);
			iReturnCode = SUCCESS;
		}
	}
	return iReturnCode;
}

/** @brief     Member function taking one arguments and returning an error code.
 *             Function checks if a local tree rotation is possible. If so the specified
 *             node will be deleted and a local tree rotation will be performed to fix the tree.
 * @param[in]  pNode: address of node to be deleted.
 * @return     SUCCESS when no error encountered and local rotation is possible.
 */
template<class T>
int CTree<T>::localRotation(CNode<T>* pNode)
{
	CNode<T>* pParentNode = 0;
	CNode<T>* pRightNode = 0;
	CNode<T>* pMiddleNode = 0;
	CNode<T>* pLeftNode = 0;
	int iReturnCode = FAILURE;

	if (pNode == 0)
	{
		iReturnCode = IS_EMPTY;
	}
	else
	{
		pParentNode = pNode->getParent();
		pRightNode = pParentNode->getChild(rightChild);
		pMiddleNode = pParentNode->getChild(middleChild);
		pLeftNode = pParentNode->getChild(leftChild);
		/* Case 1: Take from right. */
		if (pNode == pLeftNode &&
			pParentNode->getSize() == eNodeSize::twoNode &&
			pRightNode->getSize() == eNodeSize::threeNode)
		{
			pLeftNode->setSmallKey(pParentNode->getSmallKey());
			pLeftNode->setChild(rightChild, pRightNode->getChild(leftChild));
			pParentNode->setSmallKey(pRightNode->getSmallKey());
			pRightNode->setSmallKey(pRightNode->getBigKey());
			pRightNode->setBigKey(0);
			pRightNode->setChild(leftChild, pRightNode->getChild(middleChild));
			pRightNode->setChild(middleChild, 0);
			iReturnCode = SUCCESS;
		}
		/* Case 2: Take from middle first. */
		else if (pNode == pLeftNode &&
			pParentNode->getSize() == eNodeSize::threeNode &&
			pMiddleNode->getSize() == eNodeSize::threeNode)
		{
			pLeftNode->setSmallKey(pParentNode->getSmallKey());
			pLeftNode->setChild(rightChild, pMiddleNode->getChild(leftChild));
			pParentNode->setSmallKey(pMiddleNode->getSmallKey());
			pMiddleNode->setSmallKey(pMiddleNode->getBigKey());
			pMiddleNode->setBigKey(0);
			pMiddleNode->setChild(leftChild, pMiddleNode->getChild(middleChild));
			pMiddleNode->setChild(middleChild, 0);
			iReturnCode = SUCCESS;
		}
		/* Case 3: Take from right. */
		else if (pNode == pLeftNode &&
			pParentNode->getSize() == eNodeSize::threeNode &&
			pRightNode->getSize() == eNodeSize::threeNode)
		{
			pLeftNode->setSmallKey(pParentNode->getSmallKey());
			pLeftNode->setChild(rightChild, pMiddleNode->getChild(leftChild));
			pParentNode->setSmallKey(pMiddleNode->getSmallKey());
			pMiddleNode->setSmallKey(pParentNode->getBigKey());
			pMiddleNode->setChild(leftChild, pMiddleNode->getChild(rightChild));
			pMiddleNode->setChild(rightChild, pRightNode->getChild(leftChild));
			pParentNode->setBigKey(pRightNode->getSmallKey());
			pRightNode->setSmallKey(pRightNode->getBigKey());
			pRightNode->setBigKey(0);
			pRightNode->setChild(leftChild, pRightNode->getChild(middleChild));
			pRightNode->setChild(middleChild, 0);
			iReturnCode = SUCCESS;
		}
		/* Case 4: Take from right first. */
		else if (pNode == pMiddleNode &&
			pRightNode->getSize() == eNodeSize::threeNode)
		{
			pMiddleNode->setSmallKey(pParentNode->getBigKey());
			pMiddleNode->setChild(rightChild, pRightNode->getChild(leftChild));
			pParentNode->setBigKey(pRightNode->getSmallKey());
			pRightNode->setSmallKey(pRightNode->getBigKey());
			pRightNode->setBigKey(0);
			pRightNode->setChild(leftChild, pRightNode->getChild(middleChild));
			pRightNode->setChild(middleChild, 0);
			iReturnCode = SUCCESS;
		}
		/* Case 5: Take from left. */
		else if (pNode == pMiddleNode &&
			pLeftNode->getSize() == eNodeSize::threeNode)
		{
			pMiddleNode->setSmallKey(pParentNode->getSmallKey());
			pMiddleNode->setChild(rightChild, pMiddleNode->getChild(leftChild));
			pMiddleNode->setChild(leftChild, pLeftNode->getChild(rightChild));
			pParentNode->setSmallKey(pLeftNode->getBigKey());
			pLeftNode->setBigKey(0);
			pLeftNode->setChild(rightChild, pLeftNode->getChild(middleChild));
			pLeftNode->setChild(middleChild, 0);
			iReturnCode = SUCCESS;
		}
		/* Case 6: Take from left. */
		if (pNode == pRightNode &&
			pParentNode->getSize() == eNodeSize::twoNode &&
			pLeftNode->getSize() == eNodeSize::threeNode)
		{
			pRightNode->setSmallKey(pParentNode->getSmallKey());
			pRightNode->setChild(rightChild, pRightNode->getChild(leftChild));
			pRightNode->setChild(leftChild, pLeftNode->getChild(rightChild));
			pParentNode->setSmallKey(pLeftNode->getBigKey());
			pLeftNode->setBigKey(0);
			pLeftNode->setChild(rightChild, pLeftNode->getChild(middleChild));
			pLeftNode->setChild(middleChild, 0);
			iReturnCode = SUCCESS;
		}
		/* Case 7: Take from middle. */
		else if (pNode == pRightNode &&
			pParentNode->getSize() == eNodeSize::threeNode &&
			pMiddleNode->getSize() == eNodeSize::threeNode)
		{
			pRightNode->setSmallKey(pParentNode->getBigKey());
			pRightNode->setChild(rightChild, pRightNode->getChild(leftChild));
			pRightNode->setChild(leftChild, pMiddleNode->getChild(rightChild));
			pParentNode->setBigKey(pMiddleNode->getBigKey());
			pMiddleNode->setBigKey(0);
			pMiddleNode->setChild(rightChild, pMiddleNode->getChild(middleChild));
			pMiddleNode->setChild(middleChild, 0);
			iReturnCode = SUCCESS;
		}
		/* Case 8: Take from left. */
		else if (pNode == pRightNode &&
			pParentNode->getSize() == eNodeSize::threeNode &&
			pLeftNode->getSize() == eNodeSize::threeNode)
		{
			pRightNode->setSmallKey(pParentNode->getBigKey());
			pRightNode->setChild(rightChild, pRightNode->getChild(leftChild));
			pRightNode->setChild(leftChild, pMiddleNode->getChild(rightChild));
			pParentNode->setBigKey(pMiddleNode->getSmallKey());
			pMiddleNode->setSmallKey(pParentNode->getSmallKey());
			pMiddleNode->setChild(rightChild, pMiddleNode->getChild(leftChild));
			pMiddleNode->setChild(leftChild, pLeftNode->getChild(rightChild));
			pParentNode->setSmallKey(pLeftNode->getBigKey());
			pLeftNode->setBigKey(0);
			pLeftNode->setChild(rightChild, pLeftNode->getChild(middleChild));
			pLeftNode->setChild(middleChild, 0);
			iReturnCode = SUCCESS;
		}
	}
	return iReturnCode;
}

/** @brief     Member function taking one arguments and returning an error code.
 *             Function checks if a global tree rotation is possible. If so the specified
 *             node will be deleted and a global tree rotation will be performed to fix the tree.
 * @param[in]  pNode: address of node to be deleted.
 * @return     SUCCESS when no error encountered and global rotation is possible.
 */
template<class T>
int CTree<T>::globalRotation(CNode<T>* pNode)
{
	CNode<T>* pRightMinNode = 0;
	CNode<T>* pLeftMaxNode = 0;
	CNode<T>* pMiddleMinNode = 0;
	CNode<T>* pMiddleMaxNode = 0;
	int iReturnCode = FAILURE;

	if (pNode == 0)
	{
		iReturnCode = IS_EMPTY;
	}
	else
	{
		/* Leftmost child of the right child of the root. */
		pRightMinNode = getMinNode(m_pRoot->getChild(rightChild));
		/* Rightmost child of the left child of the root. */
		pLeftMaxNode = getMaxNode(m_pRoot->getChild(leftChild));
		/* Four rotations around root possible. */
		if (m_pRoot->getSize() == eNodeSize::threeNode)
		{
			/* Leftmost child of the middle child of the root. */
			pMiddleMinNode = getMinNode(m_pRoot->getChild(middleChild));
			/* Rightmost child of the middle child of the root. */
			pMiddleMaxNode = getMaxNode(m_pRoot->getChild(middleChild));
			/* Case 9: Take from leftmost child of the middle child of the root. */
			if (pNode == pLeftMaxNode &&
				pMiddleMinNode->getSize() == eNodeSize::threeNode)
			{
				pLeftMaxNode->setSmallKey(m_pRoot->getSmallKey());
				m_pRoot->setSmallKey(pMiddleMinNode->getSmallKey());
				pMiddleMinNode->setSmallKey(pMiddleMinNode->getBigKey());
				pMiddleMinNode->setBigKey(0);
				iReturnCode = SUCCESS;
			}
			/* Case 10: Take from rightmost child of the left child of the root. */
			else if (pNode == pMiddleMinNode &&
				pLeftMaxNode->getSize() == eNodeSize::threeNode)
			{
				pMiddleMinNode->setSmallKey(m_pRoot->getSmallKey());
				m_pRoot->setSmallKey(pLeftMaxNode->getBigKey());
				pLeftMaxNode->setBigKey(0);
				iReturnCode = SUCCESS;
			}
			/* Case 11: Take from leftmost child of the right child of the root. */
			else if (pNode == pMiddleMaxNode &&
				pRightMinNode->getSize() == eNodeSize::threeNode)
			{
				pMiddleMaxNode->setSmallKey(m_pRoot->getBigKey());
				m_pRoot->setBigKey(pRightMinNode->getSmallKey());
				pRightMinNode->setSmallKey(pRightMinNode->getBigKey());
				pRightMinNode->setBigKey(0);
				iReturnCode = SUCCESS;
			}
			/* Case 12: Take from rightmost child of the middle child of the root. */
			else if (pNode == pRightMinNode &&
				pMiddleMaxNode->getSize() == eNodeSize::threeNode)
			{
				pRightMinNode->setSmallKey(m_pRoot->getBigKey());
				m_pRoot->setBigKey(pMiddleMaxNode->getBigKey());
				pMiddleMaxNode->setBigKey(0);
				iReturnCode = SUCCESS;
			}
		}
		else /* TWO_NODE: Two rotations around root possible. */
		{
			/* Case 13: Take from rightmost child of the left child of the root. */
			if (pNode == pRightMinNode &&
				pLeftMaxNode->getSize() == eNodeSize::threeNode)
			{
				pRightMinNode->setSmallKey(m_pRoot->getSmallKey());
				m_pRoot->setSmallKey(pLeftMaxNode->getBigKey());
				pLeftMaxNode->setBigKey(0);
				iReturnCode = SUCCESS;
			}
			/* Case 14: Take from leftmost child of the right child of the root. */
			else if (pNode == pLeftMaxNode &&
				pRightMinNode->getSize() == eNodeSize::threeNode)
			{
				pLeftMaxNode->setSmallKey(m_pRoot->getSmallKey());
				m_pRoot->setSmallKey(pRightMinNode->getSmallKey());
				pRightMinNode->setSmallKey(pRightMinNode->getBigKey());
				pRightMinNode->setBigKey(0);
				iReturnCode = SUCCESS;
			}
		}
	}
	return iReturnCode;
}

/** @brief     Member function taking one arguments and returning an error code.
 *             Function checks if a local node merger is possible. If so the specified
 *             node will be deleted and a local node merger will be performed to fix the tree.
 * @param[in]  pNode: address of node to be deleted.
 * @return     SUCCESS when no error encountered and local node merger is possible.
 */
template<class T>
int CTree<T>::localNodeMerger(CNode<T>* pNode)
{
	CNode<T>* pParentNode = 0;
	CNode<T>* pRightNode = 0;
	CNode<T>* pMiddleNode = 0;
	CNode<T>* pLeftNode = 0;
	int iReturnCode = FAILURE;

	if (pNode == 0)
	{
		iReturnCode = IS_EMPTY;
	}
	else
	{
		pParentNode = pNode->getParent();
		pRightNode = pParentNode->getChild(rightChild);
		pMiddleNode = pParentNode->getChild(middleChild);
		pLeftNode = pParentNode->getChild(leftChild);

		if (pNode == pLeftNode &&
			pParentNode->getSize() == eNodeSize::threeNode) /* Case 15: Merge to the left. */
		{
			pLeftNode->setSmallKey(pParentNode->getSmallKey());
			pLeftNode->setBigKey(pMiddleNode->getSmallKey());
			pLeftNode->setChild(middleChild, pMiddleNode->getChild(leftChild));
			pLeftNode->setChild(rightChild, pMiddleNode->getChild(rightChild));
			pParentNode->setSmallKey(pParentNode->getBigKey());
			pParentNode->setBigKey(0);
			pParentNode->setChild(middleChild, 0);
			delete pMiddleNode;
			iReturnCode = SUCCESS;
		}
		else if (pNode == pMiddleNode &&
			pParentNode->getSize() == eNodeSize::threeNode) /* Case 16: Merge to the left. */
		{
			pLeftNode->setBigKey(pParentNode->getSmallKey());
			pLeftNode->setChild(middleChild, pLeftNode->getChild(rightChild));
			pLeftNode->setChild(rightChild, pMiddleNode->getChild(leftChild));
			pParentNode->setSmallKey(pParentNode->getBigKey());
			pParentNode->setBigKey(0);
			pParentNode->setChild(middleChild, 0);
			delete pMiddleNode;
			iReturnCode = SUCCESS;
		}
		else if (pNode == pRightNode &&
			pParentNode->getSize() == eNodeSize::threeNode) /* Case 17: Merge to the right. */
		{
			pRightNode->setSmallKey(pMiddleNode->getSmallKey());
			pRightNode->setBigKey(pParentNode->getBigKey());
			pRightNode->setChild(rightChild, pRightNode->getChild(leftChild));
			pRightNode->setChild(middleChild, pMiddleNode->getChild(rightChild));
			pRightNode->setChild(leftChild, pMiddleNode->getChild(leftChild));
			pParentNode->setBigKey(0);
			pParentNode->setChild(middleChild, 0);
			delete pMiddleNode;
			iReturnCode = SUCCESS;
		}
	}
	return iReturnCode;
}

/** @brief     Member function taking one arguments and returning an error code.
 *             Function checks if a global node merger is possible. If so the specified
 *             node will be deleted and a global node merger will be performed to fix the tree.
 * @param[in]  pNode: address of node to be deleted.
 * @param[out] ppNextNode2Fix: pointer to node pointer which points to the next node to fix, because node merger can propagate.
 * @return     SUCCESS when no error encountered and global node merger is possible.
 */
template<class T>
int CTree<T>::globalNodeMerger(CNode<T>* pNode, CNode<T>** ppNextNode2Fix)
{
	CNode<T>* pParentNode = 0;
	CNode<T>* pRightNode = 0;
	CNode<T>* pLeftNode = 0;
	int iReturnCode = FAILURE;
	*ppNextNode2Fix = 0;

	if (pNode == 0)
	{
		iReturnCode = IS_EMPTY;
	}
	else
	{
		pParentNode = pNode->getParent();
		pRightNode = pParentNode->getChild(rightChild);
		pLeftNode = pParentNode->getChild(leftChild);

		/* Case 18: Node merger propagates. */
		if (pNode == pLeftNode)
		{
			pLeftNode->setSmallKey(pParentNode->getSmallKey());
			pLeftNode->setBigKey(pRightNode->getSmallKey());
			pLeftNode->setChild(middleChild, pRightNode->getChild(leftChild));
			pLeftNode->setChild(rightChild, pRightNode->getChild(rightChild));
			pParentNode->setSmallKey(0);
			pParentNode->setChild(rightChild, 0);
			delete pRightNode;
			*ppNextNode2Fix = pParentNode;
			iReturnCode = SUCCESS;
		}
		/* Case 19: Node merger propagates. */
		else if (pNode == pRightNode)
		{
			pLeftNode->setBigKey(pParentNode->getSmallKey());
			pLeftNode->setChild(middleChild, pLeftNode->getChild(rightChild));
			pLeftNode->setChild(rightChild, pRightNode->getChild(leftChild));
			pParentNode->setChild(rightChild, 0);
			pParentNode->setSmallKey(0);
			delete pRightNode;
			*ppNextNode2Fix = pParentNode;
			iReturnCode = SUCCESS;
		}
	}
	return iReturnCode;
}

/** @brief     Member function taking three arguments and returning an error code.
 *             Function swaps an internal key value with its inorder successor.
 *             Inorder successor of an internal key is always located in a leaf node.
 * @param[in]  pNode: node pointer to an internal node containing key value to be swapped.
 * @param[in]  pKey: address of key value to be swapped with its inorder successor.
 * @param[out] ppLeafNode: pointer to node pointer which points to a leaf node containing pKey value after swap.
 * @return     SUCCESS when no error encountered.
 */
template<class T>
int CTree<T>::swapWithInOrderSuccessor(CNode<T>* pNode,
	const T* const pKey,
	CNode<T>** ppLeafNode)
{
	int iReturnCode = FAILURE;
	CNode<T>* pLeafNode = 0;
	T tLeafKey = *pKey;
	*ppLeafNode = 0;

	if (pNode == 0)
	{
		iReturnCode = IS_EMPTY;
	}
	else /* Swap key with in order successor */
	{
		pLeafNode = getNextInorderKey(pNode, &tLeafKey);
		/* Successor internal node is always smallest value leafnode. */
		if (TCompare(pKey, pNode->getSmallKey()) == EQUAL)
		{
			pLeafNode->setSmallKey(pKey);
			pNode->setSmallKey(&tLeafKey);
			*ppLeafNode = pLeafNode;
			iReturnCode = SUCCESS;
		}
		else if (TCompare(pKey, pNode->getBigKey()) == EQUAL)
		{
			pLeafNode->setSmallKey(pKey);
			pNode->setBigKey(&tLeafKey);
			*ppLeafNode = pLeafNode;
			iReturnCode = SUCCESS;
		}
	}
	return iReturnCode;
}

/** @brief     Member function taking two arguments and returning an error code.
 *             Function traverses the tree and prints the objects present in tree using the specified print function.
 *             Three traversal ways implemented [inorder, postorder, preorder].
 * @param[in]  eTraversalMethod: enum traversal type [inOrder, postOrder, preOrder].
 * @param[out] pNrOfItemsPrinted: int Nr of objects in tree.
 * @return     SUCCESS when no error encountered.
 */
template<class T>
int CTree<T>::print(eTreeTraversal eTraversalMethod, int *pNrOfItemsPrinted) const
{
	int iReturnCode = FAILURE;
	CNode<T>* (CTree<T>::*pTraversalFunc)(CNode<T>* pNode, T* pKey) const = 0;
	CNode<T>* pNodeIterator = 0;
	T tKey;
	int iItemCnt = 0;
	*pNrOfItemsPrinted = 0;

	if (m_pRoot == 0)
	{
		iReturnCode = IS_EMPTY;
	}
	else
	{
		if (eTraversalMethod == inorder)
		{
			pNodeIterator = getMinNode(m_pRoot);
			tKey = *pNodeIterator->getSmallKey();
			pTraversalFunc = &CTree<T>::getNextInorderKey;
		}
		else if (eTraversalMethod == preorder)
		{
			pNodeIterator = m_pRoot;
			tKey = *pNodeIterator->getSmallKey();
			pTraversalFunc = &CTree<T>::getNextPreorderKey;
		}
		else if (eTraversalMethod == postorder)
		{
			pNodeIterator = getMinNode(m_pRoot);
			tKey = *pNodeIterator->getSmallKey();
			pTraversalFunc = &CTree<T>::getNextPostorderKey;
		}

		do
		{
			iItemCnt++;
			std::cout << tKey << std::endl;
			if (pTraversalFunc != 0)
			{
				pNodeIterator = (this->*pTraversalFunc)(pNodeIterator, &tKey);
			}
		} while (pNodeIterator != 0);
	}
	*pNrOfItemsPrinted = iItemCnt;
	return iReturnCode;
}

/** @brief        Member function taking two arguments and returning address of next inorder node.
 *                Function for inorder traversing the tree. Function gets the next
 *                inorder key relative to pNode and pKey. The next inorder key value
 *                will be written to address pKey and next inorder node address will be returned.
 * @param[in/out] pNode: address of inorder node.
 * @param[in/out] pKey: address of inorder key value.
 * @return        address of next inorder node, returns 0 if no more inorder successors.
 */
template<class T>
CNode<T>* CTree<T>::getNextInorderKey(CNode<T>* pNode, T* pKey) const
{
	CNode<T>* pNodeIterator = pNode;
	bool bFinished = false;

	if (pNodeIterator->getSize() == eNodeSize::threeNode &&
		TCompare(pKey, pNodeIterator->getSmallKey()) == EQUAL)
	{
		if (pNodeIterator->isLeaf())
		{
			*pKey = *pNodeIterator->getBigKey();
		}
		else
		{
			pNodeIterator = getMinNode(pNodeIterator->getChild(middleChild));
			*pKey = *pNodeIterator->getSmallKey();
		}
	}
	else if (!pNodeIterator->isLeaf() &&
		((pNodeIterator->getSize() == eNodeSize::twoNode &&
			TCompare(pKey, pNodeIterator->getSmallKey()) == EQUAL) ||
			(pNodeIterator->getSize() == eNodeSize::threeNode &&
				TCompare(pKey, pNodeIterator->getBigKey()) == EQUAL)))
	{
		pNodeIterator = getMinNode(pNodeIterator->getChild(rightChild));
		*pKey = *pNodeIterator->getSmallKey();
	}
	else
	{
		do
		{
			pNodeIterator = pNodeIterator->getParent();
			if (pNodeIterator == 0)
			{
				bFinished = true;
			}
			else if (TCompare(pKey, pNodeIterator->getSmallKey()) == LESS)
			{
				*pKey = *pNodeIterator->getSmallKey();
				bFinished = true;
			}
			else if (pNodeIterator->getSize() == eNodeSize::threeNode &&
				TCompare(pKey, pNodeIterator->getBigKey()) == LESS)
			{
				*pKey = *pNodeIterator->getBigKey();
				bFinished = true;
			}
		} while (bFinished == false);
	}
	return pNodeIterator;
}

/** @brief        Member function taking two arguments and returning address of next postorder node.
 *                Function for postorder traversing the tree. Function gets the next
 *                postorder key relative to pNode and pKey. The next postorder key value
 *                will be written to address pKey and next postorder node address will be returned.
 * @param[in/out] pNode: address of postorder node.
 * @param[in/out] pKey: address of postorder key value.
 * @return        address of next postorder node, returns 0 if no more postorder successors.
 */
template<class T>
CNode<T>* CTree<T>::getNextPostorderKey(CNode<T>* pNode, T* pKey) const
{
	CNode<T>* pNodeIterator = pNode;
	CNode<T>* pChildNode = pNode;

	if (pNodeIterator->getSize() == eNodeSize::threeNode &&
		TCompare(pKey, pNodeIterator->getSmallKey()) == EQUAL)
	{
		if (pNodeIterator->isLeaf())
		{
			*pKey = *pNodeIterator->getBigKey();
		}
		else
		{
			pNodeIterator = getMinNode(pNodeIterator->getChild(rightChild));
			*pKey = *pNodeIterator->getSmallKey();
		}
	}
	else if ((pNodeIterator = pNodeIterator->getParent()) != 0)
	{
		if (pNodeIterator->getSize() == eNodeSize::twoNode)
		{
			if (pNodeIterator->getChild(leftChild) == pChildNode)
			{
				pNodeIterator = getMinNode(pNodeIterator->getChild(rightChild));
				*pKey = *pNodeIterator->getSmallKey();
			}
			else if (pNodeIterator->getChild(rightChild) == pChildNode)
			{
				*pKey = *pNodeIterator->getSmallKey();
			}
		}
		else if (pNodeIterator->getSize() == eNodeSize::threeNode)
		{
			if (pNodeIterator->getChild(leftChild) == pChildNode)
			{
				pNodeIterator = getMinNode(pNodeIterator->getChild(middleChild));
				*pKey = *pNodeIterator->getSmallKey();
			}
			else if (pNodeIterator->getChild(middleChild) == pChildNode)
			{
				*pKey = *pNodeIterator->getSmallKey();
			}
			else if (pNodeIterator->getChild(rightChild) == pChildNode)
			{
				*pKey = *pNodeIterator->getBigKey();
			}
		}
	}
	return pNodeIterator;
}

/** @brief        Member function taking two arguments and returning address of next postorder node.
 *                Function for preorder traversing the tree. Function gets the next
 *                preorder key relative to pNode and pKey. The next preorder key value
 *                will be written to address pKey and next preorder node address will be returned.
 * @param[in/out] pNode: address of preorder node.
 * @param[in/out] pKey: address of preorder key value.
 * @return        address of next preorder node, returns 0 if no more postorder successors.
 */
template<class T>
CNode<T>* CTree<T>::getNextPreorderKey(CNode<T>* pNode, T* pKey) const
{
	CNode<T>* pNodeIterator = pNode;
	CNode<T>* pPrevNode = pNode;

	if (pNodeIterator->getSize() == eNodeSize::threeNode &&
		TCompare(pKey, pNodeIterator->getSmallKey()) == EQUAL &&
		pNodeIterator->isLeaf())
	{
		*pKey = *pNodeIterator->getBigKey();
	}
	else if (TCompare(pKey, pNodeIterator->getSmallKey()) == EQUAL &&
		!pNodeIterator->isLeaf())
	{
		pNodeIterator = pNodeIterator->getChild(leftChild);
		*pKey = *pNodeIterator->getSmallKey();
	}
	else if (TCompare(pKey, pNodeIterator->getBigKey()) == EQUAL &&
		!pNodeIterator->isLeaf())
	{
		pNodeIterator = pNodeIterator->getChild(middleChild);
		*pKey = *pNodeIterator->getSmallKey();
	}
	else
	{
		while ((pNodeIterator = pNodeIterator->getParent()) != 0 &&
			pNodeIterator->getChild(rightChild) == pPrevNode)
		{
			pPrevNode = pNodeIterator;
		}

		if (pNodeIterator != 0)
		{
			if ((pNodeIterator->getSize() == eNodeSize::twoNode &&
				pNodeIterator->getChild(leftChild) == pPrevNode) ||
				(pNodeIterator->getSize() == eNodeSize::threeNode &&
					pNodeIterator->getChild(middleChild) == pPrevNode))
			{
				pNodeIterator = pNodeIterator->getChild(rightChild);
				*pKey = *pNodeIterator->getSmallKey();
			}
			else if (pNodeIterator->getChild(leftChild) == pPrevNode &&
				pNodeIterator->getSize() == eNodeSize::threeNode)
			{
				*pKey = *pNodeIterator->getBigKey();
			}
		}
	}
	return pNodeIterator;
}

/** @brief     Member function taking two argument and returning an int.
 *             Function compares the value of *pT1 and *pT1. Function returns EQUAL if
 *             *pT1 and *pT2 are equal. If *pT1 > *pT2 function returns GREATER.
 *             If *pT1 < *pT2 function returns LESS.
 *             Comparison of object can be accomplished by overloading the < operator in the template class.
 * @param[in] pT1: Address of first key value used in comparison.
 * @param[in] pT2: Address of second key value used in comparison.
 * @return if *pT1 == *pT1 returns EQUAL, if *pT1 > *pT2 returns GREATER
 *         if *pT1 < *pT2 returns LESS.
 */
template<class T>
int CTree<T>::TCompare(const T* const pT1, const T* const pT2) const
{
	int iReturnCode = FAILURE;

	if (*pT1 < *pT2)
	{
		iReturnCode = LESS;
	}
	else if (*pT2 < *pT1)
	{
		iReturnCode = GREATER;
	}
	else
	{
		iReturnCode = EQUAL;
	}

	return iReturnCode;
}