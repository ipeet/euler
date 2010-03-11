/*
A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:

1/2	= 	0.5
1/3	= 	0.(3)
1/4	= 	0.25
1/5	= 	0.2
1/6	= 	0.1(6)
1/7	= 	0.(142857)
1/8	= 	0.125
1/9	= 	0.(1)
1/10	= 	0.1
Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.

Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

// The maximum value for our search
#define MAX_VAL   1000

//#define TRACE(args...) printf(args)
#define TRACE(args...)

int cycle_len(int val) {
    /* We do simple grade-school long division, repeatedly multiplying the numerator by
     * ten and then modding by the denom, then repeating with the remainder.  Since the 
     * remainder is the only state, we know that the cycle will repeat itself when it reaches
     * a particular remainder for the second time.  There is no cycle if we reach a remainder
     * of zero. */
    TRACE("Dividing 1/%d\n",val);
    int remainders[MAX_VAL+1];
    memset(remainders,0,sizeof(int)*(MAX_VAL+1));
    int cur_digit = 1;
    int cur_remainder = 1;
    while( 1 ) {
        cur_remainder *= 10;
        TRACE("%04d DIG: %d  REM: %d\n",cur_digit,(cur_remainder/val),(cur_remainder%val));
	cur_remainder %= val;
	if(cur_remainder>val) abort();
	if(cur_remainder>MAX_VAL) abort();
	if( !cur_remainder ) {
	    // No cycle if remainder becomes 0 (decimal has finite length!)
	    return 0;
	} if( remainders[cur_remainder] ) {
	    /* If we've seen this remainder before, the cycle length is the difference
	     * between the current digit and the last seen digit */
	    return cur_digit - remainders[cur_remainder];
	} else {
	    // Touch this remainder
	    remainders[cur_remainder] = cur_digit;
	}
        ++cur_digit;
    }
} 

int main() {
    printf("Cycle finder...");
    int longest_val = 0;
    int longest_cycle = 0;
    int cur_val, cur_len;
    for(cur_val = 2; cur_val<1000; ++cur_val) {
        cur_len = cycle_len(cur_val);
	printf("%03d Length: %d",cur_val,cur_len);  // /n later
	if(cur_len>longest_cycle) {
            printf(" <<< new longest\n");
	    longest_cycle = cur_len;
	    longest_val = cur_val;
	} else if ( cur_len == longest_val ) {
            printf(" <<< equals longest\n");
	} else {
            printf("\n");
	}
    }
    printf("Winner is %d with cycle length %d\n",longest_val,longest_cycle);
    return 0;
}

