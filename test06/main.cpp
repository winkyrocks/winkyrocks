#include <iostream>

using namespace std;

int getNumberOfOnes(int number)
{
    int ones = 0;
    for (; number > 0; number >>= 1)
    {
        if ((number & 0x1) == 0x1)
            ++ones;
    }

    return ones;
}

int getNumberOfOnes2(int number)
{
    int ones = 0;
    for (; number > 0; number &= (number - 1))
    {
        ++ones;
    }

    return ones;
}

int main()
{
    union {
        int integer;
        char byte;
    } endianTest;

    endianTest.integer = 1;
    if (endianTest.byte)
        cout << "Little Endian" << endl;
    else
        cout << "Big Endian" << endl;

    cout << getNumberOfOnes(0b1101) << endl;
    cout << getNumberOfOnes2(0b1101) << endl;

    return 0;
}
