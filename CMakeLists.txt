if(Win32)
    cmake_minimum_required(VERSION 3.18.5)
else()
    cmake_minimum_required(VERSION 3.10.0)
endif()
set(CMAKE_C_STANDARD 11) 
project(micclib VERSION 0.0.1 LANGUAGES C)

add_executable(test config.h micc.h micc.c num.h num.c str.h str.c list.h list.c var.h var.c test.c)

