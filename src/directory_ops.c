#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include "directory_ops.h"

// Global pointer to keep the currently opened directory
static DIR *current_dir = NULL;

void opendir_command(char *dirName) {
    if (current_dir != NULL) {
        closedir(current_dir);
    }

    current_dir = opendir(dirName);
    if (current_dir == NULL) {
        perror("Error opening directory");
        return;
    }

    printf("Directory '%s' opened successfully.\n", dirName);
}

void readdir_command() {
    if (current_dir == NULL) {
        printf("No directory is currently opened. Use 'opendir' first.\n");
        return;
    }

    struct dirent *entry;
    printf("Reading contents of the opened directory:\n");
    while ((entry = readdir(current_dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            printf("%s\n", entry->d_name);
        }
    }

    // Reset the directory pointer for re-reading or closing later
    rewinddir(current_dir);
}

void rmdir_command(char *dirName) {
    if (rmdir(dirName) == 0) {
        printf("Directory '%s' deleted successfully.\n", dirName);
    } else {
        perror("Error deleting directory");
    }
}

void closedir_command() {
    if (current_dir != NULL) {
        closedir(current_dir);
        current_dir = NULL;
        printf("Current directory closed successfully.\n");
    } else {
        printf("No directory is currently open.\n");
    }
}
