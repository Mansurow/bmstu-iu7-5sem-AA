#include "memory.h"

std::size_t get_size_lev_mtr(std::size_t len) {
    return (len + 1) * (len + 1) * sizeof(int) +
           2 * sizeof(std::wstring) +
           2 * sizeof(std::size_t) +
           2 * sizeof(int) +
           sizeof(int **) + (len + 1) * sizeof(int *);
}

std::size_t get_size_dl_mtr(std::size_t len) {
    return (len + 1) * (len + 1) * sizeof(int) +
           2 * sizeof(std::wstring) +
           2 * sizeof(std::size_t) +
           3 * sizeof(int) +
           sizeof(int **) + (len + 1) * sizeof(int *);
}

std::size_t get_size_dl_rec(std::size_t len) {
    return (len + len) * (2 * sizeof(std::size_t) + 3 * sizeof(int) + 2 * sizeof(std::wstring));
}

std::size_t get_size_dl_rec_cash(std::size_t len) {
    return get_size_dl_rec(len) +
           (len + 1) * (len + 1) * sizeof(int) +
           sizeof(int **) + (len + 1) * sizeof(int *);
}

void measuring_memory(std::size_t max_len, std::size_t step)
{
    std::wcout << L"+--------------------------------------------------------------+\n";
    std::wcout << L"| Длина |                      Размер (байтах)                 |\n";
    std::wcout << L"|(символ)|  Левенштейн  |          Дамерау-Левенштейн          |\n";
    std::wcout << L"|       | Нерекурсивный | Нерекурсивный |     Рекурсивный      |\n";
    std::wcout << L"|       |               |               | Без кэша |  С кэшом  |\n";
    std::wcout << L"+==============================================================+\n";
    for (size_t i = 0; i <= max_len; i += step)
    {
        if (i == 0)
            continue;

        std::wprintf(L"| %5zu | %13zu | %13zu | %8zu | %9zu |\n",
                     i,
                     get_size_lev_mtr(i),
                     get_size_dl_mtr(i),
                     get_size_dl_rec(i),
                     get_size_dl_rec_cash(i));
    }
    std::wcout << L"+--------------------------------------------------------------+\n";
}
