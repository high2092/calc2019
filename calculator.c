#include "calc2019.h"

void sumNode(numNode* a, numNode* b){ // Addition of two single digits.
    	a->data += b->data - '0';
    	// free(b);
    	if(a->data >= 58){
        	if(a->pre == NULL){
            		numNode* carry = newNumNode('1');
            		carry->order = a->order + 1;
            		carry->next = a;
            		a->pre = carry;
        	}	
        	else{
            		a->pre->data += 1;
        	}
       		a->data -= 10;
    	}
}


void sum(calcStack* st, NUM* num1, NUM* num2){

    	if(num1->sign * num2->sign == -1){ // -1+2  2+(-4)   8+(-17) µîµî.
        	if(num1->sign == -1){
            		num1->sign = 1;        
            		sub(st, num2, num1);
            		return;
        	}                       /* if ¹®°ú else ¹® ¸ðµÎ À½¼öÇÑÅ× ¾ç¼öÀÎ Ã´ ½ÃÅ°°í »¬¼ÀÇÔ¼ö·Î °¡¶ó°í ÇÔ */
        	else{
            		num2->sign = 1;
            		sub(st, num1, num2);
            		return;
        	}
    	}
    	add_imaginary_tail(num1, num2); // µ¡¼À ·ÎÁ÷À» »ý°¢ÇØº¸¸é º»°ÝÀûÀ¸·Î ´õÇÏ±â¸¦ ½ÃÀÛÇÏ±â Àü¿¡ ¼Ò¼öÀÚ¸®¼ö¸¦ ¸ÂÃçÁà¾ßÇÑ´Ù!
    
    	numNode* curr1 = num1->tail;
    	numNode* curr2 = num2->tail;
    	while(curr2 != NULL){ // curr1 != NULL Á¶°Ç È®ÀÎÀº ºÒÇÊ¿äÇØ º¸ÀÎ´Ù. 
        	sumNode(curr1, curr2);
        	if(curr1->pre != NULL){    // ¿©±â ÀÖ±â ¶§¹®!
            		curr1 = curr1->pre;
        	}
        	else{ // num1ÀÌ num2º¸´Ù NULL¿¡ ¸ÕÀú(¶Ç´Â µ¿½Ã¿¡) µµ´ÞÇÑ °æ¿ìÀÌ´Ù.
            		curr1->pre = curr2->pre; // num2¿Í num1ÀÇ ±æÀÌ°¡ °°À¸¸é ÀÌ statementÀÇ ÀÇ¹Ì´Â curr1->pre = NULL; Áï ¾Æ¹« ½ÇÇàµµ ÇÏÁö ¾ÊÀº °Í°ú °°´Ù.
            		if(curr2->pre != NULL) curr2->pre->next = curr1;

            		break;
        	}
        	numNode* temp = curr2;
       		curr2 = curr2->pre;
        	free(temp);
    	}
    	while(curr1->pre != NULL && curr1->data >= 58){
        	curr1->pre->data += 1;
        	curr1->data -= 10;
        	curr1 = curr1->pre;
    	}
    	while(curr1->pre != NULL){
        	curr1 = curr1->pre;
    	}
    	if(curr1->data >= 58){
        	numNode* carry = newNumNode('1');
        	curr1->data -= 10;
        	carry->order = curr1->order + 1;
        	carry->next = curr1;
        	curr1->pre = carry;
        	curr1 = curr1->pre;
    	}
    	num1->head = curr1;
    	// rm_imaginary_head(num1);

    	while(curr1->next != NULL){
        	curr1 = curr1->next;
    	}
    	num1->tail = curr1;
    	rm_imaginary_tail(num1);


    	free(num2);
    	pushCalc(st, num1);
}
// void sum_for_div(calcStack* st, NUM* num1, NUM* num2){

