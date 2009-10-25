/*
2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2^1000?
*/
#include <stdio.h>

//Should not require more than ~400 decimal digits to express a 1000b value.
#define DIGITS 450 
char digit_buf[DIGITS]; 

int main() {
	unsigned int i, j;
	//Initialize digit buffer
	for(i = 0; i<DIGITS; ++i) {
		digit_buf[i] = 0;
	}
	//2^0 =:
	digit_buf[0] = 1;
	unsigned int carry;
	for(i = 0; i<1000; ++i) { //double 1000 times
		//Double once:
		carry = 0;
		for(j = 0; j<DIGITS; ++j) {
			digit_buf[j] = 2*digit_buf[j] + carry;
			if(digit_buf[j]>9) {
				carry = digit_buf[j]/10; //integer division truncation necessary.
				digit_buf[j] = digit_buf[j]%10;
			} else 
				carry = 0;
			if(carry>1) printf("Sanity check failed: Carry should never be > 1!\n");
			if(carry && (j+1==DIGITS)) printf("Buffer overflow detected!\n");
		}
	}
	//Sum digits.
	unsigned long sum = 0;
	for(i = 0; i<DIGITS; ++i) {
		sum+=digit_buf[i];
	}
	printf("Sum is %ld\n",sum);
	return 0;
}