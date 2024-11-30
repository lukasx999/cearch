#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "funcparse.h"


// A struct for keeping state while visit() is called recursively
typedef struct {
    Functions *funcs;
    // temporary values - do not read:
    Parameter *params;
    size_t params_index;
} RecState;



Function build_function(RecState *state, CXType type, CXCursor cursor) {

    CXType      func_returntype = clang_getResultType(type);
    CXString    func_name       = clang_Cursor_getMangling(cursor);

    size_t param_count  = (int) clang_getNumArgTypes(type);
    Parameter *params   = calloc(param_count, sizeof(Parameter));
    state->params       = params;
    state->params_index = 0;

    Function func = {
        .returntype  = func_returntype,
        .identifier  = func_name,
        .parameters  = params,
        .param_count = param_count,
    };

    return func;

}


Parameter build_parameter(CXType type, CXCursor cursor) {

    CXType      param_type      = type;
    CXString    param_name      = clang_Cursor_getMangling(cursor);

    Parameter param = {
        .identifier = param_name,
        .type       = param_type,
    };

    return param;

}


enum CXChildVisitResult visit( CXCursor cursor,
                               CXCursor parent,
                               CXClientData client_data ) {

    RecState *state = (RecState*) client_data;

    enum CXCursorKind kind   = clang_getCursorKind(cursor);
    CXType type              = clang_getCursorType(cursor);

    switch (kind) {

        case CXCursor_FunctionDecl: {

            Function func = build_function(state, type, cursor);
            functions_append(state->funcs, func);

            return CXChildVisit_Recurse;

        } break;

        case CXCursor_ParmDecl: {

            Parameter param = build_parameter(type, cursor);
            state->params[state->params_index++] = param;

        } break;

        default: {} break;

    }

    return CXChildVisit_Continue;

}




int parse_translationunit(Functions *out_functions, const char *filename) {

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
        return 1;
    }

    CXCursor cursor = clang_getTranslationUnitCursor(unit);
    Functions funcs = functions_new();

    RecState state = {
        .funcs        = &funcs,
        .params       = NULL,
        .params_index = 0,
    };

    clang_visitChildren(cursor, visit, &state);

    *out_functions = funcs;
    return 0;

}


// Caller is responsible for freeing
char** export_function_names(Functions *funcs) {

    char **function_list = calloc(funcs->size, sizeof(char*));

    for (size_t i=0; i < funcs->size; ++i) {
        function_list[i] = calloc(IDENTIFIER_BUFSIZE, sizeof(char));

        const char *id = clang_getCString(funcs->items[i].identifier);
        strncpy(function_list[i], id, IDENTIFIER_BUFSIZE-1);
    }

    return function_list;

}
