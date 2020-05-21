#include "calc2019.h"
void inputf(NUMLIST* numlist, Postfix* postfix, FILE *fp){
        char c;
    	int dec = 0;
    	int sign = 1;
    	int point = 0;
    	char latest = 0;
    	int parenthesis = 0;
    	numNode* curr = NULL;
    	opStack* opstack = newOpStack();
        if(fp == NULL){
            perror ("Error opening file");
            fclose(fp);
            return;
        }
    	while((c = getc(fp)) != EOF){
        	if('0' <= c && c <= '9'){
					if('0' <= latest && latest <= '9' || latest == '+' || latest == '-' || \
                       latest == '*' || latest == '/' || latest == '(' || latest == '.' || latest == 0){

						link_numNode(&curr, c);
						if(point) dec++;
					}
					else if(latest == ')'){
						in2post(postfix, opstack, '*');
						link_numNode(&curr, c);
					}
					else error(c);
        	}
        	else if(c == '+' || c == '-' || c == '*' || c == '/'){
            		if('0' <= latest && latest <= '9'){
                		appendNUM(numlist, newNUM(curr, sign, dec));
                		toolset(&curr, &sign, &dec, &point);

                		in2post(postfix, opstack, K);
                		in2post(postfix, opstack, c);
            		}
            		else if(latest == ')'){
                		in2post(postfix, opstack, c);
            		}
                    else if(c == '+' || c == '-' && (latest == '(' || latest == 0)){
                        if(c == '-') sign *= -1;
                    }
            		else error(c);
        	}
        	else if(c == '('){
					if('0' <= latest && latest <= '9'){
                		appendNUM(numlist, newNUM(curr, sign, dec));
                		toolset(&curr, &sign, &dec, &point);
                		in2post(postfix, opstack, K);
						in2post(postfix, opstack, '*');

						in2post(postfix, opstack, c);
						parenthesis++;
					}
            		else if(latest == ')'){ // (1)(2) , 1(2)
                		in2post(postfix, opstack, '*');
						in2post(postfix, opstack, c);
						parenthesis++;
            		}
            		else{
                		in2post(postfix, opstack, c);
                		parenthesis++;
            		}
        	}
				else if(c == ')'){
						if('0' <= latest && latest <= '9'){ // (9)
							appendNUM(numlist, newNUM(curr, sign, dec));
							toolset(&curr, &sign, &dec, &point);

							in2post(postfix, opstack, K);
							in2post(postfix, opstack, c);
							parenthesis--;
						}
						else if(latest == ')'){
							in2post(postfix, opstack, c);
							parenthesis--;
						}
						else error(c);
				}
        	else if(c == '.'){
					if('0' <= latest && latest <= '9' && point == 0) point = 1;
            		else error(c);
        	}
			else if(9 <= c && c <= 13){
					continue;
			}
        	else{
					// printf("%d ", c);
            		error(c);
        	}
        	latest = c;
    	}
        fclose(fp);
    	if('0' <= latest && latest <= '9'){
        	appendNUM(numlist, newNUM(curr, sign, dec));
        	in2post(postfix, opstack, K);
    	}
    	else if(latest != ')'){
        	error(c);
    	}
    	if(parenthesis != 0) error(')');
    	
		while(!opEmpty(opstack)){
        	if(opTop(opstack) == '(') error('(');
        	addtoPostfix(postfix, opPop(opstack));
    	}

    	NUM* ncurr = numlist->head;	
    	while(ncurr != NULL){
			rm_imaginary_head(ncurr);
			ncurr = ncurr->next;
		}
}
void input(NUMLIST* numlist, Postfix* postfix){
        char c;
    	int dec = 0;
    	int sign = 1;
    	int point = 0;
    	char latest = 0;
    	int parenthesis = 0;
    	numNode* curr = NULL;
    	opStack* opstack = newOpStack();
		printf("Enter a expression: ");
    	while((c = getchar()) != '\n'){
        	if('0' <= c && c <= '9'){
					if('0' <= latest && latest <= '9' || latest == '+' || latest == '-' || \
                       latest == '*' || latest == '/' || latest == '(' || latest == '.' || latest == 0){

						link_numNode(&curr, c);
						if(point) dec++;
					}
					else if(latest == ')'){
						in2post(postfix, opstack, '*');
						link_numNode(&curr, c);
					}
					else error(c);
        	}
        	else if(c == '+' || c == '-' || c == '*' || c == '/'){
            		if('0' <= latest && latest <= '9'){
                		appendNUM(numlist, newNUM(curr, sign, dec));
                		toolset(&curr, &sign, &dec, &point);

                		in2post(postfix, opstack, K);
                		in2post(postfix, opstack, c);
            		}
            		else if(latest == ')'){
                		in2post(postfix, opstack, c);
            		}
                    else if(c == '+' || c == '-' && (latest == '(' || latest == 0)){
                        if(c == '-') sign *= -1;
                    }
            		else error(c);
        	}
        	else if(c == '('){
					if('0' <= latest && latest <= '9'){
                		appendNUM(numlist, newNUM(curr, sign, dec));
                		toolset(&curr, &sign, &dec, &point);
                		in2post(postfix, opstack, K);
						in2post(postfix, opstack, '*');

						in2post(postfix, opstack, c);
						parenthesis++;
					}
            		else if(latest == ')'){ // (1)(2) , 1(2)
                		in2post(postfix, opstack, '*');
						in2post(postfix, opstack, c);
						parenthesis++;
            		}
            		else{
                		in2post(postfix, opstack, c);
                		parenthesis++;
            		}
        	}
				else if(c == ')'){
						if('0' <= latest && latest <= '9'){ // (9)
							appendNUM(numlist, newNUM(curr, sign, dec));
							toolset(&curr, &sign, &dec, &point);

							in2post(postfix, opstack, K);
							in2post(postfix, opstack, c);
							parenthesis--;
						}
						else if(latest == ')'){
							in2post(postfix, opstack, c);
							parenthesis--;
						}
						else error(c);
				}
        	else if(c == '.'){
					if('0' <= latest && latest <= '9' && point == 0) point = 1;
            		else error(c);
        	}
        	else{
					// printf("%d ", c);
            		error(c);
        	}
        	latest = c;
    	}
    	if('0' <= latest && latest <= '9'){
        	appendNUM(numlist, newNUM(curr, sign, dec));
        	in2post(postfix, opstack, K);
    	}
    	else if(latest != ')'){
        	error(c);
    	}
    	if(parenthesis != 0) error(')');
    	
		while(!opEmpty(opstack)){
        	if(opTop(opstack) == '(') error('(');
        	addtoPostfix(postfix, opPop(opstack));
    	}

    	NUM* ncurr = numlist->head;	
    	while(ncurr != NULL){
			rm_imaginary_head(ncurr);
			ncurr = ncurr->next;
		}
}