#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <file_operations.h>

void fcreate(char *fileName){
    int fd;
    fd = open(fileName, O_CREAT, 0644);
    
    if(fd < 0)
        perror("File could not be created!");
}