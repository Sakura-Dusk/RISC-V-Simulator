//
// Created by Sakura on 25-7-21.
//

#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include<iostream>

enum Operator_Kind {
    LUI,
    AUIPC,
    JAL,
    JALR,
    BEQ,
    BNE,
    BLT,
    BGE,
    BLTU,
    BGEU,
    LB,
    LH,
    LW,
    LBU,
    LHU,
    SB,
    SH,
    SW,
    ADDI,
    SLTI,
    SLTIU,
    XORI,
    ORI,
    ANDI,
    SLLI,
    SRLI,
    SRAI,
    ADD,
    SUB,
    SLL,
    SLT,
    SLTU,
    XOR,
    SRL,
    SRA,
    OR,
    AND,
    ERROR_KIND,
};

int sixteen_to_ten(char x) {
    if (x <= '9' && x >= '0') return x - '0';
    return x - 'A' + 10;
}

int decode_two(std::string s) {
    return sixteen_to_ten(s[1]) + sixteen_to_ten(s[0]) * 16;
}

Operator_Kind decode_operator(int word) {
    int opcode = word & 127;
    switch (opcode) {
        case 0b0110111: return LUI;
        case 0b0010111: return AUIPC;
        case 0b1101111: return JAL;
        case 0b1100111: return JALR;
        case 0b1100011: {
            int Funct3 = (word >> 12) & 7;
            switch (Funct3) {
                case 0b000: return BEQ;
                case 0b001: return BNE;
                case 0b100: return BLT;
                case 0b101: return BGE;
                case 0b110: return BLTU;
                case 0b111: return BGEU;
                default: return ERROR_KIND;
            }
        }
        case 0b0000011: {
            int Funct3 = (word >> 12) & 7;
            switch (Funct3) {
                case 0b000: return LB;
                case 0b001: return LH;
                case 0b010: return LW;
                case 0b100: return LBU;
                case 0b101: return LHU;
                default: return ERROR_KIND;
            }
        }
        case 0b0100011: {
            int Funct3 = (word >> 12) & 7;
            switch (Funct3) {
                case 0b000: return SB;
                case 0b001: return SH;
                case 0b010: return SW;
                default: return ERROR_KIND;
            }
        }
        case 0b0010011: {
            int Funct3 = (word >> 12) & 7;
            switch (Funct3) {
                case 0b000: return ADDI;
                case 0b010: return SLTI;
                case 0b011: return SLTIU;
                case 0b100: return XORI;
                case 0b110: return ORI;
                case 0b111: return ANDI;
                case 0b001: return SLLI;
                case 0b101: {
                    int Funct7 = (word >> 25) & 127;
                    switch (Funct7) {
                        case 0b0000000: return SRLI;
                        case 0b0100000: return SRAI;
                        default: return ERROR_KIND;
                    }
                }
                default: return ERROR_KIND;
            }
        }
        case 0b0110011: {
            int Funct3 = (word >> 12) & 7;
            switch (Funct3) {
                case 0b000: {
                    int Funct7 = (word >> 25) & 127;
                    switch (Funct7) {
                        case 0b0000000: return ADD;
                        case 0b0100000: return SUB;
                        default: return ERROR_KIND;
                    }
                }
                case 0b001: return SLL;
                case 0b010: return SLT;
                case 0b011: return SLTU;
                case 0b100: return XOR;
                case 0b101: {
                    int Funct7 = (word >> 25) & 127;
                    switch (Funct7) {
                        case 0b0000000: return SRL;
                        case 0b0100000: return SRA;
                        default: return ERROR_KIND;
                    }
                }
                case 0b110: return OR;
                case 0b111: return AND;
                default: return ERROR_KIND;
            }
        }
        default: return ERROR_KIND;
    }
}

#endif //INSTRUCTION_HPP
