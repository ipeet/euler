/*
We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.

What is the largest n-digit pandigital prime that exists?
*/

#include <stdio.h>
#include "calc_primes.h"


int main() {
	read_prime_list("primelist");
	printf("%ld\n",g_last_prime_lte(1000000000));
	
	return 0;
}
