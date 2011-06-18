/**
 * prime.h
 * 
 * Interface to prime function library.
 * Uses an internal cache to keep track of known primes for later use.
 * 
 * Performance Overview:
 * Ideally O(n*sqrt(n))
 * (x86-64 @ 2.53Ghz, gcc -O3)
 * Number of Primes		Time (ms)
 * ================		======
 * 100000				   164   
 * 200000				   420
 * 400000				  1124
 * 500000				  1535
 * 1000000				  4125
 * 2000000				 11025
 * 5000000				 41000
 * Author:	Iain Peet
 */


#ifndef PRIME_H_
#define PRIME_H_

#include <stdlib.h> //for size_t

//Type to use to store prime numbers
typedef unsigned long int prime_t;

/**
 * Releases all memory resources used for primes.
 */
void finalize_primes();

/**
 * Trims internal memory capacity to a specified level.
 * Will truncate sequence of known primes down to the specified length
 * if the sequence exceeds that size.
 * Does nothing if primes are currently using less space than specified.
 * Internal memory may be expanded by further use of primes.
 * @param size	The maximum number of known primes to keep in memory.
 */
void trim_primes(size_t size);

/**
 * Gets the Nth prime, for all existing primes.
 * Indexing starts at 0 - '2' is prime 0.
 * @param index	the prime to retrieve.
 * @return 		the requested prime.
 */
prime_t get_prime(size_t index);

/** 
 * Determines the position of a prime in the sequence of primes:
 * get_prime(prime_inx(x)) = x
 * @param prime	the prime to find
 * 				If this is not prime, it will be rounded to the next
 * 				largest prime.
 * @return		the index of the prime.
 */
size_t prime_inx(prime_t prime);

/**
 * Tests if a number is prime.
 * @param test	The value to test
 * @return		Nonzero if the value is prime
 * 				0 if the value is not prime.
 */
int is_prime(prime_t test);

/**
 * Gets the last prime number that is less than or equal to the
 * given value.
 * @param val	the last prime <= this value is returned.
 * @return		the requested prime.
 */
prime_t g_last_prime_lte(prime_t val);


/**
 * Gets the first prime number that is greater than or equal to
 * the given value.
 * @param val	the first prime >= this value is returned.
 * @return		the requested prime.
 */
prime_t g_first_prime_gte(prime_t val);

/**
 * Performs a prime factorization on a value.
 * Stores the exponent of each prime factor in an array, where each element
 * holds the exponent of the corresponding prime supplied by get_prime().
 * @param val		The value to factor
 * @param exp_vec	An array to store exponents in.
 * @param vec_sz	The size of prime_vec
 * @return			0 on success
 * 					1 if prime_vec is not long enough.
 */
int prime_factorize(prime_t val, size_t *exp_vec, size_t vec_sz);
void print_prime_factors(size_t *exp_vec, size_t vec_sz);

/**
 * Writes the contents of the prime list to a file for later
 * retrieval.
 * @param file	The name of the file to write to.
 */
void write_prime_list(const char* file);

/**
 * Reads the contents of a file into the prime list.
 * @param file	The name of the file to read from.
 */
void read_prime_list(const char* file);

#endif
