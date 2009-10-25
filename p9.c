/*
A Pythagorean triplet is a set of three natural numbers, a  b  c, for which,
a^2 + b^2 = c^2

For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
*/
#include <stdlib.h>
#include <stdio.h>

int main() {
	//Create a lookup table for squares of 0 thru 1000
	unsigned int sq_lup[1001];
	unsigned int i;
	for(i = 0; i<1001; ++i) {
		sq_lup[i] = i*i;
	}
	
	
	unsigned int a,b,b2,c;
	for(c = 1000; c; --c) {
		for(a = 1; a<=500; ++a) {
			b2 = sq_lup[c] - sq_lup[a];
			for(i=1; (i<1001)&&(sq_lup[i]<=b2); ++i) {
				if(sq_lup[i]==b2) {
					// c^2 - a^2 is a perfect square!  Check if a+b+c = 1000
					b = i;
					if( (a+b+c) == 1000) goto done;
				}
			}
		}
	}
	printf("Failed to find a,b,c\n");
	return 1;
	
done:
	printf("a: %d\n",a);
	printf("b: %d\n",b);
	printf("c: %d\n",c);
	printf("Product: %d\n",(a*b*c));
	return 0;
}