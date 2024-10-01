#include "4_class.hpp"  
#include <iostream>
#include <vector>


My_nums::My_nums() {}

My_nums::My_nums(std::vector<unsigned char> input_num) {
    for (int i = (input_num.size() - 1); i >= 0; --i) {
        if (0 <= (input_num[i]) && (input_num[i]) <= 3) {
            my_num.push_back(input_num[i]);
        } else {
            throw std::invalid_argument("Некорректное четверичное число.");
        }
    }
}

My_nums::My_nums(const My_nums& other) : my_num(other.my_num) {}

std::vector<unsigned char> My_nums::Get_numbers() const {
    return my_num;
}

void My_nums::Print_numbers() const {
    for (int i = (my_num.size() - 1); i > -1; --i) {
        std::cout << static_cast<int>(my_num[i]);
    }
    std::cout << std::endl;
}




My_nums My_nums::operator+(const My_nums& second_num) const {
    std::vector<unsigned char> result;
    size_t max_size = std::max(my_num.size(), second_num.my_num.size());
    unsigned char carry = 0;

    for (int i = 0; i < max_size; ++i) {
        unsigned char num1, num2;
        if (i < my_num.size()) {
            num1 = my_num[i];
        } else {
            num1 = 0;
        }
        if (i < second_num.my_num.size()) {
            num2 = second_num.my_num[i];
        } else {
            num2 = 0;
        }

        unsigned char sum = num1 + num2 + carry;
        result.push_back(sum % 4);
        carry = sum / 4;
    }

    if (carry > 0) {
        result.push_back(carry);
    }
    std::reverse(result.begin(), result.end());
    return My_nums(result);
}

// ГРАНИЦА 2 ==============================================================

My_nums My_nums::operator-(const My_nums& second_num) const {
    if (CompareNumbers(my_num, second_num.my_num) == -1){
        throw std::invalid_argument("Нельзя из меньшего вычесть большее");
    }
    std::vector<unsigned char> result = my_num;
    unsigned char borrow = 0;



    for (int i = 0; i < second_num.my_num.size(); ++i) {
        unsigned char num2 = second_num.my_num[i];

        if (result[i] < num2 + borrow) {
            result[i] = result[i] + 4 - num2 - borrow;
            borrow = 1;
        } else {
            result[i] = result[i] - num2 - borrow;
            borrow = 0;
        }
    }
    for (int i = second_num.my_num.size(); i < result.size() && borrow != 0; ++i) {
        if (result[i] < borrow) {
            result[i] = result[i] + 4 - borrow;
            borrow = 1;
        } else {
            result[i] = result[i] - borrow;
            borrow = 0;
        }
    }
    RemoveLeadingZeros(result);
    std::reverse(result.begin(), result.end());
    return My_nums(result);
}



// =========================== Рабочие методы для всяких штук, реализованы корректно ===========
My_nums& My_nums::operator=(const My_nums& second) {
    if (this != &second) {
        my_num = second.my_num;
    }
    return *this;
}

bool My_nums::operator==(const My_nums& second_num) const {
    return CompareNumbers(my_num, second_num.my_num) == 0;
}

bool My_nums::operator>(const My_nums& second_num) const {
    return CompareNumbers(my_num, second_num.my_num) == 1;
}

bool My_nums::operator<(const My_nums& second_num) const {
    return CompareNumbers(my_num, second_num.my_num) == -1;
}

void My_nums::ReverseNumber() {
    std::reverse(my_num.begin(), my_num.end());
}

int My_nums::CompareNumbers(const std::vector<unsigned char>& num1, const std::vector<unsigned char>& num2) {
    size_t size1 = num1.size();
    size_t size2 = num2.size();

    // Удаляем ведущие нули из обоих чисел (старшие разряды)
    while (size1 > 1 && num1[size1 - 1] == 0) {
        --size1;
    }
    while (size2 > 1 && num2[size2 - 1] == 0) {
        --size2;
    }

    if (size1 > size2) {
        return 1;
    }
    if (size1 < size2) {
        return -1;
    }
    for (int i = size1 - 1; i >= 0; --i) {
        if (num1[i] > num2[i]) {
            return 1;
        } else if (num1[i] < num2[i]) {
            return -1;
        }
    }

    return 0;
}

void My_nums::RemoveLeadingZeros(std::vector<unsigned char>& num) {
    while (num.size() > 1 && num.back() == 0) {
        num.pop_back(); 
    }
}
