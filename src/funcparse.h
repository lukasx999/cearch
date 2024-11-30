#include "./export.h"

// Parses a C/C++ translation unit into a `Functions` struct
extern int parse_translationunit(Functions *out_functions, const char *filename);

// Caller is responsible for freeing
extern char** export_function_names(Functions *funcs);
