#pragma once
#include "Queue.h"

#include "BSTNode.h"

template <class T>
class BNTree
{
private:
	BSTNode <T> *root;
protected:
	//------------------------------------------------------------
	// Protected Utility Methods Section:
	// Recursive helper methods for the public methods.
	//------------------------------------------------------------
	int getHeightHelper(BSTNode<T>* subTreePtr) const;
	int getNumberOfNodesHelper(BSTNode<T>* subTreePtr) const;
	// Recursively deletes all nodes from the tree.
	void destroyTree(BSTNode<T>* subTreePtr);
	// Recursively adds a new node to the tree in a based on item defined key
	// which is used in the items '>' operator.
	BSTNode<T>* addByItemKey(BSTNode<T>* subTreePtr, BSTNode<T>* newNodePtr);
	// Removes the target value from the tree by calling moveValuesUpTree
	// to overwrite value with value from child.
	BSTNode<T>* removeValue(BSTNode<T>* subTreePtr, const T target, bool& success);
	// Removes given node from tree while maintaining BST.
	BSTNode<T>* removeNode(BSTNode<T>* targetNode);
	// Removes leftmode node in left subtree of tagetNode.
	BSTNode<T>* removeLeftmostNode(BSTNode<T>* targetNode, T & data);
	// Recursively searches for target value in the tree by using a
	// preorder traversal.
	BSTNode<T>*findNode(BSTNode<T>* treePtr, T& target) const;
	// Copies the tree rooted at treePtr and returns a pointer to
	// the copy.
	BSTNode<T>* copyTree(const BSTNode<T>* treePtr) const;
	// Recursive traversal helper methods:
	void preorder(void visit(T&), BSTNode<T>* treePtr) const;
	void inorder(void visit(T&), BSTNode<T>* treePtr) const;
	void postorder(void visit(T&), BSTNode<T>* treePtr) const;
	void breadthfirst(void visit(T&), BSTNode<T>* treePtr) const;

public:
	//------------------------------------------------------------
	// Constructor and Destructor Section.
	//------------------------------------------------------------
	BNTree();
	BNTree(const T& rootItem);
	BNTree(const T& rootItem, const BNTree<T>* leftTreePtr, const BNTree<T>* rightTreePtr);
	BNTree(const BNTree<T>& tree);
	virtual ~BNTree();
	//------------------------------------------------------------
	// Public BinaryTreeInterface Methods Section.
	//------------------------------------------------------------
	bool isEmpty() const;
	int getHeight() const;
	int getNumberOfNodes() const;
	bool add(const T& newData); // Adds a node
	T find(T & recordByKey); // Finds a node
	bool remove(const T& data); // Removes a node
	bool contains(T& anEntry) const;
	//------------------------------------------------------------
	// Public Traversals Section.
	//------------------------------------------------------------
	void preorderTraverse(void visit(T&)) const;
	void inorderTraverse(void visit(T&)) const;
	void postorderTraverse(void visit(T&)) const;
	void breadthfirstTraverse(void visit(T&)) const;
	//------------------------------------------------------------
	// Overloaded Operator Section.
	//------------------------------------------------------------
	BNTree<T>& operator=(const BNTree<T> &rightHandSide);
}; // end BSTNodeTree

template<class T>
inline int BNTree<T>::getHeightHelper(BSTNode<T>* subTreePtr) const
{
	if (subTreePtr)
		return 0;
	else
		return 1 + max(getHeightHelper(subTreePtr->getLeftPtr()), getHeightHelper(subTreePtr->getRightPtr()));
}

template<class T>
inline int BNTree<T>::getNumberOfNodesHelper(BSTNode<T>* subTreePtr) const
{
	return 0;
}

template<class T>
inline void BNTree<T>::destroyTree(BSTNode<T>* subTreePtr)
{
	if (subTreePtr != nullptr)
	{
		destroyTree(subTreePtr->getLeftPtr());
		destroyTree(subTreePtr->getRightPtr());
		delete subTreePtr;
	} // end if
}

