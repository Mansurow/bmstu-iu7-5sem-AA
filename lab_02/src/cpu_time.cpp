#include "../inc/cpu_time.h"

#define NUMBER_OPER 1000

double get_time_sort(matrix_v (*multy_mtr)(const matrix_v &, const matrix_v &),
                     const matrix_v &mtr1, const matrix_v &mtr2) {
    clock_t start_t, end_t;
    double total_t;

    start_t = clock();
    matrix_v res = multy_mtr(mtr1, mtr2);
    end_t = clock();
    total_t = (double) (end_t - start_t);
    return total_t;
}

void random_mtr(matrix_v &mtr)
{
    for (size_t i = 0; i < mtr.size(); i++)
        for (size_t j = 0; j < mtr[0].size(); j++)
            mtr[i][j] = rand() % 100;
}

void resize_mtr(matrix_v &mtr, size_t n, size_t m)
{
    array_v row;
    row.resize(m, 0);
    mtr.resize(n, row);
}

void measure_time(size_t start, size_t max_len, size_t step) {


    double st1, st2, st3;

    printf("+--------+--------------------------------------------+\n");
    printf("| %5s | %16s %s %15s |\n", "Размер", "", "Время, мс", "");
    printf("|        |------------+---------------+---------------|\n");
    printf("| %6s | %15s | %20s | %21s |\n", "", "Класс.", " Винограда ", "(опт.)Винограда");
    printf("|--------|------------|---------------|---------------|\n");
    for (size_t i = start; i <= max_len; i += step)
    {
        if (i == 0)
            continue;
        matrix_v mtr1, mtr2;
        st1 = st2 = st3 = 0;

        resize_mtr(mtr1, i, i);
        resize_mtr(mtr2, i, i);

        random_mtr(mtr1);
        random_mtr(mtr2);

        for(size_t j = 0; j < NUMBER_OPER; j++) {
            st1 += get_time_sort(standart_multy, mtr1, mtr2);
            st2 += get_time_sort(vinograd_alg, mtr1, mtr2);
            st3 += get_time_sort(opt_vinograd_alg, mtr1, mtr2);
        }

        if (st1) st1 /= (NUMBER_OPER - 2);
        if (st2) st2 /= (NUMBER_OPER - 2);
        if (st3) st3 /= (NUMBER_OPER - 2);

        printf("| %6zu | %10.5f | %13.5f | %13.5g |\n", i, st1, st2, st3);
    }
    printf("+--------+------------+---------------+---------------+\n");
}