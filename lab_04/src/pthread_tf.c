#include "../inc/pthread_tf.h"

void *thread_work(void *args) {
    thread_args_t *targs = args;
    int start = targs->start_doc;
    int end = targs->end_doc;
    mtr_t *docs = targs->docs;
    cltn_t *cltn = targs->cltn;

    for (int thr = start; thr < end; thr++) {
        int word_cnt;
        cltn[thr].n = 0;
        for (int i = 0, k = 0; i < docs[thr].n; i++) {
            if (check_word_in_dict(cltn[thr].buff, docs[thr].buff[i], cltn[thr].n))
                continue;
            word_cnt = 1;
            for (int j = i + 1; j < docs[thr].n; j++) {
                if (strcmp(docs[thr].buff[i], docs[thr].buff[j]) == 0)
                    word_cnt++;
            }
            //mutex_lock
            strcpy(cltn[thr].buff[k].word, docs[thr].buff[i]);
            cltn[thr].buff[k].cnt = tf(word_cnt, docs[thr].n);
            cltn[thr].n++;
            //mutex_unlock
            k++;
        }
    }

    return NULL;
}

void parallel_find_cltn_tf(int threads, mtr_t *docs, cltn_t *cltn, size_t docs_cnt) {
    if (threads <= 0)
        return;

    pthread_t *tid = malloc(threads * sizeof(pthread_t));
    thread_args_t *args = malloc(threads * sizeof(thread_args_t));
    if (tid && args) {
        int delta_doc = docs_cnt / threads;
        int last = docs_cnt % threads;
        int start = 0;
        int end = delta_doc + last;
        for (int thr = 0; thr < threads; thr++) {
            (args + thr)->start_doc = start;
            (args + thr)->end_doc = end;
            (args + thr)->docs = docs;
            (args + thr)->cltn = cltn;
            pthread_create(tid + thr, NULL, &thread_work, args + thr);
            start = end;
            end += delta_doc;
        }
        for (int thread = 0; thread < threads; ++thread)
            pthread_join(tid[thread], NULL);
    }

    free(tid);
    free(args);
}