cmake_minimum_required(VERSION 4.2)
project(wave)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_executable(wave
    src/lexer.cpp
    src/generator.cpp
    src/main.cpp
    src/translator.cpp
)

if(MSVC)
    target_compile_options(wave PRIVATE /utf-8)
endif()

target_precompile_headers(wave PRIVATE
    src/pch.hpp
)
target_include_directories(wave PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/THIRD_PARTY/include
)

# Copy cpp_dic/ next to the built executable so wave can find
# cpp_dic/dic.json regardless of the working directory it's run from.
add_custom_command(TARGET wave POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/cpp_dic
    $<TARGET_FILE_DIR:wave>/cpp_dic
)
