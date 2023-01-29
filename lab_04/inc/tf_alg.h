#ifndef TF_ALG_H
#define TF_ALG_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORD_LEN 256
#define TEXT_LEN 256

// документ - файл или строка
// tf - терм частота
// структура для строки разделенной по словам --- матрица слов
typedef struct {
    char **buff;
    size_t n; // количесвто слов
    size_t m; // длина слова
} mtr_t;

// структура словаря
typedef struct {
    char *word;
    double cnt;
} map;

// структура результат tf коллекции
typedef struct {
    map *buff;
    size_t n;
} cltn_t;

// memory
cltn_t allocate_cltn(size_t n);
void free_cltn(cltn_t cltn);
char ** allocate_mtr(size_t n, size_t m);
void free_mtr(char **mtr, size_t n);

// раздление текста на слова
mtr_t split(char *str, char *delim);
// подсчет количество слов в документе
int get_cnt_words(const char *str);
// проверка на одно вхождение в словарь
int check_word_in_dict(const map *words, const char *find, size_t cnt);
// подсчет каждого слова и его tf
void couting_words(cltn_t *dict, const mtr_t *words);
// рассчет коэффицента tf
double tf(int find_word_cnt, int words_cnt);
void find_cltn_tf(mtr_t *docs, cltn_t *cltn, size_t docs_cnt);

#endif //TF_ALG_H
