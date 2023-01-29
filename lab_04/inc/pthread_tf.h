#ifndef PTHREAD_TF_H
#define PTHREAD_TF_H

#include "tf_alg.h"
#include <pthread.h>

typedef struct
{
    // id потока
    int start_doc;
    int end_doc;
    //pthread_mutex_t *mutex;
    mtr_t *docs; // указатель на строку на которой он работает
    cltn_t *cltn; // указатель на полученную коллекцию
} thread_args_t;

// код выполнения одного потока
void *thread_work(void *args);
// организация работы потоков
void parallel_find_cltn_tf(int threads, mtr_t *docs, cltn_t *cltn, size_t docs_cnt);

#endif //PTHREAD_TF_H
