/***************************************************************
*      scanner routine for Mini C language                    *
***************************************************************/
// 2016112158 김희수
#include <stdio.h>


#include "Scanner.h"

extern FILE *sourceFile;                       // miniC source program

char temp_str[MAX_LENGTH];
bool point_check = false;
using namespace std;

// 1. 심볼추가
// 2. tokenName추가 

// 토큰 이름
const char* tokenName[] = {
	"!",        "!=",      "%",       "%=",     "%ident",   "%number",
	/* 0          1           2         3          4          5        */
	"&&",       "(",       ")",       "*",      "*=",       "+",
	/* 6          7           8         9         10         11        */
	"++",       "+=",      ",",       "-",      "--",	    "-=",
	/* 12         13         14        15         16         17        */
	"/",        "/=",      ";",       "<",      "<=",       "=",
	/* 18         19         20        21         22         23        */
	"==",       ">",       ">=",      "[",      "]",        "eof",
	/* 24         25         26        27         28         29        */
	//   ...........    word symbols ................................. //

	"const",    "else",     "if",      "int",     "return",  "void",
	/* 30         31         32        33         34         35        */
	"while",    "{",        "||",       "}",	 "char",    "double",
	/* 36         37         38        39         40         41        */
	"for",     "switch",   "case",   "default", "continue", "break",
	/* 42         43         44        45         46         47       */
    ":",        "label",    "Integer"
	/* 48         49         50        51         52         53       */
	
};

// 키워드들
const char* keyword[NO_KEYWORD] = {
	"const",    "else",    "if", "int", "return",    "void",  "while", "char", "double",  "for",
	"label", "Integer","switch","case","default","continue",  "break",
	
};

enum tsymbol tnum[NO_KEYWORD] = {
	tconst,    telse,     tif,     tint,     treturn,    tvoid,     twhile, tchar, tdouble,tfor,
	tlabel, tInteger, tswitch,    tcase,	tdefault,tcontinue,		tbreak,
	
};

struct tokenType scanner()
{
	struct tokenType token;
	int i, index;
	char ch, id[ID_LENGTH];

	token.number = tnull;

