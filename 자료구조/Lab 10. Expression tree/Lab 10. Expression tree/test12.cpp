//--------------------------------------------------------------------
//		Lab 12									test.cpp
//
//  Test program for the operations in the Expression Tree ADT
//
//--------------------------------------------------------------------
#include <iostream>
//#include "exprtree.h"    //pre-lab
#include "logitree.h"  //in-lab1

using namespace std;

void main()
{
	ExprTree testExpression;  // Test expression

	cout << endl << "Enter an expression in prefix form : ";

	testExpression.build();
	testExpression.showStructure();
	testExpression.expression();
	cout << " = " << testExpression.evaluate() << endl;

	cout << endl << "Clear the tree" << endl;
	testExpression.clear();
	testExpression.showStructure();
}
