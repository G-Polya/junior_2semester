#include "sdt.c"
#define NO_KEYWORDS 7
#define ID_LENGTH 12
//���û�����.
#define STACKSIZE 20000;
#define NO_OPCODES 41;
//�ִ� �� ũ��.
#define LABEL_SIZE 7
//�ִ� �ؽ� ��Ŷ ������.
#define BUCKET_SIZE 97	
//�ִ� �Լ� ũ��.
#define MAX_LIBRARY_FUNC 3
//������ ũ��.
#define OPCODE_SIZE 5
#define FIRSTWORD	11


//������ �̸�
const char* opcodeName[] = {
	"notop",	"neg",	"inc",	"dec",	"dup",	"swp",	"add",	"sub",	"mult",	"div",
	"mod",		"and",	"or",	"gt",	"lt",	"ge",	"le",	"eq",	"ne",
	"lod",		"ldc",	"lda",	"ldi",	"ldp",	"str",	"sti",	"ujp",	"tjp",	"fjp",
	"call",		"ret",	"retv",	"chkh",	"chkl",	"nop",	"proc",	"end",	"bgn",	"sym",
	"dump",		"none"
};

//�ɺ��̸� ����ü, �ε����� ���̸� ������ �ִ�.
struct Table;
typedef	struct symbol {
	int index;
	int length;
} symbolName;


//�ɺ� ���̺� ����ü
typedef struct Table {
	symbolName symname;
	int index;
	int base;
	int offset;
	int width;
	int typeQualifier;
	int typeSpecifier;
	int initialValue;
} symbolTable;


//���̽�, ������, �ʺ�
int base = 1, offset = 1, width = 1;
//left value, right value
int lvalue, rvalue;
//�Ľ� ���̺� ������� level Table 
int levelTable[PS_SIZE];
//�ɹ����̺� �ε��� 
int stIdx = 0;
//��Ʈ��Ǯ �ε���
int stringpoolIndex = 0;
//��Ʈ��Ǯ ����
char stringPool[1000];
//������ �ε���
int AvailIndex = 0;
int topOfLevelTable;
//���� ������� �ؽ� ����
symbolTable hashBucket[BUCKET_SIZE];
//���� ������� �ɺ����̺� 
symbolTable symTable[BUCKET_SIZE];

//���� Ÿ�� enumeration
enum returnt {
	INT_TYPE, VOID_TYPE, VAR_TYPE, CONST_TYPE,
	FUNC_TYPE
};

FILE* ucodeFile;                        // ucode file