
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
	head = NULL;
//	head->next = NULL;
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
			else                           // cursor가 List의 끝일 경우
			{
				cursor->next = newNode;
				cursor = newNode;
			}
			
		}
	}
	else
		cout << "List is Full" << endl;

	//showStructure();
}

//------------------------------------------------


template<class DT>
void List<DT>::remove()
{
	if (!isEmpty())
	{
		ListNode<DT>* tempNode = cursor;
	
		
		if (cursor == head && cursor->next == NULL)				// List에 노드 하나만 있을 경우, cursor가 head를 가리킴 ex) 1
		{
			delete tempNode;
			head = NULL;
			cursor = head;
		}
		else if (cursor == head && cursor->next != NULL)		// List에 여러개 있고, cursor는 head를 가리킴
		{
			cursor = cursor->next;
			head = cursor;
			delete tempNode;
		}
		else if (cursor->next != NULL)							// List에 여러개 있고, cursor는 head가 아니고 끝의 원소도 아님
		{
			ListNode<DT>* prior = getPrior();
			prior->next = cursor->next;
			cursor = cursor->next;
			delete tempNode;
		}
		else if(cursor->next == NULL)							// List에 여러개 있고, cursor는 끝을 가리킴
		{
			ListNode<DT>* prior = getPrior();
			prior->next = NULL;
			cursor = head;
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
	if (!isEmpty())
		while (cursor->next)
			cursor = cursor->next;
	else
		cout << "List is Empty" << endl;
}

//------------------------------------------------

template<class DT>
ListNode<DT>* List<DT>::getNext()
{
	if (!isEmpty())
	{
		if (cursor->next != NULL)
		{
			cursor = cursor->next;
			return cursor;
		}
	}
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

template<class DT>
bool List<DT>::hasNext()
{
	if (!isEmpty())
	{
		if (cursor->next != NULL)
		{
			// cursor = cursor->next;
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

		while (tempNode->next)
		{
			if (!head->next->next)
				return tempNode;
			else
			{
				tempNode = tempNode->next;
				if (tempNode->next == cursor)
					return tempNode;
			}
			
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
		if (cursor == tempNode)
			return false;

		while (tempNode->next)
		{
			if (!head->next->next)
			{
				cursor = tempNode;
				return true;
			}
			else
			{
				
				tempNode = tempNode->next;
				if (tempNode->next == cursor)
				{
					cursor = tempNode;

					return true;
				}
				
				
			}
			
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
}



template<class DT>
void List<DT>::showStructure() const
{
	
	// cout<<"Loc: " << getCursorloc() << endl;
	if (!isEmpty())
	{
		for (ListNode<DT>* iter = head; iter != NULL; iter = iter->next)
			cout << iter->dataItem << " ";
			
		
		cout << endl;
		
		for (auto iter = head; iter!= cursor->next; iter = iter->next)
		{
			if (iter != cursor)
				cout << "  ";
			else if (iter == cursor)
				cout << "^";
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

