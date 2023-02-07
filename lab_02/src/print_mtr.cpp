#include "../inc/print_mtr.h"

void print_mtr(matrix_v mtr)
{
    size_t n = mtr.size();
    if (n == 0)
        std::cout << "[]" << std::endl;
    else {
        size_t m = mtr[0].size();
        if (m == 0) {
            std::cout << "[";
            for (size_t i = 0; i < n; i++)
                if (i == n - 1)
                    std::cout << "[]";
                else
                    std::cout << "[],";
            std::cout << "]" << std::endl;
        }
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < m; j++) {
                std::cout << mtr[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
}