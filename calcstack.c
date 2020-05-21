#include "calc2019.h"


calcNode* newCalcNode(NUM* num){
    	calcNode* temp = (calcNode*)malloc(sizeof(calcNode));
    	temp->data = num;
    	temp->next = NULL;
    	return temp;
}
calcStack* newCalcStack(void){
    	calcStack* temp = (calcStack*)malloc(sizeof(calcStack));
    	temp->top = NULL;
    	return temp;
}

void pushCalc(calcStack* st, NUM* num){
    	calcNode* temp = newCalcNode(num);
    	temp->next = st->top;
    	st->top = temp;
}

NUM* popCalc(calcStack* st){
    	calcNode* temp = st->top;
    	NUM* elem = temp->data;
    	st->top = temp->next;
    	free(temp);
    	return elem;
}
