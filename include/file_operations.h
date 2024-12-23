#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

// Function prototypes for file operations

// Create a new file
void fcreate(char *fileName);

// Delete a file
void fdelete(char *fileName);

// Copy a file
void fcopy(char *srcFile, char *destFile);

#endif // FILE_OPERATIONS_H
