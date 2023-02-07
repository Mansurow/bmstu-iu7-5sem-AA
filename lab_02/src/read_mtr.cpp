#include "../inc/read_mtr.h"

int read_size(int &n)
{
    if (!(std::cin >> n) || n <= 0)
        return 1;
    return 0;
}

int read_mtr(matrix_v &mtr, std::string mode)
{
    int n, m;
    std::cout << "Ввод размер матрицы: ";
    if (read_size(n)) {
        std::cout << "Ошибка! Размер N введен неверно!" << std::endl;
        return 1;
    }
    if (mode == "square")
        m = n;
    else
        if (read_size(m)) {
            std::cout << "Ошибка! Размер M введен неверно!" << std::endl;
            return 1;
        }

    array_v row;
    row.resize(m, 0);
    mtr.resize(n, row);

    int rc = 0;
    std::cout << "Ввод элементов матрицы:\n";
    for (size_t i = 0; !rc && i < n; i++)
        for (size_t j = 0; !rc && j < m; j++)
            if (!(std::cin >> mtr[i][j])) {
                std::cout << "Ошибка! Элемент матрицы введен неверно!" << std::endl;
                rc = 1;
            }
    return rc;
}