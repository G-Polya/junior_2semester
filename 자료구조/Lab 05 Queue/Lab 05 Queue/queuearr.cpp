#include "queuearr.h"
#include <iostream>

using namespace std;

// constructor
template<class DT>
Queue<DT>::Queue(int maxNumber)
{
	maxSize = maxNumber;
	front = -1;		// 초기 front 위치
	rear = -1;		// 초기 rear 위치
	element = new DT[maxSize];
}

// destructor
template<class DT>
Queue<DT>::~Queue()
{
	delete[] element;
}

template<class DT>
void Queue<DT>::enqueue(const DT& newData)
{
	
	if(isFull())
		cout << "Queue is full" << endl;
	else
	{
		if (!isEmpty())
		{
			rear = (rear + 1) % maxSize;
		}
		else
		{
			front = 0;
			rear = 0;
		}

		element[rear] = newData;
	}
}

template<class DT>
DT Queue<DT>::dequeue()
{
	int current = front;

	if (isEmpty())
	{
		cout << "Queue is Empty" << endl;
	}
	else
	{
		front = (front + 1) % maxSize;

		if (front == rear + 1)
		{
			front = -1;
			rear = -1;
		}

	
		return element[current];
	}
}

template<class DT>
void Queue<DT>::clear()
{
	front = -1;
	rear = -1;
}

template<class DT>
bool Queue<DT>::isFull() const
{
	if (front == 0 && rear == (maxSize - 1))
		return true;
	else if (rear == (front - 1))
		return true;
	else
		return false;
}

template<class DT>
bool Queue<DT>::isEmpty() const
{
	return (front == -1);
}

template<class DT>
void Queue<DT>::showStructure() const
{
	if (front == -1)
		cout << "Empty Queue" << endl;
	else
	{
		cout << "Front = " << front << " Rear = " << rear << endl;
		for (int i = 0; i < maxSize; i++)
			cout << i << "\t";
		cout << endl;
		if (rear >= front)
			for (int i = 0; i < maxSize; i++)
				if ((i >= front) && (i <= rear))
					cout << element[i] << "\t";
				else
					cout << " \t";
		else
			for (int i = 0; i < maxSize; i++)
				if ((i >= front) || (i <= rear))
					cout << element[i] << "\t";
				else
					cout << " \t";
		cout << endl;
	}
}

template<class DT>
void Queue<DT>::putFront(const DT& newData)
{
	if (!isFull())
	{
		if (!isEmpty())
		{
			front = (front - 1 + maxSize) % maxSize;		// (0 -1 + 8) mod 8 = 7 , (7 - 1 + 8) mod 8 = 6
		}
		else
		{
			front = 0;
			rear = 0;
		}

		element[front] = newData;
	}
	else
		cout << "Queue is full" << endl;
}

template<class DT>
DT Queue<DT>::getRear()
{
	int current = -1;
	if (isEmpty())
		cout << "Queue is Empty" << endl;
	else
	{
		if (front == rear)
		{
			front = -1;
			rear = -1;
		}
		else
		{
			rear--;
			if (rear < 0)
				rear = maxSize - 1;
		}
		return element[current];
	}
}