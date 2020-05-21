#include <stdlib.h>
#include <stdio.h>
#define K 0
#define INF -1
typedef struct numNode{

	char data;  // One node denotes a single digit.
	struct numNode* next;
	struct numNode* pre;
	int order; // Power           /* For example, data = '7', order = -1 means 7 * 10^-1. */
}numNode;

typedef struct NUM{ // A NUM denotes a number such as 17.0.
	               // In this case,
	numNode* head; // Head points the Node of which data is '1'.
	numNode* tail; // Tail points the Node of which data is '0'.
	int sign;      // 1 means positive, -1 means negative.
	int dec;       // Number of decimal.
	struct NUM* next;
}NUM;

typedef struct NUMLIST{ // A NUMLIST points starting point of NUMs which has next pointer. So, just by knowing head, program can search all NUM.

	NUM* head;
	NUM* tail; // Pointer to be used when append NUM to the list 
}NUMLIST;



typedef struct opNode{ // denotes the information of an operator.
	char data;
	struct opNode* next;
}opNode;

typedef struct opStack{
	struct opNode* top;
}opStack;

typedef struct exNode{ // denotes whether a node is operator or operand.
	char data; // 0 means operand. '+', '-', '*' means leteralness.
	struct exNode* next;
}exNode;

typedef struct Postfix{
	exNode* head;
	exNode* tail;
}Postfix;


typedef struct calcNode{ // calcNode is used for Pushing and Popping NUMs.
	NUM* data;
	struct calcNode* next;
}calcNode;

typedef struct calcStack{
	calcNode* top;
}calcStack;



numNode* newNumNode(char);
void link_numNode(numNode**, char);

NUM* newNUM(numNode*, int, int);
NUMLIST* newNUMLIST(void);
void appendNUM(NUMLIST*, NUM*);


opNode* newOpNode(char);
opStack* newOpStack(void);
void opPush(opStack*, char);
char opPop(opStack*);
char opTop(opStack*);
int opEmpty(opStack*);


exNode* newExNode(char);
Postfix* newPostfix(void);
void addtoPostfix(Postfix*, char);
void in2post(Postfix*, opStack*, char);

void input(NUMLIST*, Postfix*);
void inputf(NUMLIST*, Postfix*, FILE*);


calcNode* newCalcNode(NUM*);
calcStack* newCalcStack(void);
void pushCalc(calcStack*, NUM*);
NUM* popCalc(calcStack*);


void rm_imaginary_head(NUM*);
void rm_imaginary_tail(NUM*);
void linkZeroAtTail(NUM*);
void add_imaginary_tail(NUM*, NUM*);


void sumNode(numNode*, numNode*);
void sum(calcStack*, NUM*, NUM*);

void subNode(numNode*, numNode*);
int former_is_larger_than_latter(NUM*, NUM*);
// int former_is_not_less_than_latter(NUM*, NUM*);
void swap(NUM**, NUM**);
void sub(calcStack*, NUM*, NUM*);

NUM* mulNode(numNode*, numNode*);
void mul(calcStack*, NUM*, NUM*);


// void sum_for_div(calcStack*, NUM*, NUM*);
void sub_for_div(calcStack*, NUM*, NUM*);
void divi(calcStack*, NUM*, NUM*);
NUM* calculate(NUMLIST*, Postfix*);

void error(char);
void toolset(numNode**, int*, int*, int*);
void printSign(int);
void printNUM(NUM*);
void putNUM(NUM*, FILE*);
void print_fromFILE(FILE*);
void FREE(NUM*);