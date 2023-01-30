#include "../inc/tf_alg.h"

char ** allocate_mtr(size_t n, size_t m) {
    char **mtr = NULL;
    mtr = malloc(n * sizeof(char *));
    if (mtr != NULL) {
        for (size_t i = 0; i < n ; i++) {
            mtr[i] = malloc(m * sizeof (char));
            if (mtr[i] == NULL) {
                free_mtr(mtr, n);
                return NULL;
            }
        }
    }
    return mtr;
}
void free_mtr(char **mtr, size_t n) {
    if (mtr != NULL) {
        for (size_t i = 0; i < n; i++)
            if (mtr[i] != NULL)
                free(mtr[i]);
        free(mtr);
    }
}

cltn_t allocate_cltn(size_t n) {
    cltn_t tmp;
    tmp.buff = malloc(n * sizeof(cltn_t));
    if (tmp.buff != NULL) {
        for (int i = 0; i < n; i++) {
            tmp.buff[i].word = malloc(WORD_LEN * sizeof(char));
            if (tmp.buff[i].word == NULL) {
                free_cltn(tmp);
                tmp.buff = NULL;
                break;
            }
        }
    }

    return tmp;
}
void free_cltn(cltn_t cltn) {
    if (cltn.buff != NULL) {
        for (size_t i = 0; i < cltn.n; i++)
            if (cltn.buff[i].word != NULL)
                free(cltn.buff[i].word);
        free(cltn.buff);
    }
}


int get_cnt_words(const char *str) {
    int words_cnt = 0, flag = 0;
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] != ' ' && flag == 0) {
            flag = 1;
            words_cnt++;
        } else if (str[i] == ' ') {
            flag = 0;
        }
        i++;
    }
    return words_cnt;
}

mtr_t split(char *str, char *delim) {
    int words_cnt = get_cnt_words(str);
    mtr_t words;
    words.buff = allocate_mtr(words_cnt, 256);
    words.n = words_cnt;
    words.m = 256;

    char *word = strtok(str, delim);
    int i = 0;
    while (word != NULL) {
        strcpy(words.buff[i], word);
        word = strtok(NULL, delim);
        i++;
    }

    return words;
}

int check_word_in_dict(const map *words, const char *find, size_t cnt) {
    if (cnt <= 0)
        return 0;

    for (int i = 0; i < cnt; i++) {
        if (strcmp(find, words[i].word) == 0)
            return 1;
    }
    return 0;
}

double tf(int find_word_cnt, int words_cnt) {
    return (double) find_word_cnt / words_cnt;
}

void couting_words(cltn_t *cltn, const mtr_t *doc) {
    cltn->n = 0;
    int word_cnt;
    for (int i = 0, k = 0; i < doc->n; i++) {
        if (check_word_in_dict(cltn->buff, doc->buff[i], cltn->n))
            continue;
        word_cnt = 1;
        for (int j = i + 1; j < doc->n; j++)
            if (strcmp(doc->buff[i], doc->buff[j]) == 0)
                word_cnt++;

        strcpy(cltn->buff[k].word, doc->buff[i]);
        cltn->buff[k].cnt = tf(word_cnt, doc->n);
        cltn->n++;
        k++;
    }
}

void find_cltn_tf(mtr_t *docs, cltn_t *cltn, size_t docs_cnt) {
    for (int i = 0; i < docs_cnt; i++)
        couting_words(&cltn[i], &docs[i]);
}

void printf_cltn(const cltn_t *cltn, size_t out_cnt, size_t docs_cnt) {

    for (int doc_i = 0; doc_i < docs_cnt; doc_i++) {
        printf("Document %d:\n", doc_i + 1);
        for (int j = 0; j < cltn[doc_i].n; j++) {
//            int maxi = 0;
//            double max = cltn[doc_i].buff[j].cnt;
//            for (int i = 0; i < cltn[doc_i].n; ++i) {
//                if (cltn[doc_i].buff[i].cnt > max) {
//                    max = cltn[doc_i].buff[i].cnt;
//                    maxi = i;
//                }
//            }
            printf("   %s: %.2f\n", cltn[doc_i].buff[j].word, cltn[doc_i].buff[j].cnt);
        }
    }
}

//void copy_str(char *dest, const char *src) {
//    int i = 0;
//    while (src[i] != '\0') {
//        dest[i] = src[i];
//        i++;
//    }
//    dest[i] = '\0';
//}
