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

    functions.items = calloc(functions.capacity, sizeof(Function_));

    return functions;

}

void functions_append(Functions *funcs, Function_ new) {

    if (funcs->size == funcs->capacity) {
        funcs->capacity *= 2;
        funcs->items = realloc(funcs->items, funcs->capacity * sizeof(Function_));
    }

    funcs->items[funcs->size++] = new;

}

void functions_destroy(Functions *funcs) {

    for (size_t i=0; i < funcs->size; ++i) {

        Function_ *f = &funcs->items[i];

        for (size_t j=0; j < f->param_count; ++j) {
            Parameter *p = &f->parameters[j];
            clang_disposeString(p->identifier);
        }

        clang_disposeString(f->identifier);
        free(f->parameters);

    }

    free(funcs->items);
}

void functions_print(Functions *funcs) {

    for (size_t i=0; i < funcs->size; ++i) {

        Function_ current_func = funcs->items[i];

        const char *id              = clang_getCString(current_func.identifier);

        CXString    returntype_str  = clang_getTypeKindSpelling(current_func.returntype.kind);
        const char *returntype_cstr = clang_getCString(returntype_str);

        printf("func: %s -> %s\n", id, returntype_cstr);
        clang_disposeString(returntype_str);


        for (size_t j=0; j < current_func.param_count; ++j) {

            Parameter current_param = current_func.parameters[j];

            const char *param_id  = clang_getCString(current_param.identifier);

            CXString    type_str  = clang_getTypeKindSpelling(current_param.type.kind);
            const char *type_cstr = clang_getCString(type_str);

            printf("\tparam: %s (%s)\n", param_id, type_cstr);
            clang_disposeString(type_str);

        }


    }


}
