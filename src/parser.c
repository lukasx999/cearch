#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "./parser.h"
#include "./tokenizer.h"



void parse(Tokens tokens) {

    // function ::= <modifier>* <returntype> <identifier> "(" <parameterlist>? | "void" ")" ";"
    // parameterlist ::= <parameter> ("," <parameter>)*
    // parameter ::= <modifier>* <type> <identifier>?

    for (size_t i=0; i < tokens.size-1; ++i) {
        Token token = tokens.items[i];





    }




}
