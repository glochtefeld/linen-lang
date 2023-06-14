cmake_minimum_required(VERSION 3.16)
project(linen VERSION 0.1.0 LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(extern)

add_executable(linen src/main.c 
    include/linen.h
)
target_include_directories(linen PRIVATE include)

add_executable(tests
    tests/main.c
)
target_include_directories(tests PRIVATE extern)
target_link_libraries(tests PRIVATE munit)