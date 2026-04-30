/*
    SyntaxSculptor
    4/29/26
    int_rep.c

    Lets you view anyy value as either unsigned or two's-complement signed.
*/

#include "int_rep.h"

int is_valid_width(int width) {
    return width > 0 && width <= 32;
}