
#include "bios.h"

#include <iostream>
#include <fstream>

namespace PSX {

    // Constructs new BIOS
    BIOS::BIOS(std::string path) {
        // Allocate space for the bios memory
        data = (uint8_t *) malloc(BIOS_MEMORY_SIZE);
        // Read the specified input bios file
        std::ifstream input_stream(path, std::ios::in | std::ifstream::binary);
        // Ensure the BIOS file exists
        if (!input_stream) {
            std::cerr << "Error opening bios file " << path << std::endl;
            throw "Error opening bios file " + path;
        }
        input_stream.seekg(0, std::ios::end);
        // Ensure the bios file is the same size as the
        if (input_stream.tellg() != BIOS_MEMORY_SIZE) {
            std::cerr << "Specified BIOS file is not 512KB (" << std::to_string(input_stream.tellg()) << ")" << std::endl;
            throw "Specified BIOS file is not 512KB";
        }
        input_stream.seekg(0, 0);
        // Store the BIOS data in memory
        if (! input_stream.read((char*) data, BIOS_MEMORY_SIZE)) {
            std::cerr << "Error opening BIOS file" << std::endl;
            throw "Error opening BIOS file";
        }
    }

    // Move constructor
    BIOS::BIOS(BIOS&& other) {
        *this = std::move(other);
    }

    // Destructs BIOS
    BIOS::~BIOS() {
        // Free the memory for the BIOS code
        free(data);
    }

    // Reads a 32bit little endian word at specified offset
    // Since the BIOS is stored in little endien we will have to switch the bytes before returning
    uint32_t BIOS::load32(uint32_t offset) {
        // Read the 4 bytes
        uint8_t byte1 = data[offset];
        uint8_t byte2 = data[offset + 1];
        uint8_t byte3 = data[offset + 2];
        uint8_t byte4 = data[offset + 3];
        // Swap the endien-ness and return the word
        return byte1 | (byte2 << 8) | (byte3 << 16) | (byte4 << 24);
    }

    // Create move assignment operator
    BIOS& BIOS::operator=(BIOS&& other) {
        if (this != &other) {
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }
}
