CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
LDFLAGS = -lrt

SRC = src/*.c cli-lib/*.c main.c
OUT = build/pacman

all: $(OUT)

$(OUT):
	mkdir -p build
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(OUT)

clean:
	rm -rf build
