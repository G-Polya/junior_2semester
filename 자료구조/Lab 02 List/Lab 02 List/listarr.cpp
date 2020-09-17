//--------------------------------------------------------------------
//
//                                                       listarr.cpp
//
//  SOLUTION: Array implementation of the List ADT
//
//--------------------------------------------------------------------

// 2016112158 �����
#include "listarr.h"
#include <iomanip>
using namespace std;

//--------------------------------------------------------------------

List::List(int maxNumber): maxSize(maxNumber), size(0), cursor(-1)

// Creates an empty list. Allocates enough memory for maxNumber
// data items (defaults to defMaxListSize).
{
	// pre-lab
	dataItems = new char[maxSize];
}

//--------------------------------------------------------------------

List:: ~List()
// Frees the memory used by a list.

{
	// pre-lab
	delete[] dataItems;

}

//--------------------------------------------------------------------

void List::insert(const DataType& newDataItem)
throw (logic_error)

// Inserts newDataItem after the cursor. If the list is empty, then
// newDataItem is inserted as the first (and only) data items in the
// list. In either case, moves the cursor to newDataItem.

{

	// pre-lab
	if (isFull())
	{
		cout << "List is full. You cannot insert" << endl;
		return;
	}

	if (cursor == size - 1)
	{
		cursor++;
		size++;
		dataItems[cursor] = newDataItem;

	}
	else
	{
		cursor = size;
		size++;
		dataItems[cursor] = newDataItem;
	}
	
}

//--------------------------------------------------------------------

void List::remove() throw (logic_error)

// Removes the data items  marked by the cursor from a list. Moves the
// cursor to the next data item item in the list. Assumes that the
// first list data items "follows" the last list data item.
{
	// pre-lab
	if (isEmpty())
	{
		cout << "List is empty. You cannot remove" << endl;
		return;
	}
		
	if (cursor == size - 1)
	{
		dataItems[cursor] = NULL;
		cursor--;
		size--;
	}
	else
	{
		dataItems[cursor] = dataItems[size - 1];
		size--;
	}

	
}

//--------------------------------------------------------------------

void List::replace(const DataType& newDataItem)
throw (logic_error)

// Replaces the item marked by the cursor with newDataItem and
// leaves the cursor at newDataItem.
{
	// Requires that the list is not empty
	// pre-lab
	if (isEmpty())
		return;

	dataItems[cursor] = newDataItem;
}
//--------------------------------------------------------------------

void List::clear()
// Removes all the data items from a list.
{
	for (int i = 0; i < size; i++)
		dataItems[i] = NULL;
	cursor = -1;
	size = 0;
}

//--------------------------------------------------------------------

bool List::isEmpty() const
// Returns 1 if a list is empty. Otherwise, returns 0.
{
	// pre-lab

	return !this->size;
}

//--------------------------------------------------------------------

bool List::isFull() const
// Returns 1 if a list is full. Otherwise, returns 0.
{
	// pre-lab
	if (this->size == this->maxSize)
		return true;
	else
		return false;

}

//--------------------------------------------------------------------

bool List::gotoBeginning() throw (logic_error)
// Moves the cursor to the beginning of the list.
{
	// pre-lab
	cursor = 0;
	
	return true;
}

//--------------------------------------------------------------------

bool List::gotoEnd() throw (logic_error)

// Moves the cursor to the end of the list.

{
	// pre-lab
	cursor = size - 1;

	return 1;
}

//--------------------------------------------------------------------

bool List::gotoNext() throw (logic_error)

// If the cursor is not at the end of a list, then moves the
// cursor to the next item in the list and returns true. Otherwise,
// returns false.
{
	// pre-lab
	if (cursor != maxSize - 1)
	{
		cursor++;
		cout << "Output : " << dataItems[cursor] << endl;
		return true;
	}
	else
		return false;

}

//--------------------------------------------------------------------

bool List::gotoPrior() throw (logic_error)

// If the cursor is not at the beginning of a list, then moves the
// cursor to the preceeding item in the list and returns true.
// Otherwise, returns false.

{
	// pre-lab
	if (cursor != -1)
	{
		cursor--;
		cout << "Output : " << dataItems[cursor] << endl;
		return true;
	}
	else
		return false;

}

//--------------------------------------------------------------------

DataType List::getCursor() const throw (logic_error)
// Returns the item marked by the cursor.

{
	// pre-lab
	return dataItems[cursor];

}

//--------------------------------------------------------------------

void List::showStructure() const
// Outputs the data items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing/debugging
// purposes only.

{
     // pre-lab
	if (isEmpty())
		cout << "Empty list" << endl;
	else
	{
		cout << "Size: " << size << " Cursor: " << cursor << endl;
		for (int i = 0; i < maxSize; i++)
		{
			
			cout << setw(5) << "[" << i << "]" ;
			
		}
		cout << endl;

		for (int i = 0; i < size; i++)
		{
			
			cout << setw(7) << dataItems[i];
		}
		

	}
	
}

//--------------------------------------------------------------------

//in-lab
void List::countBases(List& dnasequence, int& aCount, int& cCount, int& tCount, int& gCount)
{
	aCount = 0, cCount = 0, tCount = 0, gCount = 0;
	for (int i = 0; i < maxSize; i++)
	{
		switch (dataItems[i])
		{
		case 'A':
			aCount++;
			break;
		case 'C':
			cCount++;
			break;
		case 'G':
			gCount++;
			break;
		case 'T':
			tCount++;
			break;
		}
	}

}