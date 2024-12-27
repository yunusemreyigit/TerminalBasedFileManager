#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "dllist.h"
#include "directory_ops.h"


void create_directory(char *dirName){
    int fd;
    fd = mkdir(dirName, 0644);
    if(fd < 0){
        perror("Could not created directory!");
    }else{
        printf("Directory created: %s\n", dirName);
    }
}
void delete_directory(char *dirName){
    int fd;
    fd = rmdir(dirName);
    if(fd < 0){
        perror("Could not delete directory!");
    }else{
        printf("Directory deleted: %s\n", dirName);
    }
}
void change_directory(char *dirName){
    int fd;

    fd = chdir(dirName);
     if(fd < 0){
        perror("Could not changed directory!");
    }  
}
char *get_current_directory(){
    char *currentDir = (char *)malloc(1024 * sizeof(char));

    if (getcwd(currentDir, 1024) != NULL) {
        return currentDir;
    } else {
        perror("get_current_directory is failed!");
    }

    free(currentDir);
    return currentDir;
}
// List directory contents
void list_directory(char *dirName) {
    struct stat buff;
    int exists;
    DIR *dir;
    struct dirent *entry;

    Dllist files, tmp;
    char *fn;
    char *s;
    char *lastSlash;

    dir = opendir(dirName);

    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    files = new_dllist();
    s = (char *) malloc(sizeof(char)*(strlen(fn)+258));

    while ((entry = readdir(dir)) != NULL) {
        fn = strdup(entry->d_name);
        sprintf(s, "%s/%s", dirName, entry->d_name);
        dll_append(files, new_jval_s(strdup(s)));
    }
    closedir(dir);

    dll_traverse(tmp, files) {
    exists = lstat(tmp->val.s, &buff);
    lastSlash = strrchr(tmp->val.s, '/');
    if (exists < 0) {
        fprintf(stderr, "%s not found\n", tmp->val.s);
    } else if (S_ISDIR(buff.st_mode)) {
        printf("%lu\t %o\t %d\t %ld\t %s/\n", buff.st_ino, buff.st_mode & 0777, buff.st_nlink, buff.st_size, lastSlash + 1);
    } else if (S_ISLNK(buff.st_mode)) {
        printf("%lu\t %o\t %d\t %ld\t %s@\n", buff.st_ino, buff.st_mode & 0777, buff.st_nlink, buff.st_size, lastSlash + 1);
    } else if (buff.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) {
        printf("%lu\t %o\t %d\t %ld\t %s*\n", buff.st_ino, buff.st_mode & 0777, buff.st_nlink, buff.st_size, lastSlash + 1);
    } else {
        printf("%lu\t %o\t %d\t %ld\t %s\n", buff.st_ino, buff.st_mode & 0777, buff.st_nlink, buff.st_size, lastSlash + 1);
    }
    free(tmp->val.s);
  }
    printf("-----\t ----\t ----\t ----\t ----\n");
    printf("INODE\t PERM\t LINK\t SIZE\t NAME\n");
    
    free(s);
    free_dllist(files);

}