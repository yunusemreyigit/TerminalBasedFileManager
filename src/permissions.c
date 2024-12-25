#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "permissions.h"

void change_permissions(char *path, mode_t mode) {
    if (chmod(path, mode) == 0) {
        printf("Permissions of '%s' changed successfully to '%o'.\n", path, mode);
    } else {
        perror("Error changing permissions");
    }
}
