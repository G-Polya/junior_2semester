#pragma once
class Interpret {
	UcodeiStack stack;
	int arBase;
	long int tcycle;
	long int exeCount;
	void predefinedProc(int);
	int findAddr(int);
	void statistic();
public:
	void execute(int);
	Interpret();
	virtual ~Interpret() { }
};