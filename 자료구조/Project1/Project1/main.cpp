#include <iostream>
#include "listarr.h"
using namespace std;

int main()
{
	char cmd;                 // Input command

	List personList(9);

	
	
	do
	{
		cout << endl << "Commands:" << endl;
		cout << "  R  : read from a file" << endl;
		cout << "  +  : add a new entry" << endl;
		cout << "  -  : remove an entry" << endl;
		cout << "  W  : write to a file" << endl;
		cout << "  M  : select a month" << endl;
		cout << "  Q  : Quit the program" << endl;
		cout << "  P  : print List " << endl;
		cout << "  S  : print Summary " << endl;
		cout << endl;



		cout << endl << "Command: ";                  // Read command
		cin >> cmd;


		switch (cmd)
		{
		case 'R':                                  // read
			personList.read();
		//	personList.printCursorSize();
			personList.printSummary();
			break;

		case '+':                                  // add
		{
			string name;
			string phoneNumber;
			string birthday;
			cout << "Add an entry : " << endl;
			cout << "Name : ";
			getline(cin, name);
			getline(cin, name);
			cout << "Phone : ";
			cin >> phoneNumber;
			cout << "Birthday : ";
			cin >> birthday;
			
			
			personList.insert(Person(name, phoneNumber, birthday));
		//	personList.printCursorSize();
			personList.printSummary();
			break;

		}

		case '-':                                  // remove
		{
			cout << "Remove an entry: " << endl;
			string name;
			cout << "Name : ";
			getline(cin, name);
			getline(cin, name);
			personList.remove(name);
		//	personList.printCursorSize();
			personList.printSummary();
			break;

		}
			
		case 'W':                                  // write
			personList.write();
			break;

		case 'M':                                  // select
			personList.select();
			break;

		case 'Q': case 'q':                   // Quit test program
			break;
		case 'P':
			personList.printList();
			break;
		case 'S':
			personList.printSummary();
			break;
		default:                               // Invalid command
			cout << "Inactive or invalid command" << endl;
		}
	} while (cmd != 'Q' && cmd != 'q');
	

	return 0;
}