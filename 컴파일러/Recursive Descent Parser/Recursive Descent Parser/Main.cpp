//2016112158 김희수
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <chrono>

#include <iostream>
#include "notOptimizedRDParser.h"
// #include "OptimizedRDParser.h"
void icg_error(int n);

using namespace std;

FILE* astFile;                          // AST file
FILE* sourceFile;                       // miniC source program
FILE* ucodeFile;                        // ucode file

#define FILE_LEN 30

// 어째선지 콘솔로 실행하면 Lexcial Error발생...
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

//	strcpy_s(fileName, "example.mc");			// 비주얼스튜디오로 실행하면 Error가 발생하지 않음.
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

	rewind(sourceFile);	// 파일 다시읽기

	
	// Parser 시작
	printf("\n === start of Parser\n");
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	getNextSymbol(); // 시작심볼을 읽는다
	//printf(" > Not yet implemented...\n");
	pD();	
	cout << endl;
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	auto elapsed_time = chrono::duration_cast<chrono::microseconds>(end - begin).count();
	printParse();		// left parse 출력
	cout << "Elapsed time to parse : " << elapsed_time <<" microseconds" <<endl;
	

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
