#ifndef _PARSER_H
#define _PARSER_H

#include "./tokenizer.h"


typedef struct {
    TokenKind type;
    TokenKind *modifiers; // NULL if none
    char identifier[TOKEN_BUFSIZE]; // may be empty
} FunctionParameter;

typedef struct {
    TokenKind returntype;
    TokenKind *modifiers; // NULL if none
    char identifier[TOKEN_BUFSIZE]; // may not be empty
    FunctionParameter *parameters;
} Function;

// TODO: Macros, Structs

typedef struct {
    enum {
        THING_TAG_FUNCTION,
    } tag;
    union {
        Function thing_function;
    };
} Thing;


extern void parse(Tokens tokens);





#endif // _PARSER_H
