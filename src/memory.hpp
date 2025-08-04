//
// Created by Sakura on 25-7-22.
//

#ifndef MEMORY_HPP
#define MEMORY_HPP
#include <map>
#include <iostream>

#include "Controller.hpp"
#include "Instruction.hpp"
#include "Value.h"
#include "RISC-V-Simulator-Template/tools.h"

std::map<unsigned int, unsigned int> memory;

enum Interface_Mode {
    BYTE,
    UNSIGNED_BYTE,
    HALF_WORD,
    UNSIGNED_HALF_WORD,
    WORD,
};

unsigned int Interface_Mode_to_unsigned(Interface_Mode x) {
    if (x == BYTE) return 0;
    if (x == UNSIGNED_BYTE) return 1;
    if (x == HALF_WORD) return 2;
    if (x == UNSIGNED_HALF_WORD) return 3;
    if (x == WORD) return 4;
    return 5;
}

Interface_Mode unsigned_to_Interface_Mode(unsigned int x) {
    if (x == 0) return BYTE;
    if (x == 1) return UNSIGNED_BYTE;
    if (x == 2) return HALF_WORD;
    if (x == 3) return UNSIGNED_HALF_WORD;
    if (x == 4) return WORD;
    return WORD;
}

void store_data_in_memory(const unsigned int address, const Bit<32> &data, const Interface_Mode mode = WORD) {
    memory[address] = to_unsigned(data.range<7, 0>());
    if (mode == HALF_WORD || mode == UNSIGNED_HALF_WORD || mode == WORD) {
        memory[address + 1] = to_unsigned(data.range<15, 8>());
        if (mode == WORD) {
            memory[address + 2] = to_unsigned(data.range<23, 16>());
            memory[address + 3] = to_unsigned(data.range<31, 24>());
        }
    }
}

void store_data_in_memory(const unsigned int address, const unsigned int &data, const Interface_Mode mode = WORD) {
    memory[address] = data & 255;
    if (mode == HALF_WORD || mode == UNSIGNED_HALF_WORD || mode == WORD) {
        memory[address + 1] = (data / 256) & 255;
        if (mode == WORD) {
            memory[address + 2] = (data / 256 / 256) & 255;
            memory[address + 3] = (data / 256 / 256 / 256) & 255;
        }
    }
    // std::cerr << "store data ---" << memory[address] << " " << memory[address + 1] << " " << memory[address + 2] << " " << memory[address + 3] << std::endl;
}

Bit<32> load_data_in_memory(const unsigned int address, const Interface_Mode mode = WORD) {
        switch (mode) {
            case BYTE: {
                Bit<8> data;
                data.set<7,0>(memory[address]);
                return to_signed(data);
            }
            case UNSIGNED_BYTE: {
                Bit<16> data;
                data.set<7,0>(memory[address]);
                return to_unsigned(data);
            }
            case HALF_WORD: {
                Bit<16> data;
                data.set<7,0>(memory[address]);
                data.set<15,8>(memory[address + 1]);
                return to_signed(data);
            }
            case UNSIGNED_HALF_WORD: {
                Bit<32> data;
                data.set<7,0>(memory[address]);
                data.set<15,8>(memory[address + 1]);
                return to_unsigned(data);
            }
            case WORD: {
                // std::cerr << memory[address] << " " << memory[address + 1] << " " << memory[address + 2] << " " << memory[address + 3] << std::endl;

                Bit<32> data;
                // std::cerr << "data = " << to_unsigned(data) << std::endl;
                data.set<7,0>(memory[address]);
                // std::cerr << "memory[" << address << "] = " << memory[address] << std::endl;
                // std::cerr << "data = " << to_unsigned(data) << std::endl;
                data.set<15,8>(memory[address + 1]);
                // std::cerr << "memory[" << address + 1 << "] = "  << memory[address + 1] << std::endl;
                // std::cerr << "data = " << to_unsigned(data) << std::endl;
                data.set<23,16>(memory[address + 2]);
                // std::cerr << "memory[" << address + 2 << "] = "  << memory[address + 2] << std::endl;
                // std::cerr << "data = " << to_unsigned(data) << std::endl;
                data.set<31,24>(memory[address + 3]);
                // std::cerr << "memory[" << address + 3 << "] = "  << memory[address + 3] << std::endl;
                // std::cerr << "data = " << to_unsigned(data) << std::endl;
                return data;
            }
            default: {
                Bit<32> data;
                return data;
            }
        }
    }

void load_instructions() {
    unsigned int  current_positions = 0;
    std::string str;
    while (std::cin >> str) {
        if (str[0] == '@') {
            unsigned int next_positions = 0;
            for (int i = 1; i <= 8; i++)
                next_positions = next_positions * 16 + sixteen_to_ten(str[i]);
            current_positions = next_positions;
        }
        else {
            memory[current_positions] = decode_two(str);
            // std::cerr << "memory[" << current_positions << "] = " << memory[current_positions] << std::endl;
            current_positions++;
        }
    }
}

struct Memory_Input {
    Wire<32> address;
    Wire<32> imm;
    Wire<1> need_load_in_memory;
    Wire<1> need_clac;
    Wire<32> store_data;
    Wire<3> mode;
};

struct Memory_Output {
    Register<1> is_done;
    Register<32> output;
};

struct Memory_inside {
    bool op;
    unsigned addr, value;
    Bit<3> now_mode;
};

struct Memory : dark::Module<Memory_Input, Memory_Output, Memory_inside> {
    void work() override {
        if (!to_unsigned(need_clac) && !op) {
            is_done <= false;
            output <= 0;
            return ;
        }
        if (op) {
            op = false;
            is_done <= true;
            switch (to_unsigned(now_mode)) {
                case 0b000: {//load byte
                    output <= load_data_in_memory(addr, BYTE);
                    break;
                }
                case 0b001: {//load unsigned byte
                    output <= load_data_in_memory(addr, UNSIGNED_BYTE);
                    break;
                }
                case 0b010: {//load half word
                    output <= load_data_in_memory(addr, HALF_WORD);
                    break;
                }
                case 0b011: {//load unsigned half word
                    output <= load_data_in_memory(addr, UNSIGNED_HALF_WORD);
                    break;
                }
                case 0b100: {//load word
                    output <= load_data_in_memory(addr, WORD);
                    break;
                }
                case 0b101: {//store byte
                    output <= 0;
                    store_data_in_memory(addr, value, BYTE);
                    break;
                }
                case 0b110: {//store half word
                    output <= 0;
                    store_data_in_memory(addr, value, HALF_WORD);
                    break;
                }
                case 0b111: {//store word
                    output <= 0;
                    store_data_in_memory(addr, value, WORD);
                    break;
                }
            }
            return ;
        }
        if (to_unsigned(need_clac)) {
            op = true;
            addr = to_unsigned(address) + to_unsigned(imm);
            value = to_unsigned(store_data);
            now_mode = mode;
            is_done <= false;
            output <= 0;
        }
    }
};

#endif //MEMORY_HPP
