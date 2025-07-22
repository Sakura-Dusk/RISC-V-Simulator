//
// Created by Sakura on 25-7-22.
//

#ifndef MEMORY_HPP
#define MEMORY_HPP
#include <map>
#include "Instruction.hpp"
#include "RISC-V-Simulator-Template/tools.h"

struct Memory {
    std::map<unsigned int, unsigned int> memory;

    void load_instrctions() {
        unsigned int  current_positions = 0;
        std::string str;
        while (std::cin >> str) {
            if (str[0] == '@') {
                unsigned int next_positions = 0;
                for (int i = 1; i <= 8; i++)
                    next_positions = next_positions * 16 + sixteen_to_ten(str[i]);
                current_positions = next_positions;
                continue;
            }
            int operator_number = 0;
            for (int i = 0, tmp = 1; i <= 3; i++, tmp <<= 4) {
                operator_number += decode_two(str) * tmp;
                if (i != 3) std::cin >> str;
            }

            memory[current_positions] = operator_number;
            current_positions++;
            // decode_operator(operator_number);
        }
    }

    enum Interface_Mode {
        BYTE,
        UNSIGNED_BYTE,
        HALF_WORD,
        UNSIGNED_HALF_WORD,
        WORD,
    };


};

#endif //MEMORY_HPP
