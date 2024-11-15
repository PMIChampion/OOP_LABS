// custom_memory_resource.cpp

#include "custom_memory_resource.h"
#include <new>
#include <iostream>

CustomMemoryResource::CustomMemoryResource() = default;

CustomMemoryResource::~CustomMemoryResource() {
    for (auto& block : blocks_) {
        ::operator delete(block.ptr, std::align_val_t(block.alignment));
    }
}

void* CustomMemoryResource::do_allocate(size_t bytes, size_t alignment) {
    for (auto& block : blocks_) {
        if (block.is_free && block.size >= bytes && block.alignment == alignment) {
            void* ptr = block.ptr;
            size_t space = block.size;
            void* aligned_ptr = std::align(alignment, bytes, ptr, space);
            if (aligned_ptr != nullptr) {
                block.is_free = false;
                return aligned_ptr;
            }
        }
    }
    void* ptr = ::operator new(bytes, std::align_val_t(alignment));
    blocks_.push_back({ ptr, bytes, alignment, false });
    return ptr;
}

void CustomMemoryResource::do_deallocate(void* p, size_t bytes, size_t alignment) {
    for (auto& block : blocks_) {
        if (block.ptr == p) {
            block.is_free = true;
            return;
        }
    }

}

bool CustomMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}
