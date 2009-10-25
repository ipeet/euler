/*
If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?
*/

#include <stdio.h>

int numchars(int num) {
	if(num==0) return 0; //termination
	if(num==1000) return 11; //one thousand
	// x00 becomes 'x' hundred
	if(num%100==0) return numchars(num/100) + 7;
	// xyz becomes 'x' hundred and 'yz'
	if(num>=100) return numchars(num/100) + 10 +numchars(num%100);
	if(num<=19) {
		switch(num) {
			case 1:  // one
			case 2:  // two
			case 6:  // six
			case 10: // ten
				return 3;
			case 4: // four
			case 5: // five
			case 9: // nine
				return 4;
			case 3: // three
			case 7: // seven
			case 8: // eight
				return 5;
			case 11: // eleven
			case 12: // twelve
				return 6;
			case 15: // fifteen
			case 16: // sixteen
				return 7;
			case 13: // thirteen
			case 14: // fourteen
			case 18: // eighteen
			case 19: // nineteen
				return 8;
			case 17: // seventeen 
				return 9;
		}
	}
	switch(num/10) {
		case 2: // twenty x
			return 6 + numchars(num-20); 
		case 3: // thirty x
			return 6 + numchars(num-30);
		case 4: // forty x
			return 5 + numchars(num-40);
		case 5: // fifty x
			return 5 + numchars(num-50);
		case 6: // sixty x
			return 5 + numchars(num-60);
		case 7: // seventy x
			return 7 + numchars(num-70);
		case 8: // eighty x
			return 6 + numchars(num-80);
		case 9: // ninety x
			return 6 + numchars(num-90);
	}
	
	printf("This statement cannot be executed\n");
	return 0;
}

int main() {
	unsigned long letters = 0;
	unsigned int i;
	for(i=1;i<=1000;++i) {
		letters += numchars(i);
	}
	printf("Total %ld characters.\n",letters);
	return 0;
}