# Compiler and flags
CC = gcc

# Source files
SOURCES = tennis_sender.c tennis_reciever.c signal_alarm.c signal_segfault.c \
          send_signal.c recv_signal.c signal_handler.c signal_sigaction.c

# Object files (replace .c with .o in the source filenames)
OBJECTS = $(SOURCES:.c=.o)

# Executable names (replace .c with empty string in the source filenames)
EXECUTABLES = $(SOURCES:.c=)

# Default target: build all executables
all: $(EXECUTABLES)

# Pattern rule to build each executable
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Clean target to remove generated files
clean:
	rm -f $(EXECUTABLES) $(OBJECTS)

# Phony targets to prevent conflicts with file names
.PHONY: all clean