//**********************************************************************//
// addByItemKey - This is the helper function used to add a generic     //
//                'item' to our BST.  Recursively searches for the      //
//                point to adds a new node to the tree.  The result of  //
//                the compare (>) operator is used to navigate the      //
//                recursion path.                                       //
// params: subTreePtr - the rtree we are adding the 'item' to.          //
//         newNodePtr - the newly node-wrapped 'item'.                  //
//                                                                      //
// pre:    1.  'item' type that has overloaded the > opreator.          //
//         2.  An existing BST.                                         //
// post:   an updated BST witht he inserted node.                       //
// return: Always retrurns 'true'.  Assumes client manages memory       //
//         allocated for 'items'.                                       //
//**********************************************************************//
template<class T>
inline BSTNode<T>* BNTree<T>::addByItemKey(BSTNode<T>* subTreePtr, BSTNode<T>* newNodePtr)
{
	// if subtree pointer is nullptr the retruned tree is the new node.
	// this is why we initialize return value to newNodePtr....
	BSTNode<T>* retval = newNodePtr;
	BSTNode<T>* temp = nullptr;    // working node pointer

	// If there are subtrees the retval gets the new node pointer...
	if (subTreePtr == nullptr) {
		retval = newNodePtr;
	}
	// ...else go recursive.  When recurion is unwound retval is the updated
	// sub tree (subTreePtr).
	else
	{
		if (subTreePtr->getItem() > newNodePtr->getItem()) {
			temp = addByItemKey(subTreePtr->getLeftPtr(), newNodePtr);
			subTreePtr->setLeftPtr(temp);
		}
		else {
			temp = addByItemKey(subTreePtr->getRightPtr(), newNodePtr);
			subTreePtr->setRightPtr(temp);

		}
		retval = subTreePtr;
	}
	return retval;
}

//**********************************************************************//
// removeValue - This is the helper function used to remove	 a generic  //
//                'item' from our BST.  Recursively searches for the    //
//                point to adds a new node to the tree.  The result of  //
//                the compare (>)  and equal to(==) operator is used	//
//				  to navigate the recursion path.                       //
// params: subTreePtr - the rtree we are removing the 'item' from.      //
//         target - the target 'item' to be removed.                    //
//                                                                      //
// pre:    1.  'item' type that has overloaded the > opreator.          //
//         2.  An existing BST.                                         //
// post:   an updated BST with the removed node.                        //
// return: Always retrurns 'true'.  Assumes client manages memory       //
//         allocated for 'items'.                                       //
//**********************************************************************//
template<class T>
inline BSTNode<T>* BNTree<T>::removeValue(BSTNode<T>* subTreePtr, const T target, bool & success)
{
	BSTNode<T>* temp{ nullptr };

	if (subTreePtr == nullptr)
	{
		success = false;
	}
	else if (subTreePtr->getItem() == target)
	{
		subTreePtr = removeNode(subTreePtr);
		success = true;
	}
	else if (subTreePtr->getItem() > target)
	{
		temp = removeValue(subTreePtr->getLeftPtr(), target, success);
		subTreePtr->setLeftPtr(temp);
	}
	else
	{
		temp = removeValue(subTreePtr->getRightPtr(), target, success);
		subTreePtr->setRightPtr(temp);
	}
	return subTreePtr;
}

//**********************************************************************//
// removeNode - This is the helper function used to remove	 a generic  //
//                'item' from our BST.  Recursively searches for the    //
//                point to adds a new node to the tree.  The result of  //
//                the compare (>)  and equal to(==) operator is used	//
//				  to navigate the recursion path.                       //
// params:																// 
//         targetNode - the target 'item' to be removed.                //
//                                                                      //
// pre:    1.  'item' type that has overloaded the > opreator.          //
//         2.  An existing BST.                                         //
// post:   an updated BST with the removed node.                        //
// return: Always retrurns 'true'.  Assumes client manages memory       //
//         allocated for 'items'.                                       //
//**********************************************************************//
template<class T>
inline BSTNode<T>* BNTree<T>::removeNode(BSTNode<T>* targetNode)
{
	// 0. Our return value.
	BSTNode<T>* retval{ nullptr };

	// 1. Target node has no children.
	if (targetNode->getLeftPtr() == nullptr &&
		targetNode->getRightPtr() == nullptr) {
		// not sure, for now just leave the item alone..
		// its memory is managed outside the container
		delete targetNode;
		targetNode = nullptr;
		retval = targetNode;
	}
	// 2. Target node has one child.
	else if (targetNode->getLeftPtr() == nullptr ||
		targetNode->getRightPtr() == nullptr) {
		// Temp working BSTNode *
		BSTNode<T>* theSingleChildPtr{ nullptr };
		// if the left child pointer is the single child...
		if (targetNode->getLeftPtr() != nullptr) {
			theSingleChildPtr = targetNode->getLeftPtr();
		}
		// ...else if the right child pointer is a single child...
		else if (targetNode->getRightPtr() != nullptr) {
			theSingleChildPtr = targetNode->getRightPtr();
		}
		// .. we return the child of the current node
		retval = theSingleChildPtr;
	}
	// 3. Target node has 2 children...
	else {
		// Temp working BSTNode *
		BSTNode<T>* temp{ nullptr };
		// get the inodersuccessor
		T newNodeValue;
		// in-order successor used here.  Its the left subtree rooted
		// an target nodes right child...
		temp = removeLeftmostNode(targetNode->getRightPtr(), newNodeValue);
		targetNode->setRightPtr(temp);
		targetNode->setItem(newNodeValue);
		retval = targetNode;
	}
	return retval;  // Return: Node at location tree location after removal.
}

