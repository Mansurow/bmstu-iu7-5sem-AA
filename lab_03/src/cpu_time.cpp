#include "../inc/cpu_time.h"

static long getThreadCpuTimeNs() {
    struct timespec t;
    if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t)) {
        perror("clock_gettime");
        return 0;
    }
    return t.tv_sec * 1000000000LL + t.tv_nsec;
}

double get_time_sort(void (*sort)(int *, size_t), int *arr, size_t n) {
    clock_t start_t, end_t;
    double total_t;

    start_t = clock();
    sort(arr, n);
    end_t = clock();
    total_t = (double) (end_t - start_t);
    return total_t;
}

void measure_time(size_t start, size_t max_len, size_t step, std::string flag) {

    double st1, st2, st3;
    long int sum;

    printf("+--------+-----------------------------------------------------------------+\n");
    printf("| %5s | %16s %s %15s | %31s |\n", "Размер", "", "Время, мс", "", "Cумма элементов");
    printf("|        |------------+---------------+---------------|    для bead_sort   |\n");
    printf("| %6s | %15s | %20s | %21s |                    |\n", "", "Шелла", "Пирамидальная", "Бусинами");
    printf("|--------|------------|---------------|---------------|--------------------|\n");
    for (size_t i = start; i <= max_len; i += step)
    {
        if (i == 0)
            continue;

        st1 = st2 = st3 = 0;

        int *shell_arr = allocate_arr(i);
        int *heap_arr = allocate_arr(i);
        int *bead_arr = allocate_arr(i);
        for(size_t j = 0; j < NUMBER_OPER; j++) {
            if (flag == "sort") {
                generate_sort_array(shell_arr, i);
                generate_sort_array(heap_arr, i);
                generate_sort_array(bead_arr, i);
            } else if (flag == "rsort") {
                generate_rsort_array(shell_arr, i);
                generate_rsort_array(heap_arr, i);
                generate_rsort_array(bead_arr, i);
            } else if (flag == "equal") {
                generate_array(shell_arr, i, 10);
                generate_array(heap_arr, i, 10);
                generate_array(bead_arr, i, 10);
            } else {
                generate_random_array(shell_arr, i);
                generate_random_array(heap_arr, i);
                generate_random_array(bead_arr, i);
            }
            st1 += get_time_sort(shell_sort, shell_arr, i);
            st2 += get_time_sort(heap_sort, heap_arr, i);
            st3 += get_time_sort(bead_sort, bead_arr, i);
        }

        if (st1) st1 /= (NUMBER_OPER - 2);
        if (st2) st2 /= (NUMBER_OPER - 2);
        if (st3) st3 /= (NUMBER_OPER - 2);

        sum = 0;
        for (int j = 0; j < i; j++) {
            sum += bead_arr[j];
        }
        printf("| %6zu | %10.5f | %13.5f | %13.5g | %18ld |\n", i, st1, st2, st3, sum);

        free_arr(shell_arr, i);
        free_arr(heap_arr, i);
        free_arr(bead_arr, i);
    }
    printf("+--------+------------+---------------+---------------+--------------------+\n");
}