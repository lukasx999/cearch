#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "./parser.h"
#include "./tokenizer.h"



static Token parser_current_token(Parser *p) {
    return p->tokens.items[p->position];
}

static void parser_next_token(Parser *p) {
    p->position++;
}





void prod_parameter(Parser *p) {
    // parameter ::= <modifier>* <type> "*"? <identifier>?
}

void prod_parameterlist(Parser *p) {
    // parameterlist ::= <parameter> ("," <parameter>)*
}

void prod_function(Parser *p) {
    // function ::= <modifier>* <returntype> "*"? <identifier> "(" <parameterlist>? | "void" ")" ";"


    Function func = { 0 };


    Token current = parser_current_token(p);

    while (current.kind == TOK_KW_CONST) {
        parser_next_token(p);
    }



}



void parse(Tokens tokens) {

    Parser parser = { .tokens = tokens, .position = 0 };

    prod_function(&parser);





}
