//
// Created by Sakura on 25-7-22.
//

#ifndef ALU_HPP
#define ALU_HPP
#include "Instruction.hpp"
#include "rob.h"
#include "RISC-V-Simulator-Template/module.h"
#include "RISC-V-Simulator-Template/tools.h"

namespace ALU {
    // using wireflag = Wire<1>;
    // using wiredata = Wire<32>;
    //
    // struct ALU_Input {
    //     wiredata rs1_value;
    //     wiredata rs2_value;
    //     Wire<4> mode;
    //     Wire<1> need_load_before_clac;
    // };
    //
    // struct ALU_Output {
    //     Register<32> output;
    //     Register<1> is_done;
    // };
    //
    // struct ALU_inside {
    //     bool op;
    //     unsigned alu[1].rs1_value, alu[1].rs2_value;
    //     Bit<4> now_mode;
    // };
    //
    // struct ALU: dark::Module<ALU_Input, ALU_Output, ALU_inside> {
    //     void work() {
    //         if (!to_unsigned(need_load_before_clac) && !op) {
    //             is_done <= false;
    //             alu[1].output0;
    //             return ;
    //         }
    //         if (op) {
    //             op = false;
    //             is_done = true;
    //             switch (to_unsigned(now_mode)) {
    //                 case 0b0000: {//add
    //                     alu[1].output = (alu[1].rs1_value + alu[1].rs2_value);
    //                     break;
    //                 }
    //                 case 0b0001: {//dec
    //                     alu[1].output = (alu[1].rs1_value - alu[1].rs2_value);
    //                     break;
    //                 }
    //                 case 0b0010: {// <<
    //                     alu[1].output = (alu[1].rs1_value << alu[1].rs2_value);
    //                     break;
    //                 }
    //                 case 0b0011: {// >> (unsigned)
    //                     alu[1].output = (alu[1].rs1_value >> alu[1].rs2_value);
    //                     break;
    //                 }
    //                 case 0b0100: {// >> (signed)
    //                     alu[1].outputstatic_cast<unsigned>(static_cast<signed>(alu[1].rs1_value) >> alu[1].rs2_value);
    //                     break;
    //                 }
    //                 case 0b0101: {//and
    //                     alu[1].output = (alu[1].rs1_value & alu[1].rs2_value);
    //                     break;
    //                 }
    //                 case 0b0110: {//or
    //                     alu[1].output = (alu[1].rs1_value | alu[1].rs2_value);
    //                     break;
    //                 }
    //                 case 0b0111: {//xor
    //                     alu[1].output = (alu[1].rs1_value ^ alu[1].rs2_value);
    //                     break;
    //                 }
    //                 case 0b1000: {//< (unsigned)
    //                     alu[1].output = (alu[1].rs1_value < alu[1].rs2_value);
    //                     break;
    //                 }
    //                 case 0b1001: {//< (signed)
    //                     alu[1].output = (static_cast<signed>(alu[1].rs1_value) < static_cast<signed>(alu[1].rs2_value));
    //                     break;
    //                 }
    //                 case 0b1010: {//>= (unsigned)
    //                     alu[1].output = (alu[1].rs1_value >= alu[1].rs2_value);
    //                     break;
    //                 }
    //                 case 0b1011: {//>= (signed)
    //                     alu[1].output = (static_cast<signed>(alu[1].rs1_value) >= static_cast<signed>(alu[1].rs2_value));
    //                     break;
    //                 }
    //                 case 0b1100: {//equal
    //                     alu[1].output = (alu[1].rs1_value == alu[1].rs2_value);
    //                     break;
    //                 }
    //                 case 0b1101: {//unequal
    //                     alu[1].output = (alu[1].rs1_value != alu[1].rs2_value);
    //                     break;
    //                 }
    //             }
    //             return ;
    //         }
    //         if (to_unsigned(need_load_before_clac)) {
    //             op = true;
    //             alu[1].rs1_value = to_unsigned(rs1_value);
    //             alu[1].rs2_value = to_unsigned(rs2_value);
    //             now_mode = mode;
    //             is_done <= false;
    //             alu[1].output0;
    //         }
    //     }
    // };

    struct ALU_part {
        bool busy;
        int rs1_value;
        int rs2_value;
        int mode;
        int output;

