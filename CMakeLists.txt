if(MSVC)
    if(MSVC_VERSION LESS 1928)
    message(FATAL_ERROR "require msvc version >= 16.8")
    endif()
    cmake_minimum_required(VERSION 3.18.5) 
else()
    cmake_minimum_required(VERSION 3.10.0)
endif()

project(micclib VERSION 0.0.1 LANGUAGES C)
set(CMAKE_C_STANDARD 11) 

add_executable(test config.h var.h micc.h micc.c num.h num.c str.h str.c test.c)

