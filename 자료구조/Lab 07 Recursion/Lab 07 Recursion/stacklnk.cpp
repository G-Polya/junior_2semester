// 2016112158 �����
#include "stacklnk.h"
#include <iostream>
using namespace std;
template<class DT>
StackNode<DT>::StackNode(const DT& nodeData, StackNode* nextPtr)
{
	this->dataItem = nodeData;
	this->next = nextPtr;
}

template<class DT>
Stack<DT>::Stack(int ignored)
{
	top = NULL;
}

template<class DT>
Stack<DT>::~Stack()
{
	clear();
}


template<class DT>
void Stack<DT>::push(const DT& newData)
{
	top = new StackNode<DT>(newData, top);
}

template<class DT>
DT Stack<DT>::pop()
{
	StackNode<DT>* temp;
	DT data;
	data = top->dataItem;
	temp = top;
	top = top->next;	// top �̵�
	delete temp;			// ���� top node����

	return data;
}

template<class DT>
void Stack<DT>::clear()
{
	StackNode<DT> *temp, *tempNext;
	temp = top;
	while (temp != NULL)
	{
		tempNext = temp->next;		// ��������ϴ� ����� ������ �ӽ� ����
		delete temp;
		temp = tempNext;				// �������� �̵�

	}
	top = NULL;
}

template<class DT>
bool Stack<DT>::isEmpty() const
{
	return (top == NULL);
}

template<class DT>
bool Stack<DT>::isFull() const
{
	StackNode<DT>* temp = new StackNode<DT>();
	if (temp == NULL)
		return true;
	else
	{
		delete temp;
		return false;
	}
		
}

template<class DT>
void Stack<DT>::showStructure() const
{
	if (top == NULL)
		cout << "Empty Stack" << endl;
	else
	{
		cout << "top ";
		for (auto iter = top; iter != NULL; iter = iter->next)
			cout << iter->dataItem << " ";
		cout << "bottom" << endl;
	}
}

template<class DT>
Stack<DT>::Stack(const Stack& valueStack)
{
	StackNode<DT>* p = valueStack.top;
	StackNode<DT>* q = top;
	while (p != NULL)
	{
		q->next = p->next;
		q = q->next;
		p = p->next;
	}
}