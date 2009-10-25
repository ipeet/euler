/*
Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:
1634 = 14 + 64 + 34 + 44
8208 = 84 + 24 + 04 + 84
9474 = 94 + 44 + 74 + 44

As 1 = 14 is not a sum it is not included.

The sum of these numbers is 1634 + 8208 + 9474 = 19316.

Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
*/

//Observe that no number > 354294 is possible, since 6(9^5), the largest 6 digit sum of
//5th powers, is 354294
#define MAX 354294

#include <stdio.h>
#include <math.h>

unsigned int sumdigexps(int num, int exp) {
	unsigned int out = 0;
	
	//Do 1's
	while(num>0) {
		out += pow(num%10,exp);
		num /= 10;
	}
	
	return out;
	
}

int main() {	
	unsigned int i;
	unsigned int sum = 0;
	for(i=2;i<=MAX;++i) {
		if(sumdigexps(i,5)==i){
			printf("%d\n",i);
			sum += i;
		}
	}
	printf("Total: %d\n",sum);
	
	return 0;
}