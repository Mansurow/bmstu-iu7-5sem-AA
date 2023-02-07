cmake_minimum_required(VERSION 3.23)
project(lab_03)

set(CMAKE_CXX_STANDARD 17)

add_executable(src main.cpp src/sorts.cpp inc/sorts.h src/allocate.cpp inc/allocate.h src/cpu_time.cpp inc/cpu_time.h src/read_array.cpp inc/read_array.h src/generate_array.cpp inc/generate_array.h)
