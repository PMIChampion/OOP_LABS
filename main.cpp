// main.cpp
#include "4_class.hpp"


int main() {
        std::vector<unsigned char> num1_vec = {1, 2, 3}; // Число 123 в четверичной системе
        std::vector<unsigned char> num2_vec = {3, 2, 1}; // Число 321 в четверичной системе
        std::vector<unsigned char> num3_vec = {0};       // Число 0 в четверичной системе

        QuaternaryNumber num1(num1_vec);
        QuaternaryNumber num2(num2_vec);
        QuaternaryNumber num3(num3_vec);

        std::cout << "Число 1: ";
        num1.Print_numbers(); // Ожидаемый вывод: 123
        std::cout << "Число 2: ";
        num2.Print_numbers(); // Ожидаемый вывод: 321
        std::cout << "Число 3: ";
        num3.Print_numbers(); // Ожидаемый вывод: 0

        QuaternaryNumber sum = num1 + num2;
        std::cout << "Сумма числа 1 и числа 2: ";
        sum.Print_numbers(); // Ожидаемый вывод: результат сложения 123 + 321 в четверичной системе

        QuaternaryNumber diff = num2 - num1;
        std::cout << "Разность числа 2 и числа 1: ";
        diff.Print_numbers(); // Ожидаемый вывод: результат вычитания 321 - 123 в четверичной системе

        if (num1 == num2) {
            std::cout << "Число 1 равно числу 2" << std::endl;
        } else if (num1 > num2) {
            std::cout << "Число 1 больше числа 2" << std::endl;
        } else {
            std::cout << "Число 1 меньше числа 2" << std::endl;
        }

        try {
            QuaternaryNumber invalid_diff = num1 - num2;
            std::cout << "Разность числа 1 и числа 2: ";
            invalid_diff.Print_numbers();
        } catch (const std::invalid_argument& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }

        QuaternaryNumber sum_with_zero = num1 + num3;
        std::cout << "Сумма числа 1 и числа 3: ";
        sum_with_zero.Print_numbers(); // Ожидаемый вывод: 123

        QuaternaryNumber num5;
        num5 = num1;
        std::cout << "Число 5 после присваивания числа 1: ";
        num5.Print_numbers(); // Ожидаемый вывод: 123

        QuaternaryNumber num6(num2);
        std::cout << "Число 6 (копия числа 2): ";
        num6.Print_numbers(); // Ожидаемый вывод: 321

        std::vector<unsigned char> num7_vec = {3, 3, 3, 3, 3, 3}; // Число 333333 в четверичной системе
        std::vector<unsigned char> num8_vec = {1};                // Число 1 в четверичной системе
        QuaternaryNumber num7(num7_vec);
        QuaternaryNumber num8(num8_vec);

        std::cout << "Число 7: ";
        num7.Print_numbers(); // Ожидаемый вывод: 333333
        std::cout << "Число 8: ";
        num8.Print_numbers(); // Ожидаемый вывод: 1

        QuaternaryNumber big_sum = num7 + num8;
        std::cout << "Сумма числа 7 и числа 8: ";
        big_sum.Print_numbers(); // Ожидаемый вывод: 1000000

        // Проверка вычитания, приводящего к нулю
        QuaternaryNumber zero_result = num1 - num1;
        std::cout << "Разность числа 1 и числа 1: ";
        zero_result.Print_numbers(); // Ожидаемый вывод: 0

} 
