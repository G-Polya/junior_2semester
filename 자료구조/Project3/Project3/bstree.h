#pragma once
#include <string>

using namespace std;

class TreeNode
{
private:
	// Constructor
	TreeNode(string name, TreeNode* child, TreeNode* sibling);

	// Data members
	string name;
	TreeNode* child,
		* sibling;

	friend class Tree;
};

class Tree
{
public:
	// Constructor
	Tree();

	// Destructor
	~Tree();

	// Operations
	void setCEO(string name);
	void hire(string name1, string name2);
	bool fire(string name);
	void print();
	void clear();
	bool isEmpty();

private:
	void hireSub(TreeNode* p, string name);
	void fireSub(TreeNode* p);
	void printSub(TreeNode* p, int level);
	void clearSub(TreeNode* p);
	TreeNode* find(string name);
	TreeNode* findSub(TreeNode* p, string name);
	//bool find(string name);
	//bool findSub(TreeNode* p, string name);
	TreeNode* parent; // 노드를 삭제할 때 부모의 위치
	TreeNode* root;
};