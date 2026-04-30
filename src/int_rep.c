/*
    SyntaxSculptor
    4/29/26
    int_rep.c

    Lets you view any value as either unsigned or two's-complement signed.
*/

#include "int_rep.h"

#include <stdint.h>

int is_valid_width(int width) {
    return width > 0 && width <= MAX_SHIFT_SIZE;
}

uint32_t mask_to_width(uint32_t value, int width) {
    if (width == MAX_SHIFT_SIZE) {
        return value;
    } else {
        uint32_t mask = ((1U << width) - 1);
        return value & mask;
    }
}

int bits_to_string(
    uint32_t value, 
    int width, 
    char* buff, 
    size_t buff_size
) {
    if (width + 1 > buff_size) {
        return 0;
    }

    for (int i = width - 1; i >= 0; i--) {
        int bit = value & (1U << i);
        int buff_idx = width - i - 1;

        if (bit > 0) {
            buff[buff_idx] = '1';
        }
        else {
            buff[buff_idx] = '0';
        }
    }

    buff[width] = '\0';
    
    return 1;
}