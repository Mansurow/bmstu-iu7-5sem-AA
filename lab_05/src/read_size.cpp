#include "../inc/read_size.h"

int get_request_number()
{
    std::cout << "Введите количество заявок (больше 0): ";
    int n = 0;
    while (scanf("%d", &n) != 1 || n < 1)
        std::cout << "Повторите попытку: ";
    char ch = 1;
    while (ch != '\n')
        scanf("%c", &ch);
    return n;
}

int get_matrix_num()
{
    std::cout << "Введите количество элементов (больше 0): ";
    int n = 0;
    while (scanf("%d", &n) != 1 || n < 1)
        std::cout << "Повторите попытку: ";

    char ch = 1;
    while (ch != '\n')
        scanf("%c", &ch);
    return n;
}

int get_matrix_n()
{
    std::cout << "Введите количество строк n (больше 0): ";
    int n = 0;
    while (scanf("%d", &n) != 1 || n < 1)
        std::cout << "Повторите попытку: ";

    char ch = 1;
    while (ch != '\n')
        scanf("%c", &ch);
    return n;
}

int get_matrix_m()
{
    std::cout << "Введите количество столбцов m (больше 0): ";
    int n = 0;
    while (scanf("%d", &n) != 1 || n < 1)
        std::cout << "Повторите попытку: ";

    char ch = 1;
    while (ch != '\n')
        scanf("%c", &ch);
    return n;
}