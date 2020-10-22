#include <iostream>
#include <assert.h>
#include "listdbl.h"

using namespace std;

template < class DT >
ListNode<DT>::ListNode(const DT& data, ListNode* priorPtr, ListNode* nextPtr)
	:dataItem(data), prior(priorPtr), next(nextPtr)
{

}

// Constructor
template < class DT >
List<DT>::List(int ignored)
	: head(NULL), cursor(NULL)
{

}

// Destructor
template < class DT >
List<DT>::~List()
{
	clear();
}


//------------ List manipulation operations ------------------

// Insert after cursor
template < class DT >
void List<DT>::insert(const DT& newDataItem)
{
	if(isFull())
		cout << "List is Full" << endl;
	else
	{
		ListNode<DT>* newNode = new ListNode<DT>(newDataItem, NULL, NULL);

		if (isEmpty())							// ����ִ� ����Ʈ�� ó������ ������ ���
		{
			head = newNode;
			cursor = head;
		}
		else
		{
			newNode->prior = cursor;

			if (cursor->next != NULL)				// ����Ʈ �߰��� ������ ���
			{
				newNode->next = cursor->next;
				cursor->next->prior = newNode;
			}

			cursor->next = newNode;
			cursor = newNode;
		}
	}
}

// Remove data item
template < class DT >
void List<DT>::remove()
{
	if (!isEmpty())
	{
		ListNode<DT>* temp = cursor;
		if (temp == head)			// ù��° ���Ҹ� ������� ���
		{
			if (cursor->next == NULL)	// ���� ���Ұ� ���� ��Ȳ���� ù��°�� ������� ��(����Ʈ�� ���� 1��)
			{
				delete temp;
				head = NULL;
				cursor = NULL;
			}
			else
			{
				head = cursor->next;
				gotoBeginning();
				temp->next = NULL;
				cursor->prior = NULL;
				delete temp;
			}
		}
		else if (cursor->next == NULL)	// ������ ���Ҹ� ������� ��
		{
			cursor->prior->next = NULL;
			gotoBeginning();
			delete temp;
		}
		else
		{
			// ����Ʈ �߰��� ���Ҹ� ������� ��
			cursor->prior->next = cursor->next;
			cursor->next->prior = cursor->prior;
			gotoNext();
			delete temp;
		}
	}
	else
		cout << "Empty List" << endl;
}

// Replace data item
template < class DT >
void List<DT>::replace(const DT& newElement)
{
	if (!isEmpty())
		cursor->dataItem = newElement;
	else
		cout << "Empty List" << endl;
}

// Clear list
template < class DT >
void List<DT>::clear()
{
	gotoBeginning();
	while (head != NULL)
		remove();
}


//------------ List status operations ------------------

// List is empty
template < class DT >
bool List<DT>::isEmpty() const
{
	return (head == NULL);
}

// List is full
template < class DT >
bool List<DT>::isFull() const
{
	ListNode<DT>* temp = new ListNode<DT>(NULL, NULL, NULL);
	if (temp == NULL)
		return true;
	else
	{
		delete temp;
		return false;
	}

}


//------------ List manipulation operations ------------------

// Go to beginning
template < class DT >
void List<DT>::gotoBeginning()
{
	if (!isEmpty())
		cursor = head;
	else
		cout << "Empty List" << endl;
}

// Go to end
template < class DT >
void List<DT>::gotoEnd()
{
	if (!isEmpty())
	{
		while (cursor->next != NULL)		// �������Ұ� �������� ���������� �ݺ�
			gotoNext();
	}
	else
		cout << "Empty List" << endl;
}

// Go to next data item
template < class DT >
bool List<DT>::gotoNext()
{
	if (!isEmpty() && (cursor->next != NULL))	// ����Ʈ�� ������� �ʰ� ���� Ŀ���� �������Ұ� �����Ѵٸ�
	{
		cursor = cursor->next;
		return true;
	}
	else
		return false;
}

// Go to prior data item
template < class DT >
bool List<DT>::gotoPrior()
{
	if (!isEmpty() && (cursor != head))		// ������� �ʰ� ����Ŀ���� head�� �ƴ϶��, �� ���� Ŀ���� ù��°�� �ƴ϶��
	{
		cursor = cursor->prior;
		return true;
	}
	else
		return false;
}


template < class DT >
DT List<DT>::getCursor() const
{
	if (!isEmpty())
		return cursor->dataItem;
	else
		cout << "Empty List" << endl;
}


//-----------------------------------------------------------

template < class DT >
void List<DT>::showStructure() const
{
	ListNode<DT>* p;   

	if (head == NULL)
		cout << "Empty list" << endl;
	else
	{
		p = head;
		do
		{
			if (p == cursor)
				cout << "[" << p->dataItem << "] ";
			else
				cout << p->dataItem << " ";
			p = p->next;
		} while (p != NULL);
		cout << endl;
	}
}


//-----------------------------------------------------------

// In-lab opertions
template < class DT >
void List<DT>::reverse()
{
	//if (isEmpty())
	//	cout << "Empty List" << endl;
	//else
	//{
	//	ListNode<DT>* first = head;			
	//	ListNode<DT>* last = cursor;	// ���������� ����
	//	
	//	while (last->next != NULL)		// ������ �����ϵ��� last �����͸� ������ �̵�
	//		last = last->next;

	//	while (first != last)
	//	{
	//		// data swap
	//		DT temp = first->dataItem;
	//		first->dataItem = last->dataItem;
	//		last->dataItem = temp;


	//		first = first->next;
	//		last = last->prior;
	//	}
	//}
	if (isEmpty())
		cout << "Empty List" << endl;
	else
	{
		ListNode<DT>* tempPtr = new ListNode<DT>(NULL, NULL, NULL);
		ListNode<DT>* headPtr = head;
		
		while (headPtr != NULL)
		{
			tempPtr = headPtr->prior;
			headPtr->prior = headPtr->next;
			headPtr->next = tempPtr;
			headPtr = headPtr->prior;
		}

		if (tempPtr != NULL)
			head = tempPtr->prior;
	}
}

//-----------------------------------------------------------