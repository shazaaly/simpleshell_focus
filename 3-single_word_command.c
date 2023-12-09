
/*
1-prompt user
2- check if no space => single word command
3- remove new line char from command enterred
4- excute


*/
#include <stdio.h>   /*For input/output functions*/
#include <stdlib.h>  /* For general purpose functions */
#include <string.h>  /* For string handling functions */
#include <unistd.h>  /*For POSIX operating system API*/

int main(void)
{
    char command[100]; /* Array to store the command entered by the user */

    char *argv[2]; /*This declares an array of pointers to character strings.
    It will be used to pass the command and its arguments to the execve function. */

    char *envp[] = { NULL }; /*declares an array of pointers to environment variables.
    In this case, it's set to NULL,
    meaning no environment variables are passed to the execve function.*/

    int status; /*To store the status returned by execve */

    while (1) /* Infinite loop to keep the shell running */
    {
        printf("$ ");
        fgets(command, sizeof(command), stdin);

        command[strcspn(command, "\n")] = 0; /* Remove the newline character from the end of the command*/

        // Check if it's a single-word command
        if (strchr(command, ' ') == NULL)
        {
            argv[0] = command; // The first argument is the command itself
            argv[1] = NULL; // The argument list must be NULL-terminated

            // Execute the command
            status = execve(command, argv, envp);
            // status = execvp(argv[0], argv);
            if (status == -1) // If execve returns, there was an error
            {
                perror(command); // print a descriptive error message to the standard error stream.
            }
        }
        else
        {
            printf("%s: not a single-word command\n", command); // Print an error message if the command is not a single word
        }
    }

    return (0); // This will never be reached because of the infinite loop
}