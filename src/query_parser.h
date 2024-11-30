#ifndef _QUERY_PARSER_H
#define _QUERY_PARSER_H



enum Type {
    TYPE_INVALID,
    TYPE_INT,
    TYPE_VOID,
    TYPE_BOOL,
    TYPE_CHAR,
};

typedef struct {
    enum Type type;
    // char identifier[];
} ParameterQuery;

typedef struct {
    enum Type returntype;
    ParameterQuery *params;
} FunctionQuery;

extern int parse_query(FunctionQuery *out_query, const char *query);



#endif // _QUERY_PARSER_H
