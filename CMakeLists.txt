cmake_minimum_required(VERSION 4.2)

project(Wave)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SOURCES
    src/*.cpp
)

add_executable(Wave ${SOURCES})

target_precompile_headers(Wave PRIVATE
    src/pch.hpp
)