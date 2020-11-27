//--------------------------------------------------------------------
//		Lab 12									exprtree.cpp
//
//--------------------------------------------------------------------

#include "exprtree.h"
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

void ExprTree::buildSub(ExprTreeNode*& p, char *&expr)
{
	ExprTreeNode* t;
	while (*expr)
	{
		t = new ExprTreeNode(NULL, NULL, NULL);
		t->element = *expr;
		p = t;

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

float ExprTree::evaluate() const
{
	return evaluateSub(root);
}

float ExprTree::evaluateSub(ExprTreeNode* p) const
{
	if (isdigit(p->element) == 0)
	{
		switch (p->element)
		{
		case '+':
			return evaluateSub(p->left) + evaluateSub(p->right);
			break;
		case '-':
			return evaluateSub(p->left) - evaluateSub(p->right);
		case '*':
			return evaluateSub(p->left) * evaluateSub(p->right);
			break;
		case '/':
			return evaluateSub(p->left) / evaluateSub(p->right);
			break;
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

void ExprTree::showSub(ExprTreeNode* p, int level) const
{
	int j;

	if (p != 0)
	{
		showSub(p->right, level + 1);
		for (j = 0; j < level; j++)
			cout << "\t";
		cout << " " << p->element;
		if ((p->left != 0) &&
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showSub(p->left, level + 1);
	}
}