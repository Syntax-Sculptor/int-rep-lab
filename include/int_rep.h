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

/*
    Interprets a value truncated to the provided bit width as a two's-complement
    signed integer. Only the lowest bits are used, while higher bits are ignored
    (i.e. interpreting 0xAB at width 4 uses the bit pattern 0xB / 1011, which
    represents -5).

    Valid widths are 1-32 inclusive. To check if a width is valid, see
    is_valid_width().
*/
int32_t get_signed_value(uint32_t value, int width);

/*
    Gets the maximum value for an unsigned 32 bit integer corresponding to the
    provided width. It's calcxulated as 2^width - 1.

    Valid widths are 1-32 inclusive. To check if a width is valid, see
    is_valid_width().
*/
uint32_t get_umax(int width);

#endif