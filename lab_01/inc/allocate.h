#ifndef LAB_01_ALLOCATE_H
#define LAB_01_ALLOCATE_H

#include <iostream>
#include <cstdlib>

void free_mtr(int **mtr, std::size_t n);
int **malloc_mtr(std::size_t n, std::size_t m);

#endif //LAB_01_ALLOCATE_H
