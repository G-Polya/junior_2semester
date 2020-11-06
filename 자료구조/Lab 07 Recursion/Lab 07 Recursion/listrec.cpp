//--------------------------------------------------------------------
//
//  Laboratory 10                                         listrec.cs
//
//  (Shell) Partial linked list implementation of the List ADT with
//  additional recursive linked list functions
//
//--------------------------------------------------------------------

#include <iostream>
#include "stacklnk.cpp"
#include "listrec.h"
// 2016112158 김희수
using namespace std;

//--------------------------------------------------------------------
//
// Insert your singly linked list implementations (from Laboratory 7)
// of the following functions:
//
//   - The ListNode class constructor
//
//   - The List class constructor, destructor, insert(), clear(), and
//     showstructure() functions. You may also need to add empty()
//     full(), and others.
//
//--------------------------------------------------------------------



//--------------------------------------------------------------------
//
// Recursively implemented linked list functions used in the Prelab
// Exercise
//
//--------------------------------------------------------------------



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

template<class DT>
void List<DT>::clear()
{
	if (head == NULL)
		cout << "Empty List" << endl;
	else
	{
		ListNode<DT>* temp;
		while (head == NULL)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
		head = NULL;
		cursor = NULL;
	}
	
}

template<class DT>
void List<DT>::showStructure() const
{
	if (head == NULL) 
	{
		cout << "Empty list" << endl;
	}
	else
	{
		ListNode<DT>* location = new ListNode<DT>(NULL, NULL);
		location = head;

		while (location->next != 0)
		{
			cout << location->dataItem << " | "; // print data item
			location = location->next;
		}

		cout << location->dataItem << endl; // print last data item
	}
}

template < class DT >
void List<DT>:: write () const

// Outputs the data in a list from beginning to end. Assumes that
// objects of type DT can be output to the cout stream.

{
    cout << "List : ";
    writeSub(head);
    cout << endl;
}



// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>:: writeSub ( ListNode<DT> *p ) const

// Recursive partner of the write() function. Processes the sublist
// that begins with the node pointed to by p.

{
    if ( p != 0 )
    {
       cout << p->dataItem;      // Output data
       writeSub(p->next);    // Continue with next node
    }
}

//--------------------------------------------------------------------

template < class DT >
void List<DT>:: insertEnd ( const DT &newDataItem )

// Inserts newDataItem at the end of a list. Moves the cursor to
// newDataItem.

{
    insertEndSub(head,newDataItem);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>:: insertEndSub ( ListNode<DT> *&p,
                               const DT &newDataItem )

// Recursive partner of the insertEnd() function. Processes the
// sublist that begins with the node pointed to by p.

{
    if ( p != 0 )
       insertEndSub(p->next,newDataItem);    // Continue searching for
    else                                     // end of list
    {
       p = new ListNode<DT>(newDataItem,0);  // Insert new node
       cursor = p;                           // Move cursor
    }
}

//--------------------------------------------------------------------

template < class DT >
void List<DT>:: writeMirror () const

// Outputs the data in a list from beginning to end and back
// again. Assumes that objects of type DT can be output to the cout
// stream.

{
    cout << "Mirror : ";
    writeMirrorSub(head);
    cout << endl;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>:: writeMirrorSub ( ListNode<DT> *p ) const

// Recursive partner of the writeMirror() function. Processes the
// sublist that begins with the node pointed to by p.

{
    if ( p != 0 )
    {
       cout << p->dataItem;           // Output data (forward)
       writeMirrorSub(p->next);   // Continue with next node
       cout << p->dataItem;           // Output data (backward)
    }
}

//--------------------------------------------------------------------

template < class DT >
void List<DT>:: reverse ()

// Reverses the order of the data items in a list.

{
    reverseSub(0,head);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>:: reverseSub ( ListNode<DT> *p, ListNode<DT> *nextP )

// Recursive partner of the reverse() function. Processes the sublist
// that begins with the node pointed to by nextP.

{
    if ( nextP != 0 )
    {
       reverseSub(nextP,nextP->next);   // Continue with next node
       nextP->next = p;                 // Reverse link
    }
    else
       head = p;                        // Move head to end of list
}

//--------------------------------------------------------------------

template < class DT >
void List<DT>:: deleteEnd ()

// Deletes the data at the end of a list. Moves the cursor to the
// beginning of the list.

{
    deleteEndSub(head);
    cursor = head;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>:: deleteEndSub ( ListNode<DT> *&p )

// Recursive partner of the deleteEnd() function. Processes the
// sublist that begins with the node pointed to by p.

{
    if ( p->next != 0 )
       deleteEndSub(p->next);   // Continue looking for the last node
    else
    {
       delete p;                // Delete node
       p = 0;                   // Set p (link or head) to null
    }
}

//--------------------------------------------------------------------

template < class DT >
int List<DT>:: getLength () const

// Returns the number of data items in a list.

{
    return getLengthSub(head);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
int List<DT>:: getLengthSub ( ListNode<DT> *p ) const

// Recursive partner of the length() function. Processes the sublist
// that begins with the node pointed to by p.

{
    int result;   // Result returned

    if ( p == 0 )
       result = 0;                            // End of list reached
    else
       result = ( getLengthSub(p->next) + 1 );   // Number of nodes after
                                              // this one + 1
    return result;
}

template<class DT>
void List<DT>::iterReverse()
{
	ListNode<DT>* next;
	ListNode<DT>* current = head->next;
	head->next = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = head;
		head = current;
		current = next;
	}

}

template<class DT>
void List<DT>::stackWriteMirror() const
{
	Stack<DT> stk;
	ListNode<DT>* p = head;
	cout << "StackMirror : ";
	while (p != NULL)
	{
		cout << p->dataItem;
		stk.push(p->dataItem);
		p = p->next;
	}
	while (!stk.isEmpty())
		cout << stk.pop();
	cout << endl;
}