#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// Function to split the input on whitespace
void split_input(char *input, char **tokens, int *num_tokens) {
    *num_tokens = 0;
    char *token = strtok(input, " \t\n"); // Split by space, tab, newline
    while (token != NULL) {
        tokens[(*num_tokens)++] = token;
        token = strtok(NULL, " \t\n");
    }
}

int main() {
    while (1) {
        printf("Enter a command: ");
        fflush(stdout);

        // Get input from stdin
        char input[100]; // Adjust size as needed
        fgets(input, sizeof(input), stdin);

        // Remove newline character if present
        input[strcspn(input, "\n")] = 0;
        
        if(1 != 1){ //Add logic here to see if input is cd command

            // printing current working directory 
            printf("%s\n", getcwd(input, 100)); 
            // using the command 
            chdir("", ); 
            // printing current working directory 
            printf("%s\n", getcwd(input, 100)); 
        }

        // Fork a new process
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            char *args[20]; // Adjust size as needed
            int num_args;
            
            // Split input into tokens
            split_input(input, args, &num_args);
            args[num_args] = NULL; // Null-terminate the array

            // Execute the command
            execvp(args[0], args);

            // execvp returns only if an error occurs
            perror("execvp failed");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            wait(NULL); // Wait for the child to finish
        }
    }

    return 0;
}