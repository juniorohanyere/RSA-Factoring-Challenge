#include <stdio.h>
#include <stdlib.h>

#include "gmp.h"

/**
 * factorize - function that factorizes a number
 *
 * @lines: array containing a list of numbers
 *
 * Return: return nothing
*/

void factorize(char **lines)
{
	int i;
	mpz_t num, f1, f2;

	mpz_init(num);
	mpz_init(f1);
	mpz_init(f2);

	for (i = 0; lines[i] != NULL; i++)
	{

		mpz_set_str(num, lines[i], 10);
		for (mpz_set_ui(f2, 2); mpz_cmp(f2, num) <= 0; mpz_add_ui(f2, f2, 1))
		{
			if (mpz_divisible_p(num, f2))
			{
				mpz_div(f1, num, f2);
				gmp_printf("%Zd=%Zd*%Zd\n", num, f1, f2);
				break;
			}
		}
	}
	mpz_clear(f1);
	mpz_clear(f2);
	mpz_clear(num);
}
