#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char input[] = "token1,token2,token3";
    char *token;

    // Duplicate the input string using strdup
    char *copy = strdup(input);

    if (copy == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 1;
    }

    // Use strtok on the copy
    token = strtok(copy, ",");

    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, ",");
    }

    // Free the dynamically allocated copy
    free(copy);

    return 0;
}
