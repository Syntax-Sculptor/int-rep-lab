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

// Tests to see if a valid width is correctly being detected as valid.
void test_is_valid_width() {
    for (int i = 1; i <= 32; i++) {
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

int main() {
    printf("Beginning tests.\n");

    test_is_valid_width();
    test_is_invalid_width();
    test_mask_to_width();

    printf("All tests passed :)");

    return EXIT_SUCCESS;
}