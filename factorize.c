#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <gmp.h>

#include "read_file.h"
#include "parser.h"
#include "factorize.h"

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

/**
 * factors - entry point
 *
 * @argc: the argument counter
 * @argv: the command line arguments
 *
 * Return: always return 0
*/

int factors(int argc, char *argv[])
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

	factorize(lines);

	free(lines);
	free(buffer);

	return (0);
}

/**
 * main - entry point
 *
 * @argc: the argument counter
 * @argv: the command line arguments
 *
 * Return: always return 0
*/

int main(int argc, char *argv[])
{
	struct rusage before, after;
	struct timeval user_duration;
	struct timeval sys_duration;

	getrusage(RUSAGE_SELF, &before);

	factors(argc, argv);

	getrusage(RUSAGE_SELF, &after);

	timersub(&after.ru_utime, &before.ru_utime, &user_duration);

	timersub(&after.ru_stime, &before.ru_stime, &sys_duration);

	printf("\n");

	printf("real %ldm%.3fs\n", (long)(after.ru_utime.tv_sec / 60),
		(double)(after.ru_utime.tv_sec % 60) +
		(double)after.ru_utime.tv_usec / 1000000);

	printf("user %ldm%.3fs\n", (long)(user_duration.tv_sec / 60),
		(double)(user_duration.tv_sec % 60) +
		(double)user_duration.tv_usec / 1000000);

	printf("sys  %ldm%.3fs\n", (long)(sys_duration.tv_sec / 60),
		(double)(sys_duration.tv_sec % 60) +
		(double)sys_duration.tv_usec / 1000000);

	return (0);
}
