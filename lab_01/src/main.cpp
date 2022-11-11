#include <iostream>
#include <io.h>
#include <fcntl.h>

#include "algorithms.h"
#include "cpu_time.h"
#include "memory.h"

#define MAX_LEN 200
#define STEP 10
#define MAX_ITEP 1000

int main() {
    setbuf(stdout, nullptr);

    _setmode(_fileno(stdout), _O_U8TEXT);
    _setmode(_fileno(stdin), _O_U8TEXT);

    wcout  << L"   Выберите алгоритм поиска растояния: \n"
             "1 - 1) Нерекурсивный алгоритм Левенштейна; \n"
             "  - 2) Нерекурсивный алгоритм Дамерау-Левенштейна; \n"
             "  - 3) Рекурсивный алгоритм Дамерау-Левенштейна без кэша; \n"
             "  - 4) Рекурсивный алгоритм Дамерау-Левенштейна с кэшом;\n"
             "2 - Замерить время и память.\n"
             "0 - Выход\n" << endl;


    int choice = -1;
    wstring word1 = L"кот";
    wstring word2 = L"скат";
    int res = 0;

    while (choice != 0) {
        wcout << L"Выбор: ";
        wcin >> choice;

        if (choice == 1) {
            wcout << L"Введите первое слово: ";
            wcin >> word1;
            wcout << L"Введите второе слово: ";
            wcin >> word2;

            wcout << L"Минимальное количество операций: " << endl;
            res = lev_mtr(word1, word2, true);
            wcout << L"   Нерекурсивный алгоритм Левенштейна: " << res << endl;
            res = dameray_lev_mtr(word1, word2, true);
            wcout << L"   Нерекурсивный алгоритм Дамерау-Левенштейна: " << res << endl;
            res = dameray_lev_rec(word1, word2);
            wcout << L"   Рекурсивный алгоритм Дамерау-Левенштейна без кэша: " << res << endl;
            res = dameray_lev_rec_hash(word1, word2, true);
            wcout << L"   Рекурсивный алгоритм Дамерау-Левенштейна с кэшом: " << res << endl;
        }
        else if (choice == 2) {
            measuring_time( MAX_LEN, MAX_ITEP);
            measuring_memory(MAX_LEN, STEP);
        }
    }
    return 0;
}
