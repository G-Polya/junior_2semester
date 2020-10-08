
#include "listlnk.h"
#include <iostream>

using namespace std;

template<class DT>
ListNode<DT>::ListNode(const DT& nodeData, ListNode* nextPtr)
{
	this->dataItem = nodeData;
	this->next = nextPtr;
}


template<class DT>
List<DT>::List(int ignored)
{
	head = new ListNode<DT>();
	//head->next = NULL;
	cursor = head;
}

//------------------------------------------------

template<class DT>
List<DT>::~List()
{
	clear();
}

//------------------------------------------------


template<class DT>
void List<DT>::insert(const DT& newData)
{
	
	if (!isFull())
	{	
		ListNode<DT>* newNode = new ListNode<DT>(newData, NULL);
		
		if (head == NULL)
		{
			head = newNode;
			cursor = head;
		}
		else
		{
			if (cursor->next != NULL)		// cursor가 List의 끝이 아닐 경우
			{
				newNode->next = cursor->next;
				cursor->next = newNode;
				cursor = newNode;
			}
			else                          // cursor가 List의 끝에 있을 경우
			{
				cursor->next = newNode;
				cursor = newNode;
			}
			
		}
	}
	else
		cout << "List is Full" << endl;

}

//------------------------------------------------


template<class DT>
void List<DT>::remove()
{
	if (!isEmpty())
	{
		ListNode<DT>* tempNode = cursor;
		if (cursor->next != NULL)
		{
			ListNode<DT>* prior = getPrior();
			prior->next = cursor->next;
			cursor = cursor->next;
			delete tempNode;
		}
		else 
		{
			ListNode<DT>* prior = getPrior();
			prior->next = NULL;
			cursor = head;
			delete tempNode;
		}

		if (cursor == head)
		{
			cursor->next = NULL;
			cursor = NULL;
			delete tempNode;
		}

		
	}
	else
		cout << "List is Empty" << endl;
	
}


//------------------------------------------------


template<class DT>
void List<DT>::replace(const DT& newData)
{
	if (!isEmpty())
		cursor->dataItem = newData;
	else
		cout << "List is Empty" << endl;
}

//------------------------------------------------


template<class DT>
void List<DT>::clear()
{
	gotoEnd();
	while (!isEmpty())
		remove();
}

//------------------------------------------------


template<class DT>
bool List<DT>::isEmpty() const
{
	return (head == NULL);
}

//------------------------------------------------


template<class DT>
bool List<DT>::isFull() const
{
	ListNode<DT>* tempNode = new ListNode<DT>();
	if (tempNode == NULL)
		return true;
	else
	{
		delete tempNode;
		return false;
	}
}

//------------------------------------------------


template<class DT>
void List<DT>::gotoBeginning()
{
	if (!isEmpty())
		cursor = head;
	else
		cout << "List is Empty" << endl;
}

//------------------------------------------------


template<class DT>
void List<DT>::gotoEnd()
{
	ListNode<DT>* tempNode = head;

	while (!tempNode->next)
		tempNode = tempNode->next;
	
	cursor = tempNode;
}

//------------------------------------------------


template<class DT>
bool List<DT>::gotoNext()
{
	if (!isEmpty())
	{
		if (cursor->next != NULL)
		{
			cursor = cursor->next;
			return true;
		}
		else
			return false;
	}
	else
	{
		cout << "List is Empty" << endl;
		return false;
	}
	
}

//------------------------------------------------

template<class DT>
ListNode<DT>* List<DT>::getPrior()		// get prior node pointer of current cursor
{	
	if (!isEmpty())
	{
		ListNode<DT>* tempNode = head;

		while (!tempNode->next)
		{
			tempNode = tempNode->next;
			if (tempNode->next == cursor)
				return tempNode;
		}
	}
	else
		cout << "List is Empty" << endl;
	
}
//------------------------------------------------

template<class DT>
bool List<DT>::gotoPrior()
{
	if (!isEmpty())
	{
		ListNode<DT>* tempNode = head;

		while (!tempNode->next)
		{
			tempNode = tempNode->next;
			if (tempNode->next = cursor)
				return true;
			else
				return false;
		}
	}
	else
	{
		cout << "List is Empty" << endl;
		return false;
	}


}

//------------------------------------------------


template<class DT>
DT& List<DT>::getCursor() const
{
	if (!isEmpty())
	{
		return cursor->dataItem;
	}
	else
		cout << "List is Empty" << endl;
		
	
}

template<class DT>
void List<DT>::showStructure() const
{
	if (!isEmpty())
	{
		for (ListNode<DT>* iter = head; iter = iter->next; iter != NULL)
		{
			cout << iter->dataItem << " ";
		}
		cout << endl;
	}
	else
		cout << "Empty List" << endl;
}

//------------------------------------------------

//use in-lab
template<class DT>
void List<DT>::insertBefore(const DT& newElement) {
    if (cursor == head) {
        ListNode<DT>* node = new ListNode<DT>(newElement, head);
        head = node; cursor = node;
    }
    else {
        gotoPrior();
        insert(newElement);
    }
}
