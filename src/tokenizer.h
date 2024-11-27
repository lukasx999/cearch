#ifndef _TOKENIZER_H
#define _TOKENIZER_H

#include <stddef.h>


#define TOKEN_BUFSIZE 50


typedef enum {
    TOK_IDENTIFIER,
    TOK_RPAREN,
    TOK_LPAREN,
    TOK_SEMICOLON,
    TOK_COMMA,
    TOK_ASTERISK,
    TOK_KW_VOID,
    TOK_KW_INT,
    TOK_KW_CHAR,
    TOK_KW_STATIC,
    TOK_KW_INLINE,
    TOK_KW_EXTERN,
    TOK_KW_CONST,
    TOK_EOF,
} TokenKind;

static const char *token_kind_repr[] = {
    "identifier",
    "rparen",
    "lparen",
    "semicolon",
    "comma",
    "asterisk",
    "kw_void",
    "kw_int",
    "kw_char",
    "kw_static",
    "kw_inline",
    "kw_extern",
    "kw_const",
    "eof",
};

typedef struct {
    TokenKind kind;
    char value[TOKEN_BUFSIZE]; // may be empty
} Token;

typedef struct {
    size_t capacity;
    size_t size;
    Token *items;
} Tokens;

extern Tokens tokens_new(void);
extern void tokens_append(Tokens *tokens, Token item);

extern Tokens tokenize(const char *source);





#endif // _TOKENIZER_H
