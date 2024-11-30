#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <ctype.h>

#include "./query_parser.h"
#include "./export.h"






size_t get_keyword(enum Type *out_type, const char *query, size_t position) {

    size_t skip = 0;

    for (size_t i=position+1; true; ++i) {
        const char c = query[i];
        if (!isalpha(c) || i == strlen(query)) {
            skip = i - position - 1;
            break;
        }
    }

    if (!strncmp(query + position, "int", skip)) {
        *out_type = TYPE_INT;
    }
    else {
        *out_type = TYPE_INVALID;
    }

    return skip;

}


int parse_query(FunctionQuery *out_query, const char *query) {

    size_t position = 0;

    FunctionQuery func = {
        .params     = calloc(127, sizeof(ParameterQuery)),
        .returntype = TYPE_INVALID,
    };

    size_t param_index = 0;
    bool is_returntype = false;
    bool need_delim    = false;

    while (1) {

        const char c = query[position];

        if (position == strlen(query)) {
            break;
        }

        switch (c) {

            case ' ': {
            } break;

            case '-': {

                if (query[position+1] == '>') {
                    position++;
                    is_returntype = true;
                    need_delim    = false;
                }
                else {
                    return 1;
                }

            } break;

            case ',': {
                need_delim = false;
            } break;

            case '+': {
            } break;

            case '#': {
            } break;

            case '*': {
            } break;

            default: {

                if (need_delim) {
                    puts("Delimiter not found!");
                    return 1;
                }

                enum Type type = TYPE_INVALID;
                size_t skip = get_keyword(&type, query, position);

                // Keyword not found
                if (type == TYPE_INVALID) {
                    puts("Identifiers not supported yet!");
                    return 1;
                }

                if (is_returntype) {
                    func.returntype = type;
                }
                else {
                    func.params[param_index++].type = type;
                }

                need_delim = true;
                position += skip;

            } break;

        }



        position++;

    }


    return 0;

}
