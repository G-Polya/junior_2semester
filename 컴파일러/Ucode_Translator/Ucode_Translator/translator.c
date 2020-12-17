#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "miniC.tbl"
#define PS_SIZE 200
#define NO_KEYWORD 7
#define ID_LENGTH 12
#define FNAME_SIZE 12



//Scanner 
struct tokenType
{
	int number;
	union
	{
		char id[ID_LENGTH];
		int num;
	} value;
};


int superLetter(char ch);
int superLetterOrDigit(char ch);
int getNumber(char firstCharacter);
int hexValue(char ch);
void lexicalError(int n);
FILE* sourceFile;
char filename[FNAME_SIZE];
struct tokenType scanner();

enum tsymbol
{
	tnull = -1,
	tnot, tnotequ, tremainder, tremAssign, tident, tnumber,
	/* 0          1            2         3            4          5     */
	tand, tlparen, trparen, tmul, tmulAssign, tplus,
	/* 6          7            8         9           10         11     */
	tinc, taddAssign, tcomma, tminus, tdec, tsubAssign,
	/* 12         13          14        15           16         17     */
	tdiv, tdivAssign, tcolon, tsemicolon, tless, tlesse,
	/* 18         19          20        21           22         23     */
	tassign, tequal, tgreat, tgreate, tlbracket, trbracket,
	/* 24         25          26        27           28         29     */
	teof, tbreak, tcase, tconst, tcontinue, tdefault,
	/* 30         31          32        33           34         35     */
	tdo, telse, tfor, tif, tint, treturn,
	/* 36         37          38        39           40         41     */
	tswitch, tvoid, twhile, tlbrace, tor, trbrace,
	/* 42         43          44        45           46         47     */
};

const char* tokenName[] =
{
	"!",        "!=",      "%",       "%=",     "%ident",   "%number",
	/* 0          1           2         3          4          5        */
	"&&",       "(",       ")",       "*",      "*=",       "+",
	/* 6          7           8         9         10         11        */
	"++",       "+=",      ",",       "-",      "--",	    "-=",
	/* 12         13         14        15         16         17        */
	"/",        "/=",      ":",       ";",      "<",       "<=",
	/* 18         19         20        21         22         23        */
	"=",       "==",       ">",       ">=",      "[",        "]",
	/* 24         25         26        27         28         29        */
	"_|_",    "break",    "case",    "const", "continue", "default",
	/* 30         31         32        33         34         35        */
	"do" ,     "else",     "for",      "if",     "int",    "return",
	/* 36         37         38        39         40         41        */
	"switch",    "void", "while",     "{",        "||",        "}"
	/* 42         43          44        45           46         47     */
};

const char* keyword[NO_KEYWORD] =
{
	"const",  "else",    "if",    "int",    "return",  "void",    "while"
};

enum tsymbol tnum[NO_KEYWORD] =
{
	tconst,    telse,     tif,     tint,     treturn,   tvoid,     twhile
};



struct tokenType scanner()
{
	struct tokenType token;
	int i, index;
	char ch, id[ID_LENGTH];

	token.number = tnull;

