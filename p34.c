/*
145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

Find the sum of all numbers which are equal to the sum of the factorial of their digits.

Note: as 1! = 1 and 2! = 2 are not sums they are not included.
*/

#include <stdio.h>

unsigned long fact(unsigned int num) {
	unsigned int i;
	unsigned long total = 1;
	for(i=1;i<=num;++i)
		total*=i;
	return total;
}

unsigned long sum_fact_dig(unsigned int num) {
	unsigned long total = 0;
	while(num>0) {
		total+=fact(num%10);
		num /= 10;
	}
	return total;
}

#define LIMIT	2600000


int main() {
	unsigned int i;
	unsigned int total = 0;
	for(i=3;i<LIMIT;++i) {
		if(i==sum_fact_dig(i)) {
			printf("Solution found: %d\n",i);	
			total += i;
		}
	}
	printf("Total: %d\n",total);
	
	return 0;	
}