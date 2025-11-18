cmake_minimum_required(VERSION 3.5)
project(memory_pool)

set(CMAKE_CXX_STANDARD 20)

add_library(memory_pool STATIC memory_pool.cpp)

target_include_directories(memory_pool PUBLIC "${CMAKE_CURRENT_LIST_DIR}")