#ifndef STRING_H
#define STRING_H
#include <stddef.h>
#include "common.h"

size_t strlen(char* str);
size_t strnlen(char* str, size_t size);
BOOL strncmp(char* str1, char* str2, size_t size);
BOOL strcmp(char* str1, char* str2);

#endif /* STRING_H */
