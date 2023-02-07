cmake_minimum_required(VERSION 3.23)
project(lab_01)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_01 main.cpp
        src/algorithms.cpp inc/algorithms.h
        src/allocate.cpp inc/allocate.h
        src/cpu_time.cpp inc/cpu_time.h
        src/print_mtr_lev.cpp inc/print_mtr_lev.h
        src/memory.cpp inc/memory.h)
