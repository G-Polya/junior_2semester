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

		if (isEmpty())							// 비어있는 리스트에 처음으로 삽입할 경우
		{
			head = newNode;
			cursor = head;
		}
		else
		{
			newNode->prior = cursor;

			if (cursor->next != NULL)				// 리스트 중간에 삽입할 경우
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
		if (temp == head)			// 첫번째 원소를 지우려는 경우
		{
			if (cursor->next == NULL)	// 다음 원소가 없는 상황에서 첫번째를 지우려고 함(리스트에 원소 1개)
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
		else if (cursor->next == NULL)	// 마지막 원소를 지우려고 함
		{
			cursor->prior->next = NULL;
			gotoBeginning();
			delete temp;
		}
		else
		{
			// 리스트 중간의 원소를 지우려고 함
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
		while (cursor->next != NULL)		// 다음원소가 존재하지 않을때까지 반복
			gotoNext();
	}
	else
		cout << "Empty List" << endl;
}

// Go to next data item
template < class DT >
bool List<DT>::gotoNext()
{
	if (!isEmpty() && (cursor->next != NULL))	// 리스트가 비어있지 않고 현재 커서의 다음원소가 존재한다면
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
	if (!isEmpty() && (cursor != head))		// 비어있지 않고 현재커서가 head가 아니라면, 즉 현재 커서가 첫번째가 아니라면
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
	//	ListNode<DT>* last = cursor;	// 끝에서부터 시작
	//	
	//	while (last->next != NULL)		// 끝에서 시작하도록 last 포인터를 끝으로 이동
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