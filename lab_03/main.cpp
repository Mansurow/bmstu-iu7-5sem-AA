#include <iostream>
#include "inc/sorts.h"
#include "inc/allocate.h"
#include "inc/read_array.h"
#include "inc/cpu_time.h"

using namespace std;

int main() {

    setbuf(stdout, nullptr);

    cout  << "   Выберите алгоритм: \n"
              "1 - Сортировка Шелла; \n"
              "2 - Пирамидальная сортировка; \n"
              "3 - Сортировка бусинами; \n"
              "4 - Замерить время работы реализаций алгоритмов сортировок.\n" << endl;

    int choice = -1;
    int *array = nullptr;
    int n = 0, rc = 0;

    while (choice != 0) {
        cout << "Выбор: ";
        cin >> choice;

        if (choice > 0 && choice < 4) {
            int choice_1 = -1;
            while (choice_1 != 0)
            {
                cout  << "   Выберите действие: \n"
                         "1 - Сгенирировать массив; \n"
                         "2 - Ввести массив; \n" << endl;
                cout << "Выбор: ";
                cin >> choice_1;

                if (choice_1 == 1) {
                    rc = random_array(&array, n);
                    std::cout << "Сгенерированный массив: ";
                    if (!rc) print_array(array, n);
                    choice_1 = 0;
                }
                else if (choice_1 == 2) {
                    rc = read_array(&array, n);
                    choice_1 = 0;
                }
            }
            if (!rc && choice == 1)
                shell_sort(array, n);
            else if (!rc && choice == 2)
                heap_sort(array, n);
            else if (!rc && choice == 3) {
                for (size_t i = 0; !rc && i < n; i++)
                    if (array[i] < 0)
                        rc = 1;
                if (!rc)
                    bead_sort(array, n);
                else
                    std::cout << "Ошибка! Сортировка бусинами рассматривает только натуральные числа и нуль!\n";

            }

            if (!rc) {
                std::cout << "Результат сортировки: ";
                print_array(array, n);
            }
            free_arr(array, n);
        }
        else if (choice == 4) {
            cout  << "   Выберите массив для замеров: \n"
                     "1 - Отсортированный массив; \n"
                     "2 - Отсортированный в обратном порядке; \n"
                     "3 - Случайный массив; \n"
                     "4 - Массив с одними и теми элементами.\n" << endl;
            cout << "Выбор: ";
            cin >> choice;

            int max_len = 0, step = 0, start = 0;
            if (choice > 0 && choice < 5)
            {
                cout << "Введите начало, макс. размер и шаг для замеров: ";
                cin >> start >> max_len >> step;
            }

            if (choice == 1)
                measure_time(0, max_len, step, "sort");
            else if (choice == 2)
                measure_time(start, max_len, step, "rsort");
            else if (choice == 3)
                measure_time(start, max_len, step);
            else if (choice == 4)
                measure_time(start, max_len, step, "equal");
        }
    }
    return 0;
}
