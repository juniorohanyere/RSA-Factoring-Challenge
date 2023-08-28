#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "main.h"

/**
 * read_file - function to read content of a file
 *
 * @filename: name of file to read from
 *
 * Description: reads the content of @filename and saves each line into an array of
 *		char pointers
 *
 * Return: return the buffer read from the file
*/

char *read_file(const char *filename)
{
	int file, rfile;
	char *buffer;

	buffer = malloc(sizeof(char) * BUFFER_SIZE);

	file = open(filename, O_RDONLY);
	if (file == -1)
	{
		printf("Unable to open file: %s\n", filename);
		exit(EXIT_FAILURE);
	}

	rfile = read(file, buffer, BUFFER_SIZE);
	if (rfile == -1)
	{
		printf("Unable to read from file: %s\n", filename);
		exit(EXIT_FAILURE);
	}
	close(file);

	return (buffer);
}
