//--------------------------------------------------------------------
//
//  Laboratory 9                                           listdbl.h
//
//  Class declarations for the circular, doubly linked list
//  implementation of the List ADT
//
//--------------------------------------------------------------------

#include <new>
#include <stdexcept>

using namespace std;

template < class DT >         // Forward declaration of the List class
class List;

template < class DT >
class ListNode                // Facilitator class for the List class
{
private:

    // Constructor
    ListNode(const DT& data,
        ListNode* priorPtr, ListNode* nextPtr);

    // Data members
    DT dataItem;        // List data item
    ListNode* prior,    // Pointer to the previous data item
        * next;     // Pointer to the next data item

    friend class List<DT>;
};

//--------------------------------------------------------------------

template < class DT >
class List
{
public:

    // Constructor
    List(int ignored = 0);

    // Destructor
    ~List();

    // List manipulation operations
    void insert(const DT& newDataItem)    // Insert after cursor
        throw (bad_alloc);
    void remove()                           // Remove data item
        throw (logic_error);
    void replace(const DT& newDataItem)   // Replace data item
        throw (logic_error);
    void clear();                           // Clear list

    // List status operations
    bool isEmpty() const;                   // List is empty
    bool isFull() const;                    // List is full

    // List iteration operations
    void gotoBeginning()                    // Go to beginning
        throw (logic_error);
    void gotoEnd()                          // Go to end
        throw (logic_error);
    bool gotoNext();                        // Go to next data item
    bool gotoPrior();                       // Go to prior data item
    DT getCursor() const                    // Return data item
        throw (logic_error);

    // Output the list structure -- used in testing/debugging
    void showStructure() const;

    // In-lab opertions
    void reverse();

private:

    // Data members
    ListNode<DT>* head,     // Pointer to the beginning of the list
        * cursor;   // Cursor pointer
};
