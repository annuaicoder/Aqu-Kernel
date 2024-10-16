#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Commands/commands.h" // Include the header file for commands

int main() {
    // Print the welcome message
    printf("Welcome to Aqu Kernel:\n");
    printf("Here's how to get started:\n");
    printf("Please Type aq docs to see docs. The docs will show you how to get started.\n");

    // Keep the program running to simulate a shell
    while (1) {
        // Print the prompt
        printf("Aqu> ");

        // Read the user input (command)
        char command[256];
        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("Error reading input.\n");
            continue;
        }

        // Remove newline character from the command
        command[strcspn(command, "\n")] = 0;

        // Exit if the user types "exit"
        if (strcmp(command, "exit") == 0) {
            printf("Exiting Aqu Kernel.\n");
            break;
        }

        // Show docs if the user types "aq docs"
        if (strcmp(command, "aq docs") == 0) {
            show_docs();
        } else {
            // For other commands, just echo back what was typed
            printf("You typed: %s\n", command);
        }
    }

    return 0;
}
