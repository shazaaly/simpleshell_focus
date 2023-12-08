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

	while (1)
	{
		printf("> ");
		fgets(command, sizeof(command), stdin);
	}
	return (0);
}
