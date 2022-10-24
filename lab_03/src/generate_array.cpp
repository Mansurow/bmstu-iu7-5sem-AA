#include "generate_array.h"

void generate_random_array(int *arr, const size_t n)
{
    for(size_t i = 0; i < n; i++)
        arr[i] = rand() % 100;
}

void generate_sort_array(int *arr, const size_t n)
{
    arr[0] = rand() % 100;
    for(size_t i = 1; i < n; i++)
        arr[i] = arr[i - 1] + 1;
}

void generate_rsort_array(int *arr, const size_t n)
{
    arr[0] = 10000;
    for(size_t i = 1; i < n; i++)
        arr[i] = arr[i - 1] - 1;
}

void generate_array(int *arr, const size_t n, const int element)
{
    for(size_t i = 0; i < n; i++)
        arr[i] = element;
}