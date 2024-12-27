#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "file_operations.h"
#include "directory_ops.h"
#include "permissions.h"
#include "jrb.h"

void print_help() {
    printf("Available commands:\n");
    printf("  creat <filename> - Create a file\n");
    printf("  remove <filename> - Delete a file\n");
    // printf("  opendir <dirname> - Open a directory\n");
    // printf("  readdir - Read contents of the currently opened directory\n");
    // printf("  closedir - Close the currently opened directory\n");
    // printf("  rmdir <dirname> - Delete a directory\n");
    printf("  chmod <path> <mode> - Change permissions\n");
    printf("  stat <filename> - Get file information\n");
    printf("  open <filename> - Open and edit a file\n");
    printf("  read <filename> - Read data from a file\n");
    printf("  write <filename> <data> - Write data to a file\n");
    printf("  rename <oldname> <newname> - Rename a file or folder\n");
    printf("  exit - Exit the program\n");
}

int main() {

    char command[256], arg1[128], arg2[128], arg3[1024];
    mode_t mode;

    print_help();

    while (1) {
        printf("%s > ", get_current_directory());
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;

        if (sscanf(command, "creat %s", arg1) == 1) {
            creat_command(arg1);
        } else if (sscanf(command, "remove %s", arg1) == 1) {
            unlink_command(arg1);
        } else if (strcmp(command, "list") == 0) {
            list_directory(".");
        } else if (sscanf(command, "list %s", arg1) == 1) { 
            list_directory(arg1);
        } else if (sscanf(command, "ddelete %s", arg1) == 1) { 
            delete_directory(arg1);
        } else if (sscanf(command, "dcreate %s", arg1) == 1) { 
            create_directory(arg1);
        } else if (sscanf(command, "go %s", arg1) == 1) { 
            change_directory(arg1);
        } else if (sscanf(command, "chmod %s %o", arg1, &mode) == 2) {
            change_permissions(arg1, mode);
        } else if (sscanf(command, "stat %s", arg1) == 1) {
            stat_command(arg1);
        } else if (sscanf(command, "open %s", arg1) == 1) {
            open_command(arg1);
        } else if (sscanf(command, "read %s", arg1) == 1) {
            read_command(arg1);
        } else if (sscanf(command, "write %s %[^\n]", arg1, arg3) == 2) {
            write_command(arg1, arg3);
        } else if (sscanf(command, "rename %s %s", arg1, arg2) == 2) {
            rename_command(arg1, arg2);
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Unknown command. Type 'help' for available commands.\n");
        }
    }

    return 0;
}