	do {
		while (isspace(ch = fgetc(sourceFile)));	// state 1: skip blanks
		if (superLetter(ch)) { // identifier or keyword
			i = 0;
			do {
				if (i < ID_LENGTH) id[i++] = ch;
				ch = fgetc(sourceFile);
			} while (superLetterOrDigit(ch));
			if (i >= ID_LENGTH) lexicalError(1);
			id[i] = '\0';
			ungetc(ch, sourceFile);  //  retract
									 // find the identifier in the keyword table
			for (index = 0; index < NO_KEYWORD; index++)
				if (!strcmp(id, keyword[index])) break;
			if (index < NO_KEYWORD)    // found, keyword exit
				token.number = tnum[index];
			else {                     // not found, identifier exit
				token.number = tident;
				strcpy_s(token.id, id);
			}
		}  // end of identifier or keyword
		else if (isdigit(ch)) {  // number
			token.number = tnumber;
			char temp[ID_LENGTH];
			double tmp = getNumber(ch);
			strcpy_s(token.str, temp_str);
			

			if (tmp >= 99999999999)//너무 숫자가 크면 그냥 출력
				strcpy_s(token.buffer, temp_str);
			else if (point_check)
			{
				sprintf_s(temp, "%1f", tmp);
				strcpy_s(token.buffer, temp);
			}

			else
			{
				sprintf_s(temp, "%d", (int)tmp);
				strcpy_s(token.buffer, temp);
			
			}
			memset(temp_str, '\0', sizeof(temp_str));
		}
		else switch (ch) // text comment
		{  
		case '/':
			ch = fgetc(sourceFile);
			
			if (ch == '*')			
			{
				char temp[MAX_LENGTH];
				i = 0;
				ch = fgetc(sourceFile);
				
				if (ch == '*') //documented comment
				{
					token.comment_type = 3;
					do {
						while (ch != '*')
						{
							if (ch == '\n')
								ch = ' ';
							temp[i++] = ch;
							ch = fgetc(sourceFile);
							
						}
						ch = fgetc(sourceFile);
						
					} while (ch != '/');
					temp[i] = '\0';
					strcpy_s(token.comment, temp);
					ungetc(ch, sourceFile);
				}
				else		//multi line comment
				{
					token.comment_type = 2;
					do {
						while (ch != '*')
						{
							if (ch == '\n')
								ch = ' ';
							temp[i++] = ch;
							ch = fgetc(sourceFile);
							
						}
						ch = fgetc(sourceFile);
						
					} while (ch != '/');
					temp[i] = '\0';
					strcpy_s(token.comment, temp);
					ungetc(ch, sourceFile);
				}
			}
			else if (ch == '/')		// single line comment
			{
				char temp[MAX_LENGTH];
				i = 0;
				token.comment_type = 1;
				do {
					ch = fgetc(sourceFile);
					
					if (ch != '\n')
						temp[i++] = ch;
				} while (ch != '\n');
				temp[i] = '\0';
				strcpy_s(token.comment, temp);
				ungetc(ch, sourceFile);
				token.number = tcomment;
			}
			else if (ch == '=')  token.number = tdivAssign;
			else {
				strcpy_s(token.str, "/");
				token.number = tdiv;
				ungetc(ch, sourceFile); // retract
			}
			break;
		

		case '!':
			ch = fgetc(sourceFile);
			if (ch == '=')  token.number = tnotequ;
			else {
				token.number = tnot;
				ungetc(ch, sourceFile); // retract
			}
			break;
		case '%':
			ch = fgetc(sourceFile);
			if (ch == '=') {
				token.number = tremAssign;
			}
			else {
				token.number = tremainder;
				ungetc(ch, sourceFile);
			}
			break;
		case '&':
			ch = fgetc(sourceFile);
			if (ch == '&')  token.number = tand;
			else {
				lexicalError(2);
				ungetc(ch, sourceFile);  // retract
			}
			break;
		case '*':
			ch = fgetc(sourceFile);
			if (ch == '=')  token.number = tmulAssign;
			else {
				token.number = tmul;
				ungetc(ch, sourceFile);  // retract
			}
			break;
		case '+':
			ch = fgetc(sourceFile);
			if (ch == '+')  token.number = tinc;
			else if (ch == '=') token.number = taddAssign;
			else {
				token.number = tplus;
				ungetc(ch, sourceFile);  // retract
			}
			break;
		case '-':
			ch = fgetc(sourceFile);
			if (ch == '-')  token.number = tdec;
			else if (ch == '=') token.number = tsubAssign;
			else {
				token.number = tminus;
				ungetc(ch, sourceFile);  // retract
			}
			break;
		case '<':
			ch = fgetc(sourceFile);
			if (ch == '=') token.number = tlesse;
			else {
				token.number = tless;
				ungetc(ch, sourceFile);  // retract
			}
			break;
		case '=':
			ch = fgetc(sourceFile);
			if (ch == '=')  token.number = tequal;
			else {
				token.number = tassign;
				ungetc(ch, sourceFile);  // retract
			}
			break;
		case '>':
			ch = fgetc(sourceFile);
			if (ch == '=') token.number = tgreate;
			else {
				token.number = tgreat;
				ungetc(ch, sourceFile);  // retract
			}
			break;
		case '|':
			ch = fgetc(sourceFile);
			if (ch == '|')  token.number = tor;
			else {
				lexicalError(3);
				ungetc(ch, sourceFile);  // retract
			}
			break;
		case '"':			// 문자열 리터럴 인식
			char buffer[MAX_LENGTH];
			i = 0;
			ch = fgetc(sourceFile);
			while (ch != '"')
			{
				if (ch == '\n')
					ch = ' ';
				buffer[i++] = ch;
				ch = fgetc(sourceFile);
			}
			buffer[i] = '\0';
			token.number = tstringlit;
			strcpy_s(token.buffer, buffer);
			strcpy_s(token.str, buffer);
			break;
		case '\'':		// 문자 리터럴 인식
			char temp1[MAX_LENGTH];
			ch = fgetc(sourceFile);
			
			temp1[0] = ch;
			temp1[1] = '\0';
			token.number = tcharlit;
			strcpy_s(token.buffer, temp1);
			strcpy_s(token.str, temp1);
			ch = fgetc(sourceFile);
			break;
		

		case '(': token.number = tlparen;         break;
		case ')': token.number = trparen;         break;
		case ',': token.number = tcomma;          break;
		case ';': token.number = tsemicolon;      break;
		case '[': token.number = tlbracket;       break;
		case ']': token.number = trbracket;       break;
		case '{': token.number = tlbrace;         break;
		case '}': token.number = trbrace;         break;
		case ':': token.number = tcolon;		  break;
		case EOF: token.number = teof;            break;
		default: {
			printf("Current character : %c", ch);
			lexicalError(4);
			break;
		}

		} // switch end
	} while (token.number == tnull);
	return token;
} // end of scanner

void lexicalError(int n)
{
	printf(" *** Lexical Error : ");
	switch (n) {
	case 1: printf("an identifier length must be less than 12.\n");
		break;
	case 2: printf("next character must be &\n");
		break;
	case 3: printf("next character must be |\n");
		break;
	case 4: printf("invalid character\n");
		break;
	}
}

int superLetter(char ch)
{
	if (isalpha(ch) || ch == '_') return 1;
	else return 0;
}

int superLetterOrDigit(char ch)
{
	if (isalnum(ch) || ch == '_') return 1;
	else return 0;
}

