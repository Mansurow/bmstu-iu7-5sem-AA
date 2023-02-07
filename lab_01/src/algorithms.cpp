#include "../inc/algorithms.h"
#include "../inc/print_mtr_lev.h"

int lev_mtr(wstring &str1, wstring &str2, bool print)
{
    size_t n = str1.length();
    size_t m = str2.length();
    int **mtr = malloc_mtr(n + 1, m + 1);
    int res = 0;

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            if (i == 0 && j == 0)
                mtr[i][j] = 0;
            else if (i > 0 && j == 0)
                mtr[i][j] = i;
            else if (j > 0 && i == 0)
                mtr[i][j] = j;
            else {
                int change = 0;
                if (str1[i - 1] != str2[j - 1])
                    change = 1;

                mtr[i][j] = std::min(mtr[i][j - 1] + 1,
                                     std::min(mtr[i - 1][j] + 1,
                                              mtr[i - 1][j - 1] + change));
            }

    if (print)
        print_mtr_lev(str1, str2, mtr, n, m);

    res = mtr[n][m];
    free_mtr(mtr, n);

    return res;
}

int dameray_lev_mtr(wstring &str1, wstring &str2, bool print)
{
    size_t n = str1.length();
    size_t m = str2.length();
    int **mtr = malloc_mtr(n + 1, m + 1);
    int res = 0;

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++) {
            if (i == 0 && j == 0)
                mtr[i][j] = 0;
            else if (i > 0 && j == 0)
                mtr[i][j] = i;
            else if (j > 0 && i == 0)
                mtr[i][j] = j;
            else {
                int change = 0;
                if (str1[i - 1] != str2[j - 1])
                    change = 1;

                mtr[i][j] = min(mtr[i][j - 1] + 1,
                                min(mtr[i - 1][j] + 1,
                                    mtr[i - 1][j - 1] + change));

                if (i > 1 && j > 1 &&
                    str1[i - 1] == str2[j - 2] &&
                    str1[i - 2] == str2[j - 1])
                    mtr[i][j] = min(mtr[i][j], mtr[i - 2][j - 2] + 1);
            }
        }

    if (print)
        print_mtr_lev(str1, str2, mtr, n, m);

    res = mtr[n][m];
    free_mtr(mtr, n);

    return res;
}

int dameray_lev_rec_t(wstring &str1, wstring &str2, size_t n, size_t m) {

    if (n == 0)
        return m;
    if (m == 0)
        return n;

    int change = 0;
    int res = 0;
    if (str1[n - 1] != str2[m - 1])
        change = 1;

    res = min(dameray_lev_rec_t(str1, str2, n, m - 1) + 1,
              min(dameray_lev_rec_t(str1, str2, n - 1, m) + 1,
                  dameray_lev_rec_t(str1, str2, n - 1, m - 1) + change));

    if (n > 1 && m > 1 &&
        str1[n - 1] == str2[m - 2] &&
        str1[n - 2] == str2[m - 1])
        res = std::min(res, dameray_lev_rec_t(str1, str2, n - 2, m - 2) + 1);
    return res;
}

int dameray_lev_rec(wstring &str1, wstring &str2)
{
    return dameray_lev_rec_t(str1, str2, str1.length(), str2.length());
}

int dameray_lev_rec_hash_t(wstring &str1, wstring &str2, int **mtr, size_t n, size_t m)
{
    if (n == 0)
        return mtr[n][m] = m;
    if (m == 0)
        return mtr[n][m] = n;

    int change = 0;
    if (str1[n - 1] != str2[m - 1])
        change = 1;


    mtr[n][m] = min(dameray_lev_rec_hash_t(str1, str2, mtr, n, m - 1) + 1,
                    min(dameray_lev_rec_hash_t(str1, str2, mtr, n - 1, m) + 1,
                        dameray_lev_rec_hash_t(str1, str2, mtr, n - 1, m - 1) + change));

    if (n > 1 && m > 1 &&
        str1[n - 1] == str2[m - 2] &&
        str1[n - 2] == str2[m - 1])
        mtr[n][m] = min(mtr[n][m], dameray_lev_rec_hash_t(str1, str2, mtr, n - 2, m - 2) + 1);

    return mtr[n][m];
}

int dameray_lev_rec_hash(wstring &str1, wstring &str2, bool print)
{
    size_t n = str1.length();
    size_t m = str2.length();

    int **mtr = malloc_mtr(n + 1, m + 1);

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++) {
                mtr[i][j] = -1;
        }
    int res = dameray_lev_rec_hash_t(str1, str2, mtr, n, m);

    if (print)
        print_mtr_lev(str1, str2, mtr, n, m);

    free_mtr(mtr, n);

    return res;
}


