
// 2016112158 ±èÈñ¼ö
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "Person.h"
#include "Month.h"
using namespace std;

const int defMaxListSize = 10;   // Default maximum list size



class List
{
public:

	// Constructor
	List(int maxNumber = defMaxListSize);

	// Destructor
	~List();

	// List manipulation operations
	void insert(const Person& newDataItem)    // Insert after cursor
		throw (logic_error);
	void remove()                                 // Remove data item
		throw (logic_error);
	void replace(const Person& newDataItem)   // Replace data item
		throw (logic_error);
	void clear();                                 // Clear list

	string getNamefromMonth(int month);
	int getMonthfromName(string name);
	int getBirthdays(string name);
	void printSummary();

	void read();			// read from file
	void select();			//


	// List status operations
	bool isEmpty() const;                    // List is empty
	bool isFull() const;                     // List is full

	// List iteration operations
	bool gotoBeginning()                     // Go to beginning
		throw (logic_error);
	bool gotoEnd()                           // Go to end
		throw (logic_error);
	bool gotoNext()                          // Go to next data item
		throw (logic_error);
	bool gotoPrior()                         // Go to prior data item
		throw (logic_error);
	Person getCursor() const
		throw (logic_error);                // Return data item

	// Output the list structure -- used in testing/debugging
	void showStructure() const;

	//in-lab
	void countBases(List& dnasequence, int& aCount, int& cCount, int& tCount, int& gCount);

	// In-lab operations
	bool find(const Person& searchDataItem)     // Find data item
		throw (logic_error);

private:
	// Data members
	Month monthes[12];
	int maxSize,
		size,             // Actual number of data item in the list
		cursor;           // Cursor array index
	Person* dataItems;  // Array containing the list data item
};

