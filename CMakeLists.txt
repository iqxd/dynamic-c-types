cmake_minimum_required(VERSION 3.18.5)
set(CMAKE_C_STANDARD 11) 
project(micclib VERSION 0.0.1 LANGUAGES C)

add_executable(test config.h micc.h micc.c num.h num.c var.h var.c test.c)

