//
// Created by Sakura on 25-7-22.
//

#ifndef ALU_HPP
#define ALU_HPP
#include "Instruction.hpp"
#include "RISC-V-Simulator-Template/module.h"
#include "RISC-V-Simulator-Template/tools.h"

namespace ALU {
    using wireflag = Wire<1>;
    using wiredata = Wire<32>;

    struct ALU_Input {
        wiredata rs1_value;
        wiredata rs2_value;
        Wire<4> mode;
        Wire<1> need_load_before_clac;
    };

    struct ALU_Output {
        Register<32> output;
        Register<1> is_done;
    };

    struct ALU_inside {
        bool op;
        unsigned now_rs1_value, now_rs2_value;
        Bit<4> now_mode;
    };

    struct ALU: dark::Module<ALU_Input, ALU_Output> {
        void work() {

        }
    };

}


#endif //ALU_HPP
