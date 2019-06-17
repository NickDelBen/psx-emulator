#include <iostream>

#include "bios.h"
#include "memory_bus.h"
#include "cpu.h"

// Test the emulator code
int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;

    PSX::BIOS bios("../bios/SCPH1001.BIN");
    PSX::MemoryBus memory(std::move(bios));
    PSX::CPU cpu(std::move(memory));

    int tst = 0;
    while (true) {
        tst++;
        cpu.runNextInstruction();
        if (tst > 10000000) {
            break;
        }
    }

    return 0;
}