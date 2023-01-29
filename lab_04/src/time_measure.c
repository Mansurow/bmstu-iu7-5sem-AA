#include "../inc/time_measure.h"

void time_measure(int start, int max_len, int step) {

    for (int stepi = start; stepi < max_len; stepi += step) {
        printf("DOC_CNT = %d\n", stepi);
        int n = stepi;
        char docs[n][TEXT_LEN];
        // рандомную генерацию....
        for (int i = 0; i < n; i++)
            strcpy(docs[i], "I am friend sdsasasdads asffaasf");

        mtr_t docs_split[n];
        cltn_t collection[n];
        for (int i = 0; i < n; i++) {
            docs_split[i] = split(docs[i], ",.!?:; ");
            collection[i] = allocate_cltn(docs_split[i].n);
        }

        long int l_total_t = 0, p_total_t = 0;
        struct timespec start_t, end_t;

        clock_gettime(CLOCK_REALTIME, &start_t);
        for (int i = 0; i < NUMBER_OPER; i++) {
            find_cltn_tf(docs_split, collection, n);
        }
        clock_gettime(CLOCK_REALTIME, &end_t);
        l_total_t =
                ((end_t.tv_sec - start_t.tv_sec) * 1000000000 + end_t.tv_nsec - start_t.tv_nsec) / NUMBER_OPER / 1000;

        clock_gettime(CLOCK_REALTIME, &start_t);
        for (int i = 0; i < NUMBER_OPER; i++) {
            parallel_find_cltn_tf(8, docs_split, collection, n);
        }
        clock_gettime(CLOCK_REALTIME, &end_t);
        p_total_t =
                ((end_t.tv_sec - start_t.tv_sec) * 1000000000 + end_t.tv_nsec - start_t.tv_nsec) / NUMBER_OPER / 1000;

        printf("  linel = %ld\n", l_total_t);
        printf("  parallel = %ld\n", p_total_t);

        for (int i = 0; i < n; i++) {
            free_mtr(docs_split[i].buff, docs_split[i].n);
            free_cltn(collection[i]);
        }
    }
}