#include "inc/conveyor.h"
#include "inc/measure.h"

int main() {
    setbuf(stdout, nullptr);

    int result = 0;
    printf("\nВас приветствует измеритель времени конвейерной обработки разреженных матриц!!!\n");
    int choice = -1;
    while (choice && result == 0)
    {
        printf("\n\n\nВыберите необходимую задачу и введите её номер для запуска.\n");
        printf("1 - запустить последовательную обработку матриц\n");
        printf("2 - запустить конвейерную обработку матриц\n");
        printf("3 - замеры времени реализаций\n");
        printf("0 - выход\n\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);
        char ch = 1;
        while (ch != '\n')
            scanf("%c", &ch);
        switch (choice)
        {
            case 1:
                linear();
                choice = -1;
                break;
            case 2:
                parallel();
                choice = -1;
                break;
            case 3:
                time_measure();
                choice = -1;
                break;
            case 0:
                break;

            default:
                printf("\nНеверный ввод, повторите попытку!!!\n\n");
                break;
        }
    }
    printf("Спасибо, что воспользовались данной программой <3<3<3\n");
    return result;

    return 0;
}
