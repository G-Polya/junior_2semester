//--------------------------------------------------------------------
//
//  Laboratory 11, In-lab Exercise 1                    getdbrec.cpp
//
//  Sample accounts database retrieval program
//
//--------------------------------------------------------------------

// Retrieves a record from an accounts database file.

#include <iostream>
#include <fstream>

using namespace std;

//--------------------------------------------------------------------
//
// Declarations specifying the accounts database
//

const int nameLength = 11;   // Maximum number of characters in
                                  //   a name
const long bytesPerRecord = 38;   // Number of bytes used to store
                                  //   each record in the accounts
                                  //   database file

struct AccountRecord
{
    int acctID;                   // Account identifier
    char firstName[nameLength],   // Name of account holder
        lastName[nameLength];
    double balance;               // Account balance
};

//--------------------------------------------------------------------

void main()
{
    ifstream acctFile("accounts.dat");   // Accounts database file
    AccountRecord acctRec;                // Account record
    long recNum;                          // User input record number

    // Get the record number to retrieve.

    cout << endl << "Enter record number: ";
    cin >> recNum;

    // Move to the corresponding record in the database file using the
    // seekg() function.

    acctFile.seekg(recNum * bytesPerRecord);

    // Read in the record.

    acctFile >> acctRec.acctID >> acctRec.firstName
        >> acctRec.lastName >> acctRec.balance;

    // Display the record.

    cout << recNum << " : " << acctRec.acctID << " "
        << acctRec.firstName << " " << acctRec.lastName << " "
        << acctRec.balance << endl;
}
