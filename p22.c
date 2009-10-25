/*
Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.

For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938  53 = 49714.

What is the total of all the name scores in the file?
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NMS 6000
#define MAX_LEN 16
char **nam_arr = 0;
unsigned int n_len = 0;

int str_c(const void* first, const void* second) {
	char *f = *((char**)first);
	char *s = *((char**)second);
	return strcmp(f,s);
}

int main() {
	FILE * names = fopen("names.txt","r");
	if(names==0) {
		 printf("Failed to open file.\n"); 
		 return 1;
	}
	
	/* Read the file */
	nam_arr = (char**)calloc(MAX_NMS,sizeof(char*));
	nam_arr[0] = (char*)calloc(MAX_LEN,sizeof(char));
	char cc = fgetc(names);
	unsigned int nm_chars = 0;
	while(cc!=EOF) {
		if(cc==',') {
			nam_arr[n_len][nm_chars] = '\0';
			n_len++;
			nm_chars = 0;
			if(n_len==MAX_NMS) {
				printf("Too many names.\n");
				return 1;
			}
			nam_arr[n_len] = (char*)calloc(MAX_LEN,sizeof(char));
			cc = fgetc(names);
			continue;
		}
		if(cc=='\"') {
			cc = fgetc(names);
			continue;
		}
		nam_arr[n_len][nm_chars] = cc;
		nm_chars++;
		if(nm_chars==MAX_LEN) {
			printf("Name too long.\n");
			return 1;
		}
		cc = fgetc(names);
	}
	
	printf("Read %d names.\n",n_len+1);
	
	qsort(nam_arr,n_len+1,sizeof(char*),str_c);
	unsigned long int i,j, nam_t, total = 0;
	for(i=0;i<=n_len;++i) {
		nam_t = 0;
		for(j=0;nam_arr[i][j]!='\0';++j) {
			nam_t += nam_arr[i][j] - 'A' + 1;
		}
		total+= (i+1)*nam_t;
	}
	printf("Total: %ld\n",total);
	
	return 0;
}