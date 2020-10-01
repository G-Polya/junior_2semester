#include "OptimizedRDParser.h"
#include <iostream>
#include <string>

int parsingNumber;
struct tokenType nextSymbol;

using namespace std;

void getNextSymbol()
{
	nextSymbol = scanner();
	// cout << nextSymbol.number << endl;
}

void error(int n)
{
	cout << "\n*** Error: " << n << endl;
	switch (n)
	{
	case 1:
		cout << "\n tident Error: " << n << endl;
		break;

	}

	exit(1);
}

void pD()
{

	
		parsingNumber = 1;
		cout << parsingNumber << endl;
		getNextSymbol();
		if ((nextSymbol.number == tlabel) ||(nextSymbol.number == tInteger) )
			getNextSymbol();

		if (nextSymbol.number == tident)
			getNextSymbol();
		else
			error(1);

		while (nextSymbol.number == tcomma)
		{
			getNextSymbol();
			if (nextSymbol.number == tident)
				getNextSymbol();
			else
				error(1);
		}
	}


//}
//void pL()
//{
//
//}
//
//void pR()
//{
//
//}