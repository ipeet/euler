/*
A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

A number whose proper divisors are less than the number is called deficient and a number whose proper divisors exceed the number is called abundant.

As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.

Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
*/

#include <stdio.h>

unsigned int sum_divs(int num) {
	unsigned int i, sum = 1;
	for(i=2;(i*i)<num;++i) {
		if(num%i==0) sum += i + (num/i);
	}
	if((i*i)==num) sum+=i;
	return sum;
}

#define MAX_NUMS	28124

unsigned int is_abundant[MAX_NUMS];
unsigned int is_abd_sum[MAX_NUMS];

int main() {
	printf("sum_divs(28): %d\n",sum_divs(28));
	
	unsigned int i,j;
	for(i=0;i<MAX_NUMS;++i) {
		is_abundant[i] = 0;
		is_abd_sum[i] = 0 ;
	}
	for(i=2;i<MAX_NUMS;++i) {
		if(sum_divs(i)>i) is_abundant[i] = 1;
	}
	unsigned int num_abt = 0;
	for(i=2;i<MAX_NUMS;++i) 
		if(is_abundant[i]) ++num_abt;	
	printf("Found %d abundant numbers.\n",num_abt);
	
	for(i=2;i<MAX_NUMS;++i) {
		if(!is_abundant[i]) continue;
		for(j=i;j<MAX_NUMS;++j) {
			if(!is_abundant[j]) continue;
			if(i+j < MAX_NUMS) is_abd_sum[i+j] = 1;
		}
	}
	
	unsigned long total = 0;
	for(i=1;i<MAX_NUMS;++i)
		if(!is_abd_sum[i]) total+=i;
	
	printf("Total: %ld\n",total);
	
	return 0;
}