cmake_minimum_required(VERSION 3.20)
project(kutiles VERSION 1 LANGUAGES C)

add_library(kutiles STATIC
    src/hash_table.c
)

add_library(kutiles::kutiles ALIAS kutiles)

target_include_directories(kutiles
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_features(kutiles PUBLIC c_std_17)
target_compile_options(kutiles PRIVATE -Wall -Wextra -Wpedantic)

include(CTest)
enable_testing()
add_subdirectory(tests)
