#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "read_file.h"

/**
 * parse - parses a buffer into lines if the buffer contains new lines
 *
 * @buffer: the buffer to be parsed
 * @delimiter: the delimiter
 *
 * Return: return an array of the parsed buffer in form of lines
*/

char **parse(char *buffer, char *delimiter)
{
	int i, buffer_size = BUFFER_SIZE;
	char *token = NULL;
	char **tokens = NULL;

	tokens = malloc(sizeof(char *) * buffer_size);
	if (tokens == NULL)
	{
		dprintf(STDERR_FILENO, "Unable to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(buffer, delimiter);
	if (token == NULL)
	{
		free(token);
		free(tokens);
		return (NULL);
	}
	for (i = 0; token != NULL; i++)
	{
		if (i >= buffer_size)
		{
			buffer_size += BUFFER_SIZE;
			tokens = realloc(tokens,
				buffer_size  * sizeof(char *));
			if (!tokens)
			{
				printf("Unable to allocate memory\n");
				free(token);
				free(tokens);
				exit(EXIT_FAILURE);
			}
		}
		tokens[i] = token;
		token = strtok(NULL, "\n");
	}
	/* null termination */
	tokens[i] = NULL;
	free(token);

	return (tokens);
}
