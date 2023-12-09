#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_command(char *command) {
    // Implement your logic to execute a command here
    // For simplicity, let's print the command for demonstration
    printf("Executing: %s\n", command);
    system(command);
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
        close(pipefd[1]);  // Close the write end of the pipe in the child
        execute_command(command1);
        exit(EXIT_SUCCESS);
    } else {
        // Parent: execute the second command and read from pipe
        close(pipefd[1]);  // Close unused write end
        dup2(pipefd[0], STDIN_FILENO);  // Redirect stdin from pipe
        close(pipefd[0]);  // Close the read end of the pipe in the parent
        execute_command(command2);
        wait(NULL);  // Wait for the child process to complete
    }
}

int main() {
    char input[256];  // Adjust the buffer size as needed
    printf("Enter command with pipe (e.g., command1 | command2): ");
    fgets(input, sizeof(input), stdin);

    // Remove newline character from input
    if (input[strlen(input) - 1] == '\n') {
        input[strlen(input) - 1] = '\0';
    }

    handle_pipe(input);

    return 0;
}
