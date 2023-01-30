#include "../inc/time_measure.h"

void random_text(char *str, size_t len) {
    int i;
    //char s[N];
    for (i = 0; i < len - 1; i++)
        if (rand() % 5)
            str[i] = 'a' + rand() % 26;
        else
            str[i] = ' ';

    str[i] = '\0';
    //puts(s);
}

int time_measure(int start, int max_len, int step) {
    FILE *f = fopen("times.csv", "w");
    if (!f)
    {
        printf("Couldn't open file\n");
        return 1;
    }
    fprintf(f, "docs,0,1,2,4,6,8,16,32,64\n");
    for (int stepi = start; stepi < max_len; stepi += step) {
        printf("DOC_CNT = %d\n", stepi);
        int n = stepi;
        char docs[n][TEXT_LEN];
        for (int i = 0; i < n; i++)
            random_text(docs[i], 64);
            //strcpy(docs[i], "I am friend sdsasasdads asffaasf");

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
        printf("---linel = %ld\n", l_total_t);
        fprintf(f, "%d,%ld", n, l_total_t);
        for (int cnt_thr = 1; cnt_thr <= 64; ) {
            clock_gettime(CLOCK_REALTIME, &start_t);
            for (int i = 0; i < NUMBER_OPER; i++) {
                parallel_find_cltn_tf(8, docs_split, collection, n);
            }
            clock_gettime(CLOCK_REALTIME, &end_t);
            p_total_t =
                    ((end_t.tv_sec - start_t.tv_sec) * 1000000000 + end_t.tv_nsec - start_t.tv_nsec) / NUMBER_OPER / 1000;
            printf("---parallel %d = %ld\n", cnt_thr, p_total_t);
            fprintf(f, ",%ld",  p_total_t);
            if (cnt_thr == 1)
                cnt_thr++;
            else if (cnt_thr < 8)
                cnt_thr += 2;
            else
                cnt_thr *= 2;
        }
        fprintf(f, "\n");
        for (int i = 0; i < n; i++) {
            free_mtr(docs_split[i].buff, docs_split[i].n);
            free_cltn(collection[i]);
        }
    }
    fclose(f);
}