cmake_minimum_required(VERSION 3.22)
project(code)

set(CMAKE_CXX_STANDARD 20)

add_executable(code src/main.cpp
        src/Instruction.hpp
        src/memory.hpp
        src/ALU.hpp
        src/Controller.hpp)
