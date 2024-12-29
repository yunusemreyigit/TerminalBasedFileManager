# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
LIBDIR = lib
LOGDIR = log
BINDIR = bin

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
	mkdir -p $(LOGDIR)

# Linking object files to create the executable
$(TARGET): $(OBJ)
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIB)

# Rule to compile each source file into an object file
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJDIR)/*.o $(TARGET)
	rm -f log/file_manager.log