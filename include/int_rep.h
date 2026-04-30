/*
    SyntaxSculptor
    4/29/26
    int_rep.h
*/

#ifndef INT_REP_H
#define INT_REP_H

/* 
    Returns whether the provided bit width is supported.

    Valid widths are 1-32 (inclusive). While a width of 32 is allowed, the
    program will handle that case separately to prevent undefined behavior.
*/
int is_valid_width(int width);

#endif