#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_STRLEN 4

char str_inplace[MAX_STRLEN] = "1234";
char str_dups[MAX_STRLEN]    = "2234";

void swap(char *arr, int i, int j)
{
    char temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void permutate_inplace(int pos, char *arr)
{
    if (pos >= MAX_STRLEN)
    {
        for (int i = 0; i < MAX_STRLEN; ++i)
            printf("%c", arr[i]);
        printf("\n");
        return;
    }

    for (int i = pos; i < MAX_STRLEN; ++i)
    {
        if (pos == i || arr[pos] != arr[i])
        {
            swap(arr, pos, i);
            permutate_inplace(pos + 1, arr);
            swap(arr, pos, i);
        }
    }
}

const char *str = "abcd";
bool permutate_used[MAX_STRLEN] = { false };
char permutate_output[MAX_STRLEN] = { 0 };

void permutate(int pos)
{
    if (pos >= strlen(str))
    {
        printf("%s\n", permutate_output);
        return;
    }

    for (int i = 0; i < strlen(str); ++i)
    {
        if (!permutate_used[i])
        {
            permutate_output[pos] = str[i];
            permutate_used[i] = true;
            permutate(pos + 1);
            permutate_used[i] = false;
        }
    }
}

char combine_output[MAX_STRLEN] = { 0 };
void combine(int pos, int start, int combine_length)
{
    if (combine_length == 0 || pos == combine_length)
    {
        printf("%s\n", strlen(combine_output) ? combine_output : "<>");
        if (combine_length) return;
    }

    for (int i = start; i < strlen(str); ++i)
    {
        combine_output[pos] = str[i];
        combine(pos + 1, i + 1, combine_length);
        combine_output[pos] = 0;
    }
}

void powerset(int pos, int start)
{
    memset(combine_output, 0, MAX_STRLEN);
    combine(pos, start, 0);
}

void powerset_norecur(const char* arr, int arr_length)
{
    for (int i = 0; i < 1 << arr_length; ++i)
    {
        memset(combine_output, 0, MAX_STRLEN);
        int output_index = 0;
        int bit = i;
        while (bit)
        {
            int arr_index = log2(bit & ~(bit - 1));
            combine_output[output_index++] = arr[arr_index];
            bit &= bit - 1;
        }

        printf("%s\n", strlen(combine_output) ? combine_output : "<>");
    }
}

int main()
{
    printf("==========permutation==========\n");
    permutate_inplace(0, str_inplace);
    printf("\n");
    permutate_inplace(0, str_dups);
    printf("\n");
    permutate(0);
    printf("\n");
    printf("==========combination==========\n");
    combine(0, 0, 2);
    printf("\n");
    printf("==========powerset==========\n");
    powerset(0, 0);
    printf("\n");
    powerset_norecur(str, MAX_STRLEN);
    printf("\n");
    return 0;
}
