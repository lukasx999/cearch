CC=gcc
CFLAGS=-Wall -Wextra -ggdb -std=c99 -pedantic
DEPS=tokenizer.h parser.h

all: main.o tokenizer.o parser.o $(DEPS)
	$(CC) $(CFLAGS) $^ -o out

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o out

.PHONY: clean