//**********************************************************************//
// removeLeftmostNode - This is the helper function used to remove		// 
//						the left most node in a tree				    //
//                'item' from our BST.  Recursively searches for the    //
//                point to adds a new node to the tree.  The result of  //
//                the compare (>)  and equal to(==) operator is used	//
//				  to navigate the recursion path.                       //
// params:																// 
//         targetNode - the target 'item' to be removed.                //
//			nextInorderItem - the next 'item' on the Binary tree in     //
//							according to inorder traversal.				//
//                                                                      //
// pre:    1.  'item' type that has overloaded the > opreator.          //
//         2.  An existing BST.                                         //
// post:   an updated BST with the removed node.                        //
// return: Always retrurns 'true'.  Assumes client manages memory       //
//         allocated for 'items'.                                       //
//**********************************************************************//
template<class T>
inline BSTNode<T>* BNTree<T>::removeLeftmostNode(BSTNode<T>* targetNode, T & nextInOrderItem)
{
	// 0. Our return value.
	BSTNode<T>* retval{ nullptr };
	BSTNode<T>* temp{ nullptr };

	if (targetNode->getLeftPtr() == nullptr) {
		nextInOrderItem = targetNode->getItem();
		retval = removeNode(targetNode);
	}
	else {
		temp = removeLeftmostNode(targetNode->getLeftPtr(), nextInOrderItem);
		targetNode->setLeftPtr(temp);
		retval = targetNode;
	}
	return retval;
}

//**********************************************************************//
// findNode - This is the helper function used to find a particular		// 
//				node in a tree.											//
//             Recursively searches through the tree until the			// 
//				target item is found.							   	    //
// params:																// 
//         targetNode - the target 'item' to be removed.                //
//			nextInorderItem - the next 'item' on the Binary tree in     //
//							according to inorder traversal.				//
//                                                                      //
// pre:    1.  A target item to find.						            //
//         2.  An existing BST.                                         //
// post:   N/A.													        //
// return:   The node with matching target item from tree if present.   //
//**********************************************************************//
template<class T>
inline BSTNode<T>* BNTree<T>::findNode(BSTNode<T>* treePtr, T & target) const
{
	if (treePtr == nullptr)
		return nullptr;
	else if (treePtr->getItem() == target)
		return treePtr;
	else if (treePtr->getItem() > target)
		return findNode(treePtr->getLeftPtr(), target);
	else
		return findNode(treePtr->getRightPtr(), target);
}

//**********************************************************************//
// copyTree - This is the helper function used to copy all				// 
//				nodes in a tree.										//
//             Recursively iterates through the tree and copies			// 
//				all nodes.										   	    //
// params:																// 
//         treePtr- A pointer to the Binary Tree to be copied.			// 
//                                                                      //
// pre:    1.  An existing Binary Tree.						            //
// post:   N/A.													        //
// return: A pointer to the newly copied tree.							// 
//**********************************************************************//
template<class T>
inline BSTNode<T>* BNTree<T>::copyTree(const BSTNode<T>* treePtr) const
{
	BSTNode<T>* newTreePtr = nullptr;
	// Copy tree nodes during a preorder traversal
	if (treePtr != nullptr)
	{
		// Copy node
		newTreePtr = new BSTNode<T>(treePtr->getItem(), nullptr, nullptr);
		newTreePtr->setLeftPtr(copyTree(treePtr->getLeftPtr()));
		newTreePtr->setRightPtr(copyTree(treePtr->getRightPtr()));
	} // end if
	// Else tree is empty (newTreePtr is nullptr)
	return newTreePtr;
}

