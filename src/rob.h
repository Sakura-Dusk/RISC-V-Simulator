//
// Created by Sakura on 25-8-5.
//

#ifndef ROB_H
#define ROB_H
#include "rrs.h"
#include "rs.h"

int PC;

const int ROB_Maxn_Size = 1;
struct ROB_value {
    enum State_Kind {
        Issue,
        Exec,
    };

    bool busy;
    int instruction;
    State_Kind state;
    int destination;
    int value;

    int now_PC, imm;
};

ROB_value rob[ROB_Maxn_Size + 1];

void ROB_work() {
    if (!rob[1].busy) return ;
    if (rob[1].state == ROB_value::Issue) return ;

    if (rob[1].instruction == 0x0ff00513) {
        std::cout << (rrs[get_rd(rob[1].instruction)].value & 255);
        exit(0);
    }

    Operator_Kind op = decode_operator(rob[1].instruction);

    rob[1].busy = false;
    switch (op) {
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
        case SLTIU:
        case LB:
        case LBU:
        case LH:
        case LHU:
        case LW: {
            rrs[rob[1].destination].value = rob[1].value;
            break;
        }
        case SB:
        case SH:
        case SW: {
            break;
        }
        case BEQ:
        case BGE:
        case BGEU:
        case BLT:
        case BLTU:
        case BNE: {
            if (rob[1].value) PC = rob[1].now_PC + rob[1].imm;
            break;
        }
        case JAL: {
            rrs[rob[1].destination].value = rob[1].now_PC + 4;
            PC = rob[1].value;
            break;
        }
        case JALR: {
            rrs[rob[1].destination].value = rob[1].now_PC + 4;
            PC = rob[1].value;
            break;
        }
        case AUIPC: {
            rrs[rob[1].destination].value = rob[1].value;
            break;
        }
        case LUI: {
            rrs[rob[1].destination].value = rob[1].imm;
        }
    }
    rrs[rob[1].destination].busy = false;
}


#endif //ROB_H
