// Common functions used with primes.
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "calc_primes.h"

//Controls expansion rate of the internal storage.
//MUST be >= 1
#define ARR_BASE 10000

//Expanding array of known primes.
prime_t *prime_cache = 0; 
size_t cache_size = 0;
size_t cache_used = 0;

/* Initilizes the internal storage space.  
 * Initial storage capacity is ARR_BASE.
 * Initial prime knowledge is 2 only. */
void _init_primes() {
	prime_cache = calloc(ARR_BASE,sizeof(prime_t));
	prime_cache[0] = 2;
	cache_size = ARR_BASE;
	cache_used = 1;
}

// Releases all resources used for primes.
void finalize_primes() {
	free(prime_cache);
	prime_cache = 0;
	cache_size = 0;
	cache_used = 0;
}


/* Reallocates the available internal storage of known primes to have 
 * the desired capacity.
 * By default, expands available storage by ARR_BASE.
 * Allows internal storage to be reduced.  If the new size is less than
 * the amount of space used by known primes, the sequence of known
 * primes will be truncated. */
void _realloc_cache(size_t new_sz) {
	if(new_sz == 0) new_sz = cache_size + ARR_BASE;
	prime_t *new_cache = calloc(new_sz,sizeof(prime_t));
	size_t i;
	for(i = 0; (i<cache_used) && (i<new_sz); ++i) {
		new_cache[i] = prime_cache[i];
	}
	free(prime_cache);
	prime_cache = new_cache;
	cache_size = new_sz;
	cache_used = new_sz>cache_used ? cache_used : new_sz;
}

// Trims known primes and memory usage down to a specified level.
void trim_primes(size_t count) {;
	if(count<cache_size) _realloc_cache(count);
}


/* Finds the next prime after the sequence of known primes. */
void _find_next_prime() {
	if(!prime_cache) _init_primes();
	if(cache_used==cache_size) _realloc_cache(0);
	
	prime_t test = prime_cache[cache_used-1];
	test = cache_used == 1 ? 3 : prime_cache[cache_used-1] + 2;
	prime_t cur_pr;
	prime_t sqrt_test;
	while(1) {
		sqrt_test = sqrt(test);
		for(cur_pr = 0; prime_cache[cur_pr] <= sqrt_test; ++cur_pr) {
			if( !(test % prime_cache[cur_pr] ) ) goto test_next; //Not prime!
		} //Falls through iff test is prime
		break;
		
	test_next: //Not prime, check the next number.
		test+=2;
	} 
	prime_cache[cache_used++] = test;
}

/* Finds primes until all primes up to and including the specified
 * index are known. */
void _fill_primes(size_t last_ind) {
	if(last_ind<cache_used) return;
	if(!prime_cache) _init_primes();
	if(last_ind>=cache_size) _realloc_cache(last_ind+ARR_BASE);
	
	prime_t test = cache_used == 1 ? 3 : prime_cache[cache_used-1] + 2;
	size_t cur_pr;
	size_t sqrt_test;
	size_t last_max_pr = 0;
	while(last_ind>=cache_used) {
		sqrt_test = sqrt(test);
		for(cur_pr = 0; cur_pr < last_max_pr; ++cur_pr)
			if( !(test % prime_cache[cur_pr]) ) goto test_next; // Not prime!
		for(;prime_cache[cur_pr] <= sqrt_test; ++cur_pr)
			if( !(test % prime_cache[cur_pr]) ) goto test_next; // Not prime!
		//Prime, record it!
		prime_cache[cache_used++] = test;
		
	test_next: //not prime, test next numner
		last_max_pr = cur_pr;
		test+=2;
	}
}

//Gets the Nth prime from the sequence of all primes.
prime_t get_prime(size_t index) {
	if(!prime_cache) _init_primes();
	if(index>=cache_used) _fill_primes(index);
	return prime_cache[index];
}

//Checks if a value is prime.
int is_prime(prime_t val) {
	if(!prime_cache) _init_primes();
	
	// Determines primality with a binary search on prime cache.
	// (i.e. logn complexity!)
	return g_last_prime_lte(val) == val;
}

//Get the last prime less than or equal to a value.
prime_t g_last_prime_lte(prime_t val) {
	if(!prime_cache) _init_primes();
	while(prime_cache[cache_used-1] < val) _find_next_prime();
	
	//Find the prime using a binary search.
	size_t a =0, b=cache_used-1, c;
	do {
		if(prime_cache[a]==val) return val;
		if(prime_cache[b]==val) return val;
		c = a + (b-a) / 2;
		if( prime_cache[c] <= val) a = c;
		else b = c;
	} while( (b-a)>1 );
	return prime_cache[a];
}

//Get the first prime greater than or equal to a value.
prime_t g_first_prime_gte(prime_t val) {
	if(!prime_cache) _init_primes();
	while(prime_cache[cache_used-1] <= val) _find_next_prime();
	
	//Find the prime using a binary search.
	size_t a = 0, b = cache_used-1, c;
	do {
		if(prime_cache[a]==val) return val;
		if(prime_cache[b]==val) return val;
		c = a + (b-a)/2;
		if( prime_cache[c]>= val ) b = c;
		else a = c;
	} while( (b-a)>1 );
	return prime_cache[b];
}

//Find the position of a prime.
size_t prime_inx(prime_t prime) {
	if(!prime_cache) _init_primes();
	if(prime_cache[cache_used-1] < prime) {
		g_first_prime_gte(prime);
		return cache_used - 1;
	}
	
	//Find the prime using a binary search.
	size_t a = 0, b = cache_used-1, c;
	do {
		if(prime_cache[a] == prime) return a;
		if(prime_cache[b] == prime) return b;
		c = a + (b-a)/2;
		if(prime_cache[c] >= prime) b = c;
		else a = c;
	} while( (b-a) > 1 );
	return b;
}

