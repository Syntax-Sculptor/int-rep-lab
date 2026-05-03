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

typedef struct mask_to_width_config {
    uint32_t value;
    int width;
    uint32_t expected_value;
} mask_to_width_config;

typedef struct get_signed_value_config {
    uint32_t value;
    int width;
    int32_t expected_value;  
} get_signed_value_config;

typedef struct get_umax_config {
    int width;
    uint32_t expected_value;
} get_umax_config;

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
    mask_to_width_config cases[] = {
        {0xAB, 4, 0xB},
        {0xAB, 8, 0xAB},
        {0x5, 4, 0x5},
        {0x123, 8, 0x23},
        {0xFFFFFFFF, 16, 0xFFFF},
        {0xFFFFFFFF, 32, 0xFFFFFFFF},
    };

    for (int i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        uint32_t res = mask_to_width(cases[i].value, cases[i].width);
        assert(res == cases[i].expected_value);
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

void test_get_signed_value() {
    get_signed_value_config cases[] = {
        {0x0, 1, 0},
        {0x1, 1, -1},

        {0x0, 4, 0},
        {0x7, 4, 7},
        {0x8, 4, -8},
        {0xB, 4, -5},
        {0xF, 4, -1},

        {0x7F, 8, 127},
        {0x80, 8, -128},
        {0xFF, 8, -1},

        {0x3039, 16, 12345},
        {0xCFC7, 16, -12345},

        {0x7FFFFFFF, 32, 2147483647},
        {0x80000000, 32, INT32_MIN},
        {0xFFFFFFFF, 32, -1},
    };

    for (int i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        int32_t res = get_signed_value(cases[i].value, cases[i].width);
        assert(res == cases[i].expected_value);
    }
}

// Tests get_umax()
void test_get_umax() {
    get_umax_config cases[] = {
        {1, 1U},
        {4, 15U},
        {8, 255U},
        {16, 65535U},
        {32, UINT32_MAX},
    };

    for (int i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        uint32_t res = get_umax(cases[i].width);
        assert(res == cases[i].expected_value);
    }
}

int main() {
    printf("Beginning tests.\n");

    test_is_valid_width();
    test_is_invalid_width();
    test_mask_to_width();
    test_bits_to_string();
    test_bits_to_string_buffer_checks();
    test_get_signed_value();
    test_get_umax();

    printf("All tests passed :)");

    return EXIT_SUCCESS;
}