#include <stdio.h>
#include <stdlib.h>

#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"
#define BYTETOBINARY(byte)  \
  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0)

/*
Count number of 1s in each integer binary between 0 and the given integer
Dynamic programing: e.g. countBits(101010y) = countBits(101010) + countBits(y)
*/
int* countBits(int num, int* returnSize)
{
    *returnSize = num + 1;
    int *result = (int*)malloc(*returnSize * sizeof(int));

    for (int i = 0; i <= num; ++i)
    {
        if (i < 2)
        {
            result[i] = i;
        }
        else
        {
            int p = i >> 1;
            int q = i & 0x1;
            result[i] = result[p] + result[q];
        }
    }

    return result;
}

/*
Count number of k in each integer between 0 and the given integer
Dynamic programing: e.g. countK(12345) = countK(1234) + countK(5)
*/
int* countK(int num, int k, int* returnSize)
{
    *returnSize = num + 1;
    if (k < 0 || k > 9) return NULL;

    int *result = (int*)malloc(*returnSize * sizeof(int));

    for (int i = 0; i <= num; ++i)
    {
        if (i < 10)
        {
            result[i] = (i == k) ? 1 : 0;
        }
        else
        {
            int p = i / 10;
            int q = i % 10;
            result[i] = result[p] + result[q];
        }
    }

    return result;
}

int main()
{
    int size;

    int *result1 = countBits(255, &size);
    for (int i = 0; i < size; ++i)
    {
        printf(BYTETOBINARYPATTERN"(%d) ", BYTETOBINARY(i), result1[i]);
    }
    free(result1);

    printf("\n\n");

    int *result2 = countK(1000, 2, &size);
    for (int i = 0; i < size; ++i)
    {
        printf("%d(%d) ", i, result2[i]);
    }
    free(result2);

    return 0;
}
