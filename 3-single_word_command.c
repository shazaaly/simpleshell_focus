#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	char command[100];

	char *argv[2];

	char *envp[] = { NULL };

	int status;

	while (1)
	{
		printf("> ");
		fgets(command, sizeof(command), stdin);

		command[strcspn(command, "\n")] = 0;

		/* Check if it's a single-word command*/
		if (strchr(command, ' ') == NULL)
		{
			argv[0] = command;
			argv[1] = NULL;

			/*Execute the command */
			status = execve(command, argv, envp);
			if (status == -1)
			{
				perror(command);
			}
		}
		else
		{
			printf("%s: not a single-word command\n", command);
		}
	}
	return (0);
}
