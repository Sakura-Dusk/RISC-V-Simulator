//
// Created by Sakura on 25-7-21.
//

#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include "Controller.hpp"
#include "RISC-V-Simulator-Template/tools.h"
#include "iostream"
#include "Controller.hpp"

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

int decode_two(std::string &s) {
    return sixteen_to_ten(s[1]) + sixteen_to_ten(s[0]) * 16;
}

Operator_Kind decode_operator(Bit<32> word) {
    auto opcode = to_unsigned(word.range<6, 0>());
    switch (opcode) {
        case 0b0110111: return LUI;
        case 0b0010111: return AUIPC;
        case 0b1101111: return JAL;
        case 0b1100111: return JALR;
        case 0b1100011: {
            auto Funct3 = to_unsigned(word.range<14, 12>());
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
            auto Funct3 = to_unsigned(word.range<14, 12>());
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
            auto Funct3 = to_unsigned(word.range<14, 12>());
            switch (Funct3) {
                case 0b000: return SB;
                case 0b001: return SH;
                case 0b010: return SW;
                default: return ERROR_KIND;
            }
        }
        case 0b0010011: {
            auto Funct3 = to_unsigned(word.range<14, 12>());
            switch (Funct3) {
                case 0b000: return ADDI;
                case 0b010: return SLTI;
                case 0b011: return SLTIU;
                case 0b100: return XORI;
                case 0b110: return ORI;
                case 0b111: return ANDI;
                case 0b001: return SLLI;
                case 0b101: {
                    auto Funct7 = to_unsigned(word.range<31, 25>());
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
            auto Funct3 = to_unsigned(word.range<14, 12>());
            switch (Funct3) {
                case 0b000: {
                    auto Funct7 = to_unsigned(word.range<31, 25>());
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
                    auto Funct7 = to_unsigned(word.range<31, 25>());
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

auto get_r1(Bit<32> word) {
    return to_unsigned(word.range<19, 15>());
}

auto get_r2(Bit<32> word) {
    return to_unsigned(word.range<24, 20>());
}

auto get_rd(Bit<32> word) {
    return to_unsigned(word.range<11, 7>());
}

std::string get_reg_name(unsigned int x) {
    if (x == 0) return "zero";
    if (x == 1) return "ra";
    if (x == 2) return "sp";
    if (x == 3) return "gp";
    if (x == 4) return "tp";
    if (x == 5) return "t0";
    if (x == 6) return "t1";
    if (x == 7) return "t2";
    if (x == 8) return "s0";
    if (x == 9) return "s1";
    if (x == 10) return "a0";
    if (x == 11) return "a1";
    if (x == 12) return "a2";
    if (x == 13) return "a3";
    if (x == 14) return "a4";
    if (x == 15) return "a5";
    if (x == 16) return "a6";
    if (x == 17) return "a7";
    if (x == 18) return "s2";
    if (x == 19) return "s3";
    if (x == 20) return "s4";
    if (x == 21) return "s5";
    if (x == 22) return "s6";
    if (x == 23) return "s7";
    if (x == 24) return "s8";
    if (x == 25) return "s9";
    if (x == 26) return "s10";
    if (x == 27) return "s11";
    if (x == 28) return "t3";
    if (x == 29) return "t4";
    if (x == 30) return "t5";
    if (x == 31) return "t6";
    return "";
}

char ten_to_sixteen(int x) {
    if (x < 10) return '0' + x;
    return 'A' + x - 10;
}

std::string write_16_from_10(int x) {
    if (x == 0) return "0";
    std::string res = "";
    bool rev = false;
    if (x < 0) rev = true, x = -x;
    while (x) {
        res = ten_to_sixteen(x % 16) + res;
        x /= 16;
    }
    if (rev) res = '-' + res;
    return res;
}

auto get_imm(Bit<32> word, Operator_Kind opk) {
    int res = 0;
    switch (opk) {
        case LUI:
        case AUIPC:
            res = to_signed(Bit(word.range<31, 12>(), Bit<12>()));
            break;
        case JAL:
            res = to_signed(Bit(word.range<31, 31>(), word.range<19, 12>(), word.range<20, 20>(), word.range<30, 21>(), Bit<1>()));
            break;
        case JALR:
        case LB:
        case LH:
        case LW:
        case LBU:
        case LHU:
        case ADDI:
        case SLTI:
        case SLTIU:
        case XORI:
        case ORI:
        case ANDI:
            res = to_signed(Bit(word.range<31, 20>()));
            break;
        case SLLI:
        case SRLI:
        case SRAI:
            res = to_signed(Bit(word.range<24, 20>()));
            break;
        case BEQ:
        case BNE:
        case BLT:
        case BGE:
        case BLTU:
        case BGEU:
            res = to_signed(Bit(word.range<31, 31>(), word.range<7, 7>(), word.range<30, 25>(), word.range<11, 8>(), Bit<1>()));
            break;
        case SB:
        case SH:
        case SW:
            res = to_signed(Bit(word.range<31, 25>(), word.range<11, 7>()));
            break;
        default: break;
    }
    return res;
}

#endif //INSTRUCTION_HPP
