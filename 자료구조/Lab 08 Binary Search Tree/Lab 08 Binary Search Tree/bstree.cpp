#include <assert.h>
#include <iostream>
#include "bstree.h"

using namespace std;

template < class TE, class KF >
BSTreeNode<TE, KF>::BSTreeNode(const TE& elem, BSTreeNode* leftPtr, BSTreeNode* rightPtr)
{
	element = elem;
	left = leftPtr;
	right = rightPtr;
}

template < class TE, class KF >
BSTree<TE, KF>::BSTree()
{
	root = NULL;
}

template < class TE, class KF >
BSTree<TE, KF>::~BSTree()
{
	clear();
}

// Insert

template < class TE, class KF >
void BSTree<TE, KF>::insert(const TE& newElement)
{
	if (isFull())
		cout << "Tree is Full" << endl;
	else
		insertSub(root, newElement);
}

template < class TE, class KF >
void BSTree<TE, KF>::insertSub(BSTreeNode<TE, KF>*& p, const TE& newElement)
{
	if (p == NULL)
	{
		p = new BSTreeNode<TE, KF>(newElement, NULL, NULL);
		if (isEmpty())
			root = p;
	}

	else if ((p->element).key() > newElement.key())
		insertSub(p->left, newElement);
	else if ((p->element).key() < newElement.key())
		insertSub(p->right, newElement);
	else
		cout << "This exists already." << endl;
}

//--------------------------------------------------------------------

// Retrieve 

template < class TE, class KF >
bool BSTree<TE, KF>::retrieve(KF searchKey, TE& searchElement) const
{
	if (isEmpty())
		return false;
	else
		return retrieveSub(root, searchKey, searchElement);
}

template < class TE, class KF >
bool BSTree<TE, KF>::retrieveSub(BSTreeNode<TE, KF>* p, KF searchKey, TE& searchElement) const
{
	if (p == NULL)
		return false;
	else if ((p->element).key() > searchKey)
		retrieveSub(p->left, searchKey, searchElement);
	else if ((p->element).key() < searchKey)
		retrieveSub(p->right, searchKey, searchElement);
	else
	{
		searchElement = p->element;
		return true;
	}
}

//--------------------------------------------------------------------

// Remove

template < class TE, class KF >
bool BSTree<TE, KF>::remove(KF deleteKey)
{
	if (isEmpty())
	{
		cout << "Tree is Empty" << endl;
		return false;
	}
	else
		return removeSub(root, deleteKey);
}

template < class TE, class KF >
bool BSTree<TE, KF>::removeSub(BSTreeNode<TE, KF>*& p, KF deleteKey)
{
	
	if (p == NULL)
		return false;
	else if ((p->element).key() > deleteKey)
		return removeSub(p->left, deleteKey);
	else if ((p->element).key() < deleteKey)
		return removeSub(p->right, deleteKey);
	else
	{
		BSTreeNode<TE, KF>* delNode = p;
		if (p->left == NULL)
			p = p->right;
		else if (p->right == NULL)
			p = p->left;
		else
			cutRightmost(p->left, delNode);

		delete delNode;
		return true;
	}
}

template < class TE, class KF >
void BSTree<TE, KF>::cutRightmost(BSTreeNode<TE, KF>*& r, BSTreeNode<TE, KF>*& delPtr)
{
	if (r->right != NULL)
		cutRightmost(r->right, delPtr);
	else
	{
		delPtr->element = r->element;
		delPtr = r;
		r = r->left;
	}
}

//--------------------------------------------------------------------

// Write Keys

template < class TE, class KF >
void BSTree<TE, KF>::writeKeys() const
{
	if (isEmpty())
		cout << "Tree is Empty" << endl;
	else
	{
		writeKeysSub(root);
		cout << endl;
	}
}

template < class TE, class KF >
void BSTree<TE, KF>::writeKeysSub(BSTreeNode<TE, KF>* p) const
{
	if (p != NULL)
	{
		writeKeysSub(p->left);
		cout << (p->element).key() << " ";
		writeKeysSub(p->right);
	}
}

//--------------------------------------------------------------------

// Clear

template < class TE, class KF >
void BSTree<TE, KF>::clear()
{
	if (!isEmpty())
	{
		clearSub(root);
		root = NULL;
	}
}

template < class TE, class KF >
void BSTree<TE, KF>::clearSub(BSTreeNode<TE, KF>* p)
{
	if (p != NULL)
	{
		clearSub(p->left);
		clearSub(p->right);
		delete p;
	}
}

//--------------------------------------------------------------------

// Empty / Full

template < class TE, class KF >
bool BSTree<TE, KF>::isEmpty() const
{
	if (root == NULL)
		return true;
	else
		return false;
}

template < class TE, class KF >
bool BSTree<TE, KF>::isFull() const
{
	BSTree<TE, KF>* temp = new BSTree();
	if (temp != NULL)
	{
		delete temp;
		return false;
	}
	return true;
}

//--------------------------------------------------------------------

// Show Structure

template < class TE, class KF >
void BSTree<TE, KF>::showStructure() const

{
	if (root == 0)
		cout << "Empty tree" << endl;
	else
	{
		cout << endl;
		showSub(root, 1);
		cout << endl;
	}
}

template < class TE, class KF >
void BSTree<TE, KF>::showSub(BSTreeNode<TE, KF>* p,
	int level) const

{
	int j;   // Loop counter

	if (p != 0)
	{
		showSub(p->right, level + 1);         // Output right subtree
		for (j = 0; j < level; j++)    // Tab over to level
			cout << "\t";
		cout << " " << p->element.key();   // Output key
		if ((p->left != 0) &&           // Output "connector"
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showSub(p->left, level + 1);          // Output left subtree
	}
}