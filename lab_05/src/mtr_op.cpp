#include "../inc/mtr_op.h"

void generate_mtr_csr(matrix_csr_t &a, size_t n, size_t m, size_t num_cnt) {
    int cnt = 0, prev = 0;
    a.n = n;
    a.m = m;

    for (size_t i = 0; i < n; i++) {
        srand(clock() % 1000000);
        int val = 0;
        for (size_t j = 0; cnt < num_cnt && j < m; j++) {
            if ((rand() % 15) - 5 > 0) {
                a.an.push_back(rand() % 10 + 1);
                a.ja.push_back(j);
                cnt++;
                val++;
            }
        }

        if (i == 0)
            a.nr.push_back(0);
        else if (val == 0) {
            if (prev == 0)
                a.nr.push_back(a.nr[i - 1]);
            else
                a.nr.push_back(a.nr[i - 1] + prev);
        }
        else
            a.nr.push_back(a.nr[i - 1] + prev);
        prev = val;
    }
    a.nr.push_back(a.nr[n - 1] + (a.an.size() - a.nr[n - 1]));
}

matrix_t decomprass(matrix_csr_t &a) {
    matrix_t mtr;
    mtr.m = a.m;
    mtr.n = a.n;

    for (int i = 0; i < a.n; i++ )
    {
        mtr.buff.emplace_back();
        for (int j = 0; j < a.m; j++ )
            mtr.buff.back().push_back(0);
    }

    int mtr_i = 0;
    for (int i = 0; i < a.n; i++) {
        for (int j = a.nr[i]; j < a.nr[i + 1]; j++)
            mtr.buff[mtr_i][a.ja[j]] = a.an[j];
        mtr_i++;
    }

    return mtr;
}

matrix_csr_t sum_mtr_csr(matrix_csr_t &a, matrix_csr_t &b) {
    matrix_csr_t c;
    c.n = a.n;
    c.m = b.n;

    int val = 0;
    for (int i = 0; i < a.nr.size() - 1; i++) {
        if (i == 0)
            c.nr.push_back(0);
        else
            c.nr.push_back(c.nr[i - 1] + val);
        val = 0;

        int ka = a.nr[i];
        int kb = b.nr[i];
        for (; ka < a.nr[i + 1] && kb < b.nr[i + 1];) {
            if (a.ja[ka] < b.ja[kb]) {
                c.ja.push_back(a.ja[ka]);
                c.an.push_back(a.an[ka++]);
            } else if (a.ja[ka] > b.ja[kb]) {
                c.ja.push_back(b.ja[kb]);
                c.an.push_back(b.an[kb++]);
            } else {
                c.ja.push_back(a.ja[ka]);
                c.an.push_back(a.an[ka++] + b.an[kb++]);
            }
            val++;
        }

        for (; ka < a.nr[i + 1]; ka++) {
            c.ja.push_back(a.ja[ka]);
            c.an.push_back(a.an[ka]);
            val++;
        }
        for (; kb < b.nr[i + 1]; kb++) {
            c.ja.push_back(b.ja[kb]);
            c.an.push_back(b.an[kb]);
            val++;
        }
    }
    c.nr.push_back(c.nr[c.nr.size() - 1] + (c.an.size() - c.nr[c.nr.size() - 1]));
    return c;
}

void print_vector(std::vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++)
        if (i == arr.size() - 1)
            std::cout << arr[i];
        else
            std::cout << arr[i] << ", ";
}

void print_mtr_csr(matrix_csr_t &a) {
    std::cout << "AN = [ ";
    print_vector(a.an);
    std::cout << " ]" << std::endl;
    std::cout << "JA = [ ";
    print_vector(a.ja);
    std::cout << " ]" << std::endl;
    std::cout << "NR = [ ";
    print_vector(a.nr);
    std::cout << " ]" << std::endl;
}

void print_mtr(matrix_t &mtr) {
    for (int i = 0; i < mtr.n; i++) {
        for (int j = 0; j < mtr.m; j++)
            std::cout << mtr.buff[i][j] << " ";
        std::cout << "\n";
    }
}


