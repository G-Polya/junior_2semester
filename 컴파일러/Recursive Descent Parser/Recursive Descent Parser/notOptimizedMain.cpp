//2016112158 �����
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include <iostream>
#include "Scanner.h"
#include "notOptimizedRDParser.h"
void icg_error(int n);

using namespace std;

FILE* astFile;                          // AST file
FILE* sourceFile;                       // miniC source program
FILE* ucodeFile;                        // ucode file

#define FILE_LEN 30

// ��°���� �ַܼ� �����ϸ� Lexcial Error�߻�...
void main()
{
	const char* fileName = "example.mc";
	int err;

	printf(" *** start of Mini C Compiler\n");
	//if (argc != 2) {	
	//	icg_error(1);
	//	exit(1);
	//}
	//strcpy_s(fileName, argv[1]);

//	strcpy_s(fileName, "example.mc");			// ���־�Ʃ����� �����ϸ� Error�� �߻����� ����.
	printf("   * source file name: %s\n", fileName);

	err = fopen_s(&sourceFile, fileName, "r");
	if (err != 0) {
		icg_error(2);
		exit(1);
	}


	printf(" === start of Scanner\n");
	struct tokenType token;

	token = scanner();

	while (token.number != teof) {

		printf("Current Token --> ");
		printToken(token);
		token = scanner();

	} /* while (1) */
	
	rewind(sourceFile);

	printf("\n === start of Parser\n");
	getNextSymbol();
	//printf(" > Not yet implemented...\n");
	pD();
	cout << endl;
	printParse();
	//printTree(root, 0);

	printf("\n === start of ICG\n");
	printf(" > Not yet implemented...\n");

	//codeGen(root);
	printf(" *** end   of Mini C Compiler\n");
} // end of main

void icg_error(int n)
{
	printf("icg_error: %d\n", n);
	//3:printf("A Mini C Source file must be specified.!!!\n");
	//"error in DCL_SPEC"
	//"error in DCL_ITEM"
}
