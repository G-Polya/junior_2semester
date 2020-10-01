#pragma once

#include "Scanner.h"

void getNextSymbol();

// nonterminal procedure
void pD();
void pL();
void pR();

// terminal procedure
void pLabel();
void pInteger();
void pId();
void pSemicolon();
void pComma();

void printParse();