#ifndef TIME_MEASURE_H
#define TIME_MEASURE_H

#include <time.h>
#include "tf_alg.h"
#include "pthread_tf.h"

#define NUMBER_OPER 1000

int time_measure(int start, int max_len, int step);

#endif //TIME_MEASURE_H
