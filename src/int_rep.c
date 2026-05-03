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

int32_t get_signed_value(uint32_t value, int width) {
    uint32_t masked = mask_to_width(value, width);

    uint32_t signed_bit = masked & (1U << (width - 1));

    if (signed_bit == 0) {
        return (int32_t) masked;
    }
    else {
        // 1 << width is equivalent to 2^width. We cast it to a uint64_t as
        // the width can be 32, which would cause an overflow if it was a
        // uint32_t.

        return (int32_t) masked - ((uint64_t)1 << width);
    }
}

uint32_t get_umax(int width) {
    // 1 << width is equivalent to 2^width. We cast it to a uint64_t as
    // the width can be 32, which would cause an overflow if it was a
    // uint32_t.
    uint64_t exp = (uint64_t)1 << width;
    return (uint32_t) (exp - 1);
}