//     	if(num1->sign * num2->sign == -1){ // -1+2  2+(-4)   8+(-17)
//         	if(num1->sign == -1){
//             		num1->sign = 1;
//             		sub(st, num2, num1);
//             		return;
//         	}
//         	else{
//             		num2->sign = 1;
//             		sub(st, num1, num2);
//             		return;
//         	}
//     	}
//     	add_imaginary_tail(num1, num2); // ??žë¦¬ë?? ë§žì¶°ì¤?.
    
//     	numNode* curr1 = num1->tail;
//     	numNode* curr2 = num2->tail;
//     	while(curr2 != NULL){ // curr1 != NULL Á¶°Ç È®ÀÎÀº ºÒÇÊ¿äÇØ º¸ÀÎ´Ù. (Áßº¹)
//         	sumNode(curr1, curr2);
//         	if(curr1->pre != NULL){
//             		numNode* temp = curr1->pre;
//             		curr1 = curr1->pre;
//         	}
//         	else{ // num1ÀÌ num2º¸´Ù NULL¿¡ ¸ÕÀú(¶Ç´Â µ¿½Ã¿¡) µµ´ÞÇÑ °æ¿ìÀÌ´Ù.
//             		curr1->pre = curr2->pre;
//             		if(curr2->pre != NULL) curr2->pre->next = curr1;

//             		break;
//         	}
//         	// numNode* temp = curr2;
//        		curr2 = curr2->pre;
//         	// free(temp);
//     	}
//     	while(curr1->pre != NULL && curr1->data >= 58){
//         	curr1->pre->data += 1;
//         	curr1->data -= 10;
//         	curr1 = curr1->pre;
//     	}
//     	while(curr1->pre != NULL){
//         	curr1 = curr1->pre;
//     	}
//     	if(curr1->data >= 58){
//         	numNode* carry = newNumNode('1');
//         	curr1->data -= 10;
//         	carry->order = curr1->order + 1;
//         	carry->next = curr1;
//         	curr1->pre = carry;
//         	curr1 = curr1->pre;
//     	}
//     	num1->head = curr1;
//     	// rm_imaginary_head(num1);

//     	while(curr1->next != NULL){
//         	curr1 = curr1->next;
//     	}
//     	num1->tail = curr1;
//     	rm_imaginary_tail(num1);


// 		// if(num1->sign ==  0) printf("?");
//     	// free(num2);
//     	pushCalc(st, num1);
// }

