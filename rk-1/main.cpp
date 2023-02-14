# include <iostream>
# include <vector>
# include <memory>
# include <string>

// структура РСФ - разреженный строчный формат матрицы
struct matrix_csr_t
{
    //matrix_csr_t(int n, int m, int cnt): an(cnt), ja(cnt), nr(n + 1) {};
    std::vector<int> an; // элементы
    std::vector<int> ja; // номер соотвествующего столбца для элемента
    std::vector<int> nr; // номер элемента в an начала следующей строки - размер N + 1, N - количество строк

    size_t n;
    size_t m;
};


int get_number(char *str, int min, int max)
{
    std::cout << str;
    int n = 0;
    while (scanf("%d", &n) != 1 || min > n || n > max)
        std::cout << "Повторите попытку: ";

    char ch = 1;
    while (ch != '\n')
        scanf("%c", &ch);
    return n;
}

int read_mtr_csr_t(matrix_csr_t &mtr) {
    int bf, val;
    std::cout << "Введите элементы матрицы:\n";
    for (size_t i = 0; i < mtr.n; i++) {
        if (i == 0)
            mtr.nr.push_back(0);
        else
            mtr.nr.push_back(mtr.nr[i - 1] + val);
        val = 0;

        for (size_t j = 0; j < mtr.m; j++)
            if (scanf("%d", &bf) == 1 && bf != 0) {
                mtr.an.push_back(bf);
                mtr.ja.push_back(j);
                val++;
            }
    }
    mtr.nr.push_back(mtr.nr[mtr.nr.size() - 1] + (mtr.an.size() - mtr.nr[mtr.nr.size() - 1]));
    return 0;
}

void print_vector(std::vector<int> &arr, int plus) {
    for (int i = 0; i < arr.size(); i++)
        if (i == arr.size() - 1)
            std::cout << arr[i] + plus;
        else
            std::cout << arr[i] + plus << ", ";
}

void print_mtr_csr(matrix_csr_t &a) {
    std::cout << "AN = [ ";
    print_vector(a.an, 0);
    std::cout << " ]" << std::endl;
    std::cout << "JA = [ ";
    print_vector(a.ja, 1);
    std::cout << " ]" << std::endl;
    std::cout << "NR = [ ";
    print_vector(a.nr, 1);
    std::cout << " ]" << std::endl;
}

int main() {
    setbuf(stdout, nullptr);
    matrix_csr_t mtr;

    mtr.n = get_number("Введите количество строк n (больше 0): ", 0, 1000);
    mtr.m = get_number("Введите количество столбцов m (больше 0): ", 0, 1000);
    read_mtr_csr_t(mtr);
    print_mtr_csr(mtr);

    if (mtr.an.empty()) {
        printf("Матрица полностью состоит из нулей.\n");
        return 0;
    }


    int find = 0, f_i = 0;
    int c = get_number("Введите индекс элемента (больше 0): ", 0, mtr.an.size()) - 1;
    for (int i = 0; !find && i < mtr.nr.size() - 1; i ++) {
        printf("В %d строке %d элемента(ов). NR[%d] - NR[%d] = %d", i + 1, mtr.nr[i + 1] - mtr.nr[i], i + 2, i + 1,
               mtr.nr[i + 1] - mtr.nr[i]);
        if (mtr.nr[i] == mtr.nr[i + 1])
            printf(" -> переходим к следующей строке.\n");
        else {
            printf(".\n");
            if (mtr.nr[i] <= c && c < mtr.nr[i + 1]) {
                printf("\tAN[%d] = %d находится в %d строке\n", c + 1, mtr.an[c], i + 1);
                find = 1;
                f_i = i;
            } else {
                printf("\tAN[%d] = %d нет в %d строке -> переходим к следующей строке.\n", c + 1, mtr.an[c], i + 1);
            }
        }
//        printf("\nНажмите пробел для следующего шага.");
//        char ch = 1;
//        while (ch != '\n')
//            scanf("%c", &ch);
    }
    printf("Строчной координатой элемента AN[%d] равна %d.\n", c + 1, f_i + 1);
    return 0;
}
