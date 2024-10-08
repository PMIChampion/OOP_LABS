#pragma once

#include <vector>
#include <iostream>

class QuaternaryNumber {
private:
    std::vector<unsigned char> my_num;
    void ReverseNumber();
    static int CompareNumbers(const std::vector<unsigned char>& num1, const std::vector<unsigned char>& num2);
    static void RemoveLeadingZeros(std::vector<unsigned char>& num); 
public:
    // Конструкторы
    QuaternaryNumber();
    QuaternaryNumber(std::vector<unsigned char> input_num);
    QuaternaryNumber(const QuaternaryNumber& other);
    QuaternaryNumber(QuaternaryNumber&& other) noexcept; // Конструктор перемещения

    // Методы
    std::vector<unsigned char> Get_numbers() const;
    void Print_numbers() const;

    // Операторы
    QuaternaryNumber operator+(const QuaternaryNumber& second_num) const;
    QuaternaryNumber operator-(const QuaternaryNumber& second_num) const;
    QuaternaryNumber& operator=(const QuaternaryNumber& second);
    QuaternaryNumber& operator=(QuaternaryNumber&& second) noexcept; // Оператор перемещения
    bool operator==(const QuaternaryNumber& second_num) const;
    bool operator>(const QuaternaryNumber& second_num) const;
    bool operator<(const QuaternaryNumber& second_num) const;
    bool operator<=(const QuaternaryNumber& second_num) const; // Оператор <=
    bool operator>=(const QuaternaryNumber& second_num) const; // Оператор >=
};

