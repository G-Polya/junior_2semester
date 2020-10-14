#include "queueLnk.h"
#include <iostream>

using namespace std;

template<class DT>
QueueNode<DT>::QueueNode(const DT& nodeData, QueueNode* nextPtr)
{
	dataItem = nodeData;
	next = nextPtr;
}

template <class DT>
Queue<DT>::Queue(int ignored)
{
	front = NULL;
	rear = NULL;
}

// Destructor
template<class DT>
Queue<DT>::~Queue()
{
	clear();
}

// Queue manipulation operations
template<class DT>
void Queue<DT>::enqueue(const DT& newData)        // Enqueue data element
{
	QueueNode<DT>* newNode = NULL;
	if (isFull())
		cout << "Queue is Full" << endl;
	else
	{
		newNode = new QueueNode<DT>(newData, NULL);

		if (isEmpty())
		{
			front = newNode;
			rear = newNode;
		}
		else
		{
			rear->next = newNode;
			rear = newNode;
		}
		newNode = NULL;
		
	}
}

template<class DT>
DT Queue<DT>::dequeue()                             // Dequeue data element
{
	QueueNode<DT>* cursor = NULL;
	DT data;
	if (isEmpty())
		cout << "Queue is Empty" << endl;
	else
	{
		cursor = front;
		data = front->dataItem;

		if (front == rear)
		{
			front = NULL;
			rear = NULL;
		}
		else
			front = front->next;
		
		delete cursor;
		cursor = NULL;

		return data;
	}
}

template <class DT>
void Queue<DT>::clear()                            // Clear queue
{
	while (!isEmpty())
		dequeue();
}
// Queue status operations
template<class DT>
bool Queue<DT>::isEmpty() const                    // Queue is empty
{
	return (front == NULL);
}

template<class DT>
bool Queue<DT>::isFull() const                     // Queue is full
{
	return false;
}

template<class DT>
void Queue<DT>::showStructure() const
{
	QueueNode<DT>* cursor;
	if (isEmpty())
		cout << "Empty Queue" << endl;
	else
	{
		for (cursor = front; cursor != NULL; cursor = cursor->next)
			cout<< cursor->dataItem << "\t";
		
		cout << endl;
	}
}

template<class DT>
void Queue<DT>::putFront(const DT& newDataItem) //Lab 2
{
	QueueNode<DT>* newNode = NULL;
	if (isFull())
		cout << "Queue is Full" << endl;
	else
	{
		newNode = new QueueNode<DT>(newDataItem, NULL);
		if (isEmpty())
		{
			front = newNode;
			rear = newNode;
		}
		else
		{
			newNode->next = front;
			front = newNode;
		}
	}
}

template <class DT>
DT Queue<DT>::getRear()
{
	QueueNode<DT>* temp = NULL;
	QueueNode<DT>* prior = NULL;
	DT data;

	if (isEmpty())
		cout << "Queue is Empty" << endl;
	else
	{
		temp = rear;
		data = rear->dataItem;

		if (front == rear)
		{
			front = NULL;
			rear = NULL;
		}
		else
		{
			prior = front;

			while (prior->next != rear)
				prior = prior->next;

			rear = prior;
			rear->next = NULL;
		}

		delete temp;
		temp = NULL;

		return data;
	}
}