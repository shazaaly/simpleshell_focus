#include <stdio.h>
#include <stdlib.h>

/**
 * main - Entry point for the command-line interface.
 *
 * This program  prompts the user
 * for commands and executes them.
 *
 * Return: Always 0 (success).
 */
int main(void)
{
	char command[100];

	while (1) /* infinite loop */
	{
		printf("> ");
		fgets(command, sizeof(command), stdin);
	}
	return (0);
}
/* Note
In general, getline can be safer than fgets
because it allocates enough memory to hold the line,
getline version dynamically allocates a buffer that's
large enough to hold the input line.
 while with fgets you have to ensure your buffer
 is large enough ahead of time. However, getline is a GNU extension and is not part of the standard C library,
so it may not be available on all platforms.

*/