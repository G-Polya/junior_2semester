
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

// left parse 출력
void printParse()
{
	for (int i = 0; i < leftParse.size(); i++)
		cout << leftParse[i] << " ";
	cout << endl;
}

