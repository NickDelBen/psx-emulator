
#include "memory_bus.h"

#include <iostream>

// Check if an address is inbetween START and START + LENGTH
#define ADDR_IN_RANGE(ADDR, START, LENGTH)  ((ADDR) >= (START) && (ADDR) < ((START) + (LENGTH)))

// Ensure a memory address is zero aligned
#define NOT_ZERO_ALIGNED(ADDR) (ADDR % 4 != 0)

namespace PSX {
    // Construct a new memory bus
    MemoryBus::MemoryBus(BIOS &&bios) :
            bios(std::move(bios)) {
    }

    // Move Constructor
    MemoryBus::MemoryBus(MemoryBus&& other) :
        bios(std::move(other.bios)) {
    }

    // Load 32bit word at specified address
    uint32_t MemoryBus::load32(uint32_t address) {
        // Ensure 4 byte alignment
        if (NOT_ZERO_ALIGNED(address)) {
            std::cerr << "Loading from not zero aligned address " << std::hex << address << std::endl;
            throw "Load32 from address not 4 byte aligned";
        }
        // If an address is in a specific range, call the specified member device's load32 method
        #define DEVICE_LOAD_MEMORY_CHECK(DEVICE, START, LENGTH) \
            if (ADDR_IN_RANGE(address, START, LENGTH)) { return DEVICE.load32(address - START); }
        // Check if the address belongs to the BIOS
        DEVICE_LOAD_MEMORY_CHECK(bios, MEMORY_BIOS_START, BIOS_MEMORY_SIZE)
        // Memory location does not belong to any mapped device
        std::cerr << "Memory address " << std::hex << address << " does not map to any device" << std::endl;
        throw "Memory address " + std::to_string(address) + " does not map to any device";
    }

    // Stores a word to the specified memory location
    void MemoryBus::store32(uint32_t address, uint32_t value) {
        // Ensure 4 byte alignment
        if (NOT_ZERO_ALIGNED(address)) {
            std::cerr << "Storing to not zero aligned address " << std::hex << address << std::endl;
            throw "Store32 to address not 4 byte aligned";
        }
        // Handle the memcontrol memory space
        if (ADDR_IN_RANGE(address, MEMORY_MEMCONTROL_START, MEMORY_MEMCONTROL_LENGTH)) {
            // There are two expansion register maps that need to be set
            // otherwise we will ignore this memory space as it is for hardware control
            switch (address - MEMORY_MEMCONTROL_START) {
                // Expansion 1
                case 0: {
                    if (value != MEMORY_MEMCONTROL_EXP1) {
                        std::cerr << "Storing invalid value to expansion 1 base address " << std::hex << address << std::endl;
                        throw "Invalid store to expansion 1 base address";
                    }
                    break;
                }
                // Expansion 2
                case 4: {
                    if (value != MEMORY_MEMCONTROL_EXP2) {
                        std::cerr << "Storing invalid value to expansion 2 base address " << std::hex << address << std::endl;
                        throw "Invalid store to expansion 2 base address";
                    }
                    break;
                }
                default: {
                    std::cout << "Ignoring memory writes to MEMCONTROL" << std::endl;
                    break;
                }
            }
        }
        // Handle the RAM config register
        else if (ADDR_IN_RANGE(address, MEMORY_RAMSIZE_START, MEMORY_RAMSIZE_LENGTH)) {
            std::cout << "Ignoring memory writes to RAMSIZE" << std::endl;
        }
        // Handle the cache control register
        else if (ADDR_IN_RANGE(address, MEMORY_CACHECONTROL_START, MEMORY_CACHECONTROL_LENGTH)) {
            std::cout << "Ignoring memory writes to CACHECONTROL" << std::endl;
        }
        else {
            // Memory location does not belong to any mapped device
            std::cerr << "Memory address " << std::hex << address << " does not map to any device" << std::endl;
            throw "Memory address " + std::to_string(address) + " does not map to any device";
        }
    }

    // Move operator
    MemoryBus& MemoryBus::operator=(MemoryBus&& other) {
        // Take the other bios
        bios = std::move(other.bios);
        return *this;
    }
}
