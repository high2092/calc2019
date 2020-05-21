#include "calc2019.h"

void error(char c){
		printf("\n\n");
		if(c == ' '){
			printf("Retry with no space.\n");
		}
		else if(c == '/'){
			printf("Division is not supported.\n");
		}
		else{
			printf("Input is illegal.\n");
		}
		printf("\n");

		exit(1);
}

void toolset(numNode** node, int* sign, int* dec, int* point){
		*node = 0; *sign = 1; *dec = 0; *point = 0;
}

void printSign(int sign){
		if(sign == -1) printf("-");
}

void printNUM(NUM* num){
    	if(!(num->head->data == '0' && num->tail->order == 0)) printSign(num->sign);
		numNode* temp = num->head;
		for(int i = 0; i < num->head->order + 1; i++){
			printf("%c", temp->data);
			temp = temp->next;
		}
		if(temp != NULL) printf(".");
		
		while(temp != NULL){
			printf("%c", temp->data);
			temp = temp->next;
		}
		if(num->dec == INF){
			printf("...");
		}
		printf("\n");
}
void putNUM(NUM* num, FILE *ofp){
    	if(!(num->head->data == '0' && num->tail->order == 0)) printSign(num->sign);
		numNode* temp = num->head;
		for(int i = 0; i < num->head->order + 1; i++){
			putc(temp->data, ofp);
			temp = temp->next;
		}
		if(temp != NULL) putc('.', ofp);
		
		while(temp != NULL){
			putc(temp->data, ofp);
			temp = temp->next;
		}
		if(num->dec == INF){
			putc('.', ofp);
			putc('.', ofp);
			putc('.', ofp);
		}
}
void print_fromFILE(FILE* fp){
		char c;
    	while((c = getc(fp)) != EOF){
			printf("%c", c);
		}
}

void rm_imaginary_head(NUM* num){
    	numNode* head = num->head;
    	while(head->data == '0' && head->order > 0){
        	num->head = head->next;
        	num->head->pre = NULL;
        	free(head);
        	head = num->head;
    	}
}

void rm_imaginary_tail(NUM* num){
    	numNode* tail = num->tail;
    	while(tail->data == '0' && tail->order < 0){
        	num->tail = tail->pre;
        	num->tail->next = NULL;
        	free(tail);
        	tail = num->tail;
        	// printf("remove 0 at num's tail\n");
    	}
}

void linkZeroAtTail(NUM* num){
    	numNode* temp = newNumNode('0');
    	num->tail->next = temp;
    	temp->pre = num->tail;
    	temp->order = num->tail->order - 1;
    	num->tail = temp;
}

void add_imaginary_tail(NUM* num1, NUM* num2){
    	if(num1->tail->order < num2->tail->order){ // order1 = -3, order2 = 0 <--> num1 = 0.012, num2 = 4
        	while(num1->tail->order < num2->tail->order){
            		// printf("add 0 at num2's tail\n");
            		linkZeroAtTail(num2);
        	}
        num2->dec = -1 * num2->tail->order;
    	}
    	else{
        	while(num1->tail->order > num2->tail->order){
            		// printf("add 0 at num1's tail\n");
            		linkZeroAtTail(num1);
        	}
        	num1->dec = -1 * num1->tail->order;
    	}
}

int former_is_larger_than_latter(NUM* num1, NUM* num2){
		// printf("former_larger_than_latter? ");
		if(num1->head->order > num2->head->order) return 1;
		else if(num1->head->order < num2->head->order) return 0;
		else{
			if(num1->head->data > num2->head->data) return 1;
			else if(num1->head->data < num2->head->data) return 0;
			else{
				numNode* curr1 = num1->head->next;
				numNode* curr2 = num2->head->next;
				while(curr1 != NULL && curr2 != NULL){
					if(curr1->data == curr2->data) ;
					else if(curr1->data > curr2->data) return 1;
					else return 0;
					curr1 = curr1->next;
					curr2 = curr2->next;
				}
				while(curr1 != NULL){
					if(curr1->data > '0') return 1;
					curr1 = curr1->next;
				}
				return 0;
			}
		}
}

int former_is_not_less_than_latter(NUM* num1, NUM* num2){
		// printf("former_larger_than_latter? ");
		if(num1->head->order > num2->head->order) return 1;
		else if(num1->head->order < num2->head->order) return 0;
		else{
			if(num1->head->data > num2->head->data) return 1;
			else if(num1->head->data < num2->head->data) return 0;
			else{
				numNode* curr1 = num1->head->next;
				numNode* curr2 = num2->head->next;
				while(curr1 != NULL && curr2 != NULL){
					if(curr1->data == curr2->data) ;
					else if(curr1->data > curr2->data) return 1;
					else return 0;
					curr1 = curr1->next;
					curr2 = curr2->next;
				}
				while(curr2 != NULL){
					if(curr2->data > '0') return 0;
					curr2 = curr2->next;
				}
				return 1;
			}
		}
}


void swap(NUM** num1, NUM** num2){
    	NUM* temp = *num1;
    	*num1 = *num2;
    	*num2 = temp;
}

void FREE(NUM* num){
	numNode* curr = num->tail;
	while(curr != NULL){
		numNode* temp = curr->pre;
		free(curr);
		curr = temp;
	}
}