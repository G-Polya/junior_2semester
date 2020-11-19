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
		size++;
		ReheapUp(0, size - 1);
	}
}

template<class DT>
void Heap<DT>::ReheapUp(int root, int btm)
{
	int parent;
	if (btm > root)
	{
		parent = (btm - 1) / 2;
		if (dataItems[parent].pty() < dataItems[btm].pty())
		{
			DT temp = dataItems[parent];
			dataItems[parent] = dataItems[btm];
			dataItems[btm] = temp;
			ReheapUp(root, parent);
		}
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

		int root = 0;
		int btm = size - 1;

		ReheapDown(root, btm);
	}
}
template<class DT>
void Heap<DT>::ReheapDown(int root, int btm)
{
	int maxChild, rightChild, leftChild;

	leftChild = 2 * root + 1;
	rightChild = 2 * root + 2;

	if (leftChild <= btm)
	{
		if (leftChild == btm)
			maxChild = leftChild;
		else
		{
			if (dataItems[leftChild].pty() <= dataItems[rightChild].pty())
				maxChild = rightChild;
			else
				maxChild = leftChild;
		}

		if (dataItems[root].pty() < dataItems[maxChild].pty())
		{
			DT temp = dataItems[maxChild];
			dataItems[maxChild] = dataItems[root];
			dataItems[root] = temp;
		}
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
	return (size == 0);
}

template < class DT >
bool Heap<DT>::isFull() const
{
	return (size == maxSize);
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