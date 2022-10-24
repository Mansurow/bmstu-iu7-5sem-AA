cmake_minimum_required(VERSION 3.23)
project(src)

set(CMAKE_CXX_STANDARD 17)

add_executable(src main.cpp sorts.cpp sorts.h allocate.cpp allocate.h cpu_time.cpp cpu_time.h read_array.cpp read_array.h generate_array.cpp generate_array.h)
