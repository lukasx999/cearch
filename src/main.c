#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>

#include <clang-c/Index.h>

#include "./export.h"


#define INPUT_BUFSIZE 100



void check_usage(int argc, char *argv[]) {

    if (argc < 2 || argc > 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

}


typedef struct {
    Functions *funcs;
    // temporary values - do not read:
    Parameter *params;
    size_t params_index;
} RecState;



enum CXChildVisitResult visit(
    CXCursor cursor,
    CXCursor parent,
    CXClientData client_data
) {

    RecState *state = (RecState*) client_data;

    enum CXCursorKind kind   = clang_getCursorKind(cursor);
    CXType type              = clang_getCursorType(cursor);

    switch (kind) {

        case CXCursor_FunctionDecl: {

            CXType      func_returntype = clang_getResultType(type);
            CXString    func_name       = clang_Cursor_getMangling(cursor);
            const char *func_name_cstr  = clang_getCString(func_name);

            int param_count     = clang_getNumArgTypes(type);
            Parameter *params   = calloc(param_count, sizeof(Parameter));
            state->params       = params;
            state->params_index = 0;

            Function func = {
                .returntype  = func_returntype,
                .identifier  = { 0 },
                .parameters  = params,
                .param_count = (size_t) param_count,
            };

            strncpy(func.identifier, func_name_cstr, IDENTIFIER_BUFSIZE-1);

            functions_append(state->funcs, func);
            clang_disposeString(func_name);

            return CXChildVisit_Recurse;

        } break;

        case CXCursor_ParmDecl: {
            CXType      param_type      = type;
            CXString    param_name      = clang_Cursor_getMangling(cursor);
            const char *param_name_cstr = clang_getCString(param_name);

            Parameter param = {
                .identifier = { 0 },
                .type = param_type,
            };

            strncpy(param.identifier, param_name_cstr, IDENTIFIER_BUFSIZE-1);
            clang_disposeString(param_name);
            state->params[state->params_index++] = param;

        } break;

        default: {} break;

    }

    return CXChildVisit_Continue;

}




CXCursor parse_translationunit(const char *filename) {

    CXIndex index = clang_createIndex(0, 0);

    CXTranslationUnit unit = clang_parseTranslationUnit(
        index,
        filename,
        NULL,
        0,
        NULL,
        0,
        CXTranslationUnit_None
    );

    if (unit == NULL) {
        fprintf(stderr, "Failed to parse translation unit\n");
        exit(EXIT_FAILURE);
    }

    CXCursor cursor = clang_getTranslationUnitCursor(unit);
    return cursor;

}



int main(int argc, char *argv[]) {

    // check_usage(argc, argv);
    // const char *filename = argv[1];

    const char *filename = "example.h";

    CXCursor cursor = parse_translationunit(filename);


    Functions funcs = functions_new();

    RecState state = {
        .funcs        = &funcs,
        .params       = NULL,
        .params_index = 0,
    };

    clang_visitChildren(cursor, visit, &state);

    functions_print(&funcs);


    // (int, char, bool) -> int
    char buf[INPUT_BUFSIZE] = { 0 };
    fgets(buf, INPUT_BUFSIZE, stdin);
    buf[strcspn(buf, "\n")] = '\0';

    const char *types[] = { "int", "char", "bool" };

    puts(buf);




    functions_destroy(&funcs);





    return EXIT_SUCCESS;

}
