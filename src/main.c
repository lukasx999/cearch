#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>

#include <readline/readline.h>
#include <clang-c/Index.h>

#include "./export.h"
#include "./funcparse.h"
#include "./query_parser.h"


#define INPUT_BUFSIZE 100



void check_usage(int argc, char *argv[]) {
    if (argc < 2 || argc > 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}








// Roadmap
// [] query types
// [] Type Qualifiers (const, restrict, volatile)
// [] Pointers
// [] Elaborate Types (typedefs)
// [] case-insensitive matching
// [] Wildcards (+, #)
// [] Parameter identifiers


int main(int argc, char *argv[]) {

    // check_usage(argc, argv);
    // const char *filename = argv[1];

    const char *filename = "example.h";

    Functions funcs = { 0 };
    int err = parse_translationunit(&funcs, filename);

    if (err != 0) {
        fprintf(stderr, "Failed to parse Translation Unit\n");
        exit(1);
    }

    // functions_print(&funcs);


    // Example Query
    // void -> void
    // void -> int
    // int, char, bool -> +
    // int, +, bool -> int (matches exactly one type)
    // int, char, # -> int (matches any number of types)
    // int, #, char -> int
    const char *query = readline("(query) ");

    FunctionQuery func_query = { 0 };

    err = parse_query(&func_query, query);
    if (err != 0) {
        fprintf(stderr, "Invalid Query: %s\n", query);
        exit(1);
    }



    functions_destroy(&funcs);





    return EXIT_SUCCESS;

}
