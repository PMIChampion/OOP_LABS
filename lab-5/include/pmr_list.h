// pmr_list.h

#ifndef PMR_LIST_H
#define PMR_LIST_H

#include <memory_resource>
#include <memory>
#include "my_struct.h" 

template <typename T>
class PMRList {
public:
    using allocator_type = std::pmr::polymorphic_allocator<T>;

    PMRList(const allocator_type& alloc = {});
    ~PMRList();

    void push_back(const T& value);
    void push_front(const T& value);

    struct Node {
        T value;
        Node* next;
        Node* prev;

        Node(const T& val, Node* n = nullptr, Node* p = nullptr);
    };

    class Iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator();
        explicit Iterator(Node* node);

        reference operator*() const;
        pointer operator->() const;

        Iterator& operator++();   
        Iterator operator++(int); 

        Iterator& operator--();   
        Iterator operator--(int); 

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        Node* node_;
    };

    Iterator begin();
    Iterator end();
    Iterator rbegin();
    Iterator rend();

private:
    Node* head_;
    Node* tail_;
    allocator_type alloc_;
    using NodeAllocator = typename std::allocator_traits<allocator_type>::template rebind_alloc<Node>;
    NodeAllocator node_alloc_;
};

extern template class PMRList<int>;
extern template class PMRList<MyStruct>;

#endif // PMR_LIST_H
