#ifndef PRIME_H
#define PRIME_H

#include <gmp.h>

void prime(char **lines);
int is_prime(mpz_t num, mpz_t factor);

#endif	/* PRIME_H */
