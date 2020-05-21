#include "calc2019.h"

exNode* newExNode(char c){
	exNode* temp = (exNode*)malloc(sizeof(exNode));
	temp->data = c;
	temp->next = NULL;
	return temp;
}

Postfix* newPostfix(void){
	Postfix* temp = (Postfix*)malloc(sizeof(Postfix));  // numList = {123, 345, 76.5}   ncurr
	temp->head = NULL;									// postfix = {K K + K -}       excurr
	temp->tail = NULL;
	return temp;
}

void addtoPostfix(Postfix* p, char c){
	exNode* temp = newExNode(c);
	if(p->head == NULL) { p->head = temp; }
	else                { p->tail->next = temp; }

	p->tail = temp;
}

void in2post(Postfix* p, opStack* st, char c){
	if(c == '+' || c == '-'){
		while(!opEmpty(st) && opTop(st) != '('){
			addtoPostfix(p, opPop(st));
		}
		opPush(st, c);
	}
	else if(c == '*' || c == '/'){
       		while(!opEmpty(st) && (opTop(st) == '*' || opTop(st) == '/')){
            		addtoPostfix(p, opPop(st));
        	}
        	opPush(st, c);
    	}
    	else if(c == '('){
        	opPush(st, c);
    	}
    	else if(c == ')'){
        	while(!opEmpty(st) && opTop(st) != '('){
            		addtoPostfix(p, opPop(st));
        	}
        	if(!opEmpty(st)) opPop(st);
    	}
    else{ // ?à´?ûê
        addtoPostfix(p, c);
    }
}

