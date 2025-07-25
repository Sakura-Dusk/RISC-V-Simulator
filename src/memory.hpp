//
// Created by Sakura on 25-7-22.
//

#ifndef MEMORY_HPP
#define MEMORY_HPP
#include <map>
#include <iostream>
#include "Instruction.hpp"
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
    memory[address] = data & 127;
    if (mode == HALF_WORD || mode == UNSIGNED_HALF_WORD || mode == WORD) {
        memory[address + 1] = (data / 128) & 127;
        if (mode == WORD) {
            memory[address + 2] = (data / 128 / 128) & 127;
            memory[address + 3] = (data / 128 / 128 / 128) & 127;
        }
    }
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
    Wire<1> is_load;
    Wire<1> is_store;
    Wire<32> store_data;
    Wire<3> mode;
};

struct Memory_Output {
    Wire<32> load_data;
};

struct Memory_Inner {
    Register<32> electronic_tick;
};

struct Memory : dark::Module<Memory_Input, Memory_Output, Memory_Inner> {
    void work() override {
        if (electronic_tick >= 5) return ;
        electronic_tick <= (electronic_tick + 1);
        if (electronic_tick == 3) {
            if (is_store) store_data_in_memory(to_unsigned(address), store_data, unsigned_to_Interface_Mode(to_unsigned(mode)));
            if (is_load) load_data <= load_data_in_memory(to_unsigned(address), unsigned_to_Interface_Mode(to_unsigned(mode)));
        }
    }
};

#endif //MEMORY_HPP
