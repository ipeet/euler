/*
A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation of the digits 1, 2, 3 and 4. If all of the permutations are listed numerically or alphabetically, we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:

012   021   102   120   201   210

What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?
*/

#include <stdio.h>

unsigned int used[10];
unsigned int vals[10];

int perms_lt(int val, int pos) {
	int perms_lsd = 1;
	unsigned int i;
	for(i = 1; i<=pos; ++i) perms_lsd*=i;
	int num_lt = 0;
	for(i=0;i<val;++i) {
		if(!used[i] ) num_lt++;
	}
	printf("%d, %d : %d\n",val,pos,num_lt*perms_lsd);
	return num_lt * perms_lsd;
}

int main() {
	unsigned int i, j, lastj;
	for(i = 0; i<10; ++i) used[i] = 0;
	
	unsigned int total_perms_lt = 0;
	for(i = 0; i<9; ++i) {
		j = 0;
		while(used[j]) j++;
		while(total_perms_lt + perms_lt(j,9-i) < 1000000) {
			lastj = j;
			++j;
			while(used[j]) ++j;
		}
		total_perms_lt += perms_lt(lastj,9-i);
		vals[i] = lastj;
		used[lastj] = 1;
		printf("i: %d, lastj: %d\n",i,lastj);
	}
	j = 0;
	while(used[j])j++;
	vals[9] = j;
	for(i=0;i<10;++i)
		printf("%d",vals[i]);
	printf("\n");
	
	return 0;
}