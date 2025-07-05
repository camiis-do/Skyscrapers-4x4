cmake_minimum_required(VERSION 3.14)
project(Skyscrapers4x4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Skyscrapers4x4
    src/main.cpp
    src/solver.cpp
)

target_include_directories(Skyscrapers4x4 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (MSVC)
    target_compile_options(Skyscrapers4x4 PRIVATE /W4 /permissive-)
else()
    target_compile_options(Skyscrapers4x4 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

enable_testing()