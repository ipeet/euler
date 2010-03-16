/*
The sum of the squares of the first ten natural numbers is,
12 + 22 + ... + 102 = 385

The square of the sum of the first ten natural numbers is,
(1 + 2 + ... + 10)2 = 552 = 3025

Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025  385 = 2640.

Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
*/

#include <stdio.h>

int main() {
	unsigned long squareOfSum = ((101*100)/2)*((101*100)/2);
	printf("Square of Sum: %ld\n",squareOfSum);
	
	unsigned long sumOfSquares = 0;
	unsigned long i;
	for(i = 1; i<=100; ++i) {
		sumOfSquares += (i*i);
	}
	printf("Sum of Squares: %ld\n",sumOfSquares);
	
	printf("Difference: %ld\n",(squareOfSum-sumOfSquares));
	return 0;
}