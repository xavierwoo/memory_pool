# A simple memory pool manager

This library manages small memory pieces.
If your project uses a lot of small heap allocated memory pieces, 
this tool can be an alterative for the new and delete operations.

Let's hopt it may offer better performance.

## Link the library via CMake

```cmake
cmake_minimum_required(VERSION 3.5)
project(test_memory_pool)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        memory_pool
        GIT_REPOSITORY https://github.com/xavierwoo/memory_pool.git
        GIT_TAG v0.1.0  # Specify the Git tag here
)
FetchContent_MakeAvailable(memory_pool)

add_executable(test_memory_pool main.cpp)

target_link_libraries(test_memory_pool memory_pool)
```

## How to use

```c++
#include "memory_pool.h"

struct Data{
    int data1, data2;
};

int main() {
    memory_pool::Pool<Data, 512> pool; // The second parameter determines the number of objects allocated at one time

    Data* ptr = pool.get(); // get one object from the pool

    // use the object
    ptr->data1 = 1;
    ptr->data2 = 2;

    pool.recycle(ptr); // recycle the object
    return 0;
}
```

## Things to note

1. Better to use plain structs with this tool. 
2. It does not execute the destructor automatically.
3. When objects popped out, the default constructor is executed.
4. Do not free or delete the objects popped out from the pool.
They will be freed automatically when the pool dies.