
// 2016112158 김희수
#include "listarr.h"
#include <iomanip>
using namespace std;

//--------------------------------------------------------------------


List::List(int maxNumber): maxSize(maxNumber), size(0), cursor(-1)
{
	// pre-lab
	dataItems = new Person[maxSize];
}

//--------------------------------------------------------------------

List:: ~List()
// Frees the memory used by a list.

{
	// pre-lab
	delete[] dataItems;

}

//--------------------------------------------------------------------
void List::insert(const Person& newDataItem)
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
		dataItems[cursor] = Person(NULL, NULL, NULL);
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

void List::replace(const Person& newDataItem)
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
		dataItems[i] = Person(NULL,NULL,NULL);
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

void List::read()
{
	string fileName;
	//cout << "Enter the name of the file: ";
	//cin >> fileName;
	//fileName = fileName + ".txt";
	fileName = "FriendFile.txt";
	fstream in;
	in.open(fileName);

	string s;
	int count = 0;
	if (!in.is_open())
		cout << "파일 열기 실패" << endl;
	else
	{
		while (getline(in, s))
		{
			count++;
			cout << s << endl;
		}
		in.close();

		cout << "Count : " << count << endl;
	}
	
	in.open(fileName);
	if (!in.is_open())
		cout << "파일 열기 실패" << endl;
	else
	{
		string* stringList = new string[count];
		int i = 0;

		while (getline(in, s))
			stringList[i++] = s;
		in.close();
		
		int numberOfentry = (count + 1) / 4;
		cout << "Total number of entries in the list: " << numberOfentry << endl;
		for (int i = 0; numberOfentry; i++)
		{
			dataItems[i].setAll(stringList[0 + 4 * i], stringList[1 + 4 * i], stringList[2 + 4 * i]);
		}
	}
	
	
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

	return true;
}

//--------------------------------------------------------------------

bool List::gotoNext() throw (logic_error)

// If the cursor is not at the end of a list, then moves the
// cursor to the next item in the list and returns true. Otherwise,
// returns false.
{
	// pre-lab
	if (cursor != size - 1)
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

Person List::getCursor() const throw (logic_error)
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
	
}