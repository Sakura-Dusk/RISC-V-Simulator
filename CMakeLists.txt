cmake_minimum_required(VERSION 3.22)
project(RISC-V-Simulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(RISC-V-Simulator src/main.cpp
        src/Instruction.hpp
        src/memory.hpp
        src/ALU.hpp
        src/Controller.hpp)
