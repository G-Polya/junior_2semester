//--------------------------------------------------------------------
//
//  Laboratory 14                                         test14.cpp
//
//  Test program for the operations in the Hash Table ADT
//
//--------------------------------------------------------------------

#include <string>
#include <iostream>
#include "hashtbl.cpp"

using namespace std;

struct TestData
{
public:
    void setKey(const string newKey) { key = newKey; }
    string getKey() const { return key; }
    int hash(string str) const
    {
        int val = 0;

        for (int i = 0; i < str.length(); i++)
            val += str[i];
        return val;
    }
private:
    string key;
};

void print_help()
{
    cout << endl << "Commands:" << endl;
    cout << "  H    : Help (displays this message)" << endl;
    cout << "  +x   : Insert (or update) data item with key x" << endl;
    cout << "  -x   : Remove the data element with the key x" << endl;
    cout << "  ?x   : Retrieve the data element with the key x" << endl;
    cout << "  E    : Empty list?" << endl;
    cout << "  F    : Full list?" << endl;
    cout << "  C    : Clear the list" << endl;
    cout << "  Q    : Quit the test program" << endl;
}

void main()
{
    HashTbl<TestData, string> testHashTbl(8);
    TestData testDataItem;
    char cmd;
    string key;

    print_help();                                // Print out the help menu

    do
    {
        testHashTbl.showStructure();

        cout << endl << "Command: ";                 // Read command
        cin >> cmd;

        if (cmd == '+' || cmd == '?' || cmd == '-')
            cin >> key;

        switch (cmd)
        {
        case 'H': case 'h':
            print_help();
            break;

        case '+':                                 // insert
            testDataItem.setKey(key);
            testHashTbl.insert(testDataItem);
            cout << "Inserted data item with key : " << key << endl;
            break;

        case '-':                                 // remove
            if (testHashTbl.remove(key) == true)
                cout << "Removed data item with key : " << key << endl;
            else
                cout << "Couldn't remove data item with key : " << key << endl;
            break;

        case '?':                                 // retrieve
            if (testHashTbl.retrieve(key, testDataItem) == true)
                cout << "Retrieved data item with key : " << key << endl;
            else
                cout << "Couldn't retrieve data item with key : " << key << endl;
            break;

        case 'C': case 'c':                      // clear
            cout << "Clear the hash table" << endl;
            testHashTbl.clear();
            break;

        case 'E': case 'e':                      // isEmpty
            if (testHashTbl.isEmpty())
                cout << "Hash table is empty" << endl;
            else
                cout << "Hash table is NOT empty" << endl;
            break;

        case 'F': case 'f':                      // isFull
            if (testHashTbl.isFull())
                cout << "Hash table is full" << endl;
            else
                cout << "Hash table is NOT full" << endl;
            break;

        case 'Q': case 'q':                   // Quit test program
            break;

        default:                               // Invalid command
            cout << "Invalid command" << endl;
        }
    } while (cmd != 'Q' && cmd != 'q');

}

