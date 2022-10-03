#include "print_mtr_lev.h"

void print_mtr_lev(std::wstring str1, std::wstring str2,
                   int **mtr, std::size_t n, std::size_t m)
{
    for(std::size_t i = 0; i <= n + 1; i++)
    {
        for(std::size_t j = 0; j <= m + 1; j++)
        {
            if (i == 0 && j == 0)
                std::wcout << "  ";
            else if (i == 0)
                if (j == 1)
                    std::wcout << "- ";
                else
                    std::wcout << str2[j - 2] << " ";
            else if (j == 0)
                if (i == 1)
                    std::wcout << "- ";
                else
                    std::wcout << str1[i - 2] << " ";
            else
                std::wcout << mtr[i - 1][j - 1] << " ";
        }
        std::wcout << std::endl;
    }
}