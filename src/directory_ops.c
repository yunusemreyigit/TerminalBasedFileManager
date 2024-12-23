#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "directory_ops.h"

// Create a directory
void dcreate(char *dirName) {
    if (mkdir(dirName, 0755) == 0) {
        printf("Directory '%s' created successfully.\n", dirName);
    } else {
        perror("Error creating directory");
    }
}

// Delete a directory
void ddelete(char *dirName) {
    if (rmdir(dirName) == 0) {
        printf("Directory '%s' deleted successfully.\n", dirName);
    } else {
        perror("Error deleting directory");
    }
}

// List directory contents
void dlist(char *dirName) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(dirName);
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    printf("Contents of '%s':\n", dirName);
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}
