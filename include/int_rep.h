/*
    SyntaxSculptor
    4/29/26
    int_rep.h
*/

#ifndef INT_REP_H
#define INT_REP_H
#define MAX_SHIFT_SIZE 32
#define MAX_BIT_STRING_SIZE (MAX_SHIFT_SIZE + 1)

#include <stdint.h>

/* 
    Returns whether the provided bit width is supported.

    Valid widths are 1-32 (inclusive). While a width of 32 is allowed, the
    program will handle that case separately to prevent undefined behavior.
*/
int is_valid_width(int width);

/*
    Returns a value truncated to the provided bit width. Only the lowest bits
    are preserved while higher bits are cleared (i.e. masking 0xAB to width 4
    results in 0xB).

    Valid widths are 1-32 (inclusive). To check if a value is valid, see
    `is_valid_width`.
*/
uint32_t mask_to_width(uint32_t value, int width);

/*
    Converts a value into a binary string. Returns 0 if the function is unable
    to run due to the risk of writing past the buffer.
*/
int bits_to_string(uint32_t value, int width, char* buff, size_t buff_size);

#endif