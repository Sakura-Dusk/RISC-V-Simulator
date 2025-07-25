//
// Created by Sakura on 25-7-22.
//

#ifndef ALU_HPP
#define ALU_HPP
#include "Instruction.hpp"
#include "RISC-V-Simulator-Template/module.h"
#include "RISC-V-Simulator-Template/tools.h"


struct ALU_Input {
    Wire<32> word;
    Wire<1> can_start;
};

struct ALU_Output {
    Wire<32> output;
    Wire<32> rd;
};

struct ALU: dark::Module<ALU_Input, ALU_Output> {
    void work() {
        if (!can_start) return ;
        Operator_Kind now = decode_operator(word);
        switch (now) {
            case ADD: {
                int r1 = get_r1(word), r2 = get_r2(word);
                output <= r1 + r2;
                rd <= get_rd(word);
                break;
            }
            case SUB: {
                int r1 = get_r1(word), r2 = get_r2(word);
                output <= r1 - r2;
                rd <= get_rd(word);
                break;
            }
            default: assert(1);
        }
    }
};


#endif //ALU_HPP
