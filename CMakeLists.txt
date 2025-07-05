cmake_minimum_required(VERSION 3.14)
project(Skyscrapers4x4 LANGUAGES CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    include/*.h
)

add_executable(Skyscrapers4x4 ${SOURCES})

if (MSVC)
    target_compile_options(Skyscrapers4x4 PRIVATE /W4 /permissive-)
else()
    target_compile_options(Skyscrapers4x4 PRIVATE -Wall -Wextra -pedantic)
endif()

include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.4
)

FetchContent_MakeAvailable(Catch2)

enable_testing()

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
    add_subdirectory(tests)
endif()