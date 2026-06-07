#include "matrix.h"

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>

namespace {

void setupConsole() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

}  // namespace

int main() {
    setupConsole();

    std::cout << "=== Обмен чётных и нечётных столбцов матрицы ===\n\n";

    int rows = 0;
    int cols = 0;

    readPositiveInt("Введите количество строк: ", rows);
    readPositiveInt("Введите количество столбцов: ", cols);

    try {
        Matrix matrix(rows, cols);

        matrix.input();

        std::cout << "\nИсходная матрица:\n";
        matrix.print();

        matrix.swapEvenOddColumns();

        std::cout << "\nРезультат (столбцы 0<->1, 2<->3, ...";
        if (cols % 2 != 0) {
            std::cout << "; последний столбец без пары";
        }
        std::cout << "):\n";
        matrix.print();
    } catch (const std::bad_alloc&) {
        std::cerr << "Ошибка: не удалось выделить память для матрицы.\n";
        return 1;
    } catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << '\n';
        return 1;
    }

    std::cout << "\nГотово.\n";
    return 0;
}
