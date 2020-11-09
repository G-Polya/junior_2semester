//2016112158 김희수
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <chrono>

#include "parser.c"

void icg_error(int n);

#define FILE_LEN 30


void main(int argc, char* argv[])
{
	int err;

	printf(" *** start of Mini C Compiler\n");
	if (argc < 2)
	{
		printf("\nEnter filename : ");
		scanf("%s", filename);
	}
	else if (argc == 2) 
	{
		strcpy(filename, argv[1]);
	}
	else 
	{
		printf("Argument error!\n");
		exit(1);
	}
	
	if ((sourceFile = fopen(filename, "r")) == NULL)
	{
		printf("File open error!\n");
		exit(2);
	}
	
	printf("   * source file name: %s\n", filename);

	err = fopen_s(&sourceFile, filename, "r");
	
	if (err != 0)
	{
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
	
	parser();

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
