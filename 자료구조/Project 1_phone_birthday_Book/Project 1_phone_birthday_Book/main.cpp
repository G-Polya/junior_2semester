#include <iostream>
#include "listarr.h"
using namespace std;

void main()
{
	char cmd;                 // Input command


	do
	{
		cout << endl << "Commands:" << endl;
		cout << "  R  : read from a file" << endl;
		cout << "  +  : add a new entry" << endl;
		cout << "  -  : remove an entry"<< endl;
		cout << "  W  : write to a file" << endl;
		cout << "  M  : select a month" << endl;
		cout << "  Q   : Quit the program" << endl;
		cout << endl;



		cout << endl << "Command: ";                  // Read command
		cin >> cmd;
		

		switch (cmd)
		{
		case 'R':                                  // read
			break;

		case '+':                                  // add
			break;

		case '-':                                  // remove
			break;

		case 'W':                                  // write
			
			break;

		case 'M':                                  // select
			break;

		case 'Q': case 'q':                   // Quit test program
			break;

		default:                               // Invalid command
			cout << "Inactive or invalid command" << endl;
		}
	} while (cmd != 'Q' && cmd != 'q');
}