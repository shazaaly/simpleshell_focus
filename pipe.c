#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/*

*/

void execute_command(char *command) {
    char *args[10];  // Assuming a maximum of 10 arguments
    char *token = strtok(command, " ");
    int i = 0;
    while (token != NULL && i < 10) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;  // Set the last element to NULL for execvp

    execvp(args[0], args);
    perror("execvp");
    exit(EXIT_FAILURE);
}

void handle_pipe(char *input) {
    char *command1 = strtok(input, "|");
    char *command2 = strtok(NULL, "|");

    if (command2 == NULL) {
        // No pipe in input, just execute the command
        execute_command(command1);
        return;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child: execute the first command and write to pipe
        close(pipefd[0]);  // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO);  // Redirect stdout to pipe
        execute_command(command1);
    } else {
        // Parent: execute the second command and read from pipe
        close(pipefd[1]);  // Close unused write end
        dup2(pipefd[0], STDIN_FILENO);  // Redirect stdin from pipe
        execute_command(command2);
    }
}