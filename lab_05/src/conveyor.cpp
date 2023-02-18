#include "../inc/conveyor.h"

std::mutex mutex_q1;
std::mutex mutex_q2;
//std::mutex mutex_q3;

//long int printf_time(timespec start_t, timespec end_t, char *str, timespec t) {
//    long int time = (end_t.tv_sec - start_t.tv_sec) * 1000000000 + end_t.tv_nsec - start_t.tv_nsec;
//    long int start = (start_t.tv_sec - t.tv_sec) * 1000000000 + start_t.tv_nsec -t.tv_nsec;
//    long int end = (end_t.tv_sec - t.tv_sec) * 1000000000 + end_t.tv_nsec - t.tv_nsec;
//    printf("%s: %ld === %ld --- %ld\n", str, time, start, end);
//    return time;
//}

void pack_data(size_t n, size_t m, size_t cnt, request_t *r) {
    generate_mtr_csr(r->mtr_a, n, m, cnt);
    generate_mtr_csr(r->mtr_b, n, m, cnt);
}

void linear() {
    int req_cnt = get_request_number();
    int n = get_matrix_n();
    int m = get_matrix_m();
    int cnt = get_matrix_num();

    std::vector<request_t *> pool(req_cnt);

    for (int i = 0; i < req_cnt; i++) {
        request_t *r = new request_t();

        clock_gettime(CLOCK_REALTIME, &r->p1_start);
        pack_data(n, m, cnt, r);
        clock_gettime(CLOCK_REALTIME, &r->p1_end);

        clock_gettime(CLOCK_REALTIME, &r->p2_start);
        r->mtr_c = sum_mtr_csr(r->mtr_a, r->mtr_b);
        clock_gettime(CLOCK_REALTIME, &r->p2_end);

        clock_gettime(CLOCK_REALTIME, &r->p3_start);
        r->result = decomprass(r->mtr_c);
        clock_gettime(CLOCK_REALTIME, &r->p3_end);

        pool[i] = r;
    }
    print_pool(pool, "linear.txt");
    for (size_t i = 0; i < pool.size(); ++i)
        delete pool[i];
}

void thread_1(size_t req_cnt, size_t n, size_t m, size_t cnt, std::queue<request_t *> &q1) {
    for (int i = 0; i < req_cnt; i++)
    {
        request_t *r = new request_t();
        clock_gettime(CLOCK_REALTIME, &r->p1_start);
        pack_data(n, m, cnt, r);

        mutex_q1.lock();
        clock_gettime(CLOCK_REALTIME, &r->p1_end);
        q1.push(r);
        mutex_q1.unlock();
    }
}

void thread_2(int req_cnt, std::queue<request_t *> &q1, std::queue<request_t *> &q2) {
    for (int i = 0; i < req_cnt; i++)
    {
        while (q1.empty());
        mutex_q1.lock();
        request_t *r = q1.front();
        q1.pop();
        mutex_q1.unlock();

        clock_gettime(CLOCK_REALTIME, &r->p2_start);
        r->mtr_c = sum_mtr_csr(r->mtr_a, r->mtr_b);

        mutex_q2.lock();
        clock_gettime(CLOCK_REALTIME, &r->p2_end);
        q2.push(r);
        mutex_q2.unlock();
    }
}

void thread_3(int req_cnt, std::queue<request_t *> &q2, std::vector<request_t *> &pool) {
    for (int i = 0; i < req_cnt; i++)
    {
        while (q2.empty());
        mutex_q2.lock();
        request_t *r = q2.front();
        q2.pop();
        mutex_q2.unlock();

        clock_gettime(CLOCK_REALTIME, &r->p3_start);
        r->result = decomprass(r->mtr_c);
        clock_gettime(CLOCK_REALTIME, &r->p3_end);
        pool[i] = r;
    }
}

