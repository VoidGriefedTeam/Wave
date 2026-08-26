cmake_minimum_required(VERSION 4.2)

project(Wave)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Wave
    src/lexer.cpp
    src/generator.cpp
)

target_precompile_headers(Wave PRIVATE
    src/pch.hpp
)

target_include_directories(Wave PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/THIRD_PARTY/include
)