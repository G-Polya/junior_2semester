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

		if (isEmpty())		// ��������� front, rear ��� newNode�� ����Ű�� ��
		{
			front = newNode;
			rear = newNode;
		}
		else
		{
			
			rear->next = newNode; // ������� ������ rear�� ������ newNode�� ����Ű�� �ϰ�
			rear = newNode;       // rear�� ��ġ�� newNode�� �̵�(�������� �̵�)
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
		QueueNode<DT>* temp = front;  // ������ ��带 ����Ű�� temp
		DT data = temp->dataItem;

		if (front == rear)			// queue�� ���Ұ� 1��(front) ���� 
		{
			front = NULL;
			rear = NULL;
		}
		else
			front = front->next;		// �������� front ��ġ �̵�
		
		delete temp;		// ��� ����
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
			newNode->next = front;	// newNode�� ������ ������ front�� �ΰ�
			front = newNode;		// front��ġ�� newNode�� �ű�
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
		QueueNode<DT>* temp = rear; // ������ ��带 ����Ű�� temp
		data = temp->dataItem;

		if (front == rear)		// queue�� ����ϳ��� ��������
		{
			front = NULL;
			rear = NULL;
		}
		else
		{
			QueueNode<DT>* prior = front;

			while (prior->next != rear)
				prior = prior->next;		// prior�� rear �ٷ� ���� ��尡 �ȴ�. 

			rear = prior;			// rear ��ġ�� �ٷ� ���� ���� �̵�
			rear->next = NULL;
			prior = NULL;
		}

		delete temp;
		temp = NULL;

		return data;
	}
}