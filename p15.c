#include <stdio.h>

#define GRID_NODES 21

unsigned long int lens[GRID_NODES][GRID_NODES];

int main() {
	unsigned int i = 0;
	unsigned int j = 0;
	for(i=0;i<GRID_NODES;++i) lens[i][0] = 1;
	for(j=0;j<GRID_NODES;++j) lens[0][j] = 1;
	for(i=1;i<GRID_NODES;++i) {
		for(j=1;j<GRID_NODES;++j) {
			lens[i][j] = 0;
			lens[i][j] = lens[i-1][j];
			lens[i][j] += lens[i][j-1];
		}
	}
	printf("Num paths for %d nodes: %ld\n",GRID_NODES,lens[GRID_NODES-1][GRID_NODES-1]);
	
	return 0;
}