#ifndef PERMISSIONS_H
#define PERMISSIONS_H

#include <sys/types.h> // For mode_t

// Function prototype for changing permissions
void change_permissions(char *path, mode_t mode);

#endif // PERMISSIONS_H
