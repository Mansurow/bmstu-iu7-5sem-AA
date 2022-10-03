cmake_minimum_required(VERSION 3.23)
project(lab_01)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_01 main.cpp
        algorithms.cpp algorithms.h
        allocate.cpp allocate.h
        cpu_time.cpp cpu_time.h
        print_mtr_lev.cpp print_mtr_lev.h
        memory.cpp memory.h)
