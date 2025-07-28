#include "Controller.hpp"
#include "memory.hpp"

int main() {
    // freopen("input.data", "r", stdin);

    load_instructions();

    dark::CPU cpu;
    Memory mem;
    cpu.add_module(&mem);

    // while (Simple_Controller::should_end_program == false) {
    //     // std::cerr << "memory[4] = " << memory[4] << std::endl;
    //     // std::cerr << "memory[5] = " << memory[5] << std::endl;
    //     // std::cerr << "memory[6] = " << memory[6] << std::endl;
    //     // std::cerr << "memory[7] = " << memory[7] << std::endl;
    //
    //     // Simple_Controller::Run_once();
    // }
    //
    // std::cout << Simple_Controller::result;

    return 0;
}