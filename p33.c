/*
The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by cancelling the 9s.

We shall consider fractions like, 30/50 = 3/5, to be trivial examples.

There are exactly four non-trivial examples of this type of fraction, less than one in value, and containing two digits in the numerator and denominator.

If the product of these four fractions is given in its lowest common terms, find the value of the denominator.
*/

#include <stdio.h>

void try_denoms(unsigned int num) {
	int msd = num/10;
	int lsd = num%10;
	
	//Try combos with msd switched to lsd.
	unsigned int i;
	for(i=1;i<10;++i) {
		int denom = 10*i+msd;
		
		if( ((double)num/denom) == ((double)lsd/i) ) 
			if(lsd!=i) 
				printf("Found candidate: %d / %d\n",num,denom);
	}
	//Try combos with lsd switched to msd
	for(i=1;i<10;++i) {
		int denom = 10*lsd + i;
		if( ((double)num/denom) == ((double)msd/i) )
			if(lsd!=i)
				printf("Found candiadate: %d / %d\n",num,denom);
	}
}

int main() {
	unsigned int i;
	for(i=1;i<100;++i) {
		try_denoms(i);
	}
	return 0;
}