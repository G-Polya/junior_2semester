#include "OptimizedRDParser.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> leftParse;
int parsingNumber;
struct tokenType nextSymbol;


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
	cout << "Procedure" << setw(19) << "Symbol number" << endl;
	cout << "pD() : " << setw(15) << nextSymbol.number << endl;
	parsingNumber = 1;
	leftParse.push_back(parsingNumber);
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

void printParse()
{
	for (int i = 0; i < leftParse.size(); i++)
		cout << leftParse[i] << " ";
	cout << endl;
}

