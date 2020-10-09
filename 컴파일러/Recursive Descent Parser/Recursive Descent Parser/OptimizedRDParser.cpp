
// 2016112158 �����
// EBNF�� ����� ����ȭ�� RDP
#include "OptimizedRDParser.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

vector<int> leftParse;
int parsingNumber;
struct tokenType nextSymbol;

// ���� �ɺ��� �о���� �Լ�
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
	case 2:
		cout << "\n tident Error: " << n << endl;
		break;
	case 3:
		cout << "\n tident Error: " << n << endl;
		break;

	}

	exit(1);
}

// noterminal <D>�� ó���ϴ� ���ν���
void pD()
{
	cout << "Procedure" << setw(19) << "Symbol number" << endl;
	cout << "pD() : " << setw(15) << nextSymbol.number << endl;	// �о�� �ɺ��� symbol number�� ����Ѵ�
	parsingNumber = 1;		// production-rule number
	leftParse.push_back(parsingNumber);		// left parse ����� ���� production-rule number�� ����
	
	cout << endl;
	if ((nextSymbol.number == tlabel) || (nextSymbol.number == tInteger))
	{
		if (nextSymbol.number == tlabel)
			cout << "label" << endl;
		else
			cout << "Integer" << endl;
		getNextSymbol();
		if (nextSymbol.number == tident)
		{
			cout << "identfier" << endl;
			getNextSymbol();
			while (nextSymbol.number == tcomma)
			{
				cout << "comma" << endl;
				getNextSymbol();
				if (nextSymbol.number == tident)
				{
					cout << "identifier" << endl;
					getNextSymbol();	
				}
					
				else
					error(1);
			}
			if (nextSymbol.number == tsemicolon)
				cout << "semicolon" << endl;
		}
		else
			error(2);
	}
	else
		error(3);
		
	

	
	/*else
		error(2);
*/
	
}

// left parse ���
void printParse()
{
	cout << "left parse : ";
	for (int i = 0; i < leftParse.size(); i++)
		cout << leftParse[i] << " ";
	cout << endl;
}

