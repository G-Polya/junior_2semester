
#include "notOptimizedRDParser.h"
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
		cout << "\n pD Error: " << n << endl;
		break;
	case 2:
		cout << "\n pL Error: " << n << endl;
		break;
	case 3:
		cout << "\n pR Error: " << n << endl;
		break;
	case 4:
		cout << "\n pLabel Error: " << n << endl;
		break;
	case 5:
		cout << "\n pInteger Error: " << n << endl;
		break;
	case 6:
		cout << "\n pId Error: " << n << endl;
		break;
	case 7:
		cout << "\n pSemicolon Error: " << n << endl;
		break;
	case 8:
		cout << "\n pComma Error: " << n << endl;
		break;
	}

	exit(1);
}
void pD()
{
	
	if (nextSymbol.number == tlabel)
	{
		parsingNumber = 1;
		cout << parsingNumber << endl;
		pLabel();
		pL();
	}
	else if (nextSymbol.number == tInteger)
	{
		parsingNumber = 2;
		cout << parsingNumber << endl;
		pInteger();
		pL();
	}
	else
		error(1);

}

void pL()
{
	if (nextSymbol.number == tident)
	{
		parsingNumber = 3;
		cout << parsingNumber << endl;
		pId();
		pR();
	}
	else
		error(2);
}

void pR()
{
	if (nextSymbol.number == tsemicolon)
	{
		parsingNumber = 4;
		cout << parsingNumber << endl;
		pSemicolon();
	}		
	else if (nextSymbol.number == tcomma)
	{
		parsingNumber = 5;
		cout << parsingNumber << endl;
		pComma();
		pL();
	}
	else
		error(3);
}

void pLabel()
{
	if (nextSymbol.number == tlabel)
		nextSymbol = scanner();
	else
		error(4);
}

void pInteger()
{
	if (nextSymbol.number == tInteger)
		nextSymbol = scanner();
	else
		error(5);
}

void pId()
{
	if (nextSymbol.number == tident)
		nextSymbol = scanner();
	else
		error(6);
}

void pSemicolon()
{
	if (nextSymbol.number == tsemicolon)
		nextSymbol = scanner();
	else
		error(7);
}

void pComma()
{
	if (nextSymbol.number == tcomma)
		nextSymbol = scanner();
	else
		error(8);
}

