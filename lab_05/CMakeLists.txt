cmake_minimum_required(VERSION 3.23)
project(lab_05)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_05 main.cpp src/mtr_op.cpp inc/mtr_op.h
                               src/read_size.cpp inc/read_size.h
                               src/conveyor.cpp inc/conveyor.h
                               src/measure.cpp inc/measure.h)
