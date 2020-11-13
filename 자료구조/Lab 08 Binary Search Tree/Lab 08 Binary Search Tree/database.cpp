//--------------------------------------------------------------------
//
//  Laboratory 11, In-lab Exercise 1                     database.cs
//
//  (Shell) Indexed accounts database program
//
//--------------------------------------------------------------------

// Builds a binary search tree index for the account records in the
// text file accounts.dat.

#include <iostream>
#include <fstream>
#include "bstree.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declarations specifying the accounts database
//

const int nameLength = 11;   // Maximum number of characters in
                                  //   a name
const long bytesPerRecord = 37;   // Number of bytes used to store
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
//
// declaration specifying the database index
//

struct IndexEntry
{
    int acctID;              // (Key) Account identifier
    long recNum;             // Record number

    void setKey(int newkey) {
        acctID = newkey;
    }

    int key() const
    {
        return acctID;
    }   // Return key field
};


//--------------------------------------------------------------------

int main(void)
{
	ifstream acctFile("accounts.dat");   // Accounts database file
	if (!acctFile.is_open())
		cout << "File is Not Open!" << endl;
	AccountRecord acctRec;                // Account record
	BSTree<IndexEntry, int> index;         // Database index
	IndexEntry entry;                     // Index entry
	int searchID;                         // User input account ID
	long recNum;                          // Record number
	int i = 0;
	// Iterate through the database records. For each record, read the
	// account ID and add the (account ID, record number) pair to the
	// index.
	while (1)
	{
		// seekg() function.
		acctFile.seekg(i * bytesPerRecord);

		// Read in the record.
		acctFile >> acctRec.acctID >> acctRec.firstName
			>> acctRec.lastName >> acctRec.balance;
		if (acctFile.eof())
			break;
		entry.acctID = acctRec.acctID;
		entry.recNum = i++;
		//cout << entry.recNum << " : " << entry.acctID << " "<< endl;
		index.insert(entry);
	}

	// Output the account IDs in ascending order.
	index.writeKeys();

	// Clear the status flags for the database file.
	acctFile.clear();

	// Read an account ID from the keyboard and output the
	// corresponding record.
	while (true)
	{
		cout << endl << "Enter account ID : ";
		cin >> searchID;
		if (index.retrieve(searchID, entry))
		{
			recNum = entry.recNum;
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
		else
			cout << "Not found" << endl;
	}
}