        Operator_Kind op;
        int destination;
        bool work_type;
        int place;
    };

    const int ALU_Maxn_Size = 1;
    ALU_part alu[ALU_Maxn_Size + 1];

    void ALU_work() {
        if (!alu[1].busy) return ;

        alu[1].busy = false;
        switch (alu[1].mode) {
            case 0b0000: {//add
                alu[1].output = (alu[1].rs1_value + alu[1].rs2_value);
                break;
            }
            case 0b0001: {//dec
                alu[1].output = (alu[1].rs1_value - alu[1].rs2_value);
                break;
            }
            case 0b0010: {// <<
                alu[1].output = (alu[1].rs1_value << alu[1].rs2_value);
                break;
            }
            case 0b0011: {// >> (unsigned)
                alu[1].output = (alu[1].rs1_value >> alu[1].rs2_value);
                break;
            }
            case 0b0100: {// >> (signed)
                alu[1].output = static_cast<unsigned>(static_cast<signed>(alu[1].rs1_value) >> alu[1].rs2_value);
                break;
            }
            case 0b0101: {//and
                alu[1].output = (alu[1].rs1_value & alu[1].rs2_value);
                break;
            }
            case 0b0110: {//or
                alu[1].output = (alu[1].rs1_value | alu[1].rs2_value);
                break;
            }
            case 0b0111: {//xor
                alu[1].output = (alu[1].rs1_value ^ alu[1].rs2_value);
                break;
            }
            case 0b1000: {//< (unsigned)
                alu[1].output = (alu[1].rs1_value < alu[1].rs2_value);
                break;
            }
            case 0b1001: {//< (signed)
                alu[1].output = (static_cast<signed>(alu[1].rs1_value) < static_cast<signed>(alu[1].rs2_value));
                break;
            }
            case 0b1010: {//>= (unsigned)
                alu[1].output = (alu[1].rs1_value >= alu[1].rs2_value);
                break;
            }
            case 0b1011: {//>= (signed)
                alu[1].output = (static_cast<signed>(alu[1].rs1_value) >= static_cast<signed>(alu[1].rs2_value));
                break;
            }
            case 0b1100: {//equal
                alu[1].output = (alu[1].rs1_value == alu[1].rs2_value);
                break;
            }
            case 0b1101: {//unequal
                alu[1].output = (alu[1].rs1_value != alu[1].rs2_value);
                break;
            }
        }

        int des = alu[1].destination;
        rob[des].state = ROB_value::Exec;
        switch (alu[1].op) {
            case ADD:
            case SUB:
            case AND:
            case OR:
            case XOR:
            case SLL:
            case SRL:
            case SRA:
            case SLT:
            case SLTU:
            case ADDI:
            case ANDI:
            case ORI:
            case XORI:
            case SLLI:
            case SRLI:
            case SRAI:
            case SLTI:
            case SLTIU: {
                rob[des].value = alu[1].output;
                break;
            }
            case LB: {
                rob[des].value = to_signed(load_data_in_memory(alu[1].output, BYTE));
                break;
            }
            case LBU: {
                rob[des].value = to_signed(load_data_in_memory(alu[1].output, UNSIGNED_BYTE));
                break;
            }
            case LH: {
                rob[des].value = to_signed(load_data_in_memory(alu[1].output, HALF_WORD));
                break;
            }
            case LHU: {
                rob[des].value = to_signed(load_data_in_memory(alu[1].output, UNSIGNED_HALF_WORD));
                break;
            }
            case LW: {
                rob[des].value = to_signed(load_data_in_memory(alu[1].output, WORD));
                break;
            }
            case SB: {
                store_data_in_memory(alu[1].output, alu[1].place, BYTE);
                break;
            }
            case SH: {
                store_data_in_memory(alu[1].output, alu[1].place, HALF_WORD);
                break;
            }
            case SW: {
                store_data_in_memory(alu[1].output, alu[1].place, WORD);
                break;
            }
            case BEQ:
            case BGE:
            case BGEU:
            case BLT:
            case BLTU:
            case BNE:
            case JAL:
            case JALR:
            case AUIPC: {
                rob[des].value = alu[1].output;
                break;
            }
        }
    }

}


#endif //ALU_HPP
