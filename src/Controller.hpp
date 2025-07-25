//
// Created by Sakura on 25-7-24.
//

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include <charconv>

#include "Instruction.hpp"
#include "memory.hpp"
#include "RISC-V-Simulator-Template/tools.h"

using flag = Register<1>;
using number = Register<32>;
using position = Bit<32>;
//
// namespace Controller {
//     struct Instruction {
//         flag is_ready;
//         Operator_Kind op;
//         number rs1_number, rs2_number;
//         number immediate_number;
//         number result;
//         position PC;
//         flag should_end_program;
//     };
// }

//first do it linear

namespace Simple_Controller {
    position PC;
    bool should_end_program;
    int result;

    int reg[32];

    Bit<32> Instruction_Fetch() {
        return load_data_in_memory(to_unsigned(PC));
    }

    void Instruction_Runner(Operator_Kind operator_kind, Bit<32> &instruction) {
        switch (operator_kind) {
            case ADD: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs2 = get_r2(instruction);
                auto rs1_data = reg[rs1];
                auto rs2_data = reg[rs2];
                reg[rd] = rs1_data + rs2_data;
                PC = PC + 4;
                break;
            }
            case SUB: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs2 = get_r2(instruction);
                auto rs1_data = reg[rs1];
                auto rs2_data = reg[rs2];
                reg[rd] = rs1_data - rs2_data;
                PC = PC + 4;
                break;
            }
            case AND: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs2 = get_r2(instruction);
                auto rs1_data = reg[rs1];
                auto rs2_data = reg[rs2];
                reg[rd] = rs1_data & rs2_data;
                PC = PC + 4;
                break;
            }
            case OR: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs2 = get_r2(instruction);
                auto rs1_data = reg[rs1];
                auto rs2_data = reg[rs2];
                reg[rd] = rs1_data | rs2_data;
                PC = PC + 4;
                break;
            }
            case XOR: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs2 = get_r2(instruction);
                auto rs1_data = reg[rs1];
                auto rs2_data = reg[rs2];
                reg[rd] = rs1_data ^ rs2_data;
                PC = PC + 4;
                break;
            }
            case SLL: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs2 = get_r2(instruction);
                auto rs1_data = reg[rs1];
                auto rs2_data = reg[rs2];
                reg[rd] = rs1_data << rs2_data;
                PC = PC + 4;
                break;
            }
            case SRL: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs2 = get_r2(instruction);
                auto rs1_data = reg[rs1];
                auto rs2_data = reg[rs2];
                reg[rd] = static_cast<unsigned int>(rs1_data) >> rs2_data;
                PC = PC + 4;
                break;
            }
            case SRA: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs2 = get_r2(instruction);
                auto rs1_data = reg[rs1];
                auto rs2_data = reg[rs2];
                reg[rd] = rs1_data >> rs2_data;
                PC = PC + 4;
                break;
            }
            case SLT: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs2 = get_r2(instruction);
                auto rs1_data = reg[rs1];
                auto rs2_data = reg[rs2];
                reg[rd] = rs1_data < rs2_data ? 1 : 0;
                PC = PC + 4;
                break;
            }
            case SLTU: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs2 = get_r2(instruction);
                auto rs1_data = reg[rs1];
                auto rs2_data = reg[rs2];
                reg[rd] = static_cast<unsigned int>(rs1_data) < static_cast<unsigned int>(rs2_data) ? 1 : 0;
                PC = PC + 4;
                break;
            }
            case ADDI: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                auto imm = get_imm(instruction, ADDI);
                auto output = rs1_data + imm;

                if (instruction == 0x0ff00513) {
                    result = reg[rd] & 255;
                    should_end_program = true;
                    break;
                }

                reg[rd] = output;
                PC = PC + 4;
                break;
            }
            case ANDI: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                auto imm = get_imm(instruction, ANDI);
                reg[rd] = rs1_data & imm;
                PC = PC + 4;
                break;
            }
            case ORI: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                auto imm = get_imm(instruction, ORI);
                reg[rd] = rs1_data | imm;
                PC = PC + 4;
                break;
            }
            case XORI: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                auto imm = get_imm(instruction, XORI);
                reg[rd] = rs1_data ^ imm;
                PC = PC + 4;
                break;
            }
            case SLLI: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                auto imm = get_imm(instruction, SLLI);
                reg[rd] = rs1_data << imm;
                PC = PC + 4;
                break;
            }
            case SRLI: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                int imm = get_imm(instruction, SRLI);
                reg[rd] = static_cast<unsigned int>(rs1_data) >> imm;
                PC = PC + 4;
                break;
            }
            case SRAI: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                int imm = get_imm(instruction, SRAI);
                reg[rd] = rs1_data >> imm;
                PC = PC + 4;
                break;
            }
            case SLTI: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                int imm = get_imm(instruction, SLTI);
                reg[rd] = rs1_data < imm ? 1 : 0;
                PC = PC + 4;
                break;
            }
            case SLTIU: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                unsigned int imm = get_imm(instruction, SLTI);
                reg[rd] = static_cast<unsigned int>(rs1_data) < imm ? 1 : 0;
                PC = PC + 4;
                break;
            }
            case LB: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                int imm = get_imm(instruction, LB);
                auto read_address = rs1_data + imm;
                reg[rd] = to_signed(load_data_in_memory(read_address, BYTE));
                PC = PC + 4;
                break;
            }
            case LBU: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                unsigned int imm = get_imm(instruction, LBU);
                auto read_address = static_cast<unsigned int>(rs1_data) + imm;
                reg[rd] = to_signed(load_data_in_memory(read_address, UNSIGNED_BYTE));
                PC = PC + 4;
                break;
            }
            case LH: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                int imm = get_imm(instruction, LH);
                auto read_address = rs1_data + imm;
                reg[rd] = to_signed(load_data_in_memory(read_address, HALF_WORD));
                PC = PC + 4;
                break;
            }
            case LHU: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                unsigned int imm = get_imm(instruction, LHU);
                auto read_address = static_cast<unsigned int>(rs1_data) + imm;
                reg[rd] = to_signed(load_data_in_memory(read_address, UNSIGNED_HALF_WORD));
                PC = PC + 4;
                break;
            }
            case LW: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                unsigned int imm = get_imm(instruction, LW);
                auto read_address = static_cast<unsigned int>(rs1_data) + imm;
                reg[rd] = to_signed(load_data_in_memory(read_address, WORD));
                PC = PC + 4;
                break;
            }
            case SB: {
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                auto rs2 = get_r2(instruction);
                auto rs2_data = reg[rs2];
                unsigned int imm = get_imm(instruction, SB);
                auto write_address = static_cast<unsigned int>(rs1_data) + imm;
                store_data_in_memory(write_address, rs2_data, BYTE);
                PC = PC + 4;
                break;
            }
            case SH: {
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                auto rs2 = get_r2(instruction);
                auto rs2_data = reg[rs2];
                unsigned int imm = get_imm(instruction, SH);
                auto write_address = static_cast<unsigned int>(rs1_data) + imm;
                store_data_in_memory(write_address, rs2_data, HALF_WORD);
                PC = PC + 4;
                break;
            }
            case SW: {
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                auto rs2 = get_r2(instruction);
                auto rs2_data = reg[rs2];
                unsigned int imm = get_imm(instruction, SW);
                auto write_address = static_cast<unsigned int>(rs1_data) + imm;
                store_data_in_memory(write_address, rs2_data, WORD);
                PC = PC + 4;
                break;
            }
            case BEQ: {
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                auto rs2 = get_r2(instruction);
                auto rs2_data = reg[rs2];
                auto imm = get_imm(instruction, BEQ);
                if (rs1_data == rs2_data) PC = PC + imm;
                else PC = PC + 4;
                break;
            }
            case BGE: {
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                auto rs2 = get_r2(instruction);
                auto rs2_data = reg[rs2];
                auto imm = get_imm(instruction, BGE);
                if (rs1_data >= rs2_data) PC = PC + imm;
                else PC = PC + 4;
                break;
            }
            case BGEU: {
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                auto rs2 = get_r2(instruction);
                auto rs2_data = reg[rs2];
                auto imm = get_imm(instruction, BGEU);
                if (static_cast<unsigned int>(rs1_data) >= static_cast<unsigned int>(rs2_data)) PC = PC + imm;
                else PC = PC + 4;
                break;
            }
            case BLT: {
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                auto rs2 = get_r2(instruction);
                auto rs2_data = reg[rs2];
                auto imm = get_imm(instruction, BLT);
                if (rs1_data < rs2_data) PC = PC + imm;
                else PC = PC + 4;
                break;
            }
            case BLTU: {
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                auto rs2 = get_r2(instruction);
                auto rs2_data = reg[rs2];
                auto imm = get_imm(instruction, BLTU);
                if (static_cast<unsigned int>(rs1_data) < static_cast<unsigned int>(rs2_data)) PC = PC + imm;
                else PC = PC + 4;
                break;
            }
            case BNE: {
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                auto rs2 = get_r2(instruction);
                auto rs2_data = reg[rs2];
                auto imm = get_imm(instruction, BNE);
                if (rs1_data != rs2_data) PC = PC + imm;
                else PC = PC + 4;
                break;
            }
            case JAL: {
                auto rd = get_rd(instruction);
                auto imm = get_imm(instruction, JAL);
                reg[rd] = to_signed(PC) + 4;
                PC = PC + imm;
                break;
            }
            case JALR: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto rs1_data = reg[rs1];
                auto imm = get_imm(instruction, JALR);;
                reg[rd] = to_signed(PC) + 4;
                PC = rs1_data + imm;
                break;
            }
            case AUIPC: {
                auto rd = get_rd(instruction);
                auto imm = get_imm(instruction, AUIPC);
                imm = imm << 12;
                reg[rd] = to_signed(PC + imm);
                PC = PC + 4;
                break;
            }
            case LUI: {
                auto rd = get_rd(instruction);
                auto imm = get_imm(instruction, LUI);

                imm = imm << 12;
                reg[rd] = imm;
                PC = PC + 4;
                break;
            }
            default: throw;
        }
        reg[0] = 0;
    }

    void Run_once() {
        Bit<32> instruction = Instruction_Fetch();

        // std::cerr << "PC = " << to_unsigned(PC) << std::endl;
        // std::cerr << "instruction = " << to_unsigned(instruction) << std::endl;

        Operator_Kind operator_kind = decode_operator(instruction);

        if (operator_kind == ERROR_KIND) {
            std::cerr << "Fail to decode the instruction!\n PC = " << to_unsigned(PC);
            exit(0);
        }

        Instruction_Runner(operator_kind, instruction);
    }
}

#endif //CONTROLLER_HPP