//Perform a prime factorization.
int prime_factorize(prime_t val, size_t *exp_vec, size_t vec_sz) {
	if(!prime_cache) _init_primes();
	if(cache_used < vec_sz) _fill_primes(vec_sz-1);
	
	size_t i, cur_pr;
	//Initialize exponent vector to 0's
	for(i = 0; i<vec_sz; ++i) exp_vec[i] = 0;
	//Do factorization.
	cur_pr = 0;
	while(val>1) {
		if( val % prime_cache[cur_pr] ) { //cur prime is not a factor
			++cur_pr;
			if(cur_pr>=vec_sz) return 1; //Overflow! 
		}
		else { //cur prime is a factor.
			++exp_vec[cur_pr];
			val /= prime_cache[cur_pr];
		}
	}
	return 0;
}

//Show a prime factorization
void print_pr_factors(size_t *exp_vec, size_t vec_sz) {
	if(!prime_cache) _init_primes();
	if(cache_used < vec_sz) _fill_primes(vec_sz-1);
	
	size_t i;
	for(i = 0; i<vec_sz; ++i) {
		if(i&&exp_vec[i-1]) printf(", ");
		if(exp_vec[i]) printf("%ld^%ld",get_prime(i),exp_vec[i]);
	}
	printf("\n");
}

// Write primes to a file
void write_prime_list(const char *fname) {
	FILE *file = fopen(fname,"w");
	if(!file || ferror(file)) return;
	
	
	// Write the number of primes
	fwrite(&cache_used,sizeof(size_t),1,file);
	
	// Number of bytes that are going to be written.
	size_t bytes = cache_used * sizeof(prime_t);
	// Write the number of bytes.
	fwrite(&bytes,sizeof(size_t),1,file);
		
	// Write all the primes.
	fwrite(prime_cache,sizeof(prime_t),cache_used,file);
}

// Read primes from a file.
void read_prime_list(const char *fname) {
	FILE *file = fopen(fname,"r");
	if(!file || ferror(file)) return;
	
	size_t num_primes;
	size_t bytes;
	int res = fread(&num_primes,sizeof(size_t),1,file);
	res = fread(&bytes,sizeof(size_t),1,file);
	
	// Check consistency (might be off if we've changed archs)
	if( bytes != (num_primes*sizeof(prime_t)) ) {
		printf("File data is inconsistent.\n");
		return;
	}
	
	// Already have all the primes that are in the file.
	if(cache_used>=num_primes) return;
	
	if(prime_cache) free(prime_cache);
	prime_cache = (prime_t*)calloc(num_primes+ARR_BASE,sizeof(prime_t));
	
	cache_size = num_primes+ARR_BASE;
	cache_used = num_primes;
	
	// Read all the primes.
	res = fread(prime_cache,sizeof(prime_t),num_primes,file);
}

void _spill_guts() {
	printf("Prime Cache Size: \t%ld\t",cache_size);
	printf("(%ld B)\n",(cache_size*sizeof(prime_t)));
	printf("Known Primes: \t%ld\n",cache_used);
	size_t i;
	for(i = 0; i<cache_used; ++i) {
		printf("\t%ld:\t%ld\n",i,prime_cache[i]);
	}
}

void _test_primes() {
	printf("Init state...\n");
	_spill_guts();
	size_t i = 0;
	for(i = 0; i<10; ++i) {
		printf("Prime %ld:\t%ld\n",i,get_prime(i));
	}
	printf("\nSpilling Guts...\n");
	_spill_guts();
	printf("\nTrimming...\n");
	trim_primes(3);
	_spill_guts();
	printf("\nGetting Prime 9: %ld...\n",get_prime(9));
	_spill_guts();
	printf("\nFinalizing...\n");
	finalize_primes();
	_spill_guts();
	printf("\nGetting last prime <= 18...\n");
	printf("%ld\n",g_last_prime_lte(18));
	printf("\nGetting last prime <= 19...\n");
	printf("%ld\n",g_last_prime_lte(19));
	printf("\nGetting first prime >= 19...\n");
	printf("%ld\n",g_first_prime_gte(19));
	printf("\nGetting first prime >=20...\n");
	printf("%ld\n",g_first_prime_gte(20));
	prime_t val = 2*2*5*7*11*11*23;
	printf("\nPrime factorizing %ld...\n",val);
	size_t exp_sz = prime_inx(g_first_prime_gte(val/2))+1;
	size_t exps[exp_sz];
	if(prime_factorize(val,exps,exp_sz)) printf("Array overflow.\n");
	else {
		size_t i;
		for(i = 0; i< exp_sz; ++i) {
			if(exps[i]) printf("%ld^%ld\n",get_prime(i),exps[i]);
		}
	}
	trim_primes(20);
	printf("\nget_prime(prime_inx(11)) = %ld\n",get_prime(prime_inx(11)));
	printf("\nget_prime(prime_inx(16)) = %ld\n",get_prime(prime_inx(16)));
	printf("\nIs 23 prime?\n%s\n",is_prime(23)?"Yes":"No");
	printf("\nIs 30 prime?\n%s\n",is_prime(30)?"Yes":"No");
	printf("\nEntering Realloc Test Loop...\n");
	size_t count = 1;
	while(1) {
		get_prime(10000);
		get_prime(100000);
		trim_primes(10000);
		finalize_primes();
		if(count%40==0) {
			printf("Memory Cycled: ~%ld KB\n",
				(count*(140000)*sizeof(prime_t))/1000);
		}
		++count;
	}
}