//**********************************************************************//
// preorder - This is the helper function used to traverse a			// 
//				binary tree in the preorder mode.						//
//             Recursively iterates through the given tree and arranges //
//				it in Preorder format.									// 
// params:																// 
//		   visit- A function defining an action to be performed.		//
//         treePtr- A pointer to the Binary Tree to be traversed.		// 
//                                                                      //
// pre:    1.  An existing BST.                                         //
// post:   The same tree arranged in Preorder format.					//
// return:  N/A															// 
//**********************************************************************//
template<class T>
inline void BNTree<T>::preorder(void visit(T&), BSTNode<T>* treePtr) const
{
	if (treePtr != nullptr) {
		// ...perform the visit action...
		T anItem = treePtr->getItem();
		visit(anItem);
		// go left young man...
		preorder(visit, treePtr->getLeftPtr());
		// ...go right young man.
		preorder(visit, treePtr->getRightPtr());
	}  // end if
}

//**********************************************************************//
// inorder - This is the helper function used to traverse a				// 
//				binary tree in the inorder mode.						//
//             Recursively iterates through the given tree and arranges //
//				it in Inorder format.									// 
// params:																// 
//		   visit- A function defining an action to be performed.		//
//         treePtr- A pointer to the Binary Tree to be traversed.		// 
//                                                                      //
// pre:    1.  An existing BST.                                         //
// post:   The same tree arranged in Inorder format.					//
// return:  N/A															// 
//**********************************************************************//
template<class T>
inline void BNTree<T>::inorder(void visit(T&), BSTNode<T>* treePtr) const
{
	if (treePtr != nullptr) {
		// go left young man...
		inorder(visit, treePtr->getLeftPtr());
		// ...perform the visit action...
		T anItem = treePtr->getItem();
		visit(anItem);
		// ...go right young man.
		inorder(visit, treePtr->getRightPtr());
	}  // end if
}  // end inorder

//**********************************************************************//
// postorder - This is the helper function used to traverse a			// 
//				binary tree in the postorder mode.						//
//             Recursively iterates through the given tree and arranges //
//				it in postorder format.									// 
// params:																// 
//		   visit- A function defining an action to be performed.		//
//         treePtr- A pointer to the Binary Tree to be traversed.		// 
//                                                                      //
// pre:    1.  An existing BST.                                         //
// post:   The same tree arranged in Postorder format.					//
// return:  N/A															// 
//**********************************************************************//
template<class T>
inline void BNTree<T>::postorder(void visit(T&), BSTNode<T>* treePtr) const
{
	if (treePtr != nullptr) {
		// go left young man...
		postorder(visit, treePtr->getLeftPtr());
		// ...go right young man.
		postorder(visit, treePtr->getRightPtr());
		// ...perform the visit action...
		T anItem = treePtr->getItem();
		visit(anItem);
	}  // end if
}

//**********************************************************************//
// breadthfirst - This is the helper function used to traverse a		// 
//				binary tree in the breadthfirst mode					//
//             Recursively iterates through the given tree and arranges //
//				it in breadthfirst format.								// 
// params:																// 
//		   visit- A function defining an action to be performed.		//
//         treePtr- A pointer to the Binary Tree to be traversed.		// 
//                                                                      //
// pre:    1.  An existing BST.                                         //
// post:   The same tree arranged in breadthfirst format.				//
// return:  N/A															// 
//**********************************************************************//
template<class T>
inline void BNTree<T>::breadthfirst(void visit(T&), BSTNode<T> * treePtr) const
{

	if (treePtr == nullptr) {
		return;
	}

	Queue<BSTNode<T> *> aQueue;
	aQueue.enqueue(treePtr);

	while (!aQueue.isEmpty()) {
		BSTNode<T> * aNode = aQueue.front();
		aQueue.dequeue();
		T anItem = aNode->getItem();
		visit(anItem);

		if (aNode->getLeftPtr() != nullptr) {
			aQueue.enqueue(aNode->getLeftPtr());
		}

		if (aNode->getRightPtr() != nullptr) {
			aQueue.enqueue(aNode->getRightPtr());
		}
	}
}

//**********************************************************************//
// BinaryTree Constructor												//
// pre:  N/A.															//
// post: Binary Tree with root pointer initialized to nullptr			//
//**********************************************************************//
template<class T>
inline BNTree<T>::BNTree()
{
	root = nullptr;
}

