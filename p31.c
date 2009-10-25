/*
In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation:
1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).

It is possible to make £2 in the following way:
1 x £1 + 1 x 50p + 2 x 20p + 1 x 5p + 1 x 2p + 3 x 1p

How many different ways can £2 be made using any number of coins?
*/
#include <stdio.h>

// Total we're trying to add up to.
unsigned int total = 200;

// Global variables used by combs as it recurrs.
unsigned int vals[8] = {200,100,50,20,10,5,2,1};
unsigned int cts[8] = {0,0,0,0,0,0,0,0};

/* Discovers how many combinations of coins, starting with the 
 * coin at 'st_coin' are possible, adding up to 'total'-'init_sum'. */
unsigned int combs(unsigned st_coin, unsigned int init_sum) {
	unsigned int cur_combs = 0;
	unsigned int cur_sum = 0;
	cts[st_coin] = 0;
	while(cur_sum<=200) {
		cur_sum = init_sum + vals[st_coin]*cts[st_coin];
		if(st_coin<7) {
			cur_combs += combs(st_coin+1,cur_sum);
		} else {
			if(cur_sum==200) cur_combs++;
		}
		++cts[st_coin];
	}
	return cur_combs;
}

int main() {
	printf("There are %d ways to make £2 in change.\n",combs(0,0));
	return 0;
}

