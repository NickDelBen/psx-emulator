
#include "cpu.h"
#include "memory_bus.h"

#include <iostream>

#define CPU_OP_JMP_PC_MASK 0xF0000000

namespace PSX {
    // Constructs a new CPU
    CPU::CPU(MemoryBus memory) :
        pc(MEMORY_BIOS_START),             /* PC begins at start of bios in memory */
        memory(std::move(memory)),         /* Move memory object to interior of this struct */
        next_instruction(Instruction(0x0)) /* Use NOP as default next instruction */
    {
    }

    // Runs the next instruction from memory
    void CPU::runNextInstruction() {
        // Load next instruction
        Instruction instruction = next_instruction;
        // Load the new next instruction
        next_instruction = Instruction(load32(pc));
        // Increment PC
        pc += CPU_INSTRUCTION_SIZE;
        // Execute the fetched instruction
        executeInstruction(instruction);
    }

    // Loads an instruction into the CPU from the specified memory offset
    uint32_t CPU::load32(uint32_t address) {
        return memory.load32(address);
    }

    // Stores a word to the specified memory location
    void CPU::store32(uint32_t address, uint32_t value) {
        return memory.store32(address, value);
    }

    // Executes the specified instruction
    void CPU::executeInstruction(Instruction instruction) {
        printState(true, false);
        switch(instruction.function()) {
            // LUI: Load Upper Immediate
            case 0b001111: {
                uint32_t rt = instruction.rt();
                uint32_t imm = instruction.immediate();
                registers[rt] = imm << 16;
                break;
            }
            // ORI: Bitwise OR Immediate
            case 0b001101: {
                uint32_t rt = instruction.rt();
                uint32_t rs = instruction.rs();
                uint32_t imm = instruction.immediate();
                registers[rt] = registers[rs] | imm;
                break;
            }
            // SW: Store Word
            case 0b101011: {
                uint32_t rt = instruction.rt();
                uint32_t rs = instruction.rs();
                uint32_t imm = instruction.immediate_se();
                store32(registers[rs] + imm, registers[rt]);
                break;
            }
            // ADDIU: Add Immediate Unsigned
            case 0b001001: {
                uint32_t imm = instruction.immediate_se();
                uint32_t rt = instruction.rt();
                uint32_t rs = instruction.rs();
                registers[rt] = registers[rs] + imm;
                break;
            }
            // J: Jump
            case 0b000010: {
                pc = (pc & CPU_OP_JMP_PC_MASK) | (instruction.immediate_jump() << 2);
                break;
            }
            // Subfunctions
            case 0b000000: {
                switch(instruction.subfunction()) {
                    // SLL: Shift left logical
                    case 0b000000: {
                        uint32_t imm = instruction.shift();
                        uint32_t rt = instruction.rt();
                        uint32_t rd = instruction.rd();
                        registers[rd] = registers[rt] << imm;
                        break;
                    }
                    // OR: or :)
                    case 0b100101: {
                        uint32_t rd = instruction.rd();
                        uint32_t sd = instruction.rs();
                        uint32_t td = instruction.rt();
                        registers[rd] = registers[sd] | registers[td];
                        break;
                    }
                    // Default
                    default: {
                        std::cerr << "Unrecognised 0b000000 subfunction " << std::hex << instruction.subfunction() << std::endl;
                        throw "Unrecognised 0b000000 subfunction " + std::to_string(instruction.operation);
                    }
                }
                break;
            }
            // Error handling instruction, possible bad instruction
            default: {
                std::cerr << "Unrecognised instruction " << std::hex << instruction.operation << std::endl;
                throw "Unrecognised instruction " + std::to_string(instruction.operation);
            }
        }
    }

    // Prints state of CPU to screen
    void CPU::printState(bool ins, bool reg) {
        if (ins) {
            std::cout << "Reg $pc" << " " << std::hex << $pc << std::endl;
            std::cout << "Instruction: " << std::hex << load32(pc - 4) << std::endl;
        }
        if (reg) {
            for (int x = 1; x < 32; x++) {
                std::cout << "Reg $" << std::dec << x << " " << std::hex << registers[x] << std::endl;
            }
        }
        std::cout << std::endl;
    }


}

