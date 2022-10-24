#ifndef CPU_TIME_H
#define CPU_TIME_H

#include <iostream>

#include "allocate.h"
#include "generate_array.h"
#include "sorts.h"

#define NUMBER_OPER 1000

void measure_time(size_t start, size_t max_len, size_t step, std::string flag="default");

#endif //CPU_TIME_H
