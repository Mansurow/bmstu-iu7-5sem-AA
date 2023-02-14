#include "inc/conveyor.h"

void printf_time(timespec start_t, timespec end_t) {
    long int time = (end_t.tv_sec - start_t.tv_sec) * 1000000000 + end_t.tv_nsec - start_t.tv_nsec;
    printf("%ld\n", time);
}

int main() {
    setbuf(stdout, nullptr);

    linear();
    return 0;
}
