#include "stackarr.h"
#include <iostream>

using namespace std;
template<class DT>
Stack<DT>::Stack(int maxNumber) 
	:maxSize(maxNumber), top(-1)
{
	element = new DT[maxSize];
	for (int i = 0; i < maxSize; i++)
	{
		element[i] = NULL;
	}
}

template<class DT>
Stack<DT>::~Stack()
{
	delete[] element;
}

template<class DT>
void Stack<DT>::push(const DT& newElement)
{
	top++;
	element[top] = newElement;
}

template<class DT>
DT Stack<DT>::pop()
{
	DT tmp = element[top];
	element[top] = NULL;
	top--;
	return tmp;
}


//clear empty full showStruture
template<class DT>
void Stack<DT>::clear()
{
	while (!empty())
		pop();
}

template<class DT>
bool Stack<DT>::empty() const
{
	if (top == -1)
		return true;
	else
		return false;
}

template<class DT>
bool Stack<DT>::full() const
{
	if (top == maxSize - 1)
		return true;
	else
		return false;
}

template<class DT>
void Stack<DT>::showStructure() const
{
	for (int i = 0; i < maxSize; i++)
	{
		cout << element[i] << " ";
	}
	cout << endl;
}