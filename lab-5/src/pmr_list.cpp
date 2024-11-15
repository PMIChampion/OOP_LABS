// pmr_list.cpp

#include "pmr_list.h"

template <typename T>
PMRList<T>::Node::Node(const T& val, Node* n, Node* p)
    : value(val), next(n), prev(p) {}

template <typename T>
PMRList<T>::Iterator::Iterator() : node_(nullptr) {}

template <typename T>
PMRList<T>::Iterator::Iterator(Node* node) : node_(node) {}

template <typename T>
typename PMRList<T>::Iterator::reference PMRList<T>::Iterator::operator*() const {
    return node_->value;
}

template <typename T>
typename PMRList<T>::Iterator::pointer PMRList<T>::Iterator::operator->() const {
    return &(node_->value);
}

template <typename T>
typename PMRList<T>::Iterator& PMRList<T>::Iterator::operator++() {
    if (node_) node_ = node_->next;
    return *this;
}

template <typename T>
typename PMRList<T>::Iterator PMRList<T>::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

template <typename T>
typename PMRList<T>::Iterator& PMRList<T>::Iterator::operator--() {
    if (node_) node_ = node_->prev;
    return *this;
}

template <typename T>
typename PMRList<T>::Iterator PMRList<T>::Iterator::operator--(int) {
    Iterator tmp = *this;
    --(*this);
    return tmp;
}

template <typename T>
bool PMRList<T>::Iterator::operator==(const Iterator& other) const {
    return node_ == other.node_;
}

template <typename T>
bool PMRList<T>::Iterator::operator!=(const Iterator& other) const {
    return node_ != other.node_;
}

template <typename T>
PMRList<T>::PMRList(const allocator_type& alloc)
    : head_(nullptr), tail_(nullptr), alloc_(alloc), node_alloc_(alloc.resource()) {}

template <typename T>
PMRList<T>::~PMRList() {
    Node* current = head_;
    while (current != nullptr) {
        Node* next = current->next;
        std::allocator_traits<NodeAllocator>::destroy(node_alloc_, current);
        node_alloc_.deallocate(current, 1);
        current = next;
    }
}

template <typename T>
void PMRList<T>::push_back(const T& value) {
    Node* new_node = node_alloc_.allocate(1);
    std::allocator_traits<NodeAllocator>::construct(node_alloc_, new_node, value, nullptr, tail_);
    if (tail_) {
        tail_->next = new_node;
    } else {
        head_ = new_node;
    }
    tail_ = new_node;
}

template <typename T>
void PMRList<T>::push_front(const T& value) {
    Node* new_node = node_alloc_.allocate(1);
    std::allocator_traits<NodeAllocator>::construct(node_alloc_, new_node, value, head_, nullptr);
    if (head_) {
        head_->prev = new_node;
    } else {
        tail_ = new_node;
    }
    head_ = new_node;
}

template <typename T>
typename PMRList<T>::Iterator PMRList<T>::begin() {
    return Iterator(head_);
}

template <typename T>
typename PMRList<T>::Iterator PMRList<T>::end() {
    return Iterator(static_cast<Node*>(nullptr)); 
}

template <typename T>
typename PMRList<T>::Iterator PMRList<T>::rbegin() {
    return Iterator(tail_);
}

template <typename T>
typename PMRList<T>::Iterator PMRList<T>::rend() {
    return Iterator(static_cast<Node*>(nullptr)); 
}

template class PMRList<int>;
template class PMRList<MyStruct>;
