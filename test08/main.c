#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LEN 10

typedef struct Tuple
{
    char chr;
    int offset_s, offset_t;
} Tuple;

int matrix[MAX_LEN][MAX_LEN] = { 0 };
Tuple seq[MAX_LEN] = { 0 };
int offset = 0;

int distance(char *s, int len_s, char *t, int len_t)
{
    if (matrix[len_s][len_t])
    {
        return matrix[len_s][len_t];
    }

    if (len_s == 0) return matrix[len_s][len_t] = len_t;
    if (len_t == 0) return matrix[len_s][len_t] = len_s;

    if (s[len_s - 1] == t[len_t - 1])
    {
        seq[offset].chr = s[len_s - 1];
        seq[offset].offset_s = len_s - 1;
        seq[offset].offset_t = len_t - 1;
        ++offset;
        return matrix[len_s][len_t] = distance(s, len_s - 1, t, len_t - 1);
    }

    int del_s_cost = distance(s, len_s - 1, t, len_t) + 1;
    int add_t_cost = distance(s, len_s, t, len_t - 1) + 1;
    int sub_cost = distance(s, len_s - 1, t, len_t - 1) + 1;

    return matrix[len_s][len_t] = fmin(sub_cost, fmin(del_s_cost, add_t_cost));
}

int main()
{
    char *s = "Orchestra";
    char *t = "Carthorse";
    int d = distance(s, strlen(s), t, strlen(t));
    printf("The distance between '%s' and '%s': %d\n", s, t, d);

    int max_len = 0, max_start = 0;
    for (int start = 0, i = 1; i < offset; ++i)
    {
        if ((seq[i - 1].offset_s > seq[i].offset_s) || (seq[i - 1].offset_t > seq[i].offset_t))
        {
            if (i - start > max_len)
            {
                max_start = start;
                max_len = i - start;
            }

            start = i;
        }
    }

    printf("The longest sequence:\n");
    for (int i = max_start; i < max_start + max_len; ++i)
    {
        printf("%c %d %d\n", seq[i].chr, seq[i].offset_s, seq[i].offset_t);
    }

    return 0;
}
