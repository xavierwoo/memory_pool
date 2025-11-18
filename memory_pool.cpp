#include "memory_pool.h"

#include <iostream>

using std::cout;

void memory_pool::it_works() {

    Pool<int, 2> pool;
    assert(pool.available_ptrs.empty());
    assert(pool.resource_count() == 0);

    auto ptr1 = pool.get();
    assert(pool.is_ptr_in_pool(ptr1));
    assert(pool.available_ptrs.size() == 1);
    assert(pool.resource_count() == 2);

    auto ptr2 = pool.get();
    assert(pool.is_ptr_in_pool(ptr2));
    assert(pool.available_ptrs.empty());
    assert(pool.resource_count() == 2);

    auto ptr3 = pool.get();
    assert(pool.is_ptr_in_pool(ptr3));
    assert(pool.available_ptrs.size() == 1);
    assert(pool.resource_count() == 4);

    pool.recycle(ptr1);
    assert(pool.available_ptrs.size() == 2);
    assert(pool.resource_count() == 4);

    pool.recycle(ptr2);
    assert(pool.available_ptrs.size() == 3);
    assert(pool.resource_count() == 4);

    ptr1 = pool.get();
    assert(pool.is_ptr_in_pool(ptr1));
    assert(pool.available_ptrs.size() == 2);
    assert(pool.resource_count() == 4);
    cout<<"memory_pool works!\n";
}