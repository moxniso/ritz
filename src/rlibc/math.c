// math.c
// Mathematical procedures
// part of the Ritz libc
// 2021 moxniso

int pow(int base, int power)
{
    int initial_base = base;
    for (int i=0;i < power;i++)
        base *= initial_base;

    return base;
}

