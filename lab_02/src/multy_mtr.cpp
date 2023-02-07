#include "../inc/multy_mtr.h"

matrix_v empty_matrix()
{
    matrix_v mtr;
    return mtr;
}

matrix_v standart_multy(const matrix_v &mtr1, const matrix_v &mtr2)
{
    if (mtr1[0].size() != mtr2.size())
        return empty_matrix();

    size_t n = mtr1.size();
    size_t m = mtr2.size();
    size_t t = mtr2[0].size();

    matrix_v res;

    array_v row;
    row.resize(t, 0);
    res.resize(n, row);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < t; j++)
            for (size_t k = 0; k < m; k++)
                res[i][j] += mtr1[i][k] * mtr2[k][j];

    return res;
}

matrix_v vinograd_alg(const matrix_v &mtr1, const matrix_v &mtr2)
{
    if (mtr1[0].size() != mtr2.size())
        return empty_matrix();

    size_t n = mtr1.size();
    size_t m = mtr2.size();
    size_t t = mtr2[0].size();
    matrix_v res;
    array_v rowSum, colSum;
    rowSum.resize(n, 0);
    colSum.resize(m, 0);
    res.resize(n, rowSum);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m / 2; j++)
            rowSum[i] = rowSum[i] + mtr1[i][2 * j] * mtr1[i][2 * j + 1];
    for (size_t i = 0; i < t; i++)
        for (size_t j = 0; j < m / 2; j++)
            colSum[i] = colSum[i] + mtr2[2 * j][i] * mtr2[2 * j + 1][i];
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < t; j++) {
            res[i][j] = -rowSum[i] - colSum[j];
            for (size_t k = 0; k < m / 2; k++)
                res[i][j] = res[i][j] + (mtr1[i][2 * k + 1] + mtr2[2 * k][j]) * (mtr1[i][2 * k] + mtr2[2 * k + 1][j]);
        }

    if (m % 2 == 1)
        for(size_t i = 0; i < n; i++)
            for(size_t j = 0; j < t; j++)
                res[i][j] = res[i][j] + mtr1[i][m - 1] * mtr2[m - 1][j];
    return res;
}

matrix_v opt_vinograd_alg(const matrix_v &mtr1, const matrix_v &mtr2)
{
    if (mtr1[0].size() != mtr2.size())
        return empty_matrix();

    size_t n = mtr1.size();
    size_t m = mtr2.size();
    size_t t = mtr2[0].size();
    size_t halfm = m / 2;
    matrix_v res;
    array_v rowSum, colSum;
    rowSum.resize(n, 0);
    colSum.resize(m, 0);
    res.resize(n, rowSum);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < halfm; j++)
            rowSum[i] += mtr1[i][j << 1] * mtr1[i][(j << 1) + 1];
    for (size_t i = 0; i < t; i++)
        for (size_t j = 0; j < halfm; j++)
            colSum[i] += mtr2[(j << 1)][i] * mtr2[(j << 1) + 1][i];
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < t; j++) {
            res[i][j] = -rowSum[i] - colSum[j];
            for (size_t k = 0; k < halfm; k++)
                res[i][j] += (mtr1[i][(k << 1) + 1] + mtr2[k << 1][j]) * (mtr1[i][k << 1] + mtr2[(k << 1) + 1][j]);
        }

    if (m % 2 == 1)
        for(size_t i = 0; i < n; i++)
            for(size_t j = 0; j < t; j++)
                res[i][j] += mtr1[i][m - 1] * mtr2[m - 1][j];
    return res;
}