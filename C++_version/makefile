# Makefile for C++ project

# *****************************************************
# Variables to control Makefile operation

CC = g++
CFLAGS = -Wall -g
INCLUDES = -I./include  # Change this to your header files' directory

# ****************************************************
# Source file directory and files

SRCDIR = src
OBJDIR = obj

# List of source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# Generate a list of object files from the source files
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# The final executable name
EXECUTABLE = main

# ****************************************************
# Targets

# The default target is the final executable
all: $(EXECUTABLE)

# Rule to link the object files into the executable
$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Rule to compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create directories if they don't exist
$(shell mkdir -p $(SRCDIR) $(OBJDIR))

# Clean up intermediate object files and the executable
clean:
	rm -f $(OBJS) $(EXECUTABLE)
