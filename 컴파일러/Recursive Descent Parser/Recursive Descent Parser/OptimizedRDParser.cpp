
// 2016112158 김희수
// EBNF를 사용한 최적화된 RDP
#include "OptimizedRDParser.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

vector<int> leftParse;
int parsingNumber;
struct tokenType nextSymbol;

// 다음 심볼을 읽어오는 함수
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

// noterminal <D>를 처리하는 프로시져
void pD()
{
	cout << "Procedure" << setw(19) << "Symbol number" << endl;
	cout << "pD() : " << setw(15) << nextSymbol.number << endl;	// 읽어온 심볼의 symbol number를 출력한다
	parsingNumber = 1;		// production-rule number
	leftParse.push_back(parsingNumber);		// left parse 출력을 위해 production-rule number를 저장
	
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

// left parse 출력
void printParse()
{
	cout << "left parse : ";
	for (int i = 0; i < leftParse.size(); i++)
		cout << leftParse[i] << " ";
	cout << endl;
}

