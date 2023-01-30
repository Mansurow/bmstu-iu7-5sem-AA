#include <stdio.h>
#include "inc/tf_alg.h"
#include "inc/pthread_tf.h"
#include "inc/time_measure.h"

#define DOCS_CNT 6
#define OUT_CNT 5

int main() {
    srand (time(NULL) );
    setbuf(stdout, NULL);

    char docs[DOCS_CNT][TEXT_LEN] = {"hello world asas asas asa ", "Good Buy&",
                                     "I am friend", "sdsasasdads asffaasf",
                              "I am friesdsdssdend", "sdsasasdadssds asffaasf"};
    mtr_t docs_split[DOCS_CNT];
    cltn_t collection[DOCS_CNT];

    char *menu = "--------- Menu --------------\n"
                 "Алгоритм выделенение терминов документа на основе TF\n"
                 "1) Однопоточная реализация\n"
                 "2) Многопоточная реализация\n"
                 "3) Замеры вермени\n";

    int choice = -1;
    int n = 0, rc = 0;


    for (int i = 0; i < DOCS_CNT; i++) {
        docs_split[i] = split(docs[i], ",.!?:; ");
        collection[i] = allocate_cltn(docs_split[i].n);
    }


    while (choice != 0) {
        printf("%s", menu);
        printf("Выбор: ");
        scanf("%u", &choice);
        if (choice == 1) {
            find_cltn_tf(docs_split, collection, DOCS_CNT);
            printf_cltn(collection, OUT_CNT, DOCS_CNT);
        }
        else if (choice == 2) {
            printf("Количество потоков: ");
            scanf("%d", &n);
            parallel_find_cltn_tf(n, docs_split, collection, DOCS_CNT);
            printf_cltn(collection, OUT_CNT, DOCS_CNT);
        } else if (choice == 3)
            time_measure(512, 7000, 512);
    }

    for (int i = 0; i < DOCS_CNT; i++) {
        free_mtr(docs_split[i].buff, docs_split[i].n);
        free_cltn(collection[i]);
    }

    return 0;
}