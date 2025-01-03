#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "file_operations.h"
#include "directory_ops.h"
#include "permissions.h"
#include "logger.h"



void print_help(char *helpDir) {
    read_command(helpDir);
}

int main() {
    // set static files directories 
    char * appDir = get_current_directory();
    char * helpDir = (char *)malloc(strlen(appDir) + 10);
    char * bannerDir = (char *)malloc(strlen(appDir) + 12);

    helpDir[0] = '\0';
    bannerDir[0] = '\0';

    strcat(helpDir, appDir);
    strcat(helpDir, "/txt/help");
    strcat(bannerDir, appDir);
    strcat(bannerDir, "/txt/banner");    
    //

    char command[256], arg1[128], arg2[128], arg3[1024];
    mode_t mode;

    set_log_directory(appDir);

    read_command(bannerDir);
    print_help(helpDir);

    while (1) {
        printf("%s > ", appDir);
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;

        if (sscanf(command, "fcreate %s", arg1) == 1) {
            creat_command(arg1);
            log_action(command,"SUCCESS");
        } else if (sscanf(command, "fdelete %s", arg1) == 1) {
            unlink_command(arg1);
        } else if (strcmp(command, "dlist") == 0) {
            list_directory(".");
            log_action(command,"SUCCESS");
        } else if (sscanf(command, "dlist %s", arg1) == 1) { 
            list_directory(arg1);
            log_action(command,"SUCCESS");
        } else if (sscanf(command, "ddelete %s", arg1) == 1) { 
            delete_directory(arg1);
            log_action(command,"SUCCESS");
        } else if (sscanf(command, "dcreate %s", arg1) == 1) { 
            create_directory(arg1);
            log_action(command,"SUCCESS");
        } else if (sscanf(command, "go %s", arg1) == 1) { 
            change_directory(arg1);
            appDir = get_current_directory();
            log_action(command,"SUCCESS");
        } else if (sscanf(command, "chmod %s %o", arg1, &mode) == 2) {
            change_permissions(arg1, mode);
            log_action(command,"SUCCESS");
        } else if (sscanf(command, "stat %s", arg1) == 1) {
            stat_command(arg1);
            log_action(command,"SUCCESS");
        } else if (sscanf(command, "open %s", arg1) == 1) {
            open_command(arg1);
            log_action(command,"SUCCESS");
        } else if (sscanf(command, "fread %s", arg1) == 1) {
            read_command(arg1);
            log_action(command,"SUCCESS");
        } else if (sscanf(command, "fwrite %s %[^\n]", arg1, arg3) == 2) {
            write_command(arg1, arg3);
            log_action(command,"SUCCESS");
        } else if (sscanf(command, "rename %s %s", arg1, arg2) == 2) {
            rename_command(arg1, arg2);
            log_action(command,"SUCCESS");
        } else if (sscanf(command, "fcopy %s %s", arg1, arg2) == 2) {
            copy_command(arg1, arg2);
            log_action(command,"SUCCESS");
        } else if (sscanf(command, "move %s %s", arg1, arg2) == 2) {
            move_command(arg1, arg2);
            log_action(command,"SUCCESS");
        } else if (strcmp(command, "help") == 0) {
            print_help(helpDir);
            log_action(command,"SUCCESS");
        } else if (strcmp(command, "exit") == 0) {
            free(appDir);
            free(helpDir);
            break;
        } else {
            printf("Unknown command. Type 'help' for available commands.\n");
            log_action(command,"FAILED");
        }
    }

    return 0;
}
