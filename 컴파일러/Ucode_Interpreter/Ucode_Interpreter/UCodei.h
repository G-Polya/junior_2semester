#pragma once

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

const int MAXINSTR = 2000;
const int MAXLABELS = 300;
const int STACKSIZE = 1000;
const int LABELSIZE = 10;
const int NO_OPCODES = 41;

enum { FALSE, TRUE };
enum procIndex { READPROC = -1, WRITEPROC = -2, LFPROC = -3 };


enum opcode {
	notop, neg, incop, decop, dup, swp, add, sub, mult, divop,
	modop, andop, orop, gt, lt, ge, le, eq, ne,
	lod, ldc, lda, ldi, ldp, str, sti, ujp, tjp, fjp,
	call, ret, retv, chkh, chkl, nop, proc, endop, bgn, sym,
	dump, none
};
typedef struct {
	int opcode;
	int value1;
	int value2;
	int value3;
} Instruction;

extern const char* opcodeName[NO_OPCODES];
extern int      executable[NO_OPCODES];
extern int      opcodeCycle[NO_OPCODES];
extern       int dynamicCnt[NO_OPCODES];
extern       int staticCnt[NO_OPCODES];

extern Instruction instrBuf[MAXINSTR];
extern ifstream inputFile;
extern ofstream outputFile;

void errmsg(const char* s, const char* s2);