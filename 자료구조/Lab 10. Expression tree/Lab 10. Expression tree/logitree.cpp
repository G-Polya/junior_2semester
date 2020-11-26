//--------------------------------------------------------------------
//		Lab 12									logitree.cpp
//
//--------------------------------------------------------------------

#include "logitree.h"
#include <assert.h>
#include <ctype.h>
#include <iostream>

using namespace std;
//--------------------------------------------------------------------

ExprTreeNode::ExprTreeNode(char elem, ExprTreeNode* leftPtr, ExprTreeNode* rightPtr)
{
	element = elem;
	left = leftPtr;
	right = rightPtr;
}

//--------------------------------------------------------------------

ExprTree::ExprTree()
{
	root = 0;
}

ExprTree::~ExprTree()
{
	clear();
}

//--------------------------------------------------------------------

void ExprTree::build()
{
	char* prefix = new char[20];
	cin >> prefix;
	buildSub(root, prefix);
}

void ExprTree::buildSub(ExprTreeNode*& p, char*& expr)
{
	ExprTreeNode* t;
	while (*expr)
	{
		t = new ExprTreeNode(NULL, NULL, NULL);
		t->element = *expr;
		p = t;

		if ((*expr) == '-')
		{
			expr++;
			buildSub(p->right, expr);
		}


		if (isdigit(*expr) == 0)
		{
			expr++;
			buildSub(p->left, expr);
			expr++;
			buildSub(p->right, expr);
			return;
		}
		else
			return;
	}
}

//--------------------------------------------------------------------

void ExprTree::expression() const
{
	exprSub(root);
}

void ExprTree::exprSub(ExprTreeNode* p) const
{
	if (p != NULL)
	{
		if (isdigit(p->element) == 0)
			cout << '(';
		exprSub(p->left);
		cout << p->element;
		exprSub(p->right);
		if (isdigit(p->element) == 0)
			cout << ')';

	}
}

//--------------------------------------------------------------------

int ExprTree::evaluate() const
{
	return evaluateSub(root);
}

int ExprTree::evaluateSub(ExprTreeNode* p) const
{
	if (isdigit(p->element) == 0)
	{
		switch (p->element)
		{
		case '+':
			return evaluateSub(p->left) || evaluateSub(p->right);
			break;
		case '-':
			return !evaluateSub(p->right);
		case '*':
			return evaluateSub(p->left) && evaluateSub(p->right);
			break;
		//case '/':
		//	return evaluateSub(p->left) / evaluateSub(p->right);
		//	break;
		default:
			return 0;
			break;
		}
	}
	else
		return p->element - '0';
}

//--------------------------------------------------------------------

void ExprTree::clear()
{
	clearSub(root);
	root = 0;
}

void ExprTree::clearSub(ExprTreeNode* p)
{
	if (p != NULL)
	{
		clearSub(p->left);
		clearSub(p->right);
		delete p;
	}
}

//--------------------------------------------------------------------

void ExprTree::showStructure() const

// Outputs an expression tree. The tree is output rotated counter-
// clockwise 90 degrees from its conventional orientation using a
// "reverse" inorder traversal. This operation is intended for testing
// and debugging purposes only.

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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void ExprTree::showSub(ExprTreeNode* p, int level) const

// Recursive partner of the showStructure() function. Outputs the
// subtree whose root node is pointed to by p. Parameter level is the
// level of this node within the expression tree.

{
	int j;   // Loop counter

	if (p != 0)
	{
		showSub(p->right, level + 1);        // Output right subtree
		for (j = 0; j < level; j++)   // Tab over to level
			cout << "\t";
		cout << " " << p->element;       // Output data item
		if ((p->left != 0) &&          // Output "connector"
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showSub(p->left, level + 1);         // Output left subtree
	}
}