void parallel() {
    int req_cnt = get_request_number();
    int n = get_matrix_n();
    int m = get_matrix_m();
    int cnt = get_matrix_num();

    std::vector<request_t *> pool(req_cnt);
    std::queue<request_t *> q1;
    std::queue<request_t *> q2;

    std::thread t_1(thread_1, req_cnt, n, m, cnt, std::ref(q1));
    std::thread t_2(thread_2, req_cnt, std::ref(q1), std::ref(q2));
    std::thread t_3(thread_3, req_cnt, std::ref(q2), std::ref(pool));

    t_1.join();
    t_2.join();
    t_3.join();

    print_pool(pool, "parallel.txt");
    for (size_t i = 0; i < pool.size(); ++i)
        delete pool[i];
}

int num = 1;
long long sum = 0;

void print_pool(std::vector<request_t *> &pool, const std::string &filename) {
    std::vector<pool_result_t> pool_sort(pool.size() * 6);
    timespec min = pool[0]->p1_start;
    for (size_t i = 0; i < pool.size(); ++i)
    {
        if (min.tv_sec > pool[i]->p1_start.tv_sec || (min.tv_sec == pool[i]->p1_start.tv_sec && min.tv_nsec > pool[i]->p1_start.tv_nsec))
            min = pool[i]->p1_start;
    }
    long long min_nano = min.tv_sec * 1000000000 + min.tv_nsec;
    for (size_t i = 0; i < pool.size(); ++i)
    {
        long long nanosec = pool[i]->p1_start.tv_sec * 1000000000 + pool[i]->p1_start.tv_nsec;
        nanosec -= min_nano;
        char *buf = new char[50];
        snprintf(buf, 50, "Request %lu start creating: %lld ns", i, nanosec);
        pool_sort[i * 6].message = std::string(buf);
        pool_sort[i * 6].nanosec = nanosec;

        nanosec = pool[i]->p1_end.tv_sec * 1000000000 + pool[i]->p1_end.tv_nsec;
        nanosec -= min_nano;
        buf = new char[50];
        snprintf(buf, 50, "Request %lu end creating: %lld ns", i, nanosec);
        pool_sort[i * 6 + 1].message = std::string(buf);
        pool_sort[i * 6 + 1].nanosec = nanosec;

        nanosec = pool[i]->p2_start.tv_sec * 1000000000 + pool[i]->p2_start.tv_nsec;
        nanosec -= min_nano;
        buf = new char[50];
        snprintf(buf, 50, "Request %lu start sum: %lld ns", i, nanosec);
        pool_sort[i * 6 + 2].message = std::string(buf);
        pool_sort[i * 6 + 2].nanosec = nanosec;

        nanosec = pool[i]->p2_end.tv_sec * 1000000000 + pool[i]->p2_end.tv_nsec;
        nanosec -= min_nano;
        buf = new char[50];
        snprintf(buf, 50, "Request %lu end sum: %lld ns", i, nanosec);
        pool_sort[i * 6 + 3].message = std::string(buf);
        pool_sort[i * 6 + 3].nanosec = nanosec;

        nanosec = pool[i]->p3_start.tv_sec * 1000000000 + pool[i]->p3_start.tv_nsec;
        nanosec -= min_nano;
        buf = new char[50];
        snprintf(buf, 50, "Request %lu start unpack: %lld ns", i, nanosec);
        pool_sort[i * 6 + 4].message = std::string(buf);
        pool_sort[i * 6 + 4].nanosec = nanosec;

        nanosec = pool[i]->p3_end.tv_sec * 1000000000 + pool[i]->p3_end.tv_nsec;
        nanosec -= min_nano;
        buf = new char[50];
        snprintf(buf, 50, "Request %lu end unpack: %lld ns", i, nanosec);
        pool_sort[i * 6 + 5].message = std::string(buf);
        pool_sort[i * 6 + 5].nanosec = nanosec;
    }
    std::sort(pool_sort.begin(), pool_sort.end());
    std::ofstream fout;
    fout.open(filename, std::ios_base::app);
    sum += pool_sort[pool_sort.size() - 1].nanosec;
    // printf("%s %lld\n", pool_sort[pool_sort.size() - 1].message.c_str(), pool_sort[pool_sort.size() - 1].nanosec);
    if (num % LOOPS == 0)
    {
        fout << sum / LOOPS << std::endl;
        sum = 0;
    }
    ++num;
    fout.close();
}