#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "logger.h"

char * logDir;


void set_log_directory(char *appDir){
    if(logDir == NULL){
    logDir = (char *)malloc(strlen(appDir) + 22);
    logDir[0] = '\0';
    }

    strcat(logDir, appDir);
    strcat(logDir, "/log/file_manager.log");
}
void log_action(char *operation, char *result) {
    if(logDir == NULL){
        printf("Please first call set_log_directory method.");
    }
    int logFd = open(logDir, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (logFd < 0) {
        perror("Error opening log file");
        return;
    }

    time_t now = time(NULL);
    char *timestamp = ctime(&now);
    timestamp[strlen(timestamp) - 1] = '\0';

    char logEntry[256];
    snprintf(logEntry, sizeof(logEntry), "[%s] Operation: %s, Result: %s\n", timestamp, operation, result);

    if (write(logFd, logEntry, strlen(logEntry)) < 0) {
        perror("Error writing to log file");
    }

    close(logFd);
}
