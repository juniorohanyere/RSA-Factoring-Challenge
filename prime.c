#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gmp.h>

#include "prime.h"
#include "read_file.h"
#include "parser.h"

/**
 * prime - function that factorizes a number
 *
 * @lines: array containing a list of numbers
 *
 * Return: return nothing
*/

void prime(char **lines)
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
				if (is_prime(num, f2) == 0)
				{
					mpz_div(f1, num, f2);
					gmp_printf("%Zd=%Zd*%Zd\n", num, f1, f2);
					break;
				}
			}
		}
	}
	mpz_clear(f1);
	mpz_clear(f2);
	mpz_clear(num);
}

/**
 * is_prime - function that checks if a given number is prime or not
 *
 * @num: the original number
 * @factor: factor of @num
 *
 * Return: return 0 if prime
 *	   return 1 otherwise
*/

int is_prime(mpz_t num, mpz_t factor)
{
	int i;
	mpz_t f, d;

	mpz_init(f);
	mpz_init(d);
	i = 0;

	for (mpz_set_ui(f, 2); mpz_cmp(f, factor) <= 0; mpz_add_ui(f, f, 1))
	{
		if (mpz_divisible_p(factor, f))
			i += 1;
		else
		{
			mpz_div(d, num, factor);
			if (mpz_divisible_p(d, f))
				i += 1;
		}
		/**
		 * more than one factor, starting from 2,
		 * shows its not prime
		*/
		if (i > 1)
		{
			mpz_clear(f);
			mpz_clear(d);
			return (1);
		}
	}

	mpz_clear(f);
	mpz_clear(d);

	return (0);
}

/**
 * main - entry point
 *
 * @argc: the argument counter
 * @argv: array containing command line arguments
 *
 * Return: always return 0
*/

int main(int argc, char *argv[])
{
	const char *filename = argv[1];
	char *buffer;
	char **lines;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "Usage: %s <filename>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	buffer = read_file(filename);
	lines = parse(buffer, "\n");

	prime(lines);

	free(lines);
	free(buffer);

	return (0);
}
