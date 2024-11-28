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


typedef struct {
    Tokens tokens;
    size_t position;
} Parser;


extern void parse(Tokens tokens);





#endif // _PARSER_H
