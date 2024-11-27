#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "./tokenizer.h"




Tokens tokens_new(void) {

    Tokens tokens = {
        .size     = 0,
        .capacity = 5,
        .items    = NULL
    };

    tokens.items = calloc(tokens.capacity, sizeof(Token));
    return tokens;

}

void tokens_append(Tokens *tokens, Token item) {

    if (tokens->size == tokens->capacity) {
        tokens->capacity += 2;
        tokens->items = realloc(tokens->items, tokens->capacity * sizeof(Token));
    }

    tokens->items[tokens->size++] = item;

}


Token token_new(void) {
    Token token = {
        .kind  = TOK_EOF,
        .value = "",
    };

    return token;
}


static bool is_identifier(char c) {
    return isalpha(c) || c == '_' || c == '$';
}



static size_t get_identifier(const char *source, size_t position) {

    for (size_t i = position + 1; true; ++i) {

        const char c = source[i];
        bool is_at_end = i == strlen(source);

        if ((!is_identifier(c) && !isdigit(c)) || is_at_end) {
            size_t skip = i - position - 1;
            return skip;
        }

    }

}


// Returns EOF token if no keyword was matched
static TokenKind match_keyword(const char *identifier) {

    TokenKind kind = TOK_EOF;

    if      (!strcmp(identifier, "void"   )) { kind = TOK_KW_VOID;   }
    else if (!strcmp(identifier, "int"    )) { kind = TOK_KW_INT;    }
    else if (!strcmp(identifier, "char"   )) { kind = TOK_KW_CHAR;   }
    else if (!strcmp(identifier, "inline" )) { kind = TOK_KW_INLINE; }
    else if (!strcmp(identifier, "extern" )) { kind = TOK_KW_EXTERN; }
    else if (!strcmp(identifier, "static" )) { kind = TOK_KW_STATIC; }
    else if (!strcmp(identifier, "const"  )) { kind = TOK_KW_CONST;  }

    return kind;

}




Tokens tokenize(const char *source) {
    Tokens tokens   = tokens_new();
    size_t position = 0;

    while (true) {
        const char c     = source[position];
        Token next       = token_new();
        bool ignore_next = false;

        if (position == strlen(source)) {
            tokens_append(&tokens, next);
            break;
        }

        switch (c) {

            case '\n':
            case ' ': { ignore_next = true; } break;

            case ';': { next.kind = TOK_SEMICOLON; } break;
            case '(': { next.kind = TOK_LPAREN;    } break;
            case ')': { next.kind = TOK_RPAREN;    } break;
            case '*': { next.kind = TOK_ASTERISK;  } break;
            case ',': { next.kind = TOK_COMMA;     } break;

            default: {

                size_t skip = get_identifier(source, position);
                char identifier[TOKEN_BUFSIZE] = { 0 };
                strncpy(identifier, source + position, skip + 1);

                TokenKind kind = match_keyword(identifier);

                if (kind == TOK_EOF) {
                    next.kind = TOK_IDENTIFIER;
                    strcpy(next.value, identifier);
                }
                else {
                    next.kind = kind;
                }

                position += skip;

            } break;

        }

        if (!ignore_next) {
            tokens_append(&tokens, next);
        }

        position++;

    }

    return tokens;

}
