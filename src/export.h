#ifndef _EXPORT_H
#define _EXPORT_H

#include <clang-c/Index.h>

#define IDENTIFIER_BUFSIZE 100


typedef struct {
    CXType type;
    char identifier[IDENTIFIER_BUFSIZE];
} Parameter;

typedef struct {
    CXType returntype;
    char identifier[IDENTIFIER_BUFSIZE];
    Parameter *parameters;
    size_t param_count;
} Function;

typedef struct {
    size_t size;
    size_t capacity;
    Function *items;
} Functions;

extern Functions functions_new(void);
extern void functions_append(Functions *funcs, Function new_);
extern void functions_destroy(Functions *funcs);
extern void functions_print(Functions *funcs);

#endif // _EXPORT_H
