#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;  // This is needed to access the environment variables

int main(void)
{
    char command[100];

    while(1) {
        printf("> ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("Error reading command\n");
            continue;
        }

        // Remove newline character
        command[strcspn(command, "\n")] = '\0';

        // Tokenize the command using strtok
        char *token = strtok(command, " ");
        char *args[10];  // Assuming a maximum of 10 arguments

        int i = 0;
        while (token != NULL && i < 10) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }

        args[i] = NULL;  // Set the last element to NULL for execvp

        // Check if the command is "env"
        if (strcmp(args[0], "env") == 0) {
            // Print the environment variables
            for (char **env = environ; *env != NULL; env++) {
                printf("%s\n", *env);
            }
            continue;
        }
    }

    return 0;
}