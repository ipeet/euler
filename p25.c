/*
The Fibonacci sequence is defined by the recurrence relation:
Fn = Fn1 + Fn2, where F1 = 1 and F2 = 1.

Hence the first 12 terms will be:
F1 = 1
F2 = 1
F3 = 2
F4 = 3
F5 = 5
F6 = 8
F7 = 13
F8 = 21
F9 = 34
F10 = 55
F11 = 89
F12 = 144

The 12th term, F12, is the first term to contain three digits.

What is the first term in the Fibonacci sequence to contain 1000 digits?
*/

#include <stdio.h>

#define DIGITS 1000

unsigned int nums[3][DIGITS];

int main() {
	unsigned int* cur = nums[2];
	unsigned int* last1 = nums[1];
	unsigned int* last2 = nums[0];
	
	unsigned int i;
	for(i=0;i<DIGITS;++i) {
		cur[i] = 0;
		last1[i] =0;
		last2[i] =0;
	}
	last1[0] = 1;
	last2[0] = 1;
	cur[0] = 2;
	unsigned int cur_term = 3;
	while(!cur[DIGITS-1]) {
		/*printf("%d: ",cur_term);
		for(i=DIGITS;i-->0;) 
			printf("%d",cur[i]);
		printf("\n");*/
		
		last2 = last1;
		last1 = cur;
		cur = last2;
		for(i=0;i<DIGITS;++i) {
			cur[i] = last1[i]+last2[i];
			cur[i+1] += cur[i]/10;
			cur[i] = cur[i]%10;
		}
		++cur_term;
	}
	printf("First 1000-digit fib term: %d\n",cur_term);
	return 0;
}