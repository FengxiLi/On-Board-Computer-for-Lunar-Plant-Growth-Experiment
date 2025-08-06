# Makefile for PG project

CC      := gcc
CFLAGS  := -Wall -O2
LDLIBS  := -lgpiod

SRCS    := main.c geiger_counter.c ms8607.c scd41.c
OBJS    := $(SRCS:.c=.o)
TARGET  := PG

.PHONY: all clean run

# Default target: build the program
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

# Compile .c files to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Remove build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Build (if necessary) and run the program
run: $(TARGET)
	@echo "Starting PG..."
	@sudo ./$(TARGET)
