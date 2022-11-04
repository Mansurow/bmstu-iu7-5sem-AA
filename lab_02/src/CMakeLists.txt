cmake_minimum_required(VERSION 3.23)
project(src)

set(CMAKE_CXX_STANDARD 14)

add_executable(src main.cpp multy_mtr.cpp multy_mtr.h print_mtr.cpp print_mtr.h read_mtr.cpp read_mtr.h matrix_config.h cpu_time.cpp cpu_time.h)
