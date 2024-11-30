CC=gcc
CFLAGS=-Wall -Wextra -ggdb -std=c99 -pedantic
LIBS=-lclang -lreadline
DEPS=export.h funcparse.h query_parser.h

all: main.o export.o funcparse.o query_parser.o $(DEPS)
	$(CC) $(CFLAGS) $(LIBS) $^ -o out

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o out

.PHONY: clean
