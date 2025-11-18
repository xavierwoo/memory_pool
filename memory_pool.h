#ifndef MEMORY_POOL_LIBRARY_H
#define MEMORY_POOL_LIBRARY_H

#include <cstdlib>
#include <vector>
#include <stack>
#include <cassert>

namespace memory_pool {

    template <typename T, size_t N>
    struct Pool {
        friend void it_works();
    private:
        std::vector<T*> ptr_batches;
        std::stack<T*> available_ptrs;

        auto is_ptr_in_pool(T*) -> bool;
        void allocate_more();

    public:
        Pool() = default;
        ~Pool();
        auto get() -> T*; //get a new available memory piece
        void recycle(T*); //recycle the memory piece
        auto resource_count() -> size_t; //get the number of managed memory pieces
    };

    void it_works();
}

template <typename T, size_t N>
memory_pool::Pool<T, N>::~Pool() {
    for (auto ptr_batch : ptr_batches) {
        std::free(ptr_batch);
    }
}

template<typename T, size_t N>
void memory_pool::Pool<T, N>::allocate_more() {
    auto ptr_bach {static_cast<T*>(std::malloc(sizeof(T) * N))};
    ptr_batches.push_back(ptr_bach);
    for (auto i=0; i < N; i++) {
        available_ptrs.push(ptr_bach + i);
    }
}

template<typename T, size_t N>
auto memory_pool::Pool<T, N>::get() -> T * {
    if (available_ptrs.empty()) {
        allocate_more();
    }
    auto elem {available_ptrs.top()}; available_ptrs.pop();
    new (elem) T();
    return elem;
}

template<typename T, size_t N>
void memory_pool::Pool<T, N>::recycle(T* ptr) {
    assert(is_ptr_in_pool(ptr));
    available_ptrs.push(ptr);
}

template<typename T, size_t N>
auto memory_pool::Pool<T, N>::is_ptr_in_pool(T* ptr) -> bool {
    for (auto ptr_batch : ptr_batches) {
        for (auto i=0; i < N; i++) {
            if (ptr_batch + i == ptr) {return true;}
        }
    }
    return false;
}

template<typename T, size_t N>
auto memory_pool::Pool<T, N>::resource_count() -> size_t {
    return ptr_batches.size() * N;
}


#endif // MEMORY_POOL_LIBRARY_H