//**********************************************************************//
// BinaryTree Constructor												//
// pre:  User Provided rootItem data.									//
// post: Binary Tree with root pointer initialized to user provided		// 
//			pointer and left and right child pointers initialized to	//
//			null pointers.												//
//**********************************************************************//
template<class T>
inline BNTree<T>::BNTree(const T & rootItem)
{
	root = new BSTNode<T>(rootItem, nullptr, nullptr);
}

//**********************************************************************//
// BinaryTree Constructor												//
// pre:  User Provided rootItem data.									//
// post: Binary Tree with root pointer initialized to user provided		// 
//			pointer and left and right child pointers initialized to	//
//			user provided item pointers.								//
//**********************************************************************//
template<class T>
inline BNTree<T>::BNTree(const T & rootItem, const BNTree<T>* leftTreePtr, const BNTree<T>* rightTreePtr)
{
	root = new BSTNode<T>(rootItem, copyTree(leftTreePtr->root), copyTree(rightTreePtr->root));
}

//**********************************************************************//
// BinaryTree Copy Constructor											//
// pre:  User Provided rootItem data.									//
// post: Binary Tree with copied item data								//
//**********************************************************************//
template<class T>
inline BNTree<T>::BNTree(const BNTree<T>& tree)
{
	root = copyTree(tree->root);
}

//**********************************************************************//
// BinaryTree Copy Destructor											//
// pre: An existing Binary Tree.										// 
// post: Binary Tree destroyed.											// 
//**********************************************************************//
template<class T>
inline BNTree<T>::~BNTree()
{
	destroyTree(root);
}

//**********************************************************************//
// isEmpty - This function used to check if a binary Tree is empty.		//
//                                                                      //
// params: N/A.															// 
//                                                                      //
// pre:    1.  An existing BST.                                         //
// return: Returns 'true' if tree is empty.                             //
//**********************************************************************//
template<class T>
inline bool BNTree<T>::isEmpty() const
{
	if (root == nullptr)
		return true;
	return false;
}

//**********************************************************************//
// isEmpty - This function used to check the height of a binary Tree.	//
//                                                                      //
// params: N/A.															// 
//                                                                      //
// pre:    1.  An existing BST.                                         //
// return: Returns the height of the tree.                              //
//**********************************************************************//
template<class T>
inline int BNTree<T>::getHeight() const
{
	return getHeightHelper(root);
}

//**********************************************************************//
// add - This function used to add a generic 'item' to our BST. It uses //
//       helper funtions to do this.Recursively searches for the        //
//                                                                      //
// params: subTreePtr - const reference to the 'item' we are adding.    //
//                                                                      //
// pre:    1.  'item' type that has overloaded the > opreator.          //
//         2.  An existing BST.                                         //
// post:   an updated BST witht he inserted node.                       //
// return: Always retrurns 'true'.  Assumes client manages memory       //
//         allocated for 'items'.                                       //
//**********************************************************************//
template<class T>
inline bool BNTree<T>::add(const T & newData)
{
	// Here is 
	BSTNode<T>* newNodePtr = new BSTNode<T>(newData);
	root = addByItemKey(root, newNodePtr);
	return true;
}

//**********************************************************************//
// find - This function used to find a generic 'item' in our BST.		//
//        It uses helper funtions to do this.							//
//		  Recursively searches for the target node in the tree.	        //
//                                                                      //
// params: recordByKey - reference to the 'item' we are looking for.    //
//                                                                      //
// pre:    1.  An existing BST.                                         //
//																		//
// post:  N/A															// 
// return:  Returns the target item if located.	                        //
//**********************************************************************//
template<class T>
inline T BNTree<T>::find(T & recordByKey)
{
	BSTNode<T>* temp = findNode(root, recordByKey);
	return (temp->getItem());
}

//**********************************************************************//
// contains - This function used to find a generic 'item' in our BST.	//
//        It uses helper funtions to do this.							//
//		  Recursively searches for the target node in the tree.	        //
//                                                                      //
// params: recordByKey - reference to the 'item' we are looking for.    //
//                                                                      //
// pre:    1.  An existing BST.                                         //
//																		//
// post:  N/A															// 
// return:  Returns true if target item is located.                     //
//**********************************************************************//
template<class T>
inline bool BNTree<T>::contains(T & newData) const
{
	// find the damned item...
	BSTNode<T>* theFoundNode = findNode(root, newData);

	if (theFoundNode != nullptr)
		return true;

	return false;
}

