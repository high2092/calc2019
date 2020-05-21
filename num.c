#include "calc2019.h"

numNode* newNumNode(char c){
		numNode* temp = (numNode*)malloc(sizeof(numNode));
		temp->data = c;
		temp->next = NULL;
		temp->pre = NULL;
		temp->order = 0;
}

void link_numNode(numNode** node, char c){
		numNode* temp = newNumNode(c);
		if(*node != NULL) (*node)->next = temp;
		temp->pre = *node;
		*node = temp;
}

NUM* newNUM(numNode* tail, int sign, int dec){
		NUM* temp = (NUM*)malloc(sizeof(NUM));
		temp->tail = tail;
		temp->sign = sign;
		temp->dec = dec;
		temp->next = NULL;
		int order = -1*dec;
		while(tail->pre != NULL){
			tail->order = order++;
			tail = tail->pre;
		}
		tail->order = order;
		temp->head = tail;
		return temp;
}

NUMLIST* newNUMLIST(void){
		NUMLIST* temp = (NUMLIST*)malloc(sizeof(NUMLIST));
		temp->head = NULL;
		temp->tail = NULL;
		return temp;
}

void appendNUM(NUMLIST* list, NUM* num){
		if(list->head == NULL) { list->head = num; }
		else                   { list->tail->next = num; }

		list->tail = num;
}
