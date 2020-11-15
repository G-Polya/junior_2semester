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
	if (isFull())
		cout << "Queue is Full" << endl;
	else
	{
		QueueNode<DT>* newNode = new QueueNode<DT>(newData, NULL);

		if (isEmpty())		// 비어있으면 front, rear 모두 newNode를 가리키게 함
		{
			front = newNode;
			rear = newNode;
		}
		else
		{
			
			rear->next = newNode; // 비어있지 않으면 rear의 다음이 newNode를 가리키게 하고
			rear = newNode;       // rear의 위치를 newNode로 이동(다음으로 이동)
		}
		newNode = NULL;
		
	}
}

template<class DT>
DT Queue<DT>::dequeue()                             // Dequeue data element
{
	if (isEmpty())
		cout << "Queue is Empty" << endl;
	else
	{
		QueueNode<DT>* temp = front;  // 삭제될 노드를 가리키는 temp
		DT data = temp->dataItem;

		if (front == rear)			// queue에 원소가 1개(front) 남음 
		{
			front = NULL;
			rear = NULL;
		}
		else
			front = front->next;		// 다음으로 front 위치 이동
		
		delete temp;		// 노드 삭제
		temp = NULL;

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
	QueueNode<DT>* ptr = new QueueNode<DT>();
	if (ptr == NULL)
		return true;
	else
	{
		delete ptr;
		return false;
	}
}

template<class DT>
void Queue<DT>::showStructure() const
{
	
	if (isEmpty())
		cout << "Empty Queue" << endl;
	else
	{
		for (auto cursor = front; cursor != NULL; cursor = cursor->next)
			cout<< cursor->dataItem << "\t";
		
		cout << endl;
	}
}

template<class DT>
void Queue<DT>::putFront(const DT& newDataItem) //Lab 2
{
	if (isFull())
		cout << "Queue is Full" << endl;
	else
	{
		QueueNode<DT>* newNode = new QueueNode<DT>(newDataItem, NULL);
		if (isEmpty())
		{
			front = newNode;
			rear = newNode;
		}
		else
		{
			newNode->next = front;	// newNode의 다음을 현재의 front로 두고
			front = newNode;		// front위치를 newNode로 옮김
		}
	}
}

template <class DT>
DT Queue<DT>::getRear()
{
	DT data;

	if (isEmpty())
		cout << "Queue is Empty" << endl;
	else
	{
		QueueNode<DT>* temp = rear; // 삭제될 노드를 가리키는 temp
		data = temp->dataItem;

		if (front == rear)		// queue에 노드하나만 남았으면
		{
			front = NULL;
			rear = NULL;
		}
		else
		{
			QueueNode<DT>* prior = front;

			while (prior->next != rear)
				prior = prior->next;		// prior는 rear 바로 직전 노드가 된다. 

			rear = prior;			// rear 위치를 바로 직전 노드로 이동
			rear->next = NULL;
			prior = NULL;
		}

		delete temp;
		temp = NULL;

		return data;
	}
}