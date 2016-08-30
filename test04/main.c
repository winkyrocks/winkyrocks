#include <stdio.h>
#include <stdlib.h>

int add(int a, int b)
{
    int result = 0, bitcarry = 0, bitpos = 0;
    while (a > 0 || b > 0)
    {
        int bita = a & 0x1;
        int bitb = b & 0x1;
        int bitadd = (bita ^ bitb) ^ bitcarry;
        bitcarry = (bita & bitb) | ((bita ^ bitb) & bitcarry);

        printf("bit %d: %d + %d = %d (%d)\n", bitpos, bita, bitb, bitadd, bitcarry);

        result |= bitadd << (bitpos++);
        a >>= 1;
        b >>= 1;
    }

    if (bitcarry > 0)
    {
        result |= bitcarry << bitpos;
    }

    return result;
}

int main()
{
    int a = 14, b = 7;
    printf("%d + %d = %d\n", a, b, add(a, b));
    return 0;
}
