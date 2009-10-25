#include <stdio.h>
#include <math.h>

int test_prime(unsigned int test, unsigned int* dest, unsigned int dest_sz) {
	//unsigned int sqr = ceil(sqrt((double)test));
	//printf("In test_prime, test %d\n",test);
	int sqr = sqrt(test);
	int i;
	for(i = 0; (i<dest_sz) && (dest[i]<=sqr); ++i) {
		//printf("i: %d pr: %d\n",i,dest[i]);
		if( test % dest[i]  == 0 ) return 0;
	}
	return 1;
}

int main() {
	const unsigned int arr_sz = 250000; //gues 250k as an upper bound for primes below 2M
	unsigned int primes[arr_sz];
	primes[0] = 2;
	primes[1] = 3;
	primes[2] = 5;
	unsigned int next = 3;
	int i;
	for(i = 6; i<2000000; i++) {
		if(next>=arr_sz) {
			printf("Array too small!\n");
			return 1;
		}
		if(test_prime(i,primes,next)) {
			//printf("%d is prime\n",i);
			primes[next] = i;
			++next;
		}
	}
	printf("Found %d primes!\n",next);
	unsigned long sum = 0;
	for(i = 0; i<next; i++) {
		if(sum>(1UL<<63)) {
			printf("Overflow detected!\n");
			return 1;
		}
		sum+=primes[i];
	}
	printf("Sum is %ld.\n",sum);
	return 0;
}
