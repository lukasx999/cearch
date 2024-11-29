#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>

#include <clang-c/Index.h>





void check_usage(int argc, char *argv[]) {

    if (argc < 2 || argc > 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

}




enum CXChildVisitResult visit(
    CXCursor cursor,
    CXCursor parent,
    CXClientData client_data
) {


    CXType type = clang_getCursorType(cursor);



    /*
    enum CXCursorKind kind = clang_getCursorKind(cursor);
    switch (kind) {
        case CXCursor_FunctionDecl: {
        } break;

        case CXCursor_ParmDecl: {
        } break;
    }
    */


    CXString str = clang_getCursorDisplayName(cursor);

    const char *c_str = clang_getCString(str);
    printf("%s\n", c_str);

    clang_disposeString(str);

    return CXChildVisit_Recurse;

}



int main(int argc, char *argv[]) {

    // check_usage(argc, argv);
    // const char *filename = argv[1];

    const char *filename = "example.h";

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

    clang_visitChildren(cursor, visit, NULL);





    return EXIT_SUCCESS;

}
