#include "calc2019.h"
#include <stdio.h>
#include <time.h>

long long getElapsedTime(unsigned int nFlag)
{
	const long long NANOS = 1000000000LL;
	static struct timespec startTS, endTS;
	static long long retDiff = 0;

	if (nFlag == 0) {
		retDiff = 0;
		if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startTS) == -1) {
			printf("Failed to call clock_gettime\n");
		}
	}
	else {
		if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endTS) == -1) {
			printf("Failed to call clock_gettime\n");
		}
		retDiff = NANOS * (endTS.tv_sec - startTS.tv_sec) + (endTS.tv_nsec - startTS.tv_nsec);
 	}

	return retDiff;
}

int main(int argc, char* argv[]){
		getElapsedTime(0);
    	NUMLIST* numlist = newNUMLIST();
    	Postfix* postfix = newPostfix();

		if(argc == 1) input(numlist, postfix);
		else{
			FILE* ifp = fopen(argv[1], "r");
			inputf(numlist, postfix, ifp);
		}

    	NUM* ans = calculate(numlist, postfix);

		// printf("answer = "); printNUM(ans);
		if(argc >= 3){
			FILE *ofp = fopen(argv[2], "w");
			putNUM(ans, ofp);
			fclose(ofp);
			printf("\n");  
		}
		printf("answer = "); printNUM(ans); printf("\n");
		printf("Elapsed Time: %lld\n", getElapsedTime(1));
		return 0;
}

