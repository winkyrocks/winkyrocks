#include <stdio.h>
#include <stdlib.h>

void Heapify(int *p, int count, int index)
{
    if (p == NULL || count < 1 || index >= count) return;
    int cur = p[index];
    while (1)
    {
        int maxChildIndex = index * 2 + 1; //left
        if ((maxChildIndex + 1 < count) && (p[maxChildIndex + 1] > p[maxChildIndex])) ++maxChildIndex; // right

        if ((maxChildIndex < count) && (cur < p[maxChildIndex]))
        {
            p[index] = p[maxChildIndex];
            p[maxChildIndex] = cur;
            index = maxChildIndex;
        }
        else
            break;
    }
}

int main()
{
    int numbers[] = { 21, 10, 5, 33, 3, 17, 23, 27, 16, 15 , 7};
    int length = sizeof(numbers) / sizeof(int);

    printf("Initial:");
    for (int j = 0; j < 10; ++j)
    {
        printf(" %i", numbers[j]);
    }

    for (int i = (length - 1) / 2; i >= 0; --i)
    {
        Heapify(numbers, length, i);
    }

    printf("\nHeap:");
    for (int j = 0; j < length; ++j)
    {
        printf(" %i", numbers[j]);
    }
    return 0;
}
