//
// Created by Sakura on 25-8-4.
//

#ifndef RS_H
#define RS_H
#include "ALU.hpp"
#include "Instruction.hpp"

const int RS_MAXN_SIZE = 1;

struct RS_value {
    bool busy;
    Operator_Kind op;
    int PC;
    int vj, vk;
    int qj, qk;
    int a;
    int destination;
};

// RS_value load_RS[RS_MAXN_SIZE];
// RS_value add_RS[RS_MAXN_SIZE];
RS_value rs[RS_MAXN_SIZE + 1];

void RS_work() {
    if (rs[1].busy && rs[1].qj == 0 && rs[1].qk == 0 && ALU::alu[1].busy == false) {
        ALU::alu[1].busy = true;
        rs[1].busy = false;
        ALU::alu[1].destination = rs[1].destination;
        ALU::alu[1].op = rs[1].op;
        switch (rs[1].op) {
            case ADD: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].vk;
                ALU::alu[1].mode = 0b0000;
                break;
            }
            case SUB: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].vk;
                ALU::alu[1].mode = 0b0001;
                break;
            }
            case AND: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].vk;
                ALU::alu[1].mode = 0b0101;
                break;
            }
            case OR: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].vk;
                ALU::alu[1].mode = 0b0110;
                break;
            }
            case XOR: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].vk;
                ALU::alu[1].mode = 0b0111;
                break;
            }
            case SLL: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].vk;
                ALU::alu[1].mode = 0b0010;
                break;
            }
            case SRL: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].vk;
                ALU::alu[1].mode = 0b0011;
                break;
            }
            case SRA: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].vk;
                ALU::alu[1].mode = 0b0100;
                break;
            }
            case SLT: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].vk;
                ALU::alu[1].mode = 0b1001;
                break;
            }
            case SLTU: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].vk;
                ALU::alu[1].mode = 0b1000;
                break;
            }
            case ADDI: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].a;
                ALU::alu[1].mode = 0b0000;
                break;
            }
            case ANDI: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].a;
                ALU::alu[1].mode = 0b0101;
                break;
            }
            case ORI: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].a;
                ALU::alu[1].mode = 0b0110;
                break;
            }
            case XORI: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].a;
                ALU::alu[1].mode = 0b0111;
                break;
            }
            case SLLI: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].a;
                ALU::alu[1].mode = 0b0010;
                break;
            }
            case SRLI: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].a;
                ALU::alu[1].mode = 0b0011;
                break;
            }
            case SRAI: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].a;
                ALU::alu[1].mode = 0b0100;
                break;
            }
            case SLTI: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].a;
                ALU::alu[1].mode = 0b1001;
                break;
            }
            case SLTIU: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].a;
                ALU::alu[1].mode = 0b1000;
                break;
            }
            case LB:
            case LBU:
            case LH:
            case LHU:
            case LW: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].a;
                ALU::alu[1].mode = 0b0000;
                break;
            }
            case SB:
            case SH:
            case SW: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].a;
                ALU::alu[1].place = rs[1].vk;
                ALU::alu[1].mode = 0b0000;
                break;
            }
            case BEQ: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].vk;
                ALU::alu[1].place = rs[1].a;
                ALU::alu[1].mode = 0b1100;
                break;
            }
            case BGE: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].vk;
                ALU::alu[1].place = rs[1].a;
                ALU::alu[1].mode = 0b1011;
                break;
            }
            case BGEU: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].vk;
                ALU::alu[1].place = rs[1].a;
                ALU::alu[1].mode = 0b1010;
                break;
            }
            case BLT: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].vk;
                ALU::alu[1].place = rs[1].a;
                ALU::alu[1].mode = 0b1001;
                break;
            }
            case BLTU: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].vk;
                ALU::alu[1].place = rs[1].a;
                ALU::alu[1].mode = 0b1000;
                break;
            }
            case BNE: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].vk;
                ALU::alu[1].place = rs[1].a;
                ALU::alu[1].mode = 0b1101;
                break;
            }
            case JAL: {
                ALU::alu[1].rs1_value = rs[1].PC;
                ALU::alu[1].rs2_value = rs[1].a;
                ALU::alu[1].mode = 0b0000;
                break;
            }
            case JALR: {
                ALU::alu[1].rs1_value = rs[1].vj;
                ALU::alu[1].rs2_value = rs[1].a;
                ALU::alu[1].mode = 0b0000;
                break;
            }
            case AUIPC: {
                ALU::alu[1].rs1_value = rs[1].PC;
                ALU::alu[1].rs2_value = rs[1].a;
                ALU::alu[1].mode = 0b0000;
                break;
            }
            default: break;
        }

    }
}

#endif //RS_H
