#ifndef LAB_01_CPU_TIME_H
#define LAB_01_CPU_TIME_H

#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <ctime>
#include "algorithms.h"

double get_cpu_time(int (*find_distance)(std::wstring &, std::wstring &), std::wstring &, std::wstring &);
double get_cpu_time(int (*find_distance)(std::wstring &, std::wstring &, bool), std::wstring &, std::wstring &);
void measuring_time(size_t max_len_str, size_t max_count_ope);

#endif //LAB_01_CPU_TIME_H
