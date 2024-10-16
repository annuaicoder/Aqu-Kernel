// ListDirectory.c
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "ListDirectory.h" // Include the header file for function declaration

// Function to list directories in the current working directory
void list_directories() {
    DIR *dir;
    struct dirent *entry;

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to read the directory");
        return;
    }

    // Print all directory entries
    printf("Directories:\n");
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            printf("  %s\n", entry->d_name);
        }
    }

    // Close the directory
    closedir(dir);
}
