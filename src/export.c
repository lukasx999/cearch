#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "./export.h"



Functions functions_new(void) {

    Functions functions = {
        .size     = 0,
        .capacity = 5,
        .items    = NULL,
    };

    functions.items = calloc(functions.capacity, sizeof(Function));

    return functions;

}

void functions_append(Functions *funcs, Function new) {

    if (funcs->size == funcs->capacity) {
        funcs->capacity *= 2;
        funcs->items = realloc(funcs->items, funcs->capacity * sizeof(Function));
    }

    funcs->items[funcs->size++] = new;

}

void functions_destroy(Functions *funcs) {

    for (size_t i=0; i < funcs->size; ++i) {
        free(funcs->items[i].parameters);
    }

    free(funcs->items);
}

void functions_print(Functions *funcs) {

    for (size_t i=0; i < funcs->size; ++i) {

        Function current_func = funcs->items[i];
        const char *id = current_func.identifier;
        CXType returntype            = current_func.returntype;

        CXString returntype_str      = clang_getTypeKindSpelling(returntype.kind);
        const char * returntype_cstr = clang_getCString(returntype_str);

        printf("func: %s -> %s\n", id, returntype_cstr);
        clang_disposeString(returntype_str);


        for (size_t j=0; j < current_func.param_count; ++j) {

            Parameter current_param = current_func.parameters[j];

            const char *param_id = current_param.identifier;
            CXType type = current_param.type;

            CXString type_str      = clang_getTypeKindSpelling(type.kind);
            const char * type_cstr = clang_getCString(type_str);

            printf("\tparam: %s (%s)\n", param_id, type_cstr);
            clang_disposeString(type_str);

        }


    }


}
