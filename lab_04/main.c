#include "inc/tf_alg.h"
#include "inc/pthread_tf.h"
#include "inc/time_measure.h"

#define DOCS_CNT 6

int main() {
    srand (time(NULL) );
    setbuf(stdout, NULL);

//    char docs[DOCS_CNT][TEXT_LEN] = {"hello world asas asas asa ", "Good Buy&",
//                                     "I am friend", "sdsasasdads asffaasf",
//                              "I am friesdsdssdend", "sdsasasdadssds asffaasf"};
//    mtr_t docs_split[DOCS_CNT];
//    cltn_t collection[DOCS_CNT];
//
//
//    for (int i = 0; i < DOCS_CNT; i++) {
//        docs_split[i] = split(docs[i], ",.!?:; ");
//        collection[i] = allocate_cltn(docs_split[i].n);
//    }
//
//    find_cltn_tf(docs_split, collection, DOCS_CNT);
//
//    parallel_find_cltn_tf(2, docs_split, collection, DOCS_CNT);
//
//    for (int i = 0; i < DOCS_CNT; i++) {
//        free_mtr(docs_split[i].buff, docs_split[i].n);
//        free_cltn(collection[i]);
//    }

    time_measure(7168, 8000, 1024);

    return 0;
}