#ifndef CUSTOM_MEMORY_RESOURCE_H
#define CUSTOM_MEMORY_RESOURCE_H

#include <memory_resource>
#include <list>
#include <cstddef>

class CustomMemoryResource : public std::pmr::memory_resource {
public:
    CustomMemoryResource();
    ~CustomMemoryResource();

protected:
    void* do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void* p, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

private:
    struct Block {
        void* ptr;
        size_t size;
        size_t alignment;
        bool is_free;
    };

    std::list<Block> blocks_;
};

#endif // CUSTOM_MEMORY_RESOURCE_H