//**********************************************************************//
// contains - This function used to remove a generic 'item' from our BST.//
//        It uses helper funtions to do this.							//
//		  Recursively searches for the target node in the tree.	        //
//                                                                      //
// params: recordByKey - reference to the 'item' we are looking for.    //
//                                                                      //
// pre:    1.  An existing BST.                                         //
//																		//
// post:  N/A															// 
// return:  Returns true if target item is located.                     //
//**********************************************************************//
template<class T>
inline bool BNTree<T>::remove(const T & data)
{
	bool isRemoved{ false };
	root = removeValue(root, data, isRemoved);
	return isRemoved;
}

//**********************************************************************//
// preorderTraverse - This is the helper function used to traverse a	// 
//				binary tree in the preorder mode.						//
//				Uses a helper function to perform the traversal			//
//              Recursively iterates through the given tree and arranges//
//				it in Preorder format.									// 
// params:																// 
//		   visit- A function defining an action to be performed.		//
//                                                                      //
// pre:    1.  An existing BST.                                         //
// post:   The same tree arranged in Preorder format.					//
// return:  N/A															// 
//**********************************************************************//
template<class T>
inline void BNTree<T>::preorderTraverse(void visit(T&)) const
{
	// here we call the helper function inorder to do the recursive
	// preorder traversal.
	preorder(visit, root);
}

//**********************************************************************//
// inorderTraverse - This is the helper function used to traverse a		// 
//				binary tree in the inorder mode.						//
//				Uses a helper function to perform the traversal			//
//              Recursively iterates through the given tree and arranges//
//				it in Inorder format.									// 
// params:																// 
//		   visit- A function defining an action to be performed.		//
//                                                                      //
// pre:    1.  An existing BST.                                         //
// post:   The same tree arranged in Preorder format.					//
// return:  N/A															// 
//**********************************************************************//
template<class T>
inline void BNTree<T>::inorderTraverse(void visit(T&)) const
{
	// here we call the helper function inorder to do the recursive
	// in-order traversal.
	inorder(visit, root);
}

//**********************************************************************//
// postorderTraverse - This is the helper function used to traverse a	// 
//				binary tree in the postorder mode.						//
//				Uses a helper function to perform the traversal			//
//              Recursively iterates through the given tree and arranges//
//				it in Postorder format.									// 
// params:																// 
//		   visit- A function defining an action to be performed.		//
//                                                                      //
// pre:    1.  An existing BST.                                         //
// post:   The same tree arranged in Postorder format.					//
// return:  N/A															// 
//**********************************************************************//
template<class T>
inline void BNTree<T>::postorderTraverse(void visit(T&)) const
{
	// here we call the helper function inorder to do the recursive
	// in-order traversal.
	postorder(visit, root);
}

//**********************************************************************//
// breadthfirstTraverse - This is the helper function used to traverse  // 
//				binary tree in the breadthfirst mode.					//
//				Uses a helper function to perform the traversal			//
//              Recursively iterates through the given tree and arranges//
//				it in breadthfirst format.								// 
// params:																// 
//		   visit- A function defining an action to be performed.		//
//                                                                      //
// pre:    1.  An existing BST.                                         //
// post:   The same tree arranged in Breadthfirst format.				//
// return:  N/A															// 
//**********************************************************************//
template<class T>
inline void BNTree<T>::breadthfirstTraverse(void visit(T&)) const
{
	// here we call the helper function inorder to do the recursive
	// in-order traversal.
	breadthfirst(visit, root);
}

//**********************************************************************//
// Overloaded = operator. Assigns the value of the operand on			// 
// the left of the "=" to the right.									//
// Returns a pointer to the updated object.								//
//**********************************************************************//
template<class T>
inline BNTree<T>& BNTree<T>::operator=(const BNTree<T> &rhs)
{
	if (this != &rhs) {
		destroyTree(root); // deallocate lefthand side
		copyTree(rhs); // copy righthand side
	}
	return *this;
}

/*

********************************************************
// Overloaded << operator. Gives std::cout the ability to     *
// directly display Dollar objects.                      *
********************************************************
std::ostream & operator<<(std::ostream &strm, const T &obj)
{
	strm << obj.name << " dollars, " << obj.bday << " cents :";
	return strm;
}
*/
