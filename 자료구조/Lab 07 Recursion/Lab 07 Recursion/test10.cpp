//--------------------------------------------------------------------
//
//  Laboratory 10                                         test10.cpp
//
//  Test program for a set of recursive linked list functions
//
//--------------------------------------------------------------------

// Reads a list of characters and calls the specified recursive
// routine.

#include <iostream>
#include "listrec.cpp"

void main()
{
    List<char> testList;   // Test list
    char testData;         // List data element

    cout << endl << "Enter a list of characters : ";
    cin.get(testData);
    while ( testData != '\n' )
    {
        testList.insert(testData);
        cin.get(testData);
    }
    testList.showStructure();

    // Call a recursive routine by uncommenting the call you wish to
    // execute.
    
//PA  
	testList.write();
//PA
	testList.insertEnd('!');
//PB  
	testList.writeMirror();
//PC  
	testList.reverse();
//PD  
	testList.deleteEnd();
//PE  
	cout << "length = " <<  testList.getLength() << endl;

//1A 
	testList.iterReverse();
//1B  
	testList.stackWriteMirror();

    testList.showStructure();

	system("pause");
}
