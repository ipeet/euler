/*
2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest number that is evenly divisible by all of the numbers from 1 to 20?
*/

#include <stdio.h>

int main() {
	unsigned long int i = 20, j;
	while(1) {
		for(j = 11; j<=20; ++j) {
			if(i%j) goto test_next; //Not divisible, check next
		}
		//Divisible by all!
		break;
	test_next:
		i+=20;
	}
	printf("Found number: %ld\n",i);
	return 0;
}