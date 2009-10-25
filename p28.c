/*
Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:

21 22 23 24 25
20  7  8  9 10
19  6  1  2 11
18  5  4  3 12
17 16 15 14 13

It can be verified that the sum of both diagonals is 101.

What is the sum of both diagonals in a 1001 by 1001 spiral formed in the same way?
*/

#include <stdio.h>

#define GRID_SZ 1001

unsigned int diag1[GRID_SZ];
unsigned int diag2[GRID_SZ];

int main() {
	unsigned int i,j;
	diag1[0] = 1;
	diag2[0] = 1;
	
	unsigned int val = 1;
	for(i=1;i<=(GRID_SZ/2);++i) {
		for(j=0;j<4;++j) {
			val+=(i*2);
			if(j%2==0) diag1[1+((i-1)*2)+j/2] = val;
			else diag2[1+((i-1)*2)+j/2] = val;
		}
	}
	
	/*printf("Diag1: ");
	for(i=0;i<GRID_SZ;++i) printf("%d ",diag1[i]);
	printf("\nDiag2: ");
	for(i=0;i<GRID_SZ;++i) printf("%d ",diag2[i]);
	printf("\n");*/
	
	unsigned long sum1 = 0, sum2 = 0;
	for(i=0;i<GRID_SZ;++i) {
		sum1 += diag1[i];
		sum2 += diag2[i];
	}
	printf("Total: %ld\n",(sum1+sum2-1));
	
	return 0;
}