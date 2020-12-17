#include "sdt.c"
#define NO_KEYWORDS 7
#define ID_LENGTH 12
//스택사이즈.
#define STACKSIZE 20000;
#define NO_OPCODES 41;
//최대 라벨 크기.
#define LABEL_SIZE 7
//최대 해쉬 버킷 사이즈.
#define BUCKET_SIZE 97	
//최대 함수 크기.
#define MAX_LIBRARY_FUNC 3
//연산자 크기.
#define OPCODE_SIZE 5
#define FIRSTWORD	11


//연산자 이름
const char* opcodeName[] = {
	"notop",	"neg",	"inc",	"dec",	"dup",	"swp",	"add",	"sub",	"mult",	"div",
	"mod",		"and",	"or",	"gt",	"lt",	"ge",	"le",	"eq",	"ne",
	"lod",		"ldc",	"lda",	"ldi",	"ldp",	"str",	"sti",	"ujp",	"tjp",	"fjp",
	"call",		"ret",	"retv",	"chkh",	"chkl",	"nop",	"proc",	"end",	"bgn",	"sym",
	"dump",		"none"
};

//심볼이름 구조체, 인덱스와 길이를 가지고 있다.
struct Table;
typedef	struct symbol {
	int index;
	int length;
} symbolName;


//심볼 테이블 구조체
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


//베이스, 오프셋, 너비
int base = 1, offset = 1, width = 1;
//left value, right value
int lvalue, rvalue;
//파싱 테이블 사이즈만한 level Table 
int levelTable[PS_SIZE];
//심벌테이블 인덱스 
int stIdx = 0;
//스트링풀 인덱스
int stringpoolIndex = 0;
//스트링풀 변수
char stringPool[1000];
//가능한 인덱스
int AvailIndex = 0;
int topOfLevelTable;
//버켓 사이즈만한 해쉬 버켓
symbolTable hashBucket[BUCKET_SIZE];
//버켓 사이즈만한 심볼테이블 
symbolTable symTable[BUCKET_SIZE];

//리턴 타임 enumeration
enum returnt {
	INT_TYPE, VOID_TYPE, VAR_TYPE, CONST_TYPE,
	FUNC_TYPE
};

FILE* ucodeFile;                        // ucode file