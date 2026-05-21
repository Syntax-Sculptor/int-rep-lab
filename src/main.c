/*
    SyntaxSculptor
    4/29/26
    main.c
*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include "int_rep.h"

// Checks if the given string converts into a nonnegative integer. This works  
// for both plain integers and hex values.
int parse_uint32t(const char* input, uint32_t* out) {
    size_t len = strlen(input);

    if (len == 0 || input[0] == '-') {
        return 0;
    }

    char* endptr;
    errno = 0;

    unsigned long parsed = strtoul(input, &endptr, 0);

    if (errno == ERANGE) {
        return 0;
    }

    if (endptr == input || *endptr != '\0' || parsed > UINT32_MAX) {
        return 0;
    } 

    *out = (uint32_t) parsed;

    return 1;
}

// Checks if the given string converts into a nonnegative integer.
int parse_width(const char* input, int* out) {
    size_t len = strlen(input);

    if (len == 0 || input[0] == '-') {
        return 0;
    }

    char* endptr;
    errno = 0;

    unsigned long parsed = strtoul(input, &endptr, 10);

    if (errno == ERANGE) {
        return 0;
    }

    if (endptr == input || *endptr != '\0' || parsed > INT_MAX) {
        return 0;
    } 

    *out = (int) parsed;

    return 1;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: ./int_rep value width\n");
        return EXIT_FAILURE;
    }

    uint32_t val;
    int width;

    if (!parse_uint32t(argv[1], &val) || !parse_width(argv[2], &width)) {
        printf(
            "Please enter a valid nonnegative integer or hexadecimal value.\n"
        );
        return EXIT_FAILURE;
    }

    if (!is_valid_width(width)) {
        printf("Please enter a valid width between 1 and 32\n");
        return EXIT_FAILURE;
    }

    // Actual reporting magic!
    uint32_t masked_val = mask_to_width(val, width);
    char bits[MAX_BIT_STRING_SIZE];
    int bits_to_string_res = bits_to_string(masked_val, width, bits, MAX_BIT_STRING_SIZE);

    if (bits_to_string_res == 0) {
        printf("Failed to convert bits to string properly.\n");
        return EXIT_FAILURE;
    }


    printf("Bits:       %s\n", bits);
    printf("Width:      %d\n", width);
    printf("Unsigned:   %u\n", masked_val);
    printf("twos-comp:  %d\n", get_signed_value(masked_val, width));
    printf("TMin:       %d\n", get_tmin(width));
    printf("TMax:       %d\n", get_tmax(width));
    printf("UMax:       %u\n", get_umax(width));

    return EXIT_SUCCESS;
}