#include "calc2019.h"

opNode* newOpNode(char c){
		opNode* temp = (opNode*)malloc(sizeof(opNode));
		temp->data = c;
		temp->next = NULL;
		return temp;
}

opStack* newOpStack(void){
		opStack* temp = (opStack*)malloc(sizeof(opStack));
		temp->top = NULL;
		return temp;
}

void opPush(opStack* st, char c){
		opNode* temp = newOpNode(c);
		temp->next = st->top;
		st->top = temp;
}

char opPop(opStack* st){
		opNode* temp = st->top;
		char elem = temp->data;
		st->top = temp->next;
		free(temp);
		return elem;
}

char opTop(opStack* st){
		return st->top->data;
}

int opEmpty(opStack* st){
		return !!!(st->top);
}