	do
	{
		while (isspace(ch = fgetc(sourceFile)));	// state 1: skip blanks
		if (superLetter(ch))
		{ // identifier or keyword
			i = 0;
			do {
				if (i < ID_LENGTH)
					id[i++] = ch;
				ch = fgetc(sourceFile);
			} while (superLetterOrDigit(ch));
			if (i >= ID_LENGTH)
				lexicalError(1);
			id[i] = '\0';
			ungetc(ch, sourceFile);  //  retract
									 // find the identifier in the keyword table
			for (index = 0; index < NO_KEYWORD; index++)
				if (!strcmp(id, keyword[index])) break;
			if (index < NO_KEYWORD)    // found, keyword exit
				token.number = tnum[index];
			else
			{                     // not found, identifier exit
				token.number = tident;
				strcpy_s(token.value.id, ID_LENGTH, id);
			}
		}  // end of identifier or keyword
		else if (isdigit(ch))
		{  // number
			token.number = tnumber;
			token.value.num = getNumber(ch);
		}
		else switch (ch)
		{  // special character
		case '/':
			ch = fgetc(sourceFile);
			if (ch == '*')			// text comment
				do
				{
					while (ch != '*') ch = fgetc(sourceFile);
					ch = fgetc(sourceFile);
				} while (ch != '/');
			else if (ch == '/')		// line comment
				while (fgetc(sourceFile) != '\n');
			else if (ch == '=')
				token.number = tdivAssign;
			else
			{
				token.number = tdiv;
				ungetc(ch, sourceFile); // retract
			}
			break;
		case '!':
			ch = fgetc(sourceFile);
			if (ch == '=')
				token.number = tnotequ;
			else
			{
				token.number = tnot;
				ungetc(ch, sourceFile); // retract
			}
			break;
		case '%':
			ch = fgetc(sourceFile);
			if (ch == '=')
			{
				token.number = tremAssign;
			}
			else
			{
				token.number = tremainder;
				ungetc(ch, sourceFile);
			}
			break;
		case '&':
			ch = fgetc(sourceFile);
			if (ch == '&')
				token.number = tand;
			else
			{
				lexicalError(2);
				ungetc(ch, sourceFile);  // retract
			}
			break;
		case '*':
			ch = fgetc(sourceFile);
			if (ch == '=')
				token.number = tmulAssign;
			else
			{
				token.number = tmul;
				ungetc(ch, sourceFile);  // retract
			}
			break;
		case '+':
			ch = fgetc(sourceFile);
			if (ch == '+')
				token.number = tinc;
			else if (ch == '=')
				token.number = taddAssign;
			else
			{
				token.number = tplus;
				ungetc(ch, sourceFile);  // retract
			}
			break;
		case '-':
			ch = fgetc(sourceFile);
			if (ch == '-')
				token.number = tdec;
			else if (ch == '=')
				token.number = tsubAssign;
			else
			{
				token.number = tminus;
				ungetc(ch, sourceFile);  // retract
			}
			break;
		case '<':
			ch = fgetc(sourceFile);
			if (ch == '=')
				token.number = tlesse;
			else
			{
				token.number = tless;
				ungetc(ch, sourceFile);  // retract
			}
			break;
		case '=':
			ch = fgetc(sourceFile);
			if (ch == '=')
				token.number = tequal;
			else
			{
				token.number = tassign;
				ungetc(ch, sourceFile);  // retract
			}
			break;
		case '>':
			ch = fgetc(sourceFile);
			if (ch == '=')
				token.number = tgreate;
			else
			{
				token.number = tgreat;
				ungetc(ch, sourceFile);  // retract
			}
			break;
		case '|':
			ch = fgetc(sourceFile);
			if (ch == '|')
				token.number = tor;
			else
			{
				lexicalError(3);
				ungetc(ch, sourceFile);  // retract
			}
			break;
		case '(': token.number = tlparen;         break;
		case ')': token.number = trparen;         break;
		case ',': token.number = tcomma;          break;
		case ';': token.number = tsemicolon;      break;
		case '[': token.number = tlbracket;       break;
		case ']': token.number = trbracket;       break;
		case '{': token.number = tlbrace;         break;
		case '}': token.number = trbrace;         break;
		case EOF: token.number = teof;            break;
		default:
		{
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
	switch (n)
	{
	case 1:
		printf("an identifier length must be less than 12.\n");
		break;
	case 2:
		printf("next character must be &\n");
		break;
	case 3:
		printf("next character must be |\n");
		break;
	case 4:
		printf("invalid character\n");
		break;
	}
}

int superLetter(char ch)
{
	if (isalpha(ch) || ch == '_')
		return 1;
	else
		return 0;
}

int superLetterOrDigit(char ch)
{
	if (isalnum(ch) || ch == '_')
		return 1;
	else
		return 0;
}

int getNumber(char firstCharacter)
{
	int num = 0;
	int value;
	char ch;

	if (firstCharacter == '0')
	{
		ch = fgetc(sourceFile);
		if ((ch == 'X') || (ch == 'x'))
		{		// hexa decimal
			while ((value = hexValue(ch = fgetc(sourceFile))) != -1)
				num = 16 * num + value;
		}
		else if ((ch >= '0') && (ch <= '7'))	// octal
			do
			{
				num = 8 * num + (int)(ch - '0');
				ch = fgetc(sourceFile);
			} while ((ch >= '0') && (ch <= '7'));
		else num = 0;						// zero
	}
	else
	{									// decimal
		ch = firstCharacter;
		do
		{
			num = 10 * num + (int)(ch - '0');
			ch = fgetc(sourceFile);
		} while (isdigit(ch));
	}
	ungetc(ch, sourceFile);  /*  retract  */
	return num;
}

int hexValue(char ch)
{
	switch (ch)
	{
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



enum nodeNumber {
	ACTUAL_PARAM, ADD, ADD_ASSIGN, ARRAY_VAR, ASSIGN_OP,
	BREAK_ST, CALL, CASE_EXP, CASE_LST, CASE_ST,
	COMPOUND_ST, CONST_NODE, CONTINUE_ST, DCL, DCL_ITEM,
	DCL_LIST, DCL_SPEC, DEFAULT_ST, DIV, DIV_ASSIGN,
	EQ, ERROR, EXP_ST, FORMAL_PARA, FOR_DCL,
	FOR_EXP, FOR_INC, FOR_ST, FUNC_DEF, FUNC_HEAD,
	GE, GT, IDENT, IF_ELSE_ST, IF_ST,
	INDEX, INT_NODE, LE, LOGICAL_AND, LOGICAL_NOT,
	LOGICAL_OR, LT, MOD_ASSIGN, MUL, MUL_ASSIGN,
	NE, NUMBER, PARAM_DCL, POST_DEC, POST_INC,
	PRE_DEC, PRE_INC, PROGRAM, MOD, RETURN_ST,
	SIMPLE_VAR, STAT_LIST, SUB, SUB_ASSIGN, SWITCH_ST,
	UNARY_MINUS, VOID_NODE, WHILE_ST
};

const char* nodeName[] = {
	"ACTUAL_PARAM",	"ADD",			"ADD_ASSIGN",	"ARRAY_VAR",	"ASSIGN_OP",
	"BREAK_ST",		"CALL",			"CASE_EXP",		"CASE_LST",		"CASE_ST",
	"COMPOUND_ST",	"CONST_NODE",	"CONTINUE_ST",	"DCL",			"DCL_ITEM",
	"DCL_LIST",		"DCL_SPEC",		"DEFAULT_ST",	"DIV",			"DIV_ASSIGN",
	"EQ",			"ERROR",		"EXP_ST",		"FORMAL_PARA",	"FOR_DCL",
	"FOR_EXP",		"FOR_INC",		"FOR_ST",		"FUNC_DEF",		"FUNC_HEAD",
	"GE",			"GT",			"IDENT",		"IF_ELSE_ST",	"IF_ST",
	"INDEX",		"INT_NODE",		"LE",			"LOGICAL_AND",	"LOGICAL_NOT",
	"LOGICAL_OR",	"LT",			"MOD_ASSIGN",	"MUL",			"MUL_ASSIGN",
	"NE",			"NUMBER",		"PARAM_DCL",	"POST_DEC",		"POST_INC",
	"PRE_DEC",		"PRE_INC",		"PROGRAM",		"MOD",  	    "RETURN_ST",
	"SIMPLE_VAR",	"STAT_LIST",	"SUB",			"SUB_ASSIGN",	"SWITCH_ST",
	"UNARY_MINUS",	"VOID_NODE",	"WHILE_ST"
};

int ruleName[] = {
	0, 			PROGRAM, 		0, 				0, 				0,
	0, 			FUNC_DEF, 		FUNC_HEAD,		DCL_SPEC,		0,
	0, 			0, 				0, 				CONST_NODE, 	INT_NODE,
	VOID_NODE, 	0, 				FORMAL_PARA,	0, 				0,
	0, 			0, 				PARAM_DCL, 		COMPOUND_ST,	DCL_LIST,
	DCL_LIST,	0,				0,				DCL,			0,
	0,			DCL_ITEM,		DCL_ITEM,		SIMPLE_VAR,		ARRAY_VAR,
	0,			0,				STAT_LIST,		0,				0,
	0,			0,				0,				0,				0,
	0,			EXP_ST,			0,				0,				IF_ST,
	IF_ELSE_ST,	WHILE_ST,		RETURN_ST,		0,				0,
	ASSIGN_OP,	ADD_ASSIGN,		SUB_ASSIGN,		MUL_ASSIGN,		DIV_ASSIGN,
	MOD_ASSIGN,	0,				LOGICAL_OR,		0,				LOGICAL_AND,
	0,			EQ,				NE,				0,				GT,
	LT,			GE,				LE,				0,				ADD,
	SUB,		0,				MUL,			DIV,			MOD,
	0,			UNARY_MINUS,	LOGICAL_NOT,	PRE_INC,		PRE_DEC,
	0,			INDEX,			CALL,			POST_INC,		POST_DEC,
	0,			0,				ACTUAL_PARAM,	0,				0,
	0,			0,				0
};




typedef struct nodeType {
	struct tokenType token;            // 토큰 종류
	int noderep;  // 노드의 종류
	struct nodeType* son;             // 왼쪽 링크
	struct nodeType* brother;         // 오른쪽 링크
	struct nodeType* father;		   // 상위 링크
} Node;

void semantic(int);
void printToken(struct tokenType token);
void dumpStack();
void errorRecovery();
Node* parser();
Node* buildNode(struct tokenType token);
Node* buildTree(int nodeNumber, int rhsLength);
int meaningfulToken(struct tokenType token);


int sp;                               // stack pointer
int stateStack[PS_SIZE];              // state stack
int symbolStack[PS_SIZE];             // symbol stack
Node* valueStack[PS_SIZE];            // value stack

Node* parser()
{
	extern int parsingTable[NO_STATES][NO_SYMBOLS + 1];
	extern int leftSymbol[NO_RULES + 1], rightLength[NO_RULES + 1];
	int entry, ruleNumber, lhs;
	int currentState;
	struct tokenType token;
	Node* ptr;

	sp = 0; stateStack[sp] = 0;  // initial state
	token = scanner();
	while (1) {
		currentState = stateStack[sp];
		entry = parsingTable[currentState][token.number];
		if (entry > 0)                          /* shift action */
		{
			sp++;
			if (sp > PS_SIZE) {
				printf("critical compiler error: parsing stack overflow");
				exit(1);
			}
			symbolStack[sp] = token.number;
			stateStack[sp] = entry;
			valueStack[sp] = meaningfulToken(token) ? buildNode(token) : NULL;
			token = scanner();
		}
		else if (entry < 0)                   /* reduce action */
		{
			ruleNumber = -entry;
			if (ruleNumber == GOAL_RULE) /* accept action */
			{
				//                      printf(" *** valid source ***\n");
				return valueStack[sp - 1];
			}
			semantic(ruleNumber);
			ptr = buildTree(ruleName[ruleNumber], rightLength[ruleNumber]);
			sp = sp - rightLength[ruleNumber];
			lhs = leftSymbol[ruleNumber];
			currentState = parsingTable[stateStack[sp]][lhs];
			sp++;
			symbolStack[sp] = lhs;
			stateStack[sp] = currentState;
			valueStack[sp] = ptr;
		}
		else                               /* error action */
		{
			printf(" === error in source ===\n");
			printf("Current Token : ");
			printToken(token);
			dumpStack();
			errorRecovery();
			token = scanner();
		}
	} /* while (1) */
} /* parser */

void semantic(int n)
{
	printf("reduced rule number = %d\n", n);
}

void dumpStack()
{
	int i, start;

	if (sp > 10) start = sp - 10;
	else start = 0;

	printf("\n *** dump state stack :");
	for (i = start; i <= sp; ++i)
		printf(" %d", stateStack[i]);

	printf("\n *** dump symbol stack :");
	for (i = start; i <= sp; ++i)
		printf(" %d", symbolStack[i]);
	printf("\n");
}

void printToken(struct tokenType token)
{
	if (token.number == tident)
		printf("token number: %d,   value: %s\n", token.number, token.value.id);
	else if (token.number == tnumber)
		printf("token number: %d,   value: %d\n", token.number, token.value.num);
	else
		printf("token number: %d,   value: %s\n", token.number, tokenName[token.number]);

}

void errorRecovery()
{
	struct tokenType tok;
	int parenthesisCount, braceCount;
	int i;

	// step 1: skip to the semicolon
	parenthesisCount = braceCount = 0;
	while (1) {
		tok = scanner();
		if (tok.number == teof) exit(1);
		if (tok.number == tlparen) parenthesisCount++;
		else if (tok.number == trparen) parenthesisCount--;
		if (tok.number == tlbrace) braceCount++;
		else if (tok.number == trbrace) braceCount--;
		if ((tok.number == tsemicolon) && (parenthesisCount <= 0) && (braceCount <= 0))
			break;
	}

	// step 2: adjust state stack
	for (i = sp; i >= 0; i--) {
		// statement_list ->  statement_list .  statement
		if (stateStack[i] == 36) break;	 // second statement part

		// statement_list ->  .  statement
		// statement_list ->  .  statement_list statement
		if (stateStack[i] == 24) break;	 // first statement part

		// declaration_list ->  declaration_list .  declaration
		if (stateStack[i] == 25) break;  // second internal dcl

		// declaration_list ->  .  declaration
		// declaration_list ->  .  declaration_list declaration
		if (stateStack[i] == 17) break;  // internal declaration

		// external declaration
		// external_dcl ->  .  declaration
		if (stateStack[i] == 2) break;	// after first external dcl
		if (stateStack[i] == 0) break;	// first external declaration
	}
	sp = i;
}

int meaningfulToken(struct tokenType token)
{
	if ((token.number == tident) || (token.number == tnumber))
		return 1;
	else return 0;
}

// SDT


enum { terminal, nonterm };



Node* buildNode(struct tokenType token)
{
	Node* ptr;
	ptr = (Node*)malloc(sizeof(Node));
	if (!ptr) {
		printf("malloc error in buildNode()\n");
		exit(1);
	}
	ptr->token = token;
	ptr->noderep = terminal;
	ptr->son = ptr->brother = NULL;
	return ptr;
}


Node* buildTree(int nodeNumber, int rhsLength)
{
	int i, j, start;
	Node* first, * ptr;

	i = sp - rhsLength + 1;
	/* step 1: find a first index with node in value stack */
	while (i <= sp && valueStack[i] == NULL) i++;
	if (!nodeNumber && i > sp) return NULL;
	start = i;
	/* step 2: linking brothers */
	while (i <= sp - 1) {
		j = i + 1;
		while (j <= sp && valueStack[j] == NULL) j++;
		if (j <= sp) {
			ptr = valueStack[i];
			while (ptr->brother) ptr = ptr->brother;
			ptr->brother = valueStack[j];
		}
		i = j;
	}
	first = (start > sp) ? NULL : valueStack[start];
	/* step 3: making subtree root and linking son */
	if (nodeNumber) {
		ptr = (Node*)malloc(sizeof(Node));
		if (!ptr) {
			printf("malloc error in buildTree()\n");
			exit(1);
		}
		ptr->token.number = nodeNumber;
		ptr->noderep = nonterm;
		ptr->son = first;
		ptr->brother = NULL;
		return ptr;
	}
	else return first;
}


void printNode(Node* pt, int indent);
void printTree(Node* pt, int indent);

void printTree(Node* pt, int indent)
{
	Node* p = pt;
	while (p != NULL) {
		printNode(p, indent);
		if (p->noderep == nonterm) printTree(p->son, indent + 5);
		p = p->brother;
	}
}
FILE* astFile;
void printNode(Node* pt, int indent)
{
	
	int i;

	for (i = 1; i <= indent; i++) fprintf(astFile, " ");
	if (pt->noderep == terminal) {
		if (pt->token.number == tident)
			fprintf(astFile, " Terminal: %s", pt->token.value.id);
		else if (pt->token.number == tnumber)
			fprintf(astFile, " Terminal: %d", pt->token.value.num);
	}
	else { // nonterminal node
		i = (int)(pt->token.number);
		fprintf(astFile, " Nonterminal: %s", nodeName[i]);
	}
	fprintf(astFile, "\n");
}

#define HASH_BUCKET_SIZE 97
#define SYMTAB_SIZE 200
#define LEVEL_STACK_SIZE 10
#define LABEL_SIZE 12

FILE * ucodeFile;

void initSymbolTable();
int hash(char*);
int lookup(char*);
int insert(char*, int, int, int, int, int, int);
void dumpSymbolTable();
void set();
void reset();

typedef enum {
	NON_SPECIFIER, VOID_TYPE, INT_TYPE
} TypeSpecifier;

typedef enum {
	NON_QUALIFIER, FUNC_TYPE, PARAM_TYPE, CONST_TYPE, VAR_TYPE
} TypeQuailfier;

const char* typeName[] = {
		"none",   "void",   "int"
};

const char* qualifierName[] = {
		"NONE", "FUNC_TYPE",  "PARAM_TYPE",  "CONST_TYPE", "VAR_TYPE"
};

typedef enum {
	ZERO_DIMENSION, ONE_DIMENSION
} Dimension;

struct SymbolEntry {
	char symbolName[ID_LENGTH];
	int typeSpecifier;
	int typeQualifier;
	int base;
	int offset;
	int width;					// size
	int initialValue;			// initial value
	int nextIndex;				// link to next entry.
};
struct SymbolEntry symbolTable[SYMTAB_SIZE];		// symbol table
int symbolTableTop;
int hashBucket[HASH_BUCKET_SIZE];
int levelStack[SYMTAB_SIZE];						// level table
int levelTop;
int base, offset;

void emitSym(int base, int offset, int size) {
	fprintf(ucodeFile, "           sym %d %d %d\n", base, offset, size);
	printf("           sym %d %d %d\n", base, offset, size);
}


void emitJump(const char* value, const char* label) {
	fprintf(ucodeFile, "           %s %s\n", value, label);
	printf("           %s %s\n", value, label);
}


void emit0(const char* value) {
	fprintf(ucodeFile, "           %s\n", value);
	printf("           %s\n", value);
}

void emit1(const char* value, int p) {
	fprintf(ucodeFile, "           %s %d\n", value, p);
	printf("           %s %d\n", value, p);
}

void emit2(const char* value, int p, int q) {
	fprintf(ucodeFile, "           %s %d %d\n", value, p, q);
	printf("           %s %d %d\n", value, p, q);
}

void emitFunc(const char* value, int p, int q, int r) {
	fprintf(ucodeFile, "           %s %d %d %d\n", value, p, q, r);
	printf("           %s %d %d %d\n", value, p, q, r);
}

void genLabel(char* label) {
	static int labelNum = 0;
	sprintf(label, "$$%d", labelNum++);
}

void emitLabel(const char* label) {
	fprintf(ucodeFile, "%-10s nop\n", label);
	printf("%-10s nop\n", label);
}

void icg_error(int err) {
	printf("error %d\n", err);
}

void rv_emit(Node* ptr) {
	int stIndex;

	if (ptr->token.number == tnumber)
		emit1("ldc", ptr->token.value.num);
	else {
		stIndex = lookup(ptr->token.value.id);

		if (stIndex == -1) return;
		if (symbolTable[stIndex].typeQualifier == CONST_TYPE) // constant
			emit1("ldc", symbolTable[stIndex].initialValue);
		else if (symbolTable[stIndex].width > 1) { 			// array var
			emit2("lda", symbolTable[stIndex].base, symbolTable[stIndex].offset);
		}
		else 												// simple var
			emit2("lod", symbolTable[stIndex].base, symbolTable[stIndex].offset);
	}
}


/*------------------ TABLE INITIALIZE FUNCTION -----------------------------*/
void initSymbolTable()
{
	int i;

	symbolTableTop = -1;
	levelTop = -1;
	base = 1; offset = 1;

	for (i = 0; i < HASH_BUCKET_SIZE; i++)
		hashBucket[i] = -1;

	for (i = 0; i < LEVEL_STACK_SIZE; i++)
		levelStack[i] = 0;
}

/*--------------------- HASH FUNCTION --------------------------------------*/
int hash(char* symbolName)
{
	int hashValue;

	for (hashValue = 0; *symbolName; symbolName++)
		hashValue += *symbolName;

	return (hashValue % HASH_BUCKET_SIZE);
}


/*------------------ LOOKUP FUNCTION ---------------------------------------*/
int lookup(char* symbol)
{
	int stIndex;

	stIndex = hash(symbol);
	for (stIndex = hashBucket[stIndex];
		stIndex >= 0 && strcmp(symbol, symbolTable[stIndex].symbolName);
		stIndex = symbolTable[stIndex].nextIndex);

	if (stIndex < 0)
		printf("undefined identifier: %s\n", symbol);

	return stIndex;
}

/*-------------------- INSERT SYMBOL FUNCTION ------------------------------*/
int insert(char* symbol, int specifier, int qualifier, int base, int offset,
	int width, int initialValue)
{
	int hashValue;
	int i;

	hashValue = hash(symbol);
	for (i = hashBucket[hashValue]; i >= 0 && strcmp(symbol, symbolTable[i].symbolName);)
		i = symbolTable[i].nextIndex;

	if ((i >= 0) && (base == symbolTable[i].base)) {	// found
		printf("multiply defined identifier : %s\n", symbol);

		printf("base = %d, symbolTable[i].base = %d\n", base, symbolTable[i].base);
		return -1;
	}

	if (symbolTableTop > SYMTAB_SIZE) {
		printf("symbol table overflow\n");
		dumpSymbolTable();
		exit(1);
	}

	symbolTableTop++;
	strcpy(symbolTable[symbolTableTop].symbolName, symbol);
	symbolTable[symbolTableTop].typeSpecifier = specifier;
	symbolTable[symbolTableTop].typeQualifier = qualifier;
	symbolTable[symbolTableTop].base = base;
	symbolTable[symbolTableTop].offset = offset;
	symbolTable[symbolTableTop].width = width;
	symbolTable[symbolTableTop].initialValue = initialValue;

	symbolTable[symbolTableTop].nextIndex = hashBucket[hashValue];
	hashBucket[hashValue] = symbolTableTop;

	return symbolTableTop;
}


/*------------------ SET BLOCK FUNCTION ------------------------------------*/
void set()
{
	++levelTop;
	//	printf("level stack top in set function = %d\n", levelTop);
	if (levelTop > LEVEL_STACK_SIZE)
		printf("error: level stack overflow.\n");

	levelStack[levelTop] = symbolTableTop;
	++base; offset = 1;
}

/*--------------------- RESET BLOCK FUNCTION -------------------------------*/
void reset(void)
{
	int hashValue;
	int i;

	i = symbolTableTop;
	symbolTableTop = levelStack[levelTop];
	levelTop--;

	for (; i > symbolTableTop; i--) {
		hashValue = hash(symbolTable[i].symbolName);
		hashBucket[hashValue] = symbolTable[i].nextIndex;
	}
	base--;

}

/*-------------------   Dump Symbol Table   -----------------------------*/
void dumpSymbolTable()
{
	int i;

	printf(" === Dump Symbol Table ===\n");
	for (i = 0; i <= symbolTableTop; i++)
		printf("id = %-12s : \ttype = %s, \tqualifier = %s, \tbase = %d, \toffset = %d \twidth = %d, \tvalue = %d\n",
			symbolTable[i].symbolName,
			typeName[symbolTable[i].typeSpecifier],
			qualifierName[symbolTable[i].typeQualifier],
			symbolTable[i].base,
			symbolTable[i].offset,
			symbolTable[i].width,
			symbolTable[i].initialValue);
}

/*------------------- generate Symbol Table -----------------------------*/
void genSym(int base)
{
	int stIndex;

	//	//fprintf(ucodeFile, "// Information for Symbol Table\n");

	for (stIndex = 0; stIndex <= symbolTableTop; stIndex++) {
		if ((symbolTable[stIndex].typeQualifier == FUNC_TYPE) ||
			(symbolTable[stIndex].typeQualifier == CONST_TYPE)) continue;

		if (base == symbolTable[stIndex].base)
			emitSym(symbolTable[stIndex].base, symbolTable[stIndex].offset, symbolTable[stIndex].width);
	}
}

void processSimpleVariable(Node* ptr, int typeSpecifier, int typeQualifier);
void processArrayVariable(Node* ptr, int typeSpecifier, int typeQualifier);

int checkPredefined(Node* ptr);
void processDeclaration(Node* ptr);
void processFuncHeader(Node* ptr);
void processOperator(Node* ptr);
void processStatement(Node* ptr);
void processCondition(Node* ptr);
void processFunction(Node* ptr);

void genLabel(char* label);
void codeGen(Node* ptr);



//extern FILE* ucodeFile;

int offest = 0;
int width = 0;
int lvalue = 0;
int rvalue = 0;
int flag = 0;

void processDeclaration(Node* ptr) {
	int typeSpecifier;
	int typeQualifier;
	Node* p, * q;

	if (ptr->token.number != DCL_SPEC) icg_error(4);

	printf("processDeclaration!\n");
	//step 1 : process DCL_SPEC
	typeSpecifier = INT_TYPE;
	typeQualifier = VAR_TYPE;

	p = ptr->son;

	while (p) {
		if (p->token.number == INT_NODE)
			typeSpecifier = INT_TYPE;
		else if (p->token.number == CONST_NODE)
			typeQualifier = CONST_TYPE;
		else { // AUTO, EXTERN, REGISTER, FLOAT, DOUBLE, SIGNED, UNSIGNED
			printf("not yet implemented!!\n");
			return;
		}
		p = p->brother;
	}

	//step 2 : process DCL_ITEM
	p = ptr->brother;

	if (p->token.number != DCL_ITEM) icg_error(5);

	while (p) {	//SIMPLE_VAR or ARRAY_VAR
		q = p->son;
		switch (q->token.number) {
		case SIMPLE_VAR:
			processSimpleVariable(q, typeSpecifier, typeQualifier);
			break;
		case ARRAY_VAR:
			processArrayVariable(q, typeSpecifier, typeQualifier);
			break;
		default:
			printf("error in SIMPLE VAR or ARRAY_VAR\n");
			break;
		} // end switch
		p = p->brother;
	} // end while
}

void processSimpleVariable(Node* ptr, int typeSpecifier, int typeQualifier) {
	int sign = 1;

	Node* p = ptr->son;
	Node* q = ptr->brother;
	int stIndex, size, initialValue;
	size = 1;

	if (ptr->token.number != SIMPLE_VAR)
		printf("error in SIMPLE_VAR\n");

	if (typeQualifier == CONST_TYPE) {
		if (q == NULL) {
			printf("%s must have a constant value\n", ptr->token.value.id);
			return;
		}

		if (q->token.number == UNARY_MINUS) {
			sign = -1;
			q = q->son;
		}

		initialValue = sign * (q->token.value.num);
		stIndex = insert(p->token.value.id, typeSpecifier, typeQualifier, 0/* base */, 0/* offset */, width/* width */, initialValue);

	}
	else {
		stIndex = insert(p->token.value.id, typeSpecifier, typeQualifier, base, offset, size, 0);
		offset++;
	}
}

void processArrayVariable(Node* ptr, int typeSpecifier, int typeQualifier) {
	Node* p = ptr->son;
	int stIndex, size;

	if (ptr->token.number != ARRAY_VAR) {
		printf("error in ARRAY_VAR\n");
		return;
	}

	if (p->brother == NULL) {
		printf("array size must be typeSpecifierified\n");
		return;
	}
	else
		size = p->brother->token.value.num;

	stIndex = insert(p->token.value.id, typeSpecifier, typeQualifier, base, offset, size, 0);

	offset += size;

}

void processOperator(Node* ptr) {
	int stIndex;
	switch (ptr->token.number) {
		// assignment operator
	case ASSIGN_OP:
	{
		Node* lhs = ptr->son;
		Node* rhs = ptr->son->brother;

		if (lhs->token.number == ASSIGN_OP && rhs->token.number == ASSIGN_OP)
			flag = 1;

		// step 1 : generate instructions for left-hand side if INDEX node.
		if (lhs->noderep == nonterm) {
			lvalue = 1;
			processOperator(lhs);
			lvalue = 0;
		}
		// step 2 : generate instructions for right-hand side
		if (rhs->noderep == nonterm) {
			rvalue = 1;
			processOperator(rhs);
			rvalue = 0;
		}

		else {
			rv_emit(rhs);
		}


		//step 3 : generate a store instruction
		if (lhs->noderep == terminal) {
			stIndex = lookup(lhs->token.value.id);
			if (stIndex == -1) {
				printf("undefined variable: %s\n", lhs->token.value.id);
				return;
			}

			emit2("str", symbolTable[stIndex].base, symbolTable[stIndex].offset);
		}
		else
			emit0("sti");
		break;
	}
	// complex assignment operators
	case ADD_ASSIGN: case SUB_ASSIGN: case MUL_ASSIGN:
	case DIV_ASSIGN: case MOD_ASSIGN:
	{
		Node* lhs = ptr->son;
		Node* rhs = ptr->son->brother;

		int nodeNumber = ptr->token.number;

		ptr->token.number = ASSIGN_OP;

		// step 1 : code generation for left hand side
		if (lhs->noderep == nonterm) {
			lvalue = 1;
			processOperator(lhs);
			lvalue = 0;
		}

		ptr->token.number = nodeNumber;

		// step 2 : code generation for repeatng part
		if (lhs->noderep == nonterm)
			processOperator(lhs);
		else
			rv_emit(lhs);

		// step 3 : code generation for right hand side
		if (rhs->noderep == nonterm)
			processOperator(rhs);
		else
			rv_emit(rhs);



		// step 4 : emit the correspoinding operation code			
		switch (ptr->token.number) {
		case ADD_ASSIGN: emit0("add");	break;
		case SUB_ASSIGN: emit0("sub"); 	break;
		case MUL_ASSIGN: emit0("mult"); break;
		case DIV_ASSIGN: emit0("div"); 	break;
		case MOD_ASSIGN: emit0("mod"); 	break;
		}

		// step 5 : code generation for store code
		if (lhs->noderep == terminal) {
			stIndex = lookup(lhs->token.value.id);
			if (stIndex == -1)	return;

			emit2("str", symbolTable[stIndex].base, symbolTable[stIndex].offset);
		}
		else
			emit0("sti");
		break;
	}
	// binary(arithmetic / realational / logical) operations
	case ADD:	case SUB:	case MUL:	case DIV:	case MOD:
	case EQ:	case NE:	case GT:	case LT:	case GE:
	case LE:	case LOGICAL_AND: case LOGICAL_OR:
	{
		Node* lhs = ptr->son;
		Node* rhs = ptr->son->brother;

		// step 1 : visit left operand
		if (lhs->noderep == nonterm)	processOperator(lhs);
		else	rv_emit(lhs);
		// step 2 : visit right operand
		if (rhs->noderep == nonterm)	processOperator(rhs);
		else 	rv_emit(rhs);

		// step 3 : visit root
		switch (ptr->token.number) {
		case ADD:		emit0("add");		break;
		case SUB:		emit0("sub");		break;
		case MUL:		emit0("mult");		break;
		case DIV:		emit0("div");		break;
		case MOD:		emit0("mod");		break;
		case EQ:		emit0("eq");		break;
		case NE:		emit0("ne");		break;
		case GT:		emit0("gt");		break;
		case LT:		emit0("lt");		break;
		case GE:		emit0("ge");		break;
		case LE:		emit0("le");		break;
		case LOGICAL_AND:	emit0("and");	break;
		case LOGICAL_OR:	emit0("or");	break;
		}
		if (flag == 1) {
			emit0("dup");
			flag = 0;
		}
		break;


	}

	case UNARY_MINUS:	case LOGICAL_NOT:
	{
		Node* p = ptr->son;

		if (p->noderep == nonterm)	processOperator(p);
		else 	rv_emit(p);

		switch (ptr->token.number) {
		case UNARY_MINUS:	emit0("neg");	break;
		case LOGICAL_NOT:	emit0("not");	break;
		}
		break;
	}

	case INDEX:
	{
		Node* indexExp = ptr->son->brother;

		if (indexExp->noderep == nonterm)	processOperator(indexExp);
		else 	rv_emit(indexExp);

		stIndex = lookup(ptr->son->token.value.id);

		if (stIndex == -1) {
			printf("undefined variable: %s\n", ptr->son->token.value.id);
			return;
		}

		emit2("lda", symbolTable[stIndex].base, symbolTable[stIndex].offset);
		emit0("add");

		if (!lvalue) emit0("ldi");
		break;
	}
	// increment / decrement operatiors
	case PRE_INC:	case PRE_DEC:	case POST_INC:	case POST_DEC:
	{
		Node* p = ptr->son;
		Node* q;
		int stIndex; int amount = 1;

		if (p->noderep == nonterm)	processOperator(p);
		else 	rv_emit(p);

		q = p;

		while (q->noderep != terminal)
			q = q->son;

		if (!q || (q->token.number != tident)) {
			printf("increment/decrement operators can not be applied in expression\n");
			return;
		}

		stIndex = lookup(q->token.value.id);
		if (stIndex == -1) return;

		switch (ptr->token.number) {
		case PRE_INC:	emit0("inc");	break;
		case PRE_DEC:	emit0("dec");	break;
		case POST_INC:	emit0("inc");	break;
		case POST_DEC:	emit0("dec");	break;
		}

		if (p->noderep == terminal) {
			stIndex = lookup(p->token.value.id);
			if (stIndex == -1)	return;
			emit2("str", symbolTable[stIndex].base, symbolTable[stIndex].offset);
		}
		else if (p->token.number == INDEX) {
			lvalue = 1;
			processOperator(p);
			lvalue = 0;
			emit0("sti");
		}
		else printf("error increase/decrease operators\n");
		break;
	}

	case CALL:
	{
		Node* p = ptr->son;
		char* functionName;
		int stIndex;
		int noArguments;

		if (checkPredefined(p)) break;

		functionName = p->token.value.id;
		stIndex = lookup(functionName);

		if (stIndex == -1)	break;

		noArguments = symbolTable[stIndex].width;

		emit0("ldp");
		p = p->brother;

		while (p) {
			if (p->noderep == nonterm)	processOperator(p);
			else 	rv_emit(p);

			noArguments--;
			p = p->brother;
		}

		if (noArguments > 0)
			printf("%s: too few actual arguments\n", functionName);
		if (noArguments < 0)
			printf("%s: too many actual arguments\n", functionName);

		emitJump("call", ptr->son->token.value.id);
		break;
	}
	}
}

void processStatement(Node* ptr) {
	Node* p, * q;
	char* startLabel, * endLabel;
	if (ptr != NULL)
	{
		switch (ptr->token.number) {
		case COMPOUND_ST:
			p = ptr->son->brother;
			p = p->son;
			while (p) {
				processStatement(p);
				p = p->brother;
			}
			break;

		case EXP_ST:
			if (ptr->son != NULL) processOperator(ptr->son);
			break;

		case RETURN_ST:
			if (ptr->son != NULL) {
				p = ptr->son;
				if (p->noderep == nonterm)
					processOperator(p);
				else
					rv_emit(p);
				emit0("retv");
			}
			else
				emit0("ret");
			break;

		case IF_ST:
				{
					char label[LABEL_SIZE];

					genLabel(label);
					processCondition(ptr->son);
					emitJump("fjp", label);
					processStatement(ptr->son->brother);
					emitLabel(label);
				}
				break;

		case IF_ELSE_ST:
		{
			char label1[LABEL_SIZE], label2[LABEL_SIZE];

			genLabel(label1);	genLabel(label2);
			processCondition(ptr->son);

			emitJump("fjp", label1);
			processStatement(ptr->son->brother);
			emitJump("ujp", label2);

			emitLabel(label1);
			processStatement(ptr->son->brother->brother);
			emitLabel(label2);
		}
		break;

		case WHILE_ST:
		{
			char label1[LABEL_SIZE], label2[LABEL_SIZE];

			genLabel(label1);	genLabel(label2);
			emitLabel(label1);
			processCondition(ptr->son);

			emitJump("fjp", label2);
			processStatement(ptr->son->brother);
			emitJump("ujp", label1);
			emitLabel(label2);
		}
		break;
		}
	}
	
}
void processCondition(Node* ptr) {
	if (ptr->noderep == nonterm)	processOperator(ptr);
	else 	rv_emit(ptr);
}

void processFuncHeader(Node* ptr) {
	int noArguments, returnType;
	int stIndex;
	Node* p = ptr;

	printf("processFunctionHeader\n\n");

	if (ptr->token.number != FUNC_HEAD) {
		printf("error in processFunctionHeader!\n");
		printTree(ptr, 0);
		exit(1);
	}

	// step 1 : process the function return type
	p = ptr->son->son;
	while (p) {
		if (p->token.number == INT_NODE)
			returnType = INT_TYPE;
		else if (p->token.number == VOID_NODE)
			returnType = VOID_TYPE;
		else printf("invalid function return type!\n");

		p = p->brother;
	}

	// step 2 : count the number of formal parameters
	p = ptr->son->brother->brother;  // FORMAL_PARA
	p = p->son;  // PARAM_DCL

	noArguments = 0;

	while (p) {
		noArguments++;
		p = p->brother;
	}

	// step 3 : insert the function name
	stIndex = insert(ptr->son->brother->token.value.id, returnType, FUNC_TYPE, 1/*base*/, 0/*offset*/, noArguments/*width*/, 0/*initalValue*/);

}

void codeGen(Node* ptr) {
	Node* p;
	int globalSize;

	initSymbolTable();
	// step 1 : process the declaration part
	for (p = ptr->son; p; p = p->brother) {
		if (p->token.number == DCL) {
			printf("\n\n\n");
			processDeclaration(p->son);
		}
		else if (p->token.number == FUNC_DEF) processFuncHeader(p->son);
		else icg_error(3);
	}

	// dumpSymbolTable();
	globalSize = offset - 1;
	// printf("size of global variables = %d\n", globalSize);

	genSym(base);

	// step 2 : process the function part
	for (p = ptr->son; p; p = p->brother)
		if (p->token.number == FUNC_DEF) processFunction(p);
	//if(!mainExist) warningmsg("main does not exist");

	// step 3 : generate codes for starting routine
	emit1("bgn", globalSize);
	emit0("ldp");
	emitJump("call", "main");
	emit0("end");
}

int checkPredefined(Node* ptr) {
	Node* p = ptr;
	char* functionName;
	int noArguments;
	int stIndex;
	functionName = p->token.value.id;

	if (strcmp(functionName, "read") == 0) {
		noArguments = 1;
		emit0("ldp");
		p = p->brother;
		while (p) {
			if (p->noderep == nonterm)
				processOperator(p);
			else {
				stIndex = lookup(p->token.value.id);

				if (stIndex == -1)
					return 0;

				emit2("lda", symbolTable[stIndex].base, symbolTable[stIndex].offset);
			}
			noArguments--;
			p = p->brother;
		}

		if (noArguments > 0) printf("%s: too few actual arguments\n", functionName);
		else if (noArguments < 0) printf("%s: too many actual arguments\n", functionName);

		emitJump("call", functionName);
		return 1;
	}
	else if (strcmp(functionName, "write") == 0) {
		noArguments = 1;
		emit0("ldp");
		p = p->brother;
		while (p) {
			if (p->noderep == nonterm)
				processOperator(p);
			else {
				stIndex = lookup(p->token.value.id);

				if (stIndex == -1)
					return 0;

				emit2("lod", symbolTable[stIndex].base, symbolTable[stIndex].offset);
			}
			noArguments--;
			p = p->brother;
		}

		if (noArguments > 0) printf("%s: too few actual arguments\n", functionName);
		else if (noArguments < 0) printf("%s: too many actual arguments\n", functionName);

		emitJump("call", functionName);
		return 1;

	}

	return 0;
}


void processFunction(Node* ptr) {
	Node* p;
	int i;

	printf("prcessFunction\n\n");
	printTree(ptr, 0);
	// process function header

	// process function body
	// step 1 : process formal parameters
	if (ptr->son->son->brother->brother->son) {	// PARAM_DCL
		for (p = ptr->son->son->brother->brother->son; p; p = p->brother) {
			if (p->token.number == PARAM_DCL)
				processDeclaration(p->son);
			else return;
		}
	}

	// step 2 : process the declaration part in function body
	for (p = ptr->son->brother->son->son; p; p = p->brother) {
		if (p->token.number == DCL)
			processDeclaration(p->son);
		else return;
	}

	// step 3 : emit the funtion start code
	emitFunc("fun", offset - 1, base, 2);

	for (i = 0; i < symbolTableTop; i++) {
		genSym(i);
	}

	// step 4 : process the statement part in function body	
	for (p = ptr->son; p; p = p->brother) {
		if (p->token.number == COMPOUND_ST)
			processStatement(p);
	}

	// step 5 : check if return check if return type and return value
	emit0("ret");

	// step 6 : generate the ending codes
	emit0("end");
}