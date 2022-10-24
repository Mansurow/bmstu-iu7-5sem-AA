#include "allocate.h"

int *allocate_arr(size_t n)
{
    int *arr = nullptr;
    if (n > 0)
        arr = static_cast<int *>(calloc(n, sizeof(int)));

    return arr;
}

void free_arr(int *arr, size_t n)
{
    if (n > 0)
        free(arr);
}