void subNode(numNode* a, numNode* b){
    	a->data -= b->data - '0';
    	if(a->data < 48){ // segmentation error?Š” ë°œìƒ?•˜ì§? ?•Š?Š”?‹¤. ?™œ?ƒ?•˜ë©? ?žë¦¿ìˆ˜ê°? ê°™ì„ ?• a->data >= 48 ?¼ ê²ƒì´ê³?, ê·? ?™¸?—” ?•ž ?…¸?“œ?— ?•´?‹¹?•˜?Š” ?ˆ˜?˜ ?žë¦¿ìˆ˜ê°? ?” ë§Žì„ ê²ƒì´ê¸? ?•Œë¬¸ì´?‹¤.
        	a->data += 10;
        	a->pre->data -= 1;
    	}
}
void sub(calcStack* st, NUM* num1, NUM* num2){ // subtract num2 from num. (result will be stored at num1's memory.)
		// Signs are opposite to each other.
    	if(num1->sign * num2->sign == -1){ // -2-1      1-(-2)   /* sign follows former's.
        	num2->sign = num1->sign;
        	sum(st, num1, num2);
        	return;
    	}

    	// Signs equal each other.
		else if(former_is_larger_than_latter(num2, num1)){ // | num2 | > | num1 |
        	swap(&num1, &num2);
        	if(num1->sign == 1) num1->sign = -1; // absolutely smaller positive number - absolutely bigger positive number < 0

        	else num1->sign = 1; // absolutely smaller negative number - absolutely bigger negative number > 0
       		// num1->sign = -1*num1->sign ?œ¼ë¡? ê³ ì¹  ?ˆ˜ ?žˆì§?ë§? ê°??…?„±?„ ê³ ë ¤?•˜?ž.
    	}


    	add_imaginary_tail(num1, num2); // ??žë¦¬ë?? ë§žì¶°ì¤?.

    	numNode* curr1 = num1->tail;
    	numNode* curr2 = num2->tail;

    	while(curr2 != NULL){
        	subNode(curr1, curr2);

        	curr1 = curr1->pre;

        	numNode* temp = curr2;
        	curr2 = curr2->pre;
        	free(temp);
    	}
    	if(curr1 != NULL){
        	while(curr1->data < 48){
            		curr1->data += 10;
            		curr1->pre->data -= 1;
            		curr1 = curr1->pre;
        	}
    	}
    	rm_imaginary_head(num1);
    	rm_imaginary_tail(num1);
    	
		free(num2);

		pushCalc(st, num1);
}
void sub_for_div(calcStack* st, NUM* num1, NUM* num2){ // subtract num2 from num. (result will be stored at num1's memory.)
		// Signs are opposite to each other.
    	if(num1->sign * num2->sign == -1){ // -2-1      1-(-2)   /* sign follows former's.
        	num2->sign = num1->sign;
        	sum(st, num1, num2);
        	return;
    	}

    	// Signs equal each other.
		else if(former_is_larger_than_latter(num2, num1)){ // | num2 | > | num1 |
        	swap(&num1, &num2);
        	if(num1->sign == 1) num1->sign = -1; // absolutely smaller positive number - absolutely bigger positive number > 0

        	else num1->sign = 1; // absolutely smaller negative number - absolutely bigger negative number > 0
       		// num1->sign = -1*num1->sign ?œ¼ë¡? ê³ ì¹  ?ˆ˜ ?žˆì§?ë§? ê°??…?„±?„ ê³ ë ¤?•˜?ž.
    	}


    	add_imaginary_tail(num1, num2); // ??žë¦¬ë?? ë§žì¶°ì¤?.

    	numNode* curr1 = num1->tail;
    	numNode* curr2 = num2->tail;

    	while(curr2 != NULL){
        	subNode(curr1, curr2);

        	curr1 = curr1->pre;

        	// numNode* temp = curr2;
        	curr2 = curr2->pre;
        	// free(temp);
    	}
    	if(curr1 != NULL){
        	while(curr1->data < 48){
            		curr1->data += 10;
            		curr1->pre->data -= 1;
            		curr1 = curr1->pre;
        	}
    	}
    	rm_imaginary_head(num1);
    	rm_imaginary_tail(num1);
    	
		// free(num2);

		pushCalc(st, num1);
}


NUM* mulNode(numNode* a, numNode* b){
    	int temp = (a->data-'0') * (b->data-'0');
    	numNode* block = NULL;
    		if(temp >= 10){
        		block = newNumNode('0');
        		while(temp >= 10){
            			block->data += 1;
            			temp -= 10;
        		}
    		}
    	link_numNode(&block, temp+'0');
    	NUM* piece = newNUM(block, 1, -1*(a->order+b->order));
    	
    		
    	return piece;
}



void mul(calcStack* st, NUM* num1, NUM* num2){ // ?™?  ê³„íšë²•ì„ ê³ ë ¤?•´ë³´ìž
    	NUM* ans = newNUM(newNumNode('0'), 1, 0);
    	int sign = num1->sign * num2->sign;
    	numNode* curr1 = num1->tail;
 	
    	while(curr1 != NULL){
        	numNode* curr2 = num2->tail;
        	while(curr2 != NULL){
            	sum(st, ans, mulNode(curr1, curr2));
            	popCalc(st);
            	curr2 = curr2->pre;
        	}
			numNode* temp = curr1->pre;
			free(curr1);
        	curr1 = temp;

    	}
		free(num1);
		FREE(num2);
		free(num2);
    	ans->sign = sign;
		rm_imaginary_head(ans); // 100 * 0.000001
    
    	pushCalc(st, ans);
}