double getNumber(char firstCharacter)
{
	char* temp;
	double num = 0;
	int value;
	char ch;
	int point_count = 1;
	int i = 0;
	temp_str[i++] = firstCharacter;
	if (firstCharacter == '0') {
		ch = fgetc(sourceFile);
		if (ch != '\n' && isDigitOrPoint(ch))
			temp_str[i++] = ch;
		if ((ch == 'X') || (ch == 'x')) {		// hexa decimal
			while ((value = hexValue(ch = fgetc(sourceFile))) != -1)
			{
				if (ch != '\n' && isDigitOrPoint(ch))
					temp_str[i++] = ch;
				num = 16 * num + value;
			}
		}
		else if ((ch >= '0') && (ch <= '7'))	// octal
			do {
				num = 8 * num + (int)(ch - '0');
				ch = fgetc(sourceFile);
				if (ch != '\n' && isDigitOrPoint(ch))
					temp_str[i++] = ch;
				
			} while ((ch >= '0') && (ch <= '7'));
		else if (ch == '.' || ch == 'e' || ch == 'E')	//floating point
		{
			{
				point_check = true;
				do {
					if (ch == 'e' || ch == 'E')//using e
					{
						ch = fgetc(sourceFile);
						if (ch != '\n' && isDigitOrPoint(ch))
							temp_str[i++] = ch;
						int temp = 0;
						do {
							temp = 10 * temp + (int)(ch - '0');
							ch = fgetc(sourceFile);
							
							if (ch != '\n' && isDigitOrPoint(ch))
								temp_str[i++] = ch;
							
						} while (isDigitOrPoint(ch));
						num *= pow(10, temp);
						if (num == (int)num)
							point_check = false;
					}
					else
					{
						if (ch >= '0' && ch <= '9')
							num += (double)(ch - '0') * (1.0 / (double)pow(10, (point_count++)));
						ch = fgetc(sourceFile);
						if (ch != '\n' && isDigitOrPoint(ch))
							temp_str[i++] = ch;
						
					}
				} while (isDigitOrPoint(ch));
			}
		}
		else num = 0;						// zero
	}
	else {									// decimal
		ch = firstCharacter;
		do {
			if (ch == '.' || ch == 'e' || ch == 'E')					//floating point
			{
				point_check = true;
				do {
					if (ch == 'e' || ch == 'E')//using e
					{
						ch = fgetc(sourceFile);
						if (ch != '\n' && isDigitOrPoint(ch))
							temp_str[i++] = ch;
						int temp = 0;
						do {
							temp = 10 * temp + (int)(ch - '0');
							ch = fgetc(sourceFile);
							
							if (ch != '\n' && isDigitOrPoint(ch))
								temp_str[i++] = ch;
							
						} while (isDigitOrPoint(ch));
						num *= pow(10, temp);
						if (num == (int)num)
							point_check = false;
					}
					else
					{
						if (ch >= '0' && ch <= '9')
							num += (double)(ch - '0') * (1.0 / (double)pow(10, (point_count++)));
						ch = fgetc(sourceFile);
						if (ch != '\n' && isDigitOrPoint(ch))
							temp_str[i++] = ch;
					}
				} while (isDigitOrPoint(ch));
			}
			else
			{
				num = 10 * num + (int)(ch - '0');
				ch = fgetc(sourceFile);
				if (ch != '\n' && isDigitOrPoint(ch))
					temp_str[i++] = ch;
			
			}
		} while (isDigitOrPoint(ch));
	}
	ungetc(ch, sourceFile);  /*  retract  */
	return num;
}
int hexValue(char ch)
{
	switch (ch) {
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		return (ch - '0');
	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
		return (ch - 'A' + 10);
	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
		return (ch - 'a' + 10);
	default: return -1;
	}
}

void printToken(struct tokenType token)
{
	if (token.comment_type == 0)
	{
		switch (token.number)
		{
		case tident:
			printf("number: %d, value: %s\n", token.number, token.id);
			break;
		case tnumber:
			printf("number: %d, value: %s\n", token.number, token.str);
			break;
		case tcharlit:
			printf("number: %d, value: %s\n", token.number, token.str);
			break;
		case tstringlit:
			printf("number: %d, value: %s\n", token.number, token.str);
			break;
		default:
			printf("number: %d(%s)\n", token.number, tokenName[token.number]);
			break;

		}
	}
	else if (token.comment_type == 1)
		printf("   Single - line   |  <%s>  \n", token.comment);
	else if (token.comment_type == 2)
		printf("    Multi - line   |  <%s>  \n", token.comment);
	else if (token.comment_type == 3)
		printf("Documented comments|  <%s>  \n", token.comment);
}

bool isDigitOrPoint(char c)
{
	if ((c >= '0' && c <= '9') || c == '.' || c == 'e' || c == 'E' || c == 'x' || c == 'X' || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
		return true;
	else
		return false;
}