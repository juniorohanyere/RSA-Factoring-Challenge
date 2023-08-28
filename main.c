#include <stdlib.h>

#include "read_file.h"
#include "parser.h"
#include "factorize.h"

/**
 * main - entry point
 *
 * @argc: the argument counter
 * @argv: the command line arguments
 *
 * Return: always return 0
*/

int main(int __attribute__((unused))argc, char *argv[])
{
	const char *filename = argv[1];
	char *buffer;
	char **lines;

	buffer = read_file(filename);
	lines = parse(buffer, "\n");

	factorize(lines);

	free(lines);
	free(buffer);

	return (0);
}
