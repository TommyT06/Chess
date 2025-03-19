# Compiler
CC = gcc

# Use pkg-config to get SDL3 and SDL3-image flags for compilation and linking
CFLAGS = -Wall -Wextra $(shell pkg-config --cflags sdl3 sdl3-image)
LIBS = $(shell pkg-config --libs sdl3 sdl3-image)

# Target executable name
TARGET = chess

# Source files
SOURCES = main.c moves.c checkmate.c king.c scoring.c search_tree.c

# Automatically generate object files list
OBJECTS = $(SOURCES:.c=.o)

# Default target: build the executable
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LIBS)

# Compile each .c file into a .o file using CFLAGS
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(TARGET) $(OBJECTS)
all:
	./chess