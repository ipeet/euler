/*
The nth term of the sequence of triangle numbers is given by, tn = ½n(n+1); so the first ten triangle numbers are:

1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

By converting each letter in a word to a number corresponding to its alphabetical position and adding these values we form a word value. For example, the word value for SKY is 19 + 11 + 25 = 55 = t10. If the word value is a triangle number then we shall call the word a triangle word.

Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common English words, how many are triangle words?
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRACE(args...)   printf(args)
//#define TRACE(args...)

int word_to_num(const char* word) {
    int i, sum=0;
    // Caps only, folks
    for(i=0;word[i]!='\0';++i) sum += word[i] - 'A' + 1;
    return sum;
}

/* Triangle numbers have the form T = 0.5n(n+1)
 * So, if 'S' is a triangle number,  S = 0.5n^2 + 0.5
 * S - 0.5 = 0.5n^2
 * sqrt( 2S - 1 ) = n   yields integer n */
int is_trinum(int num) {
    int cur_trinum = 1, i = 2;
    // find first trinum >= the number
    for(i = 2; cur_trinum < num; ++i) cur_trinum+=i;
    // Check if num is a trinum
    if(cur_trinum==num) return 1;
    return 0;
}

// We're cheating a little and expecting the file to be piped into stdin (which makes testing easier)
int main() {
    // So I felt like writing the parse code myself.  What of it? 
    char cur_ch;
    char cur_word[32];  // more than enough for the words in the file
    int word_inx = 0;
    int num_tri_words=0;
    while( 1 ) {
        if( (cur_ch=getchar()) == EOF ) break;
	// Expecting opening "
	if( cur_ch != '"' ) {
	    printf("Expected opening '\"'");
	    abort();
	}
	// Get word
	word_inx=0;
	while( (cur_ch=getchar()) != '"' ) {
            if( cur_ch == EOF ) {
                printf("Unexpected EOF.");
		abort();
	    }
	    cur_word[word_inx++]=cur_ch;
	}
	cur_word[word_inx]='\0';
	// Have the word
	TRACE("Word! '%s' = %d %s\n",
			cur_word,
			word_to_num(cur_word),
			is_trinum(word_to_num(cur_word))?"triword!":"");
	if( is_trinum(word_to_num(cur_word)) ) ++num_tri_words;
	// If there are more words, a comma should be next
	if( (cur_ch=getchar()) != ',' ) break;  // (done)
    }
    printf("Done!  Found %d triangle words.\n",num_tri_words);
    return 0;
}

