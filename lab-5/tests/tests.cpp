#include <gtest/gtest.h>
#include "custom_memory_resource.h"
#include "pmr_list.h"
#include "my_struct.h"

TEST(PMRListTest, IntPushBack) {
    CustomMemoryResource my_resource;
    std::pmr::polymorphic_allocator<std::byte> alloc(&my_resource);
    PMRList<int> int_list(alloc);

    int_list.push_back(10);
    int_list.push_back(20);
    int_list.push_back(30);

    PMRList<int>::Iterator it = int_list.begin();
    ASSERT_EQ(*it, 10);
    ++it;
    ASSERT_EQ(*it, 20);
    ++it;
    ASSERT_EQ(*it, 30);
    ++it;
    ASSERT_EQ(it, int_list.end());
}

TEST(PMRListTest, IntPushFront) {
    CustomMemoryResource my_resource;
    std::pmr::polymorphic_allocator<std::byte> alloc(&my_resource);
    PMRList<int> int_list(alloc);

    int_list.push_front(10);
    int_list.push_front(20);
    int_list.push_front(30);

    PMRList<int>::Iterator it = int_list.begin();
    ASSERT_EQ(*it, 30);
    ++it;
    ASSERT_EQ(*it, 20);
    ++it;
    ASSERT_EQ(*it, 10);
    ++it;
    ASSERT_EQ(it, int_list.end());
}

TEST(PMRListTest, MyStructTest) {
    CustomMemoryResource my_resource;
    std::pmr::polymorphic_allocator<std::byte> alloc(&my_resource);
    PMRList<MyStruct> struct_list(alloc);

    struct_list.push_back(MyStruct(1, 1.1, "first"));
    struct_list.push_back(MyStruct(2, 2.2, "second"));
    struct_list.push_back(MyStruct(3, 3.3, "third"));

    PMRList<MyStruct>::Iterator it = struct_list.begin();

    ASSERT_EQ(it->a, 1);
    ASSERT_DOUBLE_EQ(it->b, 1.1);
    ASSERT_EQ(it->c, "first");
    ++it;

    ASSERT_EQ(it->a, 2);
    ASSERT_DOUBLE_EQ(it->b, 2.2);
    ASSERT_EQ(it->c, "second");
    ++it;

    ASSERT_EQ(it->a, 3);
    ASSERT_DOUBLE_EQ(it->b, 3.3);
    ASSERT_EQ(it->c, "third");
    ++it;

    ASSERT_EQ(it, struct_list.end());
}

TEST(PMRListTest, BidirectionalIterator) {
    CustomMemoryResource my_resource;
    std::pmr::polymorphic_allocator<std::byte> alloc(&my_resource);
    PMRList<int> int_list(alloc);

    int_list.push_back(1);
    int_list.push_back(2);
    int_list.push_back(3);

    PMRList<int>::Iterator it = int_list.rbegin();
    ASSERT_EQ(*it, 3);
    --it;
    ASSERT_EQ(*it, 2);
    --it;
    ASSERT_EQ(*it, 1);
    --it;
    ASSERT_EQ(it, int_list.rend());
}

TEST(PMRListTest, EmptyList) {
    CustomMemoryResource my_resource;
    std::pmr::polymorphic_allocator<std::byte> alloc(&my_resource);
    PMRList<int> int_list(alloc);

    ASSERT_EQ(int_list.begin(), int_list.end());
}
