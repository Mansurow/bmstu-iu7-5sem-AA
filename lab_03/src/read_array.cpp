#include "read_array.h"

int read_size(int &n) {
    std::cout << "Введите размер массива: ";
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "Ошибка! Размер массива это натуральное число!";
        return 1;
    }
    return 0;
}

int read_array(int **array, int &n)
{
    if (read_size(n))
        return 1;

    int rc = 0;
    *array = allocate_arr(n);
    if (*array == nullptr){
        std::cout << "Ошибка! Память не выделена под массива!";
        rc = 1;
    } else {
        std::cout << "Введите элементы массива:\n";
        for (int i = 0; !rc && i < n; i++)
            if (!(std::cin >> (*array)[i])) {
                std::cout << "Ошибка! Введено не число!";
                rc = 1;
            }
    }

    return rc;
}

int random_array(int **array, int &n) {
    if (read_size(n))
        return 1;

    int rc = 0;
    *array = allocate_arr(n);
    if (*array == nullptr){
        std::cout << "Ошибка! Память не выделена под массива!";
        rc = 1;
    } else
        generate_random_array(*array, n);
    return rc;
}