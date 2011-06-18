/*
By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

What is the 10001st prime number?
*/
#include <stdio.h>
#include "calc_primes.h"

int main() {
	printf("10001th Prime: %ld\n",get_prime(10001-1));
	return 0;
}
