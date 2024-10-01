#pragma once

#include <vector>
#include <iostream>

class My_nums {
private:
    std::vector<unsigned char> my_num;
    void ReverseNumber();
    static int CompareNumbers(const std::vector<unsigned char>& num1, const std::vector<unsigned char>& num2);
    static void RemoveLeadingZeros(std::vector<unsigned char>& num); 
public:
    // Конструкторы
    My_nums();
    My_nums(std::vector<unsigned char> input_num);
    My_nums(const My_nums& other);

    // Методы
    std::vector<unsigned char> Get_numbers() const;
    void Print_numbers() const;

    // Операторы
    My_nums operator+(const My_nums& second_num) const;
    My_nums operator-(const My_nums& second_num) const;
    My_nums& operator=(const My_nums& second);
    bool operator==(const My_nums& second_num) const;
    bool operator>(const My_nums& second_num) const;
    bool operator<(const My_nums& second_num) const;
};

