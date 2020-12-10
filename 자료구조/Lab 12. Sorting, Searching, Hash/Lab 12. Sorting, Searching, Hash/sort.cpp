//--------------------------------------------------------------------
//
//  Laboratory C, In-lab Exercise 2                        sort.cpp
//
//  Implementation of a set of sorting routines
//
//--------------------------------------------------------------------

template<class DT>
void swap(DT& a, DT& b)
{
	DT temp = a;
	a = b;
	b = temp;
}

template<class DT>
int minIndex(DT keyList[], int start, int end)
{
	int indexOfMin = start;
	for (int i = start + 1; i <= end; i++)
	{
		if (keyList[i] < keyList[indexOfMin])
			indexOfMin = i;
	}
	return indexOfMin;
}

template < class DT >
void selectionSort(DT keyList[], int numKeys)

// Selection sort routine. Sorts the first numKeys keys in keyList
// into ascending order.

{
	int endIndex = numKeys - 1;
	for (int current = 0; current < endIndex; current++)
	{
		swap(keyList[current], keyList[minIndex(keyList, current, endIndex)]);
	}
}

//--------------------------------------------------------------------

template < class DT >
void quickPartition(DT keyList[], int numKeys, int left, int right);

template < class DT >
void quickSort(DT keyList[], int numKeys)

// Quicksort routine. Sorts the first numKeys keys in keyList into
// ascending order.

{
    quickPartition(keyList, numKeys, 0, numKeys - 1);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void quickPartition(DT keyList[], int numKeys,
    int left, int right)

    // Recursive partner of the quickSort routine. Partitions the array
    // entries between left and right into two subarrays. One subarray
    // contains the keys that are less than or equal to splitValue, and
    // the other contains the keys that are greater than splitValue.
    // Recursively sorts each of these subarrays.

{
	
	int i = left, j = right;
		
	int pivot = left;
			

	do
	{

		while (keyList[i] < keyList[pivot]) 
			i++;

		
		while (keyList[pivot] < keyList[j])
			j--;



		if (i <= j)

		{
			swap(keyList[i], keyList[j]);
			i++;                         
			j--;                            
		}

	}while (i <= j);

	if (left < j)
		quickPartition(keyList, numKeys, left, j);

	if (i < right)
		quickPartition(keyList, numKeys, i, right);

}

//--------------------------------------------------------------------
template<class DT>
void bubbleUp(DT keyList[], int start, int end)
{
	for (int index = end; index > start; index--)
		if (keyList[index] < keyList[index - 1])
			swap(keyList[index], keyList[index - 1]);
}


template < class DT >
void bubbleSort(DT keyList[], int numKeys)

{
	int current = 0;
	while (current < numKeys - 1)
	{
		bubbleUp(keyList, current, numKeys - 1);
		current++;
	}
}
