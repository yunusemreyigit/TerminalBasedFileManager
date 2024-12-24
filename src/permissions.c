#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>   // For chmod and mode_t
#include "permissions.h"

// Change file or directory permissions
void change_permissions(char *path, mode_t mode) {
    if (chmod(path, mode) == 0) {
        printf("Permissions of '%s' changed successfully to '%o'.\n", path, mode);
    } else {
        perror("Error changing permissions");
    }
}
