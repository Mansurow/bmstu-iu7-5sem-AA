cmake_minimum_required(VERSION 3.23)
project(lab_04)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab_04 main.cpp src/multy_mtr.cpp inc/multy_mtr.h src/print_mtr.cpp inc/print_mtr.h src/read_mtr.cpp inc/read_mtr.h inc/matrix_config.h src/cpu_time.cpp inc/cpu_time.h)
