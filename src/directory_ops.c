#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "directory_ops.h"
#include "jrb.h"


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
    struct stat buff;
    int exists;
    DIR *dir;
    struct dirent *entry;

    JRB files, tmp;
    int maxlen;
    char *fn;

    dir = opendir(dirName);

    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    maxlen = 0;
    files = make_jrb();

    while ((entry = readdir(dir)) != NULL) {
        fn = strdup(entry->d_name);
        jrb_insert_str(files, fn, new_jval_i(0));
        if(strlen(entry->d_name) > maxlen) maxlen = strlen(entry->d_name);
    }
    closedir(dir);

    jrb_traverse(tmp, files) {
    exists = lstat(tmp->key.s, &buff);
    if (exists < 0) {
        fprintf(stderr, "%s not found\n", tmp->key.s);
    } else if (S_ISDIR(buff.st_mode)) {
        // printf("%*s/ %10lld\n", -maxlen,tmp->key.s, buff.st_size);
        printf("%lu\t %hu\t %10lld\t %s/\n", buff.st_ino, buff.st_mode, buff.st_size, tmp->key.s);

    } else if (S_ISLNK(buff.st_mode)) {
        printf("%lu\t %hu\t %10lld\t %s@\n", buff.st_ino, buff.st_mode, buff.st_size, tmp->key.s);
        // printf("%*s@ %10lld\n", -maxlen,tmp->key.s, buff.st_size);
    } else if (buff.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) {
        printf("%lu\t %hu\t %10lld\t %s*\n", buff.st_ino, buff.st_mode, buff.st_size, tmp->key.s);
        // printf("%*s* %10lld\n", -maxlen,tmp->key.s, buff.st_size);
    } else {
        printf("%lu\t %hu\t %10lld\t %s\n", buff.st_ino, buff.st_mode, buff.st_size, tmp->key.s);
        // printf("%*s  %10lld\n", -maxlen,tmp->key.s, buff.st_size);
    }
  }
}