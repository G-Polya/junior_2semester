// 2016112158 �����
// EBNF�� ������� ���� RDP
#include "notOptimizedRDParser.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

int parsingNumber;
struct tokenType nextSymbol;
vector<int> leftParse;

// ���� �ɺ��� �о���� �Լ�
void getNextSymbol()
{
	nextSymbol = scanner();
	// cout << nextSymbol.number << endl;
}

// left parse ���
void printParse()
{
	cout << "LeftParse is ";
	for (int i = 0; i < leftParse.size(); i++)
		cout << leftParse[i] << " ";
	cout << endl;
}

// �����޽��� ���
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

// nonterminal <D>�� ó���ϱ� ���� ���ν���
void pD()
{
	cout << "Procedure" << setw(19) << "Symbol number" << endl;
	cout <<"pD() : " << setw(15) << nextSymbol.number << endl;	// �о�� �ɺ��� symbol number ���

	if (nextSymbol.number == tlabel)		// productin-rule 1�� ó��
	{
		parsingNumber = 1;
		leftParse.push_back(parsingNumber);
		pLabel();
		pL();
	}
	else if (nextSymbol.number == tInteger) // productin-rule 2�� ó��
	{
		parsingNumber = 2;
		leftParse.push_back(parsingNumber);
		pInteger();
		pL();
	}
	else
		error(1);

}

// nonterminal <L>�� ó���ϱ� ���� ���ν���
void pL()
{
	cout << "pL() : " << setw(15) << nextSymbol.number << endl;
	
	if (nextSymbol.number == tident)		// production-rule 3�� ó��
	{
		parsingNumber = 3;
		leftParse.push_back(parsingNumber);
		pId();
		pR();
	}
	else
		error(2);
}

// nonterminal <L>�� ó���ϱ� ���� ���ν���
void pR()
{
	cout << "pR() : " << setw(15) << nextSymbol.number << endl;
	
	if (nextSymbol.number == tsemicolon)		// production-rule 4�� ó��
	{
		parsingNumber = 4;
		leftParse.push_back(parsingNumber);
		pSemicolon();
	}		
	else if (nextSymbol.number == tcomma)		// production-rule 5�� ó��
	{
		parsingNumber = 5;
		leftParse.push_back(parsingNumber);
		pComma();
		pL();
	}
	else
		error(3);
}

// terminal 'label'�� ó���ϱ� ���� ���ν���
void pLabel()
{
	cout << "pLabel() : "<<setw(11) << nextSymbol.number << endl;
	if (nextSymbol.number == tlabel)
		nextSymbol = scanner();
	else
		error(4);
}

// terminal 'Integer'�� ó���ϱ� ���� ���ν���
void pInteger()
{
	cout << "pInteger() : " << setw(9) << nextSymbol.number << endl;

	if (nextSymbol.number == tInteger)
		nextSymbol = scanner();
	else
		error(5);
}

// terminal <id>�� ó���ϱ� ���� ���ν���
void pId()
{
	cout << "pId() : " << setw(14) << nextSymbol.number << endl;

	if (nextSymbol.number == tident)
		nextSymbol = scanner();
	else
		error(6);
}

// terminal ';'�� ó���ϱ� ���� ���ν���
void pSemicolon()
{
	cout << "pSemicolon() : " << setw(7) << nextSymbol.number << endl;

	if (nextSymbol.number == tsemicolon)
		nextSymbol = scanner();
	else
		error(7);
}

// terminal ','�� ó���ϱ� ���� ���ν���
void pComma()
{
	cout << "pComma() : " << setw(11) << nextSymbol.number << endl;

	if (nextSymbol.number == tcomma)
		nextSymbol = scanner();
	else
		error(8);
}

