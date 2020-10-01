/***************************************************************
*      scanner routine for Mini C language                    *
*                                   2003. 3. 10               *
***************************************************************/

#pragma once
#include <string.h>
#include <ctype.h>
#include <math.h>


#define NO_KEYWORD 17
#define ID_LENGTH 12
#define MAX_LENGTH 1000



struct tokenType {
	int number;

	char id[ID_LENGTH];
	
	char buffer[ID_LENGTH] = { '0' };
	char str[ID_LENGTH] = { '\0' };
	int comment_type = 0;
	char comment[MAX_LENGTH] = { '0' };
};


// 심볼을 정의하는 열거
enum tsymbol {
	tnull = -1,
	tnot,       tnotequ,  tremainder, tremAssign, tident,    tnumber,
	/* 0          1            2         3            4          5     */
	tand,    tlparen,     trparen,     tmul,   tmulAssign,    tplus,
	/* 6          7            8         9           10         11     */
	tinc,     taddAssign,  tcomma,   tminus,        tdec,  tsubAssign,
	/* 12         13          14        15           16         17     */
	tdiv,    tdivAssign, tsemicolon,  tless,      tlesse,    tassign,
	/* 18         19          20        21           22         23     */
	tequal,     tgreat,    tgreate,  tlbracket,  trbracket,    teof,
	/* 24         25          26        27           28         29     */
	//   ...........    word symbols ................................. //
	/* 30         31          32        33           34         35     */
	tconst,     telse,       tif,      tint,      treturn,    tvoid,
	/* 36         37          38        39           40         41     */
	twhile,    tlbrace,      tor,    trbrace,      tchar,    tdouble,
	/* 42         43          44        45           46         47     */
	tfor,       tswitch,     tcase,  tdefault,   tcontinue,   tbreak,
	/* 48		  49		  50	    51           52         53     */
    tcolon,      tlabel,   tInteger,  tcharlit,  tstringlit, tcomment,
	/* 54         55          56        57           58         59    */
};

struct tokenType scanner();
void printToken(struct tokenType token);


int superLetter(char ch);
int superLetterOrDigit(char ch);
double getNumber(char firstCharacter);
int hexValue(char ch);
void lexicalError(int n);
bool isDigitOrPoint(char c);//숫자나 숫자표현에 사용된 문자인지 판단

