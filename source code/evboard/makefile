# Makefile for TLE92466ED Raspberry Pi Project

CC = gcc
CFLAGS = -Wall -O2
LDFLAGS = -lgpiod
SRC = main.c gpio_ctrl.c spi_ctrl.c TLE92464_CommLayer.c TLE92464_RegLayer.c
OBJ = $(SRC:.c=.o)
TARGET = tle92466_test

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

run: all
	sudo ./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
