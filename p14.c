#include <stdio.h>

#define MAXVAL	1000000

unsigned int seq_len[MAXVAL+1]; //Stores the sequence lengths found for each value.
unsigned int seq_stk[MAXVAL]; //Stores the values that have been encountered so far for this sequence
unsigned int stk_ptr = 0; //Points to the top of seq_stk

int main() {
	//Initialize default values.:
	unsigned int i,j, n, grtst, grt_len;
	grtst = 1;
	grt_len = 1;
	for(i=0;i<=MAXVAL;++i) seq_len[i] = 0;
	seq_len[1] = 1;
	
	for(i=1;i<=MAXVAL;++i) {
		n = i;
		stk_ptr = 0;
		seq_stk[0] = n;
		while( (n!=1)  ) {
			if( (n<=MAXVAL) && (seq_len[n]!=0) ) {
				//Already know this one.
				break;
			}
			if(n%2) //Odd
				n = 3*n + 1;
			else  //Even
				n = n/2;
			//Push the current item in the sequence to the stack.
			seq_stk[++stk_ptr] = n;
		}
		//We've either traversed to 1, or found an item with a known length.
		//seq_stk[stk_ptr] is the first known-length item we've found.
		//Pop the whole stack, since we've found the sequence length for all
		for(j=0;j<stk_ptr;++j) {
			if(seq_stk[j]<=MAXVAL)
				seq_len[seq_stk[j]] = seq_len[seq_stk[stk_ptr]] + (stk_ptr-j);
		}
		if(seq_len[i]>grt_len) {
			grt_len = seq_len[i];
			grtst = i;
		}
	}
	
	printf("%d produeces a %d-item sequence.\n",grtst,grt_len);
	return 0;
}