/*
Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a  b, then a and b are an amicable pair and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.
*/

#include <stdio.h>

unsigned int sum_divs(int num) {
	unsigned int i, sum = 1;
	for(i=2;(i*i)<=num;++i) {
		if(num%i==0) sum = sum + i + (num/i);
	}
	return sum;
}

#define MAX	10000
unsigned int is_amic[MAX];

int main() {
	unsigned int i;
	for(i = 0; i<MAX; ++i) is_amic[i] = 0;
	
	printf("d(220)=%d\n",sum_divs(220));
	printf("d(284)=%d\n",sum_divs(284));
	
	unsigned int sd, sdsd, total = 0; //sum of divisors, sum of divisors of sum or divisors
	for(i=2;i<MAX;++i) {
		if(is_amic[i]) continue; //already found and added
		sd = sum_divs(i);
		if(sd==i) continue; //amicable nums have to be different.
		sdsd = sum_divs(sd);
		if(i==sdsd) {
			//It's an amicable number.
			total = total + i + sd;
			is_amic[i] = 1;
			is_amic[sd] = 1;
		}
	}
	
	printf("Total: %d\n",total);
	
	return 0;
}