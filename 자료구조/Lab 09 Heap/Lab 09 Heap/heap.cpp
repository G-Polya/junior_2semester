//--------------------------------------------------------------------
//
//  Laboratory 13                                             heap.cpp
//
//  Actual implementation of class in the Heap ADT
//--------------------------------------------------------------------

#include "heap.h"
#include <iostream>
using namespace std;
//--------------------------------------------------------------------


template<class DT>
Heap<DT>::Heap(int maxNumber) throw(bad_alloc)
{
	maxSize = maxNumber;
	size = 0;
	dataItems = new DT[maxSize];
	for (int i = 0; i < maxSize; i++)
		dataItems[i].setPty(0);
}

template < class DT >
Heap<DT>::~Heap()
{
	delete[] dataItems;
}

//--------------------------------------------------------------------

template < class DT >
void Heap<DT>::insert(const DT& newElement)
{
	if (isFull())
		cout << "Heap is Full" << endl;
	else
	{
		dataItems[size] = newElement;
		
		int btm = size;
		int parent = (btm - 1) / 2;

		while (btm > 0)
		{
			parent = (btm - 1) / 2;
			if (dataItems[parent].pty() < dataItems[btm].pty())
			{
				DT temp = dataItems[parent];
				dataItems[parent] = dataItems[btm];
				dataItems[btm] = temp;
			}
			btm = (btm - 1) / 2;
		}
		size++;
	}
}


template < class DT >
DT Heap<DT>::removeMax()
{
	if (isEmpty())
	{
		DT result;
		result.setPty(0);
		return result;
	}
	else
	{
		DT result = dataItems[0];
		dataItems[0] = dataItems[size - 1];
		size--;

		int parent = 0;
		int child = parent * 2 + 1;		// 초기 max는 left로 설정

		while (child < size)
		{
			if (child + 1 < size)
				if (dataItems[child].pty() < dataItems[child + 1].pty())	// left가 right보다 작다면 max를 right로 설정
					child++;

			if (dataItems[parent].pty() < dataItems[child].pty())
			{
				DT temp = dataItems[parent];
				dataItems[child] = dataItems[parent];
				dataItems[parent] = temp;
				parent = child;
				child = parent * 2 + 1;
			}
			else
				break;
		}
		return result;
	}
}

template < class DT >
void Heap<DT>::clear()
{
	size = 0;
}

//--------------------------------------------------------------------

template < class DT >
bool Heap<DT>::isEmpty() const
{
	if (size == 0)
		return true;
	else
		return false;
}

template < class DT >
bool Heap<DT>::isFull() const
{
	if (size == maxSize)
		return true;
	else
		return false;
}

//--------------------------------------------------------------------

template < class HD >
void Heap<HD>:: showStructure () const

// Outputs the priorities of the data in a heap in both array
// and tree form. If the heap is empty, outputs "Empty heap". This
// operation is intended for testing/debugging purposes only.

{
    int j;   // Loop counter

    cout << endl;
    if ( size == 0 )
       cout << "Empty heap" << endl;
    else
    {
       cout << "size = " << size << endl;       // Output array form
       for ( j = 0 ; j < maxSize ; j++ )
           cout << j << "\t";
       cout << endl;
       for ( j = 0 ; j < size ; j++ )
           cout << dataItems[j].pty() << "\t";
       cout << endl << endl;
       showSubtree(0,0);                        // Output tree form
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void Heap<DT>:: showSubtree ( int index, int level ) const

// Recursive partner of the showStructure() function. Outputs the
// subtree (subheap) whose root is stored in dataItems[index]. Argument
// level is the level of this dataItems within the tree.

{
     int j;   // Loop counter

     if ( index < size )
     {
        showSubtree(2*index+2,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )        // Tab over to level
            cout << "\t";
        cout << " " << dataItems[index].pty();   // Output dataItems's pty
        if ( 2*index+2 < size )                // Output "connector"
           cout << "<";
        else if ( 2*index+1 < size )
           cout << "\\";
        cout << endl;
        showSubtree(2*index+1,level+1);        // Output left subtree
    }
}