/*
You are given the following information, but you may prefer to do some research for yourself.
1 Jan 1900 was a Monday.
Thirty days has September,
April, June and November.
All the rest have thirty-one,
Saving February alone,
Which has twenty-eight, rain or shine.
And on leap years, twenty-nine.
A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.

How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
*/

#include <stdio.h>

inline int days(int mo, int yr) {
	switch(mo) {
		case 4: //april
		case 6: //june
		case 9: //sept
		case 11: //nov
			return 30;
		case 1: //jan
		case 3: //mar
		case 5: //may
		case 7: //jul
		case 8: //aug
		case 10: //oct
		case 12: //dec
			return 31;
		case 2:
			return ( (yr%100) && (yr%4==0) ) || (yr%400==0) ? 29 : 28;
		default:
			printf("Invalid month\n"); return 0; 
	}
}

int main() {
	unsigned int year, mo;
	unsigned int totaldays = 1;
	
	unsigned int sun_fst_ct = 0;
	
	printf("feb 1996: %d\n",days(2,1996));
	printf("feb 2000: %d\n",days(2,2000));
	
	for(year = 1900; year<2001;++year) {
		for(mo=1; mo<=12; ++mo) {
			totaldays+=days(mo,year);
			if((year>1900) && (totaldays%7==0)) ++sun_fst_ct;
		}
	}
	if(totaldays%7==0) --sun_fst_ct; //remove jan 1, 2001
	
	printf("Sunday the 1st in 20th Century: %d\n",sun_fst_ct);
	
	return 0;
}