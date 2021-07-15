int pow(int base, int power)
{
    int initial_base = base;
    for (int i=0;i < power;i++)
        base *= initial_base;

    return base;
}

