#include "sorts.h"

void print_array(int *array, size_t n)
{
    for(int i = 0; i < n; i++)
        std::cout << array[i] << " ";
    std::cout << std::endl;
}

void swap(int &el1, int &el2)
{
    int temp = el1;
    el1 = el2;
    el2 = temp;
}

void shell_sort(int *array, size_t n)
{
    if (array != nullptr && n > 0)
    {
        for (int s = n / 2; s > 0; s /= 2)
        {
            for (int i = s, j; i < n; i++)
            {
                int temp = array[i];
                for (j = i; array[j - s] > temp && j >= s; j -= s)
                    array[j] = array[j - s];
                array[j] = temp;
            }
        }
    }
}

void heapify(int *array, size_t i, size_t n)
{
    size_t largest;
    int done = 0;
    size_t l, r;

    while((2 * i <= n) && !done)
    {
        l = 2 * i;
        r = 2 * i + 1;

        if (l == n)
        {
            largest = l;
        } else if (array[l] > array[r])
            largest = l;
        else
            largest = r;

        if (array[i] < array[largest])
        {
            swap(array[i], array[largest]);
            i = largest;
        }
        else
            done = 1;
    }
}

void heap_sort(int *array, size_t n)
{
    if (array != nullptr && n > 0)
    {
        for (int i = n / 2; i >= 0; i--)
        {
            heapify(array, i, n - 1);
        }

        for (int i = n - 1; i >= 1; i--)
        {
            swap(array[0], array[i]);
            heapify(array, 0, i - 1);
        }
    }
}

void bead_sort(int *array, size_t n){
    if (array != nullptr && n > 0) {
        int i, j, max, sum;
        unsigned char *beads;

        for (i = 1, max = array[0]; i < n; i++)
            if (array[i] > max)
                max = array[i];

        beads = static_cast<unsigned char *>(calloc(1, max * n));

        for (i = 0; i < n; i++)
            for (j = 0; j < array[i]; j++)
                beads[i * max + j] = 1;

        for (j = 0; j < max; j++)
        {
            for (sum = i = 0; i < n; i++)
            {
                sum += beads[i * max + j];
                beads[i * max + j] = 0;
            }
            for (i = n - sum; i < n; i++)
                beads[i * max + j] = 1;
        }

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < max && beads[i * max + j]; j++);
            array[i] = j;
        }
        free(beads);
    }
}