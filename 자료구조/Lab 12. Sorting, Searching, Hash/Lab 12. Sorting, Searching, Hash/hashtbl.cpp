#include <iostream>
#include "hashtbl.h"

template < class DT, class KF >
HashTbl<DT, KF>::HashTbl(int initTableSize):tableSize(initTableSize) {
    dataTable = new List<DT>[tableSize];
}

template < class DT, class KF >
HashTbl<DT, KF>::~HashTbl() {
    delete[] dataTable;
}

template < class DT, class KF >
void HashTbl<DT, KF>::insert(const DT& newDataItem) throw (bad_alloc) {
	int index = newDataItem.hash(newDataItem.getKey()) % tableSize;

	if (dataTable[index].isEmpty())
		dataTable[index].insert(newDataItem);
	else
	{
		dataTable[index].gotoBeginning();

		do
		{
			if (dataTable[index].getCursor().getKey() == newDataItem.getKey())
			{
				dataTable[index].replace(newDataItem);
				return;
			}
		} while (dataTable[index].gotoNext());

		dataTable[index].insert(newDataItem);
	}

}

template < class DT, class KF >
bool HashTbl<DT, KF>::remove(KF searchKey) {
	DT temp;
	int index = temp.hash(searchKey) % tableSize;

	if (dataTable[index].isEmpty())
		return false;

	dataTable[index].gotoBeginning();

	do
	{
		if (dataTable[index].getCursor().getKey() == searchKey)
		{
			dataTable[index].remove();
			return true;
		}
	} while (dataTable[index].gotoNext());

	return false;
}

template < class DT, class KF >
bool HashTbl<DT, KF>::retrieve(KF searchKey, DT& dataItem) {
	int index = dataItem.hash(searchKey) % tableSize;

	if (dataTable[index].isEmpty())
		return false;

	dataTable[index].gotoBeginning();

	do
	{
		if (dataTable[index].getCursor().getKey() == searchKey)
		{
			dataItem = dataTable[index].getCursor();
			return true;
		}
	} while (dataTable[index].gotoNext());

	return false;
}

template < class DT, class KF >
void HashTbl<DT, KF>::clear() {
	for (int i = 0; i < tableSize; i++)
		dataTable[i].clear();
}

template < class DT, class KF >
bool HashTbl<DT, KF>::isEmpty() const {
	for (int i = 0; i < tableSize; i++)
		if (!dataTable[i].isEmpty())
			return false;

	return true;
}

template < class DT, class KF >
bool HashTbl<DT, KF>::isFull() const {
	for (int i = 0; i < tableSize; i++)
		if (!dataTable[i].isFull())
			return false;

	return true;
}

template < class DT, class KF >
void HashTbl<DT, KF>::showStructure() const
{
    for (int i = 0; i < tableSize; i++)
    {
        cout << i << ": ";
        if (dataTable[i].isEmpty())
            cout << "_";
        else
        {
            dataTable[i].gotoBeginning();
            do {
                cout << dataTable[i].getCursor().getKey() << " ";
            } while (dataTable[i].gotoNext());
        }
        cout << endl << endl;
    }
}
