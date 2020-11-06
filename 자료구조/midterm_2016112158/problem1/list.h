#pragma once
#include <iostream>
using namespace std;
const int defMaxListSize = 10;
typedef string DataType;
class List
{
public:

	
	List(int maxNumber = defMaxListSize);

	
	~List();

	
	void insert(const DataType& newDataItem);
	
	void remove();     // Remove data item
		
	void replace(const DataType& newDataItem);   // Replace data item
		
	void clear();                                 // Clear list

	
	bool isEmpty() const;                    // List is empty
	bool isFull() const;                     // List is full

	

	
	void showStructure() const;
	
	bool find(const DataType& searchDataItem);   // Find data item
	

private:
	// Data members
	int maxSize,
		size,             // Actual number of data item in the list
		cursor;           // Cursor array index
	DataType* dataItems;  // Array containing the list data item
};