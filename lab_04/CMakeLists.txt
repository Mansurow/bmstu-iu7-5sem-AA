cmake_minimum_required(VERSION 3.23)
project(lab_04 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab_04 main.c src/tf_alg.c inc/tf_alg.h src/pthread_tf.c inc/pthread_tf.h src/time_measure.c inc/time_measure.h)
