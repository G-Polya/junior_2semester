// 2016112158 김희수
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
	top = top->next;	// top 이동
	delete temp;			// 이전 top node제거

	return data;
}

template<class DT>
void Stack<DT>::clear()
{
	StackNode<DT> *temp, *tempNext;
	temp = top;
	while (temp != NULL)
	{
		tempNext = temp->next;		// 지우고자하는 노드의 다음을 임시 저장
		delete temp;
		temp = tempNext;				// 다음으로 이동

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