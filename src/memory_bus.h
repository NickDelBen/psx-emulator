/******************************************************
 * Contains description of a memory manager for PSX emulation
 * The different devices may have different memory mappings,
 * this should allow for interop
 *
 * Created by: Nick DelBen
 * Created on: June 16, 2019
 ******************************************************/

#ifndef PSX_EMU_MEMORY_BUS_H
#define PSX_EMU_MEMORY_BUS_H

#include "bios.h"

#define MEMORY_BIOS_START          0xbfc00000
#define MEMORY_MEMCONTROL_START    0x1f801000
#define MEMORY_MEMCONTROL_EXP1     0x1f000000
#define MEMORY_MEMCONTROL_EXP2     0x1f802000
#define MEMORY_MEMCONTROL_LENGTH   64
#define MEMORY_RAMSIZE_START       0x1f801060
#define MEMORY_RAMSIZE_LENGTH      4
#define MEMORY_CACHECONTROL_START  0xFFFE0130
#define MEMORY_CACHECONTROL_LENGTH 4

namespace PSX {
    class MemoryBus {
    private:
        // BIOS memory
        BIOS bios;
    public:
        // Move Constructor
        MemoryBus(MemoryBus&& other);
        // Constructs a new interconnect instance
        MemoryBus(BIOS &&bios);
        // Load 32bit word at specified address
        uint32_t load32(uint32_t address);
        // Stores a word to the specified memory location
        void store32(uint32_t address, uint32_t value);
        // Move operator
        MemoryBus& operator=(MemoryBus&& other);
    };
}

#endif //PSX_EMU_MEMORY_BUS_H
