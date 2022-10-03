#include "cpu_time.h"

std::wstring gen_random(const size_t len) {
    std::wstring al = L"0123456789"
                      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                      "abcdefghijklmnopqrstuvwxyz"
                      "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                      "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    std::wstring tmp_s = L"";
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += al[rand() % (al.length() - 1)];
    }

    return tmp_s;
}

static long getThreadCpuTimeNs() {
    struct timespec t;
    if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t)) {
        perror("clock_gettime");
        return 0;
    }
    return t.tv_sec * 1000000000LL + t.tv_nsec;
}

double get_cpu_time(int (*find_distance)(std::wstring &, std::wstring &), std::wstring &str1, std::wstring &str2)
{
    clock_t start_t, end_t;
    double total_t;

    start_t = getThreadCpuTimeNs();
    find_distance(str1, str2);
    end_t = getThreadCpuTimeNs();
    std::cout << end_t << std::endl;
    total_t = (double) (end_t - start_t) / CLOCKS_PER_SEC;
    return total_t;
}

double get_cpu_time(int (*find_distance)(std::wstring &, std::wstring &, bool), std::wstring &str1, std::wstring &str2)
{
    clock_t start_t, end_t;
    double total_t;

    start_t = getThreadCpuTimeNs();
    find_distance(str1, str2, false);
    end_t = getThreadCpuTimeNs();
    std::cout << end_t << std::endl;
    total_t = (double) (end_t - start_t) / CLOCKS_PER_SEC;
    return total_t;
}

void measuring_time(std::size_t max_len_str, std::size_t max_count_oper)
{
    std::wstring word1, word2;
    double time_l, time_dl, time_dl_rec, time_dl_rec_hash;

    std::wcout << L"+--------------------------------------------------------------+\n";
    std::wcout << L"| Длина |                      Время(нс)                       |\n";
    std::wcout << L"|       |  Левенштейн   |          Дамерау-Левенштейн          |\n";
    std::wcout << L"|       | Нерекурсивный | Нерекурсивный |     Рекурсивный      |\n";
    std::wcout << L"|       |               |               | Без кэша |  С кэшом  |\n";
    std::wcout << L"+==============================================================+\n";
    for(size_t i = 0; i < max_len_str; )
    {
        if (i < 10)
            i++;
        else if (i < 100)
            i += 10;
        else
            i += 100;

        time_l = 0;
        time_dl = 0;
        time_dl_rec = 0;
        time_dl_rec_hash = 0;
        word1 = gen_random(i);
        word2 = gen_random(i);
        for(size_t j = 0; j <= max_count_oper; j++) {
            time_l += get_cpu_time(lev_mtr, word1, word2);
            time_dl += get_cpu_time(dameray_lev_mtr, word1, word2);
            if (i < 20) {
                time_dl_rec += get_cpu_time(dameray_lev_rec, word1, word2);
                time_dl_rec_hash += get_cpu_time(dameray_lev_rec_hash, word1, word2);
            }
        }
        time_l /= (max_count_oper - 2);
        time_dl /= (max_count_oper - 2);
        if (i < 20) {
            time_dl_rec /= (max_count_oper - 2);
            time_dl_rec_hash /= (max_count_oper - 2);
            std::wprintf(L"| %5d | %13.5g | %13.5g | %8.5g |  %8.5g |\n",
                          i, time_l,time_dl, time_dl_rec, time_dl_rec_hash);
        }
        else
            std::wprintf(L"| %5d | %13.5g | %13.5g | %8s |  %8s |\n",
                          i, time_l, time_dl, "-", "-");

    }
    std::wcout << L"+--------------------------------------------------------------+\n";
}