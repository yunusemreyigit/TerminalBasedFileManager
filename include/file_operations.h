#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H


void creat_command(char *fileName);    
void unlink_command(char *fileName);    
void stat_command(char *fileName);     
void open_command(char *fileName);        
void read_command(char *fileName);         
void write_command(char *fileName, char *data); 
void rename_command(char *oldName, char *newName); 

#endif // FILE_OPERATIONS_H
