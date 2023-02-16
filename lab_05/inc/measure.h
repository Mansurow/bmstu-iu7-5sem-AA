#ifndef MEASURE_H
#define MEASURE_H

#include <iostream>
#include "conveyor.h"

double parallel_measure(size_t req_cnt, size_t size);
double linear_measure(size_t req_cnt, size_t size);
void time_measure();

#endif //MEASURE_H
