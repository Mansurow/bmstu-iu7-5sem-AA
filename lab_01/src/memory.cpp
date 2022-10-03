#include "memory.h"

std::size_t get_size_lev_mtr(std::size_t len) {
    return len * len * sizeof(int) + 3 * sizeof(int) + 2 * sizeof(std::wstring);
}

std::size_t get_size_lev_rec(std::size_t len) {
    return (len + len) * (5 * sizeof(int) + 2 * sizeof(std::wstring));
}

void measuring_memory(std::size_t max_len, std::size_t step)
{
    std::wcout << L"+--------------Память-------------+\n";
    std::fwprintf(stdout,L"| Длина |  Нерек.(б) |   Рек.(б)  |\n", 2, 3);
    std::wcout << L"+---------------------------------+\n";
    for (int i = 0; i <= max_len; i += step)
    {
        if (i == 0)
            continue;
        std::fwprintf(stdout,L"| %5d | %10d | %10d |\n",
                      i,
                      get_size_lev_mtr(i),
                      get_size_lev_rec(i));
    }
    std::wcout << L"+---------------------------------+\n";
}
