#ifndef MY_STRUCT_H
#define MY_STRUCT_H

#include <string>

struct MyStruct {
    int a;
    double b;
    std::string c;

    MyStruct(int a_, double b_, const std::string& c_);
};

#endif // MY_STRUCT_H
