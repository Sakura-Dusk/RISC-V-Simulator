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

namespace Controller {
    struct Data_Not_Sure {
        number data;
        flag not_sure;
    };

    struct Instruction {
        flag inside;
        flag is_ready;
        Operator_Kind op;
        number rs1, rs2;
        flag rs1_sure, rs2_sure;
        number immediate_number;
        number result;
        position PC;
        flag should_end_program;
    };

    struct Regist {
        Register<32> data;
        flag is_in_clac;
        number clac_id;
    };

    struct Rstype {
        Instruction reservation_staion[16];
        bool have_value[16];
    };
}

//first do it linear

namespace Simple_Controller {
    position PC;
    bool should_end_program;
    int result;

    int reg[32];

void cerr_write_Operator_Kind(Operator_Kind op, Bit<32> instruction) {
    if (instruction == 0x00008067) {
        std::cerr << "ret\n";
        return ;
    }
    switch (op) {
        case LUI:
            std::cerr << "LUI " << get_reg_name(get_rd(instruction)) << " " << std::hex << get_imm(instruction, LUI) << std::dec << std::endl;
            break;
        case AUIPC:
            std::cerr << "AUIPC " << get_reg_name(get_rd(instruction)) << " " << get_imm(instruction, AUIPC) << std::endl;
            break;
        case JAL:
            std::cerr << "JAL " << get_reg_name(get_rd(instruction)) << " " << std::hex << to_unsigned(PC) + get_imm(instruction, JAL) << std::dec << std::endl;
            break;
        case JALR:
            std::cerr << "JALR " << get_reg_name(get_rd(instruction)) << " " << get_reg_name(get_r1(instruction)) << " " << get_imm(instruction, JALR) << std::endl;
            break;
        case BEQ:
            std::cerr << "BEQ " << get_reg_name(get_r1(instruction)) << " " << get_reg_name(get_r2(instruction)) << " " << std::hex << to_unsigned(PC) + get_imm(instruction, BEQ) << std::dec << std::endl;
            break;
        case BNE:
            std::cerr << "BNE " << get_reg_name(get_r1(instruction)) << " " << get_reg_name(get_r2(instruction)) << " " << std::hex << to_unsigned(PC) + get_imm(instruction, BNE) << std::dec << std::endl;
            break;
        case BLT:
            std::cerr << "BLT " << get_reg_name(get_r1(instruction)) << " " << get_reg_name(get_r2(instruction)) << " " << std::hex << to_unsigned(PC) + get_imm(instruction, BLT) << std::dec << std::endl;
            break;
        case BGE:
            std::cerr << "BGE " << get_reg_name(get_r1(instruction)) << " " << get_reg_name(get_r2(instruction)) << " " << std::hex << to_unsigned(PC) + get_imm(instruction, BGE) << std::dec << std::endl;
            break;
        case BLTU:
            std::cerr <<"BLTU " << get_reg_name(get_r1(instruction)) << " " << get_reg_name(get_r2(instruction)) << " " << std::hex << to_unsigned(PC) + get_imm(instruction, BLTU) << std::dec << std::endl;
            break;
        case BGEU:
            std::cerr << "BGEU " << get_reg_name(get_r1(instruction)) << " " << get_reg_name(get_r2(instruction)) << " " << to_unsigned(PC) + get_imm(instruction, BGEU) << std::endl;
            break;
        case LB:
            std::cerr << "LB " << get_reg_name(get_rd(instruction)) << " " << get_imm(instruction, LB) << "(" << get_reg_name(get_r1(instruction)) << ")\n";
            break;
        case LH:
            std::cerr << "LH " << get_reg_name(get_rd(instruction)) << " " << get_imm(instruction, LH) << "(" << get_reg_name(get_r1(instruction)) << ")\n";
            break;
        case LW:
            std::cerr << "LW " << get_reg_name(get_rd(instruction)) << " " << get_imm(instruction, LW) << "(" << get_reg_name(get_r1(instruction)) << ")\n";
            break;
        case LBU:
            std::cerr << "LBU " << get_reg_name(get_rd(instruction)) << " " << get_imm(instruction, LBU) << "(" << get_reg_name(get_r1(instruction)) << ")\n";
            break;
        case LHU:
            std::cerr << "LHU " << get_reg_name(get_rd(instruction)) << " " << get_imm(instruction, LHU) << "(" << get_reg_name(get_r1(instruction)) << ")\n";
            break;
        case SB:
            std::cerr << "SB " << get_reg_name(get_r2(instruction)) << " " << get_imm(instruction, SB) << "(" << get_reg_name(get_r1(instruction)) << ")\n";
            break;
        case SH:
            std::cerr << "SH " << get_reg_name(get_r2(instruction)) << " " << get_imm(instruction, SH) << "(" << get_reg_name(get_r1(instruction)) << ")\n";
            break;
        case SW:
            std::cerr << "SW " << get_reg_name(get_r2(instruction)) << " " << get_imm(instruction, SW) << "(" << get_reg_name(get_r1(instruction)) << ")\n";
            break;
        case ADDI:
            std::cerr << "ADDI " << get_reg_name(get_rd(instruction)) << " " << get_reg_name(get_r1(instruction)) << " " << get_imm(instruction, ADDI) << std::endl;
            break;
        case SLTI:
            std::cerr << "SLTI " << get_reg_name(get_rd(instruction)) << " " << get_reg_name(get_r1(instruction)) << " " << get_imm(instruction, SLTI) << std::endl;
            break;
        case SLTIU:
            std::cerr << "SLTIU " << get_reg_name(get_rd(instruction)) << " " << get_reg_name(get_r1(instruction)) << " " << get_imm(instruction, SLTIU) << std::endl;
            break;
        case XORI:
            std::cerr << "XORI " << get_reg_name(get_rd(instruction)) << " " << get_reg_name(get_r1(instruction)) << " " << get_imm(instruction, XORI) << std::endl;
            break;
        case ORI:
            std::cerr << "ORI " << get_reg_name(get_rd(instruction)) << " " << get_reg_name(get_r1(instruction)) << " " << get_imm(instruction, ORI) << std::endl;
            break;
        case ANDI:
            std::cerr << "ANDI " << get_reg_name(get_rd(instruction)) << " " << get_reg_name(get_r1(instruction)) << " " << get_imm(instruction, ANDI) << std::endl;
            break;
        case SLLI:
            std::cerr << "SLLI " << get_reg_name(get_rd(instruction)) << " " << get_reg_name(get_r1(instruction)) << " " << get_imm(instruction, SLLI) << std::endl;
            break;
        case SRLI:
            std::cerr << "SRLI " << get_reg_name(get_rd(instruction)) << " " << get_reg_name(get_r1(instruction)) << " " << get_imm(instruction, SRLI) << std::endl;
            break;
        case SRAI:
            std::cerr << "SRAI " << get_reg_name(get_rd(instruction)) << " " << get_reg_name(get_r1(instruction)) << " " << get_imm(instruction, SRAI) << std::endl;
            break;
        case ADD:
            std::cerr << "ADD " << get_reg_name(get_rd(instruction)) << " " << get_reg_name(get_r1(instruction)) << " " << get_reg_name(get_r2(instruction)) << std::endl;
            break;
        case SUB:
            std::cerr << "SUB " << get_reg_name(get_rd(instruction)) << " " << get_reg_name(get_r1(instruction)) << " " << get_reg_name(get_r2(instruction)) << std::endl;
            break;
        case SLL:
            std::cerr << "SLL " << get_reg_name(get_rd(instruction)) << " " << get_reg_name(get_r1(instruction)) << " " << get_reg_name(get_r2(instruction)) << std::endl;
            break;
        case SLT:
            std::cerr << "SLT " << get_reg_name(get_rd(instruction)) << " " << get_reg_name(get_r1(instruction)) << " " << get_reg_name(get_r2(instruction)) << std::endl;
            break;
        case SLTU:
            std::cerr << "SLTU " << get_reg_name(get_rd(instruction)) << " " << get_reg_name(get_r1(instruction)) << " " << get_reg_name(get_r2(instruction)) << std::endl;
            break;
        case XOR:
            std::cerr << "XOR " << get_reg_name(get_rd(instruction)) << " " << get_reg_name(get_r1(instruction)) << " " << get_reg_name(get_r2(instruction)) << std::endl;
            break;
        case SRL:
            std::cerr << "SRL " << get_reg_name(get_rd(instruction)) << " " << get_reg_name(get_r1(instruction)) << " " << get_reg_name(get_r2(instruction)) << std::endl;
            break;
        case SRA:
            std::cerr << "SRA " << get_reg_name(get_rd(instruction)) << " " << get_reg_name(get_r1(instruction)) << " " << get_reg_name(get_r2(instruction)) << std::endl;
            break;
        case OR:
            std::cerr << "OR " << get_reg_name(get_rd(instruction)) << " " << get_reg_name(get_r1(instruction)) << " " << get_reg_name(get_r2(instruction)) << std::endl;
            break;
        case AND:
            std::cerr << "AND " << get_reg_name(get_rd(instruction)) << " " << get_reg_name(get_r1(instruction)) << " " << get_reg_name(get_r2(instruction)) << std::endl;
            break;
        default:
            std::cerr << "ERROR_KIND\n";
            break;
        }
    }

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
                unsigned int imm = get_imm(instruction, LB);
                auto read_address = static_cast<unsigned int>(rs1_data) + imm;
                reg[rd] = to_signed(load_data_in_memory(read_address, BYTE));
                reg[rd] = static_cast<int>(static_cast<unsigned int>(reg[rd]) << 24) >> 24;
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
                unsigned int imm = get_imm(instruction, LH);
                auto read_address = static_cast<unsigned int>(rs1_data) + imm;
                reg[rd] = to_signed(load_data_in_memory(read_address, HALF_WORD));
                reg[rd] = static_cast<int>(static_cast<unsigned int>(reg[rd]) << 16) >> 16;
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
                // std::cerr << "pos = " << read_address << std::endl;
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
                // std::cerr << "pos = " << write_address << std::endl;
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
                reg[rd] = to_signed(PC + 4);
                PC = rs1_data + imm;
                break;
            }
            case AUIPC: {
                auto rd = get_rd(instruction);
                auto imm = get_imm(instruction, AUIPC);

                reg[rd] = to_signed(PC + imm);
                PC = PC + 4;
                break;
            }
            case LUI: {
                auto rd = get_rd(instruction);
                auto imm = get_imm(instruction, LUI);

                reg[rd] = imm;
                PC = PC + 4;
                break;
            }
            default: throw;
        }
        reg[0] = 0;
    }

    int counter = 0;

    void Run_once() {
        Bit<32> instruction = Instruction_Fetch();

        // std::cerr << "PC = " << to_unsigned(PC) << std::endl;
        // std::cerr << "instruction = " << to_unsigned(instruction) << std::endl;

        Operator_Kind operator_kind = decode_operator(instruction);
        cerr_write_Operator_Kind(operator_kind, instruction);

        if (operator_kind == ERROR_KIND) {
            // std::cerr << "Fail to decode the instruction!\n PC = " << to_unsigned(PC);
            exit(0);
        }

        Instruction_Runner(operator_kind, instruction);

        counter++; std::cerr << "counter = " << counter << std::endl;
        for (int i = 0; i < 32; i++) std::cerr << reg[i] << " "; std::cerr << std::endl;
    }
}

