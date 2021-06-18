// stdlib.h
// General standard library functions
// Part of rlibc
// 2021 moxniso

#include <stddef.h>

void* memset(void* m, unsigned char c, size_t n)
{
    unsigned char* p = m; // so any ptr type can be passed
    for (int i=0;i<=n;i++) { 
        *p = c;
        p++;
    }
 
    return m;
}

void* memcpy(void* dest, const void* src, size_t n)
{
    unsigned char* pd = dest;
    unsigned const char* ps = src;
    for (int i=0;i<=n;i++) 
        *pd++ = *ps++;
 
    return dest;
}
