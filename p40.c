/*
An irrational decimal fraction is created by concatenating the positive integers:

0.123456789101112131415161718192021...

It can be seen that the 12th digit of the fractional part is 1.

If dn represents the nth digit of the fractional part, find the value of the following expression.

d1 * d10 * d100 * d1000 * d10000 * d100000 * d1000000
*/
#include <stdio.h>

unsigned int dn(unsigned int n) {
	unsigned int next_dig_incr = 10;
	unsigned int digits_per_num = 1;
	unsigned int digits_used = 0;
	unsigned int cur_num = 1;
	unsigned int dig_stk[10] = {0,0,0,0,0,0,0,0,0,0};
	unsigned int ds_ptr = 0;
	
	while(1) {
		if(cur_num==next_dig_incr) {
			++digits_per_num;
			next_dig_incr *= 10;
		}
		
		if( (digits_used+digits_per_num) >= n ) {
			// Using a digit from this number.
			while(cur_num) {
				dig_stk[ds_ptr] = cur_num%10;
				cur_num/=10;
				++ds_ptr;
			}
			return dig_stk[ds_ptr-(n-digits_used)];
		}
		
		digits_used += digits_per_num;
		++cur_num;
	}
}

int main() {
	unsigned int i;
	for(i=1;i<35;++i) {
		printf("%d",dn(i));
	}
	unsigned int digs[] = {1,10,100,1000,10000,100000,1000000};
	unsigned int num = 7;
	unsigned int prod = 1;
	unsigned int cur;
	for(i=0;i<num;++i) {
		cur = dn(digs[i]);
		printf("d%d = %d\n",digs[i],cur);
		prod*=cur;
	}
	printf("Product: %d\n",prod);
	
	return 0;	
}