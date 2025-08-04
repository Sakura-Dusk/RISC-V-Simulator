#include "Controller.hpp"
#include "memory.hpp"
#include "rs.h"
#include "rob.h"
#include "rrs.h"


int result;

void launch() {
    int is_free = -1;
    if (!rob[1].busy) is_free = 0;
    if (is_free == -1) return ;

    is_free = -1;
    if (!rs[1].busy) is_free = 0;
    if (is_free == -1) return ;

    int instruction = to_signed(load_data_in_memory(PC));

    rob[1].busy = true;
    rob[1].instruction = instruction;
    rob[1].state = ROB_value::Issue;

    Operator_Kind operator_kind = decode_operator(instruction);

    // Simple_Controller::cerr_write_Operator_Kind(operator_kind, instruction);

    if (operator_kind == LUI) rob[1].state = ROB_value::Exec;
    switch (operator_kind) {
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
        case LW:
        case JAL:
        case JALR:
        case AUIPC:
        case LUI:
            rob[1].destination = get_rd(instruction);
    }
    rob[1].now_PC = PC;
    if (operator_kind == BEQ || operator_kind == BGE || operator_kind == BGEU || operator_kind == BLT || operator_kind == BLTU || operator_kind == BNE) {
        rob[1].imm = get_imm(instruction, operator_kind);
    }
    if (operator_kind == LUI)
        rob[1].imm = get_imm(instruction, operator_kind);



    rs[1].busy = true;
    rs[1].op = operator_kind;
    rs[1].PC = PC;
    rs[1].destination = 1;
    switch (operator_kind) {
        case ADD: {
                auto rs1 = get_r1(instruction);
                auto rs2 = get_r2(instruction);

                if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
                    else rs[1].vj = rrs[rs1].value;
                if (rrs[rs2].busy) rs[1].qk = rrs[rs2].reorder;
                    else rs[1].vk = rrs[rs2].value;

                PC = PC + 4;
                break;
            }
        case SUB: {
                auto rs1 = get_r1(instruction);
                auto rs2 = get_r2(instruction);

                if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
                else rs[1].vj = rrs[rs1].value;
                if (rrs[rs2].busy) rs[1].qk = rrs[rs2].reorder;
                else rs[1].vk = rrs[rs2].value;

                PC = PC + 4;
                break;
            }
        case AND: {
            auto rs1 = get_r1(instruction);
            auto rs2 = get_r2(instruction);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            if (rrs[rs2].busy) rs[1].qk = rrs[rs2].reorder;
            else rs[1].vk = rrs[rs2].value;

            PC = PC + 4;
                break;
            }
        case OR: {
            auto rs1 = get_r1(instruction);
            auto rs2 = get_r2(instruction);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            if (rrs[rs2].busy) rs[1].qk = rrs[rs2].reorder;
            else rs[1].vk = rrs[rs2].value;

            PC = PC + 4;
                break;
            }
        case XOR: {
            auto rs1 = get_r1(instruction);
            auto rs2 = get_r2(instruction);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            if (rrs[rs2].busy) rs[1].qk = rrs[rs2].reorder;
            else rs[1].vk = rrs[rs2].value;

            PC = PC + 4;
                break;
            }
        case SLL: {
            auto rs1 = get_r1(instruction);
            auto rs2 = get_r2(instruction);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            if (rrs[rs2].busy) rs[1].qk = rrs[rs2].reorder;
            else rs[1].vk = rrs[rs2].value;

            PC = PC + 4;
                break;
            }
        case SRL: {
            auto rs1 = get_r1(instruction);
            auto rs2 = get_r2(instruction);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            if (rrs[rs2].busy) rs[1].qk = rrs[rs2].reorder;
            else rs[1].vk = rrs[rs2].value;

            PC = PC + 4;
                break;
            }
        case SRA: {
            auto rs1 = get_r1(instruction);
            auto rs2 = get_r2(instruction);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            if (rrs[rs2].busy) rs[1].qk = rrs[rs2].reorder;
            else rs[1].vk = rrs[rs2].value;

            PC = PC + 4;
                break;
            }
        case SLT: {
            auto rs1 = get_r1(instruction);
            auto rs2 = get_r2(instruction);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            if (rrs[rs2].busy) rs[1].qk = rrs[rs2].reorder;
            else rs[1].vk = rrs[rs2].value;

            PC = PC + 4;
                break;
            }
        case SLTU: {
            auto rs1 = get_r1(instruction);
            auto rs2 = get_r2(instruction);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            if (rrs[rs2].busy) rs[1].qk = rrs[rs2].reorder;
            else rs[1].vk = rrs[rs2].value;

            PC = PC + 4;
                break;
            }
            case ADDI: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto imm = get_imm(instruction, ADDI);

                // if (instruction == 0x0ff00513) {
                //     result = reg[rd] & 255;
                //     should_end_program = true;
                //     break;
                // }

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
                else rs[1].vj = rrs[rs1].value;
            rs[1].a = imm;

                PC = PC + 4;
                break;
            }
        case ANDI: {
            auto rd = get_rd(instruction);
            auto rs1 = get_r1(instruction);
            auto imm = get_imm(instruction, ANDI);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            rs[1].a = imm;

            PC = PC + 4;
                break;
            }
        case ORI: {
            auto rd = get_rd(instruction);
            auto rs1 = get_r1(instruction);
            auto imm = get_imm(instruction, ORI);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            rs[1].a = imm;

            PC = PC + 4;
                break;
            }
        case XORI: {
            auto rd = get_rd(instruction);
            auto rs1 = get_r1(instruction);
            auto imm = get_imm(instruction, XORI);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            rs[1].a = imm;

            PC = PC + 4;
                break;
            }
        case SLLI: {
            auto rd = get_rd(instruction);
            auto rs1 = get_r1(instruction);
            auto imm = get_imm(instruction, SLLI);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            rs[1].a = imm;

            PC = PC + 4;
                break;
            }
        case SRLI: {
            auto rd = get_rd(instruction);
            auto rs1 = get_r1(instruction);
            auto imm = get_imm(instruction, SRLI);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            rs[1].a = imm;

            PC = PC + 4;
                break;
            }
        case SRAI: {
            auto rd = get_rd(instruction);
            auto rs1 = get_r1(instruction);
            auto imm = get_imm(instruction, SRAI);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            rs[1].a = imm;

            PC = PC + 4;
                break;
            }
        case SLTI: {
            auto rd = get_rd(instruction);
            auto rs1 = get_r1(instruction);
            auto imm = get_imm(instruction, SLTI);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            rs[1].a = imm;

            PC = PC + 4;
                break;
            }
        case SLTIU: {
            auto rd = get_rd(instruction);
            auto rs1 = get_r1(instruction);
            auto imm = get_imm(instruction, SLTIU);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            rs[1].a = imm;

            PC = PC + 4;
                break;
            }
        case LB: {
            auto rd = get_rd(instruction);
            auto rs1 = get_r1(instruction);
            auto imm = get_imm(instruction, LB);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            rs[1].a = imm;

            PC = PC + 4;
                break;
            }
        case LBU: {
            auto rd = get_rd(instruction);
            auto rs1 = get_r1(instruction);
            auto imm = get_imm(instruction, LBU);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            rs[1].a = imm;

            PC = PC + 4;
                break;
            }
        case LH: {
            auto rd = get_rd(instruction);
            auto rs1 = get_r1(instruction);
            auto imm = get_imm(instruction, LH);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            rs[1].a = imm;

            PC = PC + 4;
                break;
            }
        case LHU: {
            auto rd = get_rd(instruction);
            auto rs1 = get_r1(instruction);
            auto imm = get_imm(instruction, LHU);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            rs[1].a = imm;

            PC = PC + 4;
                break;
            }
        case LW: {
            auto rd = get_rd(instruction);
            auto rs1 = get_r1(instruction);
            auto imm = get_imm(instruction, LW);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            rs[1].a = imm;

            PC = PC + 4;
                break;
            }
            case SB: {
                auto rs1 = get_r1(instruction);
                auto rs2 = get_r2(instruction);
                unsigned int imm = get_imm(instruction, SB);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
                else rs[1].vj = rrs[rs1].value;
            if (rrs[rs2].busy) rs[1].qk = rrs[rs2].reorder;
                else rs[1].vk = rrs[rs2].value;
            rs[1].a = imm;

                PC = PC + 4;
                break;
            }
        case SH: {
            auto rs1 = get_r1(instruction);
            auto rs2 = get_r2(instruction);
            unsigned int imm = get_imm(instruction, SH);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            if (rrs[rs2].busy) rs[1].qk = rrs[rs2].reorder;
            else rs[1].vk = rrs[rs2].value;
            rs[1].a = imm;

            PC = PC + 4;
                break;
            }
        case SW: {
            auto rs1 = get_r1(instruction);
            auto rs2 = get_r2(instruction);
            unsigned int imm = get_imm(instruction, SW);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            if (rrs[rs2].busy) rs[1].qk = rrs[rs2].reorder;
            else rs[1].vk = rrs[rs2].value;
            rs[1].a = imm;

            PC = PC + 4;
                break;
            }
        case BEQ: {
            auto rs1 = get_r1(instruction);
            auto rs2 = get_r2(instruction);
            unsigned int imm = get_imm(instruction, BEQ);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            if (rrs[rs2].busy) rs[1].qk = rrs[rs2].reorder;
            else rs[1].vk = rrs[rs2].value;
            rs[1].a = imm;

            PC = PC + 4;
                break;
            }
        case BGE: {
            auto rs1 = get_r1(instruction);
            auto rs2 = get_r2(instruction);
            unsigned int imm = get_imm(instruction, BGE);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            if (rrs[rs2].busy) rs[1].qk = rrs[rs2].reorder;
            else rs[1].vk = rrs[rs2].value;
            rs[1].a = imm;

            PC = PC + 4;
                break;
            }
        case BGEU: {
            auto rs1 = get_r1(instruction);
            auto rs2 = get_r2(instruction);
            unsigned int imm = get_imm(instruction, BGEU);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            if (rrs[rs2].busy) rs[1].qk = rrs[rs2].reorder;
            else rs[1].vk = rrs[rs2].value;
            rs[1].a = imm;

            PC = PC + 4;
                break;
            }
        case BLT: {
            auto rs1 = get_r1(instruction);
            auto rs2 = get_r2(instruction);
            unsigned int imm = get_imm(instruction, BLT);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            if (rrs[rs2].busy) rs[1].qk = rrs[rs2].reorder;
            else rs[1].vk = rrs[rs2].value;
            rs[1].a = imm;

            PC = PC + 4;
                break;
            }
        case BLTU: {
            auto rs1 = get_r1(instruction);
            auto rs2 = get_r2(instruction);
            unsigned int imm = get_imm(instruction, BLTU);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            if (rrs[rs2].busy) rs[1].qk = rrs[rs2].reorder;
            else rs[1].vk = rrs[rs2].value;
            rs[1].a = imm;

            PC = PC + 4;
                break;
            }
        case BNE: {
            auto rs1 = get_r1(instruction);
            auto rs2 = get_r2(instruction);
            unsigned int imm = get_imm(instruction, BNE);

            if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
            else rs[1].vj = rrs[rs1].value;
            if (rrs[rs2].busy) rs[1].qk = rrs[rs2].reorder;
            else rs[1].vk = rrs[rs2].value;
            rs[1].a = imm;

            PC = PC + 4;
                break;
            }
            case JAL: {
                auto rd = get_rd(instruction);
                auto imm = get_imm(instruction, JAL);

                rs[1].a = imm;

                PC = PC + imm;
                break;
            }
            case JALR: {
                auto rd = get_rd(instruction);
                auto rs1 = get_r1(instruction);
                auto imm = get_imm(instruction, JALR);

                if (rrs[rs1].busy) rs[1].qj = rrs[rs1].reorder;
                else rs[1].vj = rrs[rs1].value;
                rs[1].a = imm;

                // reg[rd] = to_signed(PC + 4);
                // PC = rs1_data + imm;
                PC = PC + 4;
                break;
            }
            case AUIPC: {
                auto rd = get_rd(instruction);
                auto imm = get_imm(instruction, AUIPC);

                rs[1].a = imm;

                // reg[rd] = to_signed(PC + imm);
                PC = PC + 4;
                break;
            }
            case LUI: {
                auto rd = get_rd(instruction);
                auto imm = get_imm(instruction, LUI);

                rs[1].a = imm;

                // reg[rd] = imm;
                PC = PC + 4;
                break;
            }
            default: throw;
        }
}

int main() {
    // freopen("../testcases/array_test2.data", "r", stdin);

    load_instructions();

    int tot = 0;
    while (true) {
        tot++;
        // std::cout << tot << " PC = " << PC << std::endl;

        launch();
        RS_work();
        ALU::ALU_work();
        ROB_work();

        flush_zero_register();
        // for (int i = 0; i < 32; i++)
        //     std::cerr << rrs[i].value << " ";
        // std::cerr << std::endl;
    }

    // dark::CPU cpu;
    // Memory mem;
    // cpu.add_module(&mem);

    // while (Simple_Controller::should_end_program == false) {
    // //     // std::cerr << "memory[4] = " << memory[4] << std::endl;
    // //     // std::cerr << "memory[5] = " << memory[5] << std::endl;
    // //     // std::cerr << "memory[6] = " << memory[6] << std::endl;
    // //     // std::cerr << "memory[7] = " << memory[7] << std::endl;
    //
    //     Simple_Controller::Run_once();
    // }
    //
    // std::cout << Simple_Controller::result;

    return 0;
}