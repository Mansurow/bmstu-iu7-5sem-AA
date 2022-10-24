#ifndef READ_ARRAY_H
#define READ_ARRAY_H

#include <iostream>

#include "allocate.h"
#include "generate_array.h"

int read_size(int &n);
int read_array(int **array, int &n);
int random_array(int **array, int &n);

#endif //READ_ARRAY_H
