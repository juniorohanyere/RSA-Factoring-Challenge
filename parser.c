#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

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
	char *token;
	char **tokens;

	tokens = malloc(sizeof(char *) * buffer_size);
	if (!tokens)
	{
		printf("Unable to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(buffer, delimiter);
	if (token == NULL)
	{
		free(token);
		return (NULL);
	}
	for (i = 0; token != NULL; i++)
	{
		tokens[i] = token;
		if (i >= buffer_size)
		{
			/* realloc */
			buffer_size += BUFFER_SIZE;
			tokens = realloc(tokens,
				buffer_size  * sizeof(char *));
			if (!tokens)
			{
				printf("Unable to allocate memory\n");
				free(token);
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, delimiter);
	}
	/* null termination */
	tokens[i] = NULL;
	free(token);

	return (tokens);
}
