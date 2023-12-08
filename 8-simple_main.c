#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void executeInteractive() {
    char input[256];  // Adjust the buffer size as needed
    printf("Simple Shell > ");
    fgets(input, sizeof(input), stdin);
    // Remove newline character from input
    if (input[strlen(input) - 1] == '\n') {
        input[strlen(input) - 1] = '\0';
    }
    // Add your logic to execute the command in interactive mode
    // For example: executeCommand(input);
}

void executeNonInteractive() {
    char input[256];  // Adjust the buffer size as needed
    while (fgets(input, sizeof(input), stdin) != NULL) {
        // Remove newline character from input
        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }
        // Add your logic to execute the command in non-interactive mode
        // For example: executeCommand(input);
    }
}

int main(int argc, char *argv[]) {
    if (isatty(STDIN_FILENO)) {
        // Interactive mode
        executeInteractive();
    } else {
        // Non-interactive mode (e.g., reading from a file or pipe)
        executeNonInteractive();
    }

    return 0;
}
