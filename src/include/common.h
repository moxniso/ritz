// common.h
// Common definitions used throughout the ritz API
// part of the Ritz libc
// 2020 moxniso

#ifndef COMMON_H
#define COMMON_H

typedef enum {FALSE, TRUE} BOOL; // capitalized to avoid conflict with C++ bool
#define nullptr ((void*)0)

typedef struct tS {
    char* month;
    char day_first_digit;
    char day_second_digit;
    char year_first_digit;
    char year_second_digit;
    char year_third_digit;
    char year_fourth_digit;
} time_strs;


#endif /* COMMON_H */
