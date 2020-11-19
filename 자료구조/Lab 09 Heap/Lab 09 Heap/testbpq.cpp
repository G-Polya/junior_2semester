//--------------------------------------------------------------------
//
//  Laboratory B, In-lab Exercise 1                    testbpq.cpp
//
//  Test program for the operations in the Priority Queue ADT
//
//--------------------------------------------------------------------

#include <iostream>
#include "ptyqueue.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declaration for the priority queue data item class
//

class TestData
{
  public:

    void setPty ( int newPty )
        { priority = newPty; }   // Set the priority

    int pty () const
        { return priority; }     // Returns the priority

  private:

    int priority;                // Priority for the data item
};

//--------------------------------------------------------------------

void main()
{
    PtyQueue<TestData> testQueue(8);   // Test priority queue
    TestData testData;                 // Queue data item
    int inputPty;                      // User input priority
    char cmd;                          // Input command

    cout << endl << "Commands:" << endl;
    cout << "  +x : Enqueue data item with priority x" << endl;
    cout << "  -  : Dequeue data item" << endl;
    cout << "  C  : Clear the queue" << endl;
    cout << "  E  : Empty queue?" << endl;
    cout << "  F  : Full queue?" << endl;
    cout << "  Q  : Quit the test program" << endl;
    cout << endl;

    do
    {
        testQueue.showStructure();                    // Output queue

        cout << endl << "Command: ";                  // Read command
        cin >> cmd;
        if ( ( cmd == '+' ) || ( cmd == '>' ) )
           cin >> inputPty;

        switch ( cmd )
        {
          case '+' :                                  // enqueue
               testData.setPty(inputPty);
               cout << "Enqueue :  pty = " << testData.pty()
                    << endl;
               testQueue.enqueue(testData);
               break;

          case '-' :                                  // dequeue
               testData = testQueue.dequeue();
               cout << "Dequeued :  pty = " << testData.pty()
                    << endl;
               break;

          case 'C' : case 'c' :                       // clear
               cout << "Clear the queue" << endl;
               testQueue.clear();
               break;

          case 'E' : case 'e' :                       // isEmpty
               if ( testQueue.isEmpty() )
                  cout << "Queue is empty" << endl;
               else
                  cout << "Queue is NOT empty" << endl;
               break;

          case 'F' : case 'f' :                       // isFull
               if ( testQueue.isFull() )
                  cout << "Queue is full" << endl;
               else
                  cout << "Queue is NOT full" << endl;
               break;

          case 'Q' : case 'q' :                   // Quit test program
               break;

          default :                               // Invalid command
               cout << "Invalid command" << endl;
        }
    }
    while ( ( cmd != 'Q' ) && ( cmd != 'q' ) );
}
