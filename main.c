#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>

#include "./tokenizer.h"




// Caller is responsible for calling free()
char* read_file(const char *filename) {

    FILE *file = fopen(filename, "r");
    struct stat stat_buf = { 0 };

    stat(filename, &stat_buf);
    size_t file_size = stat_buf.st_size;

    char *mem = calloc(file_size + 1, sizeof(char)); // NOTE: +1 for nullbyte
    size_t mem_index = 0;

    char c = '\0';
    while ((c = fgetc(file)) != EOF) {
        mem[mem_index++] = c;
    }

    fclose(file);
    return mem;

}



int main(int argc, char **argv) {

    #if 0
    if (argc < 2 || argc > 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(1);
    }

    const char *filename = argv[1];
    #endif

    const char *filename = "example.h";

    char *file = read_file(filename);



    Tokens tokens = tokenize(file);



    for (size_t i=0; true; ++i) {
        Token token = tokens.items[i];

        if (!strlen(token.value)) {
            printf("%s\n", token_kind_repr[token.kind]);
        }
        else {
            printf("%s '%s'\n", token_kind_repr[token.kind], token.value);
        }

        if (token.kind == TOK_EOF) {
            break;
        }
    }


    free(file);







    return EXIT_SUCCESS;

}
