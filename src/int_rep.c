/*
    SyntaxSculptor
    4/29/26
    int_rep.c

    Lets you view any value as either unsigned or two's-complement signed.
*/

#include "int_rep.h"

#include <stdint.h>

int is_valid_width(int width) {
    return width > 0 && width <= 32;
}

uint32_t mask_to_width(uint32_t value, int width) {
    if (width == 32) {
        return value;
    } else {
        uint32_t mask = ((1U << width) - 1);
        return value & mask;
    }
}