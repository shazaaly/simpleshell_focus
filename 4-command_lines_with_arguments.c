#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char command[100];

    while(1) {
        printf("> ");
        fgets(command, sizeof(command), stdin);

        // Remove newline character
        command[strcspn(command, "\n")] = '\0';

        // Tokenize the command using strtok
        char *token = strtok(command, " "); /*  This line uses the strtok function to split the command string into tokens (words) separated by spaces. The function returns a pointer to the first token. */
        char *args[10];  // Assuming a maximum of 10 arguments

        int i = 0;
        while (token != NULL && i < 10) {
            args[i++] = token;
            token = strtok(NULL, " "); /* This line gets the next token. When strtok is called with NULL as the first argument, it continues tokenizing the same string from where it left off. On the second iteration of the loop, this will return "la". */
        }

        args[i] = NULL;  // Set the last element to NULL for execvp

        // Fork a child process
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // In the child process, execute the command
            execvp(args[0], args);

            // If execvp fails
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            // In the parent process, wait for the child to complete
            waitpid(pid, NULL, 0);
        }
    }

    return 0;
}
/* So, after this code is executed,
the args array contains the tokens from the command string:
args[0] is "ls", args[1] is "la", and args[2] is NULL. */