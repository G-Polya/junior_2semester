
#include "notOptimizedRDParser.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

int parsingNumber;
struct tokenType nextSymbol;
vector<int> leftParse;


void getNextSymbol()
{
	nextSymbol = scanner();
	// cout << nextSymbol.number << endl;
}

void printParse()
{
	cout << "LeftParse is ";
	for (int i = 0; i < leftParse.size(); i++)
		cout << leftParse[i] << " ";
	cout << endl;
}

void error(int n)
{
	cout << "\n*** Error: " << n << endl;
	switch (n)
	{
	case 1:
		cout << "\npD Error: " << n << endl;
		break;
	case 2:
		cout << "\npL Error: " << n << endl;
		break;
	case 3:
		cout << "\npR Error: " << n << endl;
		break;
	case 4:
		cout << "\npLabel Error: " << n << endl;
		break;
	case 5:
		cout << "\npInteger Error: " << n << endl;
		break;
	case 6:
		cout << "\npId Error: " << n << endl;
		break;
	case 7:
		cout << "\npSemicolon Error: " << n << endl;
		break;
	case 8:
		cout << "\npComma Error: " << n << endl;
		break;
	}

	exit(1);
}
void pD()
{
	cout << "Procedure" << setw(19) << "Symbol number" << endl;
	cout <<"pD() : " << setw(15) << nextSymbol.number << endl;

	if (nextSymbol.number == tlabel)
	{
		parsingNumber = 1;
		leftParse.push_back(parsingNumber);
		pLabel();
		pL();
	}
	else if (nextSymbol.number == tInteger)
	{
		parsingNumber = 2;
		leftParse.push_back(parsingNumber);
		pInteger();
		pL();
	}
	else
		error(1);

}

void pL()
{
	cout << "pL() : " << setw(15) << nextSymbol.number << endl;
	
	if (nextSymbol.number == tident)
	{
		parsingNumber = 3;
		leftParse.push_back(parsingNumber);
		pId();
		pR();
	}
	else
		error(2);
}

void pR()
{
	cout << "pR() : " << setw(15) << nextSymbol.number << endl;
	
	if (nextSymbol.number == tsemicolon)
	{
		parsingNumber = 4;
		leftParse.push_back(parsingNumber);
		pSemicolon();
	}		
	else if (nextSymbol.number == tcomma)
	{
		parsingNumber = 5;
		leftParse.push_back(parsingNumber);
		pComma();
		pL();
	}
	else
		error(3);
}

void pLabel()
{
	cout << "pLabel() : "<<setw(11) << nextSymbol.number << endl;
	if (nextSymbol.number == tlabel)
		nextSymbol = scanner();
	else
		error(4);
}

void pInteger()
{
	cout << "pInteger() : " << setw(9) << nextSymbol.number << endl;

	if (nextSymbol.number == tInteger)
		nextSymbol = scanner();
	else
		error(5);
}

void pId()
{
	cout << "pId() : " << setw(14) << nextSymbol.number << endl;

	if (nextSymbol.number == tident)
		nextSymbol = scanner();
	else
		error(6);
}

void pSemicolon()
{
	cout << "pSemicolon() : " << setw(7) << nextSymbol.number << endl;

	if (nextSymbol.number == tsemicolon)
		nextSymbol = scanner();
	else
		error(7);
}

void pComma()
{
	cout << "pComma() : " << setw(11) << nextSymbol.number << endl;

	if (nextSymbol.number == tcomma)
		nextSymbol = scanner();
	else
		error(8);
}

