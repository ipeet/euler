/*
The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 
*/

#include <stdio.h>
#include <math.h>

int main() {
	unsigned long bigno = 600851475143UL;
	unsigned long sqbn = ceil(sqrt((long double)bigno));
	unsigned long lrg_pr_fact = 2;
	if( sqbn*sqbn < bigno ) printf("Warning: Double precision error!\n");
	printf("Searching for largest prime factor of %ld\n",bigno);
	
	#define PR_SZ 1000000
	unsigned long primes[PR_SZ];
	primes[0] = 2;
	unsigned long pr_ct = 1;
	
	unsigned long i, j;
	short int isPrime;
	for(i = 3; i<=sqbn; i++) {
		isPrime = 1;
		for(j = 0; (j<pr_ct) && (i >= primes[j]*primes[j]) ; j++) {
			if( (i%primes[j]) == 0 ) {
				isPrime = 0;
				break;
			}
		}
		if(isPrime) {
			if( bigno % i == 0 ) lrg_pr_fact = i;
			primes[pr_ct] = i;
			++pr_ct;
			if(pr_ct==PR_SZ) {
				printf("ERROR: Ran out of space for primes.\n");
				return 1;
			}
		}
	}
	printf("Largest prime factor: %ld\n",lrg_pr_fact);
	
	return 0;
}
