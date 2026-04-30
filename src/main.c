/*
    SyntaxSculptor
    4/29/26
    main.c
*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "int_rep.h"

int main() {
    // TODO: Add a proper unit test file.
    uint32_t val = 0xAB;
    int width = 4;
    uint32_t res = mask_to_width(val, width);
    printf("Result: %02x\n", res);

    return EXIT_SUCCESS;
}