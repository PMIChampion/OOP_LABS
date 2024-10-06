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

    // Методы
    std::vector<unsigned char> Get_numbers() const;
    void Print_numbers() const;

    // Операторы
    QuaternaryNumber operator+(const QuaternaryNumber& second_num) const;
    QuaternaryNumber operator-(const QuaternaryNumber& second_num) const;
    QuaternaryNumber& operator=(const QuaternaryNumber& second);
    bool operator==(const QuaternaryNumber& second_num) const;
    bool operator>(const QuaternaryNumber& second_num) const;
    bool operator<(const QuaternaryNumber& second_num) const;
};

