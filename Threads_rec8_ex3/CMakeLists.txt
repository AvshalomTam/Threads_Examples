cmake_minimum_required(VERSION 3.9)

project(Threads_rec8)
find_package (Threads)

set(CMAKE_CXX_STANDARD 98)

add_executable(Threads_rec8
        README.md threads_example.cpp)

target_link_libraries (Threads_rec8 ${CMAKE_THREAD_LIBS_INIT})
