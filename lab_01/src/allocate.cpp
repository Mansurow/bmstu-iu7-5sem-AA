#include "allocate.h"

void free_mtr(int **mtr, std::size_t n) {
    if (mtr != nullptr)
    {
        for (std::size_t i = 0; i < n; i++)
            if (mtr[i] != nullptr)
                free(mtr[i]);
        free(mtr);
    }
}

int **malloc_mtr(std::size_t n, std::size_t m)
{
    if (n == 0)
        return nullptr;

    int **mtr = static_cast<int **>(malloc(n * sizeof(int *)));
    if (mtr != nullptr)
        for (std::size_t i = 0; mtr[i] != nullptr && i < n; i++) {
            mtr[i] = static_cast<int *>(malloc(m * sizeof(int)));
            if (mtr[i] == nullptr)
                free_mtr(mtr, n);
        }

    return mtr;
}