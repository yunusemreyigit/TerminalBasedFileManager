# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude -g  # -Iinclude adds the include directory to the search path

# Directories
SRCDIR = src
INCDIR = include

# Source and object files
SRC = $(SRCDIR)/main.c $(SRCDIR)/file_operations.c $(SRCDIR)/directory_ops.c $(SRCDIR)/permissions.c $(SRCDIR)/logger.c
OBJ = main.o file_operations.o directory_ops.o permissions.o logger.o
TARGET = file_manager

# Default rule
all: $(TARGET)

# Linking object files to create the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

# Rule to compile each source file into an object file
%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJ) $(TARGET)
