#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int delay(int time){
	int i, j;
	
	for(i = 0; i < time; i++)
		for(j = 0; j < 5000; j++)
			;
}

int main(){

	struct timeval start;
	struct timeval end;
	
	int temp;
	unsigned long diff;

	gettimeofday(&start,NULL);
	delay(10);
	gettimeofday(&end,NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("the difference is %ld (ms)\n", diff);

	return 0;
}
