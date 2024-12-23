#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_operations.h"
#include "directory_ops.h"
#include "permissions.h"
#include "logger.h"

void print_help() {
    printf("Available commands:\n");
    printf("  fcreate <filename> - Create a file\n");
    printf("  fdelete <filename> - Delete a file\n");
    printf("  fcopy <source> <destination> - Copy a file\n");
    printf("  dcreate <dirname> - Create a directory\n");
    printf("  ddelete <dirname> - Delete a directory\n");
    printf("  dlist <dirname> - List contents of a directory\n");
    printf("  chmod <path> <mode> - Change permissions\n");
    printf("  help - Show this help message\n");
    printf("  exit - Exit the program\n");
}

int main() {
    char command[256];
    char arg1[128], arg2[128];
    mode_t mode;

    print_help();

    while (1) {
        printf("> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // Remove newline

        if (sscanf(command, "fcreate %s", arg1) == 1) {
            fcreate(arg1);
            log_action("fcreate", "Success");
        } else if (sscanf(command, "fdelete %s", arg1) == 1) {
            fdelete(arg1);
            log_action("fdelete", "Success");
        } else if (sscanf(command, "fcopy %s %s", arg1, arg2) == 2) {
            fcopy(arg1, arg2);
            log_action("fcopy", "Success");
        } else if (sscanf(command, "dcreate %s", arg1) == 1) {
            dcreate(arg1);
            log_action("dcreate", "Success");
        } else if (sscanf(command, "ddelete %s", arg1) == 1) {
            ddelete(arg1);
            log_action("ddelete", "Success");
        } else if (sscanf(command, "dlist %s", arg1) == 1) {
            dlist(arg1);
            log_action("dlist", "Success");
        } else if (sscanf(command, "chmod %s %o", arg1, &mode) == 2) {
            change_permissions(arg1, mode);
            log_action("chmod", "Success");
        } else if (strcmp(command, "help") == 0) {
            print_help();
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Unknown command. Type 'help' for a list of commands.\n");
        }
    }

    return 0;
}
