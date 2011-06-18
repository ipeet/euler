/*
The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.

There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.

How many circular primes are there below one million?
*/

#include <stdio.h>
#include "calc_primes.h"

#define LIMIT 1000000

unsigned int is_circ(int pr) {
	unsigned int msd_fact = 1;
	unsigned int curv = pr;
	while(curv>=10) {
		curv/=10;
		msd_fact*=10;
	}
	
	unsigned int i;
	unsigned int cur = pr;
	for(i=1;i<=msd_fact;i*=10) {
		if(!is_prime(cur)) return 0;
		cur = (msd_fact*(cur%10)) + (cur/10);
	}
	return 1;
}

int main() {
	printf("Last prime lte %d: %ld\n",LIMIT,g_last_prime_lte(LIMIT));
	
	unsigned int i;
	unsigned int count = 0;
	for(i=0;get_prime(i)<LIMIT;++i) {
		if(is_circ(get_prime(i))) {
			//printf("Found solution: %ld\n",get_prime(i));
			++count;
		}
	}
	printf("Found %d circular primes.\n",count);
	
	return 0;
}
