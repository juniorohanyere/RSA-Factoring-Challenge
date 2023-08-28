#include <stdio.h>
#include <stdlib.h>

#include "gmp.h"

void factorize(char **lines)
{
	int i;
	mpz_t num, f1, f2, m;
	long f;

	mpz_init(num);
	mpz_init(m);
	mpz_init(f1);
	mpz_init(f2);

	for (i = 0; lines[i] != NULL; i++)
	{

		mpz_set_str(num, lines[i], 10);
		f = 2;
		while (1)
		{
			mpz_set_ui(f2, f);

			mpz_mod(m, num, f2);
			if (mpz_cmp_ui(m, 0UL) == 0)
			{
				mpz_div(f1, num, f2);
				gmp_printf("%Zd=%Zd*%Zd\n", num, f1, f2);
				break;
			}
			else
				f++;
		}
	}
	mpz_clear(f1);
	mpz_clear(m);
	mpz_clear(f2);
	mpz_clear(num);
}
