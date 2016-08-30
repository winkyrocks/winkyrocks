#include <stdio.h>

typedef struct node
{
    int max;
    int pre;
} node;

void dump(int *array, int i, node* result)
{
    if (i < 0)
        return;

    dump(array, result[i].pre, result);
    printf("%2d[%d] ", array[i], i);
}

int find_longest_nondescending(int *array, size_t len)
{
    int max_length = 0;
    node result[len];

    // calculating for array[0:i] to include array[i]
    for (int i = 0; i < len; ++i)
    {
        result[i].pre = -1;
        result[i].max = 1;
        for (int j = i - 1; j >= 0; --j)
        {
            if (array[j] <= array[i])
            {
                if (result[j].max + 1 >= result[i].max)
                {
                    result[i].max = result[j].max + 1;
                    result[i].pre = j;

                    printf("%d: ", i);
                    dump(array, i, result);
                    printf("(%d)\n", result[i].max);
                }
            }
        }

        if (result[i].max > max_length)
        {
            max_length = result[i].max;
        }
    }

    return max_length;
}

int find_longest_continous_nondescending(int *array, size_t len)
{
    int max_length = 1;
    int start = 0;

    for (int i = 1; i <= len; ++i)
    {
        if (i == len || array[i - 1] > array[i])
        {
            if ( i - start >= max_length)
            {
                max_length = i - start;
                for (int j = start; j < i; ++j)
                    printf("%d[%d] ", array[j], j);
                printf("(%d)\n", max_length);
            }

            start = i;
        }
    }

    return max_length;
}

int main()
{
    int a[] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 17};
    int max = find_longest_nondescending(a, sizeof(a)/sizeof(int));
    printf("MAX=%d\n", max);

    max = find_longest_continous_nondescending(a, sizeof(a)/sizeof(int));
    printf("MAX=%d\n", max);
}


