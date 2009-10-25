/*
The decimal number, 585 = 10010010012 (binary), is palindromic in both bases.

Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.

(Please note that the palindromic number, in either base, may not include leading zeros.)
*/

// All binary palindromes may be constructed by bitwise or-ing these values:
#define PAL_BIN_SZ	12
unsigned int pal_bin[PAL_BIN_SZ] =
{
	0x00800001,
 	0x00400002,
  	0x00200004,
    0x00100008,
	0x00080010,
 	0x00040020,
  	0x00020040,
   	0x00010080,
	0x00008100,
 	0x00004200,
  	0x00002400,
   	0x00001800
};

#define DEC_DIG_SZ	10
unsigned char dec_digits[DEC_DIG_SZ] = 
{
	0,0,0,0,0
	0,0,0,0,0
};
	
unsigned int is_dec_pal(unsigned int val) {
	unsigned int i = 0;
	while(val) {
		dec_digits[i++] = val%10;
		val /= 10;
	}
	unsigned int j;
	for(j=0;j<=(i/2);++j) {
		if( dec_digits[j] != dec_digits[i-j-1] )
			return 0;
	}
	return 1;
}

unsigned long soln_sum = 0;

unsigned int try_combos(int st_ind, unsigned int cur_val) {
	if((cur_val<1000000)is_dec_pal(cur_val)) {
		soln_sum += cur_val;
		if(st_ind<(PAL_BIN_SZ-1)) {
			try_combos(st_ind+1,cur_val);
		}
	}
	cur_val = cur_val | pal_bin[st_ind];
	if(is_dec_pal(cur_val)) {
		
	}
}