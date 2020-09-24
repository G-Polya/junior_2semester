
//2016112158 ±èÈñ¼ö
#include "stackarr.h"
#include <iostream>

using namespace std;

// Constructor
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

// Destructor
template<class DT>
Stack<DT>::~Stack()
{
	delete[] element;
}


// Push
template<class DT>
void Stack<DT>::push(const DT& newElement)
{
	if (!full()) 
	{
		cout << "Push " << newElement << endl;

		top++;
		element[top] = newElement;

	}
	else
		cout << "Stack is Full" << endl;
}

// pop
template<class DT>
DT Stack<DT>::pop()
{
	if (!empty())
	{
		DT tmp = element[top];
		element[top] = NULL;
		top--;
		cout << "Popped " << tmp << endl;

		return tmp;
	}
	else
	{
		cout << "Stack is Empty" << endl;
		return NULL;
	}

	
}

// remove all
template<class DT>
void Stack<DT>::clear()
{
	delete[] element;
	element = new DT(maxSize);
	//while (!empty())
	//	pop();
}

// Is stack empty?
template<class DT>
bool Stack<DT>::empty() const
{
	if (top == -1)
		return true;
	else
		return false;
}

// Is stack full?
template<class DT>
bool Stack<DT>::full() const
{
	if (top == maxSize - 1)
		return true;
	else
		return false;
}

// show all
template<class DT>
void Stack<DT>::showStructure() const
{
	for (int i = 0; i < maxSize; i++)
	{
		cout << element[i] << " ";
	}
	cout << endl;
}