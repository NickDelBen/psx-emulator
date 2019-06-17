/******************************************************
 * Contains description of a PSX BIOS
 *
 * Created by: Nick DelBen
 * Created on: June 17, 2019
 ******************************************************/

#ifndef PSX_EMU_BIOS_H
#define PSX_EMU_BIOS_H

#include <cstdint>
#include <string>

// The BIOS we are using (SCPH1001) is 512KB in size
#define BIOS_MEMORY_SIZE 512 * 1024

namespace PSX {
    class BIOS {
    private:
        // Memory for BIOS code
        uint8_t * data;
    public:
        // Reads a 32bit little endian word at specified offset
        uint32_t load32(uint32_t offset);
        // Constructs a new instance of BIOS
        BIOS(std::string path);
        // Move Constructor
        BIOS(BIOS&& other);
        // Destructs BIOS
        ~BIOS();
        // Move assignment operator
        BIOS& operator=(BIOS&& other);
    };
}

#endif //PSX_EMU_BIOS_H
