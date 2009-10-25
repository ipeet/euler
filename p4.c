


/*
A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91  99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/

#include <stdio.h>
//The first 3 digits of the palindrome, and weights used to calculate its value
unsigned int val_digits[3] = {9,9,9}; //10 in index 0 will denote an underflow.
unsigned int val_mults[3] = {100001,10010,1100};
//Calculate the value of the palindrome represented above
unsigned int get_val() {
	unsigned int val = 0;
	unsigned int i;
	for(i = 0; i<3; ++i) {
		val+=val_digits[i]*val_mults[i];
	}
	return val;
}
//Check if a palindrome has two 3-digit factors
int check_val(unsigned int value) {
	unsigned int i;
	for(i = 999; i>99; --i) {
		if( (!(value % i)) && ( value/i < 1000) ) return i;
	}
	return -1;
}
//Get the next largest palindrome in the sequence
void nextPalindrome() {
	if(!val_digits[2]) {
		val_digits[2] = 9;
		if(!val_digits[1]) {
			val_digits[1] = 9;
			if(!val_digits[0]) {
				val_digits[0] = 10;
			} else {
				--val_digits[0];
			}
		} else {
			--val_digits[1];
		}
	} else {
		--val_digits[2];
	}
}
int main() {
	int a, b;
	unsigned int value = get_val();
	while(val_digits[0] < 10) {
		a = check_val(value);
		if( a >= 0 ) {
			//Found a match!
			b = value/a;
			break;
		}
		nextPalindrome();
		value = get_val();
	}
	if(val_digits[0] == 10) {
		printf("Failed to find a solution.\n");
		return 1;
	}
	printf("Found match! %d * %d = %d\n",a,b,a*b);
	return 0;
}
