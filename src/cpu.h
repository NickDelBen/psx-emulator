/******************************************************
 * Contains description of a PSX CPU
 *
 * Created by: Nick DelBen
 * Created on: June 16, 2019
 ******************************************************/

#ifndef PSX_EMU_CPU_H
#define PSX_EMU_CPU_H

#include <cstdint>

#include "memory_bus.h"
#include "instruction.h"

#include "register_shorthands.h"

// Instructions are 4 bytes (32 bits)
#define CPU_INSTRUCTION_SIZE 4
// CPU has 32 general purpose registers
#define CPU_NUM_GENERAL_REGISTERS 32

namespace PSX {
    class CPU {
    private:
        // Program Counter register
        uint32_t pc;
        // Next instruction to be executed, helps with branch delay
        Instruction next_instruction;
        // General purpose registers
        uint32_t registers[CPU_NUM_GENERAL_REGISTERS] = {0};
        // The memory controller for our device
        MemoryBus memory;
    public:
        // Constructs a new CPU
        CPU(MemoryBus memory);
        // Runs the next instruction from memory
        void runNextInstruction();
        // Loads a word into the CPU from the specified memory offset
        uint32_t load32(uint32_t address);
        // Stores a word to the specified memory location
        void store32(uint32_t address, uint32_t value);
        // Executes the specified instruction
        void executeInstruction(Instruction instruction);
        // Prints state of CPU to stdout
        // flags control what data to print
        void printState(bool ins = true, bool reg = true);
    };
}

#endif //PSX_EMU_CPU_H
