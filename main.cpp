// main.cpp
#include "4_class.hpp"
#include <iostream>
#include <vector>

int main() {
    try {
        // Создание четверичных чисел
        std::vector<unsigned char> num1_vec = {1, 2, 3}; // Число 123 в четверичной системе
        std::vector<unsigned char> num2_vec = {3, 2, 1}; // Число 321 в четверичной системе
        std::vector<unsigned char> num3_vec = {0};       // Число 0 в четверичной системе

        // Инициализация объектов My_nums
        My_nums num1(num1_vec);
        My_nums num2(num2_vec);
        My_nums num3(num3_vec);

        // Вывод чисел
        std::cout << "Число 1: ";
        num1.Print_numbers(); // Ожидаемый вывод: 123
        std::cout << "Число 2: ";
        num2.Print_numbers(); // Ожидаемый вывод: 321
        std::cout << "Число 3: ";
        num3.Print_numbers(); // Ожидаемый вывод: 0

        // Сложение чисел
        My_nums sum = num1 + num2;
        std::cout << "Сумма числа 1 и числа 2: ";
        sum.Print_numbers(); // Ожидаемый вывод: результат сложения 123 + 321 в четверичной системе

        // Вычитание чисел
        My_nums diff = num2 - num1;
        std::cout << "Разность числа 2 и числа 1: ";
        diff.Print_numbers(); // Ожидаемый вывод: результат вычитания 321 - 123 в четверичной системе

        // Сравнение чисел
        if (num1 == num2) {
            std::cout << "Число 1 равно числу 2" << std::endl;
        } else if (num1 > num2) {
            std::cout << "Число 1 больше числа 2" << std::endl;
        } else {
            std::cout << "Число 1 меньше числа 2" << std::endl;
        }

        // Попытка вычитания большего числа из меньшего
        try {
            My_nums invalid_diff = num1 - num2;
            std::cout << "Разность числа 1 и числа 2: ";
            invalid_diff.Print_numbers();
        } catch (const std::invalid_argument& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }

        // Сложение с нулём
        My_nums sum_with_zero = num1 + num3;
        std::cout << "Сумма числа 1 и числа 3: ";
        sum_with_zero.Print_numbers(); // Ожидаемый вывод: 123

        // Проверка оператора присваивания
        My_nums num5;
        num5 = num1;
        std::cout << "Число 5 после присваивания числа 1: ";
        num5.Print_numbers(); // Ожидаемый вывод: 123

        // Проверка конструктора копирования
        My_nums num6(num2);
        std::cout << "Число 6 (копия числа 2): ";
        num6.Print_numbers(); // Ожидаемый вывод: 321

        // Тестирование больших чисел
        std::vector<unsigned char> num7_vec = {3, 3, 3, 3, 3, 3}; // Число 333333 в четверичной системе
        std::vector<unsigned char> num8_vec = {1};                // Число 1 в четверичной системе
        My_nums num7(num7_vec);
        My_nums num8(num8_vec);

        std::cout << "Число 7: ";
        num7.Print_numbers(); // Ожидаемый вывод: 333333
        std::cout << "Число 8: ";
        num8.Print_numbers(); // Ожидаемый вывод: 1

        My_nums big_sum = num7 + num8;
        std::cout << "Сумма числа 7 и числа 8: ";
        big_sum.Print_numbers(); // Ожидаемый вывод: 1000000

        // Проверка вычитания, приводящего к нулю
        My_nums zero_result = num1 - num1;
        std::cout << "Разность числа 1 и числа 1: ";
        zero_result.Print_numbers(); // Ожидаемый вывод: 0

    } catch (const std::invalid_argument& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
