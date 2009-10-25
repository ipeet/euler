/*
By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.

3
7 5
2 4 6
8 5 9 3

That is, 3 + 7 + 4 + 9 = 23.

Find the maximum total from top to bottom in triangle.txt (right click and 'Save Link/Target As...'), a 15K text file containing a triangle with one-hundred rows.
*/

#include <stdio.h>

#define TRI_SZ 100
unsigned int tri[TRI_SZ][TRI_SZ];

void read_f() {
	FILE *triangle = fopen("triangle.txt","r");
	if(!triangle) {
		printf("Failed to open file.\n");
		return;
	}
	
	unsigned int i,j;
	for(i=1;i<=100;++i) {
//		printf("%02d: ",i);
		for(j=0;j<i;++j) {
			fscanf(triangle,"%d",tri[i-1]+j);
//			if(j<=20) printf("%02d ",tri[i-1][j]);
//			else if(j==21) printf("...");
		}
//		printf("\n");
	}
}

int main() {
	read_f();
	
	unsigned int i, j;
	unsigned int lvls_dn = TRI_SZ;	
	unsigned int tri_max[TRI_SZ][TRI_SZ];
	
//	printf("\nPropagating maxima up tree...\n");
	//First pass, max known at leaves are leaves.
//	printf("%02d: ",(lvls_dn-1));
	for(i=0;i<lvls_dn;++i) {
		tri_max[lvls_dn-1][i] = tri[lvls_dn-1][i];
//		if(i<20) printf("%02d ",tri_max[lvls_dn-1][i]);
	}
//	printf("\n");
	
	//Now, propagate maxima back up to the top of the tree.
	for(i=lvls_dn-1;i-->0;) {
//		printf("%d: ",i);
		for(j=0;j<=i;++j) {
			if( tri_max[i+1][j] > tri_max[i+1][j+1] ) {
				tri_max[i][j] = tri[i][j] + tri_max[i+1][j];
			} else {
				tri_max[i][j] = tri[i][j] + tri_max[i+1][j+1];
			}
//			if(j<20) printf("%02d ",tri_max[i][j]);
//			else if(j==20) printf("...");
		}
//		printf("\n");
	}
	printf("Maximum: %d\n",tri_max[0][0]);
	
	return 0;
}
