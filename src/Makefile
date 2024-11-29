CC=gcc
CFLAGS=-Wall -Wextra -ggdb -std=c99 -pedantic
LIBS=-lclang

all: main.o
	$(CC) $(CFLAGS) $(LIBS) $^ -o out

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o out

.PHONY: clean