void divi(calcStack* st, NUM* num1, NUM* num2){
	int sign = num1->sign * num2->sign;
	int order = 0;
	num1->sign = 1; num2->sign = 1;
	if(num2->head->order == 0 && num2->tail->data == '0'){
		printf("Division by zero occurred in the expression.\n\n");
		exit(1);
	}
	// rm_imaginary_tail(num1); // why?
	if(num1->head->order == 0 && num1->tail->data == '0'){
		pushCalc(st, newNUM(newNumNode('0'), 1, 0));
		return;
	}
	while(former_is_larger_than_latter(num1, num2)){
		numNode* curr = num2->head;
		while(curr != NULL){
			curr->order += 1;
			curr = curr->next;
		}
		order++;
		if(num2->tail->order == 1){
			numNode* temp = newNumNode('0');
			temp->order = num2->tail->order - 1;
			temp->pre = num2->tail;
			num2->tail->next = temp;
			num2->tail = temp;
		}

	}
	while(former_is_larger_than_latter(num2, num1)){
		numNode* curr = num2->head;
		while(curr != NULL){
			curr->order -= 1;
			curr = curr->next;
		}
		order--;
		if(num2->head->order == -1){
			numNode* temp = newNumNode('0');
			temp->next = num2->head;
			temp->order = num2->head->order + 1;
			num2->head->pre = temp;
			num2->head = temp;
		}
		else{
			rm_imaginary_tail(num2);
		}
	}
	int i = 0;
	int clear = 0;
	NUM* ans = newNUM(newNumNode('0'), 1, 0);
	while(i < 100 || ans->tail->order > -101){
		sub_for_div(st, num1, num2); popCalc(st);
		sum(st, ans, newNUM(newNumNode('1'), 1, -order)); popCalc(st);
		if(num1->head->order == 0 && num1->tail->data == '0') {clear = 1; break; }
		while(former_is_larger_than_latter(num2, num1)){
			numNode* curr = num2->head;
			while(curr != NULL){
				curr->order -= 1;
				curr = curr->next;
			}
			order--; i++;
			if(num2->head->order == -1){
				numNode* temp = newNumNode('0');
				temp->next = num2->head;
				temp->order = num2->head->order + 1;
				num2->head->pre = temp;
				num2->head = temp;
			}
		}
	}
	if(!clear){
		ans->dec = INF;
		if(ans->tail->order == -101){
			numNode* temp = ans->tail;
			ans->tail = ans->tail->pre;
			ans->tail->next = NULL;
			free(temp);
		}
	}
	// printf("i = %d, ans->tail->order = %d\n", i, ans->tail->order);
	// printf("tail : %c\n", ans->tail->data);
	ans->sign = sign;

	FREE(num1);
	FREE(num2);

	pushCalc(st, ans);
}



NUM* calculate(NUMLIST* numlist, Postfix* postfix){
		NUM* ncurr = numlist->head;
		exNode* excurr = postfix->head;
    	printf("\ncalculating..\n\n\n");

    	calcStack* calcstack = newCalcStack();
    	while(excurr != NULL){
        	if(excurr->data == K){
            		// printf("K ");
            		pushCalc(calcstack, ncurr);
            		ncurr = ncurr->next;
        	}
        	else if(excurr->data == '+'){
            		// printf("+ ");
            		sum(calcstack, popCalc(calcstack), popCalc(calcstack));
        	}
        	else if(excurr->data == '-'){
            		sub(calcstack, popCalc(calcstack), popCalc(calcstack));
        	}
        	else if(excurr->data == '*'){
            		mul(calcstack, popCalc(calcstack), popCalc(calcstack));
        	}
			else if(excurr->data == '/'){
					divi(calcstack, popCalc(calcstack), popCalc(calcstack));
			}
			else{
				printf("\n\nunexpected error.\n");
				exit(1);
			}
        	excurr = excurr->next;
    	}
	return popCalc(calcstack);
}


