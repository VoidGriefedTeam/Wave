cmake_minimum_required(VERSION 4.2)

project(wave)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(wave
    src/lexer.cpp
    src/generator.cpp
    src/main.cpp
)

target_precompile_headers(wave PRIVATE
    src/pch.hpp
)

target_include_directories(wave PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/THIRD_PARTY/include
)