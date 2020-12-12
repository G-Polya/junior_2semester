#include "bstree.h"
#include <iostream>
#include <algorithm>

using namespace std;

TreeNode::TreeNode(string name, TreeNode* child, TreeNode* sibling)
{
	this->name = name;
	this->child = child;
	this->sibling = sibling;
}

Tree::Tree()
{
	this->root = NULL;
	this->parent = NULL;
}

Tree::~Tree()
{
	clear();
}

void Tree::setCEO(string name)
{
	root = new TreeNode(name, NULL, NULL);
}

TreeNode* Tree::find(string name)
{
	if (root != NULL)
	{
		parent = root;
		return findSub(root, name);
	}
	else return 0;
}

TreeNode* Tree::findSub(TreeNode* p, string name)
{
	TreeNode* result = NULL;
	if (p->name == name)
	{
		return p;
	}
	else
	{
		if (p->sibling != NULL)
		{
			result = findSub(p->sibling, name);
			if (result != NULL) return result;
		}
		if (p->child != NULL)
		{
			parent = p;
			result = findSub(p->child, name);
			if (result != NULL) return result;
		}
	}
	return NULL;
}

void Tree::hire(string name1, string name2)
{
	TreeNode* superior = find(name1); // superior는 name1을 가진 노드
	if (superior != NULL)
	{
		if (findSub(root, name2) == NULL) // 조직도에 name2를 가진 노드가 없으면
			hireSub(superior, name2); // hireSub를 통해 name2를 고용
	}
}

void Tree::hireSub(TreeNode* p, string name)
{
	if (p->child == NULL) // p가 가리키는 노드가 비어 있어야 그 자리에 name의 노드를 생성
		p->child = new TreeNode(name, NULL, NULL);
	else // 아니면 p의 sibling에서 실행
	{
		TreeNode* addPtr = p->child;
		while (addPtr->sibling != NULL)
		{
			addPtr = addPtr->sibling;
		}
		addPtr->sibling = new TreeNode(name, NULL, NULL);
	}
}

bool Tree::fire(string name)
{
	TreeNode* delPtr = find(name);
	if (delPtr != NULL)
	{
		fireSub(delPtr);
		return true;
	}
	else
		return false;
}

void Tree::fireSub(TreeNode* p)
{
	TreeNode* tmp = p;
	TreeNode* pre;
	if (tmp == parent->child) // p가 첫째일 때
	{
		pre = parent;
		while (tmp->child != NULL) // p의 부하직원이 존재
		{
			tmp->name = tmp->child->name; // 부하직원을 승진시킴
			pre = tmp;
			tmp = tmp->child;
		}
		while (tmp->sibling != NULL) // p의 형제 노드가 존재
		{
			tmp->name = tmp->sibling->name; // 형제 노드를 하나씩 올려줌
			pre = tmp;
			tmp = tmp->sibling;
		} // 정렬이 끝나면
		if (pre->child == tmp) // 삭제하려는 노드가 상사의 자식 노드일 경우
			pre->child = NULL;
		else if (pre->sibling == tmp) // 삭제하려는 노드가 동료의 형제 노드일 경우
			pre->sibling = NULL;
		delete tmp; // tmp를 삭제
	}
	else // p가 첫째가 아닐 때
	{
		if (tmp != root) // p가 CEO가 아닐 때
		{
			if (tmp->child != NULL) // 부하직원이 존재
			{
				pre = parent;
				while (tmp->child != NULL) // p의 부하직원이 존재
				{
					tmp->name = tmp->child->name; // 부하직원을 승진시킴
					pre = tmp;
					tmp = tmp->child;
				}
				while (tmp->sibling != NULL) // p의 형제 노드가 존재
				{
					tmp->name = tmp->sibling->name; // 형제 노드를 하나씩 올려줌
					pre = tmp;
					tmp = tmp->sibling;
				} // 정렬이 끝나면
				if (pre->child == tmp) // 삭제하려는 노드가 상사의 자식 노드일 경우
					pre->child = NULL;
				else if (pre->sibling == tmp) // 삭제하려는 노드가 동료의 형제 노드일 경우
					pre->sibling = NULL;
			}
			else // 부하직원이 존재하지 않을 경우
			{
				pre = parent->child;
				while (pre->sibling != tmp)
					pre = pre->sibling; // 삭제하려는 노드의 이전 노드까지 pre를 옮겨줌
				pre->sibling = tmp->sibling; // 앞뒤 노드를 연결
			}
			delete tmp;
		}
		else // p가 CEO일 때
		{
			if (tmp->child == NULL) // 부하직원이 없으면
			{
				delete tmp;
				root = NULL; // 그대로 삭제
			}
			else // 부하직원이 있으면
			{
				swap(tmp->name, tmp->child->name); // CEO와 부하직원을 바꿔줌
				fireSub(tmp->child); // 바꾼 CEO를 삭제하는 함수 호출
			}
		}
	}
}

void Tree::print()
{
	printSub(root, 0);
}

void Tree::printSub(TreeNode* p, int level)
{
	if (p != NULL)
	{
		for (int i = 0; i < level; i++)
			cout << '+';
		cout << p->name << endl;
	}
	if (p->child != NULL)
		printSub(p->child, level + 1);
	if (p->sibling != NULL)
		printSub(p->sibling, level);
}

void Tree::clear()
{
	clearSub(root);
	root = NULL;
}

void Tree::clearSub(TreeNode* p)
{
	if (p != NULL)
	{
		clearSub(p->child);
		clearSub(p->sibling);
		delete p;
	}
}

bool Tree::isEmpty()
{
	return (root == NULL); // root가 NULL이면 비어있으므로 true 반환
}