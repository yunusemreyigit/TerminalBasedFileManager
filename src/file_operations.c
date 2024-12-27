#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "file_operations.h"

void creat_command(char *fileName) {
    int fd = creat(fileName, 0644);
    if (fd < 0) {
        perror("Error creating file");
    } else {
        printf("File '%s' created successfully.\n", fileName);
        close(fd);
    }
}

void unlink_command(char *fileName) {
    if (unlink(fileName) == 0) {
        printf("File '%s' deleted successfully.\n", fileName);
    } else {
        perror("Error deleting file");
    }
}

void stat_command(char *fileName) {
    struct stat fileStat;
    if (stat(fileName, &fileStat) < 0) {
        perror("Error getting file information");
        return;
    }

    // convert st_mtime to readable format
    struct tm *tm_info = localtime(&fileStat.st_mtime);
    char timeString[100];
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", tm_info);

    printf("File: %s\n", fileName);
    printf("Size: %ld bytes\n", fileStat.st_size);
    printf("Permissions: %o\n", fileStat.st_mode & 0777);
    printf("Last modified: %s\n", timeString);
}

void open_command(char *fileName) {
    int fd = open(fileName, O_RDWR);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }

    char buffer[1024];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }

    buffer[bytesRead] = '\0';
    printf("File content:\n%s\n", buffer);

    const char *newContent = "Appending new data to file.\n";
    if (write(fd, newContent, strlen(newContent)) < 0) {
        perror("Error writing to file");
    } else {
        printf("Data written to file successfully.\n");
    }

    close(fd);
}

void read_command(char *fileName) {
    int fd = open(fileName, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file for reading");
        return;
    }

    char buffer[2048];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }

    buffer[bytesRead] = '\0';
    printf("%s\n", buffer);

    close(fd);
}

void write_command(char *fileName, char *data) {
    int fd = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Error opening file for writing");
        return;
    }

    if (write(fd, data, strlen(data)) < 0) {
        perror("Error writing to file");
    } else {
        printf("Data written to file successfully.\n");
    }

    close(fd);
}

void rename_command(char *oldName, char *newName) {
    if (rename(oldName, newName) == 0) {
        printf("Renamed '%s' to '%s' successfully.\n", oldName, newName);
    } else {
        perror("Error renaming file or directory");
    }
}
