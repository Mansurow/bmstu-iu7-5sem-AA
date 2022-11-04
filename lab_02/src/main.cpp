#include <iostream>
#include "read_mtr.h"
#include "multy_mtr.h"
#include "print_mtr.h"
#include "cpu_time.h"

int main() {
    setbuf(stdout, NULL);

    int rc = 0;
    int choose = -1, start, max_len, step;

    std::string mode = "normal";
    std::string menu = "--------------- Menu --------------\n"
                       "1 - Классический алгоритм умножения матриц\n"
                       "2 - Алгоритм Винограда\n"
                       "3 - Оптимизированный алгоритм Винограда\n"
                       "4 - Все алгоритмы вместе\n"
                       "5 - Замерить время\n"
                       "0 - Выход\n";

    while (choose != 0) {
        matrix_v mtr1, mtr2, res;
        std::cout << menu;
        std::cout << "Выбор: ";
        if (!(std::cin >> choose) || choose < 0 || choose > 5)
            std::cout << "Ошибка! Неверно ввод! Нужно вести число от 0-5!\n";

        if (choose > 0 && choose < 5)
        {
            if (choose == 2 ||choose == 3)
                mode = "square";

            std::cout << "Ввод матрицы A:\n";
            if (!read_mtr(mtr1, mode)) {
                std::cout << "Ввод матрицы B:\n";
                if(read_mtr(mtr2, mode))
                    std::cout << "Ошибка! Матрица B неверна введена!\n";
            } else
                std::cout << "Ошибка! Матрица A неверна введена!\n";

            if (mtr1[0].size() != mtr2.size()) {
                std::cout << "Ошибка! Умножения матриц невозможно при таких размерах!\n";
                continue;
            }

            if (choose == 1)
                res = standart_multy(mtr1, mtr2);
            else if (choose == 2) {
                res = vinograd_alg(mtr1, mtr2);
            } else if (choose == 3) {
                res = opt_vinograd_alg(mtr1, mtr2);
            } else if (choose == 4)
            {
                matrix_v res_vin, res_opt_vin;
                res = standart_multy(mtr1, mtr2);

                if (mtr1.size() == mtr1[0].size() && mtr2.size() == mtr2[0].size())
                {
                    res_vin = vinograd_alg(mtr1, mtr2);
                    res_opt_vin = opt_vinograd_alg(mtr1, mtr2);
                } else
                    std::cout << "Ошибка! Для алгоритма Винограда требуется квадратные матрицы!\n";

                std::cout << "Результаты:\n";
                std::cout << "Классический алгоритм:\n";
                print_mtr(res);
                std::cout << "\nАлгоритм Винограда:\n";
                print_mtr(res_vin);
                std::cout << "\nОптимизированный алгоритм Винограда:\n";
                print_mtr(res_opt_vin);
                continue;
            }
            std::cout << "Результат: \n";
            print_mtr(res);
        } else if (choose == 5)
        {
            std::cout << "Введите параметры для замеров времени (в порядке нач. и макс. размер квадратной матрицы, шаг увелечения размера):\n";
            if (!(std::cin >> start >> max_len >> step))
                std::cout << "Ошибка! Вводите числа!\n";
            else
                measure_time(start, max_len, step);
        }
    }
    return 0;
}
