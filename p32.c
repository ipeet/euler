/*
We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.

The product 7254 is unusual, as the identity, 39 * 186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.

Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.
*/

#include <stdio.h>

// Returns 0 if the digits represented by the first and second
// operands and their product are 1-9 pandigital.
// Returns the product if they are.
unsigned int test_pan(unsigned int *first, unsigned int first_len,
					  unsigned int *snd, unsigned int snd_len) 
{
	// Tracks which digits have already been used.
	unsigned int used[10] = {0,0,0,0,0,0,0,0,0,0};
	
	// Get first operand -
	unsigned int fst_ttl = 0;
	unsigned int col = 1;
	unsigned int i;
	for(i=0;i<first_len;++i) {
		fst_ttl += col*first[i];
		if(!used[first[i]]) used[first[i]] = 1;
		else return 0;
		col*=10;
	}
	
	// Get second operand -
	unsigned int snd_ttl = 0;
	col = 1;
	for(i=0;i<snd_len;++i) {
		snd_ttl += col*snd[i];
		if(!used[snd[i]]) used[snd[i]] = 1;
		else return 0;
		col*=10;
	}
	
	// Get product:
	unsigned int prod = fst_ttl*snd_ttl;
	while(prod>0) {
		if(!used[prod%10]) used[prod%10] = 1;
		else return 0;
		prod/=10;
	}
	
	//Not allowed to use 0
	if(used[0]) return 0;
	
	//Check if all digits were used
	for(i=1;i<10;++i) {
		if(!used[i]) return 0;
	}
	//They were.
	printf("%d * %d = %d is pandigital.\n",
		   fst_ttl,snd_ttl,fst_ttl*snd_ttl);
	return fst_ttl*snd_ttl;
}

// Returns the sum of all pandigitals of the given form.
unsigned int test_form(unsigned int num_fst, unsigned int num_snd) {
	unsigned int fst[10];
	unsigned int snd[10];
	unsigned int i;
	unsigned int sum = 0;
	/* Cycle through possible values of the first operand */
	for(i=0;i<=num_fst;++i) fst[i] = 0;
	while(1) {
		/* Increment the first operand*/
		i = 0;
		++fst[i];
		while(fst[i]>=10) {
			fst[i+1] += fst[i]/10;
			fst[i] = fst[i]%10;
			++i;
		}
		// If we overflowed the allotted count, we're done.
		if(i>=num_fst) break;
		
		/* Clear the second operand, then cycle through
		 * possibilities */
		for(i=0;i<=num_snd;++i) snd[i] = 0;
		while(1) {
			/* Increment the second operand */
			i = 0;
			++snd[i];
			while(snd[i]>=10) {
				snd[i+1] += snd[i]/10;
				snd[i] = snd[i]%10;
				++i;
			}
			// If we overflowed, we've cycled all possibilities.
			if(i>=num_snd) break;
			
			// Test the current pair of operands.
			sum+=test_pan(fst,num_fst,snd,num_snd);
		}
		
	}
	return sum;
}

int main() {
	
	//Run through 1*4 configurations:
	unsigned int total = 0;
	total+=test_form(1,4);
	total+=test_form(2,3);
	
	return 0;
}