// namespace Controller_true {
//     struct Controller_input {
//         Wire<32> ALU_output;
//         Wire<1> ALU_is_done;
//
//         Wire<32> memory_output;
//         Wire<1> memory_is_done;
//     };
//
//     struct Controller_output {
//         Register<1> should_end_program;
//
//         Register<32> ALU_rs1_value;
//         Register<32> ALU_rs2_value;
//         Register<4> ALU_mode;
//         Register<1> ALU_need_load_before_clac;
//
//         Register<32> memory_address;
//         Register<32> memory_imm;
//         Register<1> memory_need_load_in_memory;
//         Register<1> memory_need_clac;
//         Register<32> memory_store_data;
//         Register<3> memory_mode;
//     };
//
//     struct Controller_inside {
//         std::array<Controller::Regist, 32> reg;
//         std::array<Controller::Instruction, 8> Rob;
//         std::array<Controller::Rstype, 8> Rs;
//         Register<4> buffer_head, buffer_tail;
//         Register<32> PC, flush_PC;
//         Register<1> need_flush;
//         Register<32> memory_pos;
//     };
//
//     struct Controller_true: dark::Module<Controller_input, Controller_output, Controller_inside> {
//         bool memory_busy, ALU_busy;
//         int load_pos;
//
//         void flush() {
//             buffer_head.assign(0); buffer_tail.assign(0);
//             PC.assign(flush_PC);
//             for (int i = 0; i < 8; i++) instructions_buffer[i].inside.assign(false);
//             for (int i = 0; i < 32; i++) reg[i].is_in_clac.assign(false);
//             memory_need_clac.assign(false);
//             need_flush.assign(false);
//         }
//
//         void work() {
//             if (need_flush) {
//                 flush(); return ;
//             }
//
//             if (memory_is_done) {
//                 memory_busy = false;
//                 if (load_pos) {
//                     reg[load_pos].data <= memory_output;
//                     instructions_buffer[to_unsigned(memory_pos)].result <= memory_output;
//                 }
//                 instructions_buffer[to_unsigned(memory_pos)].
//             }
//         }
//     };
// }

#endif //CONTROLLER_HPP
