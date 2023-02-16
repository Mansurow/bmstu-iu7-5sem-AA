#include "../inc/measure.h"

double get_time(timespec start, timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
}

double parallel_measure(size_t req_cnt, size_t size) {
    timespec start, end;

    clock_gettime(CLOCK_REALTIME, &start);
    std::vector<request_t *> pool(req_cnt);
    std::queue<request_t *> q1;
    std::queue<request_t *> q2;
    std::queue<request_t *> q3;

    std::thread t_1(thread_1, req_cnt, size, size, size / 2, std::ref(q1));
    std::thread t_2(thread_2, req_cnt, std::ref(q1), std::ref(q2));
    std::thread t_3(thread_3, req_cnt, std::ref(q2), std::ref(pool));

    t_1.join();
    t_2.join();
    t_3.join();
    clock_gettime(CLOCK_REALTIME, &end);
    print_pool(pool, "m_parallel.txt");
    for (size_t i = 0; i < pool.size(); ++i)
        delete pool[i];

    double time = get_time(start, end);
    return time;
}

double linear_measure(size_t req_cnt, size_t size) {

    timespec start, end;
    std::vector<request_t *> pool(req_cnt);

    clock_gettime(CLOCK_REALTIME, &start);
    for (int i = 0; i < req_cnt; i++) {
        request_t *r = new request_t();

        clock_gettime(CLOCK_REALTIME, &r->p1_start);
        pack_data(size, size, size / 2, r);
        clock_gettime(CLOCK_REALTIME, &r->p1_end);

        clock_gettime(CLOCK_REALTIME, &r->p2_start);
        r->mtr_c = sum_mtr_csr(r->mtr_a, r->mtr_b);
        clock_gettime(CLOCK_REALTIME, &r->p2_end);

        clock_gettime(CLOCK_REALTIME, &r->p3_start);
        r->result = decomprass(r->mtr_c);
        clock_gettime(CLOCK_REALTIME, &r->p3_end);

        pool[i] = r;
    }
    clock_gettime(CLOCK_REALTIME, &end);
    print_pool(pool, "m_linear.txt");
    for (size_t i = 0; i < pool.size(); ++i)
        delete pool[i];

    double time = get_time(start, end);
    return time;
}

void time_measure() {
    double tl = 0, tp = 0;

    printf("size,l,p\n");
    for (int i = 10; i <= MAX_REQUEST; i += 10) {
        for (int j = 0; j < LOOPS; j++) {
            tl += linear_measure(i, MATRIX_SIZE);
            tp += parallel_measure(i, MATRIX_SIZE);
        }
        if (tl > 0)
            tl /= (MATRIX_SIZE - 2) * 10000;
        if (tp > 0)
            tp /= (MATRIX_SIZE - 2) * 10000;
        printf("%d,%.2lf,%.2lf\n", i, tl, tp);
    }
}