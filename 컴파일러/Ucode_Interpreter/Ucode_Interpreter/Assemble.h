#pragma once
class Assemble {
	int instrCnt;
	char lineBuffer[80];
	int bufIndex;
	Label labelProcess;
	char label[LABELSIZE];
	void getLabel();
	int getOpcode();
	int getOperand();
	void instrWrite();
public:
	void assemble();
	int startAddr;
	Assemble() {
		startAddr = 0;
		instrCnt = 0;
		bufIndex = 0;
		memset(lineBuffer, 0, sizeof(lineBuffer));
		memset(label, 0, sizeof(label));
	}
};
