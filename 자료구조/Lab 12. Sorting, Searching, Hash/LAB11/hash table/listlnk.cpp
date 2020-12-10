#include <iostream>
#include "listlnk.h"

using namespace std;

template<class DT>
ListNode<DT>::ListNode(const DT& nodeData, ListNode* nextPtr)
	:dataItem(nodeData),
	next(nextPtr)
{

}


template<class DT>
List<DT>::List(int ignored)
	:cursor(0), head(0)
{

}

//------------------------------------------------

template<class DT>
List<DT>::~List()
{
	List<DT>::clear();
}

//------------------------------------------------


template<class DT>
void List<DT>::insert(const DT& newData)
{
	if (!List<DT>::isFull()) {
		if (head == NULL) {
			head = new ListNode<DT>(newData, NULL);
			cursor = head;
		}
		else if (cursor->next == NULL) {
			ListNode<DT>* temp = cursor;
			cursor = new ListNode<DT>(newData, NULL);
			temp->next = cursor;
		}
		else {
			ListNode<DT>* temp = new ListNode<DT>(newData, cursor->next);
			cursor->next = temp;
			cursor = cursor->next;
		}

	}
}

//------------------------------------------------


template<class DT>
void List<DT>::remove()
{
	if (!List<DT>::isEmpty()) {
		if (head->next == NULL) {
			delete head;
			head = cursor = NULL;
		}
		else if (cursor == head) {
			cursor = cursor->next;
			delete head;
			head = cursor;
		}
		else {
			ListNode<DT>* temp = cursor;
			gotoPrior();
			cursor->next = temp->next;
			delete temp;
		}
		if (cursor != head) {
			cursor = cursor->next;
		}
	}
	else cout << "Empty list";
}



//------------------------------------------------


template<class DT>
void List<DT>::replace(const DT& newData)
{
	if (!List<DT>::isEmpty()) {
		cursor->dataItem = newData;
	}
}

//------------------------------------------------


template<class DT>
void List<DT>::clear()
{
	ListNode<DT>* tempNode;
	while (head != NULL) {
		tempNode = head;
		head = head->next;
		delete tempNode;
	}
	cursor = NULL;
}

//------------------------------------------------


template<class DT>
bool List<DT>::isEmpty() const
{
	if (head == NULL)
		return true;
	else 
		return false;
}

//------------------------------------------------


template<class DT>
bool List<DT>::isFull() const
{
	return false;
}

//------------------------------------------------


template<class DT>
void List<DT>::gotoBeginning()
{
	if (!List<DT>::isEmpty()) {
		cursor = head;
	}
}

//------------------------------------------------


template<class DT>
void List<DT>::gotoEnd()
{
	if (!List<DT>::isEmpty()) {
		while (cursor->next != NULL) {
			gotoNext();
		}
	}
}

//------------------------------------------------


template<class DT>
bool List<DT>::gotoNext()
{
	if (cursor->next != NULL)
	{
		cursor = cursor->next;
		return true;
	}
	else
		return false;
}

//------------------------------------------------


template<class DT>
bool List<DT>::gotoPrior()
{
	ListNode<DT>* tempNode = head;
	if (List<DT>::isEmpty()) {
		return false;
	}
	else if (cursor == head) {
		return false;
	}
	else {
		while (tempNode->next != cursor) {
			tempNode = tempNode->next;
		}
		cursor = tempNode;
		return true;
	}
}

//------------------------------------------------


template<class DT>
DT& List<DT>::getCursor() const
{
	if (!List<DT>::isEmpty()) {
		return cursor->dataItem;
	}
	else cout << "Empty";
}

template<class DT>
void List<DT>::showStructure() const
{
	if (List<DT>::isEmpty()) {
		cout << "Empty list" << endl;
	}
	else {
		cout << "현재 cursor가 가리키는 data: " << cursor->dataItem << endl;
		ListNode<DT>* tempNode = head;
		while (tempNode != NULL) {
			cout << tempNode->dataItem << " ";
			tempNode = tempNode->next;
		}
		cout << endl;
	}
}
