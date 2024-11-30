CC=gcc
CFLAGS=-Wall -Wextra -ggdb -std=c99 -pedantic
LIBS=-lclang
DEPS=export.h funcparse.h

all: main.o export.o funcparse.o $(DEPS)
	$(CC) $(CFLAGS) $(LIBS) $^ -o out

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o out

.PHONY: clean
