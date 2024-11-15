// main.cpp

#include <iostream>
#include "custom_memory_resource.h"
#include "pmr_list.h"
#include "my_struct.h"

int main() {
    CustomMemoryResource my_resource;

    // Создаем полиморфный аллокатор с использованием нашего кастомного memory_resource
    std::pmr::polymorphic_allocator<std::byte> alloc(&my_resource);

    // PMRList<int>
    PMRList<int> int_list(alloc);

    int_list.push_back(1);
    int_list.push_back(2);
    int_list.push_back(3);

    std::cout << "Содержимое PMRList<int> (прямой обход):\n";
    for (auto it = int_list.begin(); it != int_list.end(); ++it) {
        std::cout << *it << "\n";
    }

    std::cout << "Содержимое PMRList<int> (обратный обход):\n";
    for (auto it = int_list.rbegin(); it != int_list.rend(); --it) {
        std::cout << *it << "\n";
    }

    // PMRList<MyStruct>
    PMRList<MyStruct> struct_list(alloc);

    struct_list.push_back(MyStruct(1, 2.0, "hello"));
    struct_list.push_back(MyStruct(3, 4.0, "world"));

    std::cout << "\nСодержимое PMRList<MyStruct> (прямой обход):\n";
    for (auto it = struct_list.begin(); it != struct_list.end(); ++it) {
        std::cout << "a: " << it->a << ", b: " << it->b << ", c: " << it->c << "\n";
    }

    std::cout << "Содержимое PMRList<MyStruct> (обратный обход):\n";
    for (auto it = struct_list.rbegin(); it != struct_list.rend(); --it) {
        std::cout << "a: " << it->a << ", b: " << it->b << ", c: " << it->c << "\n";
    }

    return 0;
}
