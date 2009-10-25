/*
n! means n  (n  1)  ...  3  2  1

Find the sum of the digits in the number 100!
*/

#include <stdio.h>
#include <string.h>

#define MAX_DIG 	200
unsigned long digits[MAX_DIG];

int main() {
	unsigned int i, j;
	for(i=0;i<MAX_DIG; ++i) digits[i] = 0;
	digits[0] = 1;
	for(i=1;i<=100;++i) {
		//multiply through all columns
		for(j=0;j<MAX_DIG;++j) digits[j] *= i;
		
		//resolve carry-throughs
		for(j=0;j+1<MAX_DIG;++j) {
			digits[j+1] += digits[j]/10;
			digits[j] = digits[j]%10;
		}
	}
	
	if(digits[MAX_DIG-1] >= 10 ) printf("OVERFLOW!\n");
	
	unsigned int sum = 0;
	for(i=0;i<MAX_DIG;++i) {
		sum+=digits[i];
	}
	 
	printf("Sum: %d\n",sum);
	
	return 0;
}