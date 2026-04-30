/*
    SyntaxSculptor
    4/29/26
    test_int_rep.c

    Implements unit tests for functions found in int_rep.c
*/

#include "int_rep.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef struct bits_to_string_config {
    uint32_t value;
    int width;
    char *expected_value;
} bits_to_string_config;

// Tests to see if a valid width is correctly being detected as valid.
void test_is_valid_width() {
    for (int i = 1; i <= MAX_SHIFT_SIZE; i++) {
        int res = is_valid_width(i);
        assert(res == 1);
    }
}

// Tests to see if an invalid width is correctly being detected as invalid.
void test_is_invalid_width() {
    int cases[] = {0, -1, 33};

    for (int i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        int res = is_valid_width(cases[i]);
        assert(res == 0);
    }
}

// Tests to make sure masking values work.
void test_mask_to_width() {
    // {value, mask width, expected value}
    uint32_t cases[][3] = {
        {0xAB, 4, 0xB},
        {0xAB, 8, 0xAB},
        {0x5, 4, 0x5},
        {0x123, 8, 0x23},
        {0xFFFFFFFF, 16, 0xFFFF},
        {0xFFFFFFFF, 32, 0xFFFFFFFF},
    };

    for (int i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        uint32_t res = mask_to_width(cases[i][0], cases[i][1]);
        assert(res == cases[i][2]);
    }
}

// Tests to make sure converting bits to a string works.
void test_bits_to_string() {
    bits_to_string_config cases[] = {
        {0x1, 4, "0001"},
        {0xB, 4, "1011"},
        {0xF, 4, "1111"},
        {0x80, 8, "10000000"},
        {0x7F, 8, "01111111"},
    };

    for (int i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        char buff[MAX_BIT_STRING_SIZE];

        bits_to_string(
            cases[i].value, 
            cases[i].width, 
            buff, 
            cases[i].width + 1
        );
        
        int res = strcmp(buff, cases[i].expected_value);

        assert(res == 0);
    }
}

void test_bits_to_string_buffer_checks() {
    char buff[MAX_BIT_STRING_SIZE];
    int safe_res = bits_to_string(0xFF, 4, buff, 5);
    assert(safe_res == 1);

    int unsafe_res = bits_to_string(0xFF, 4, buff, 1);
    assert(unsafe_res == 0);
}

int main() {
    printf("Beginning tests.\n");

    test_is_valid_width();
    test_is_invalid_width();
    test_mask_to_width();
    test_bits_to_string();
    test_bits_to_string_buffer_checks();

    printf("All tests passed :)");

    return EXIT_SUCCESS;
}