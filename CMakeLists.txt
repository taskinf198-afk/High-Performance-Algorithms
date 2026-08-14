cmake_minimum_required(VERSION 3.14)
project(HighPerformanceDSA CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optimization Flags for GCC/Clang
if(MSVC)
    add_compile_options(/O2)
else()
    add_compile_options(-O3 -march=native)
endif()

# Target Executables
add_executable(trapping_rain_water trapping_rain_water_2.cpp)
add_executable(word_ladder_2 word_ladder_2.cpp)
add_executable(benchmark main_benchmark.cpp)
