#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "logger.h"

void log_action(char *operation, char *result) {
    int logFd = open("file_manager.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
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
