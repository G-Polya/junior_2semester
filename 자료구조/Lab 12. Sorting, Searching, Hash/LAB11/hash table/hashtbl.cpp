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

}

template < class DT, class KF >
bool HashTbl<DT, KF>::remove(KF searchKey) {

}

template < class DT, class KF >
bool HashTbl<DT, KF>::retrieve(KF searchKey, DT& dataItem) {

}

template < class DT, class KF >
void HashTbl<DT, KF>::clear() {

}

template < class DT, class KF >
bool HashTbl<DT, KF>::isEmpty() const {

}

template < class DT, class KF >
bool HashTbl<DT, KF>::isFull() const {

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
