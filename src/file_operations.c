#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "file_operations.h"

// Create a new file
void fcreate(char *fileName) {
    int fd = creat(fileName, 0644);
    if (fd < 0) {
        perror("Error creating file");
    } else {
        printf("File '%s' created successfully.\n", fileName);
        close(fd);
    }
}

// Delete a file
void fdelete(char *fileName) {
    if (unlink(fileName) == 0) {
        printf("File '%s' deleted successfully.\n", fileName);
    } else {
        perror("Error deleting file");
    }
}

// Copy a file
void fcopy(char *srcFile, char *destFile) {
    int srcFd, destFd, bytesRead;
    char buffer[1024];

    srcFd = open(srcFile, O_RDONLY);
    if (srcFd < 0) {
        perror("Error opening source file");
        return;
    }

    destFd = open(destFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destFd < 0) {
        perror("Error opening destination file");
        close(srcFd);
        return;
    }

    while ((bytesRead = read(srcFd, buffer, sizeof(buffer))) > 0) {
        if (write(destFd, buffer, bytesRead) == -1) {
            perror("Error writing to destination file");
            break;
        }
    }

    if (bytesRead < 0)
        perror("Error reading from source file");

    close(srcFd);
    close(destFd);
}

//Writes content of desired file
void see(char *fileName){
    int bufferSize = 1024;
    char *buffer;
    int fd;

    buffer = (char *)malloc(bufferSize*sizeof(char));

    fd = open(fileName, O_RDONLY);
    if(fd < 0){
        perror("File could not open");
        return;
    }
    
    while((bufferSize = read(fd, buffer, bufferSize)) > 0){
        if(write(1, buffer, bufferSize) < 0){
            perror("File could not shown");
            break;
        }
    }
    close(fd);
}