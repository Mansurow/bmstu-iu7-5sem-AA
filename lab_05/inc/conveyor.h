#ifndef CONV_H
#define CONV_H

#include <queue>
#include <pthread.h>
#include <thread>
#include <mutex>
#include <algorithm>
#include <string>
#include <ctime>
#include <fstream>

#include "../inc/mtr_op.h"
#include "../inc/read_size.h"

struct request_t {
    matrix_csr_t mtr_a;
    matrix_csr_t mtr_b;
    matrix_csr_t mtr_c;
    matrix_t result;

    timespec p1_start;
    timespec p1_end;
    timespec p2_start;
    timespec p2_end;
    timespec p3_start;
    timespec p3_end;
};

# define MAX_REQUEST 100
# define MATRIX_SIZE 10
# define LOOPS 100

struct pool_result_t
{
public:
    pool_result_t()=default;
    bool operator < (const pool_result_t &other) const
    {
        return this->nanosec < other.nanosec;
    }

    pool_result_t &operator = (const pool_result_t &other)
    {
        this->message = other.message;
        this->nanosec = other.nanosec;
        return *this;
    }

    long long nanosec;
    std::string message;
};

void pack_data(size_t n, size_t m, size_t cnt, request_t *r);

void linear();
void parallel();

void thread_1(size_t req_cnt, size_t n, size_t m, size_t cnt, std::queue<request_t *> &q1);
void thread_2(int req_cnt, std::queue<request_t *> &q1, std::queue<request_t *> &q2);
void thread_3(int req_cnt, std::queue<request_t *> &q2, std::vector<request_t *> &pool);

void print_pool(std::vector<request_t *> &pool, const std::string &filename);

#endif //CONV_H
