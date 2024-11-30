#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


int main(void) {

    char buf[5] = { 0 };
    strncpy(buf, "foobarbaz", 5-1);


    return 0;
}
