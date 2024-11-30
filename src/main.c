#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>

#include <clang-c/Index.h>

#include "./export.h"
#include "./funcparse.h"


#define INPUT_BUFSIZE 100



void check_usage(int argc, char *argv[]) {
    if (argc < 2 || argc > 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}






// TODO: Export list of functions
// TODO: Get list of functions for fuzzy-finding with fzf


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

    functions_print(&funcs);

    #if 0
    char **function_list = export_function_names(&funcs);

    FILE *f = fopen("functions.export", "w");

    for (size_t i=0; i < funcs.size; ++i) {
        printf("func: %s\n", function_list[i]);
        fprintf(f, "%s\n", function_list[i]);
    }

    fclose(f);
    #endif





    // (int, char, bool) -> int
    char buf[INPUT_BUFSIZE] = { 0 };
    // fgets(buf, INPUT_BUFSIZE, stdin);
    buf[strcspn(buf, "\n")] = '\0';

    const char *types[] = { "int", "char", "bool" };

    puts(buf);




    functions_destroy(&funcs);





    return EXIT_SUCCESS;

}
