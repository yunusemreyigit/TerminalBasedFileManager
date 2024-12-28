# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
LIBDIR = lib

# Compiler and flags
CC = gcc
CFLAGS = -Wall -I$(INCDIR)
LIB = $(LIBDIR)/libfdr.a

# Source and object files
_SRC = main.c file_operations.c directory_ops.c permissions.c logger.c
SRC = $(patsubst %,$(SRCDIR)/%,$(_SRC))

_OBJ = main.o file_operations.o directory_ops.o permissions.o logger.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

TARGET = ./bin/file_manager

# Default rule
all: $(TARGET)
	mkdir -p log

# Linking object files to create the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIB)

# Rule to compile each source file into an object file
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJDIR)/*.o $(TARGET)