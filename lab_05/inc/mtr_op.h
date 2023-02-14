#ifndef MTR_OP_H
#define MTR_OP_H

# include <iostream>
# include <vector>
# include <memory>
# include <string>

// структура РСФ - разреженный строчный формат матрицы
struct matrix_csr_t
{
    //matrix_csr_t(int n, int m, int cnt): an(cnt), ja(cnt), nr(n + 1) {};
    std::vector<int> an; // элементы
    std::vector<int> ja; // номер соотвествующего столбца для элемента
    std::vector<int> nr; // номер элемента в an начала следующей строки - размер N + 1, N - количество строк

    size_t n;
    size_t m;
};

// стурктура простой матрицы
struct matrix_t
{
    //matrix_t() : buff(n, std::vector<int>(m)) {};
    std::vector<std::vector<int>> buff;
    size_t n;
    size_t m;
};

void generate_mtr_csr(matrix_csr_t &a, size_t n, size_t m, size_t num_cnt);
matrix_csr_t sum_mtr_csr(matrix_csr_t &a, matrix_csr_t &b);
matrix_t decomprass(matrix_csr_t &a);

void print_mtr(matrix_t &mtr);
void print_vector(std::vector<int> &arr);
void print_mtr_csr(matrix_csr_t &a);

#endif //MTR_OP_H
