#include "CPU.h"
#include <iostream>
#include <fstream>
#include <cstring>

CPU::CPU() {
    // Initialize registers to 0
    std::memset(D, 0, sizeof(D));  // Clear data registers
    std::memset(A, 0, sizeof(A));  // Clear address registers
    PC = 0x0000;  // Program counter starts at address 0
    SR = 0x2700;  // Default status register (SR) value (supervisor mode)
    CCR = 0;  // Clear condition code register
}

CPU::~CPU() {
    // Any cleanup needed (not much for this example)
}

void CPU::initialize() {
    // Reset CPU state
    std::memset(D, 0, sizeof(D));  // Clear data registers
    std::memset(A, 0, sizeof(A));  // Clear address registers
    PC = 0x0000;  // Start program counter at 0
    SR = 0x2700;  // Supervisor mode (default)
    CCR = 0;  // Clear condition code register
}

void CPU::loadROM(const std::string& romPath) {
    std::ifstream romFile(romPath, std::ios::binary);
    if (!romFile) {
        std::cerr << "YOU ARE A FAILURE, YOU ARE A WORTHLESS BITCH ASS FAGGOT. YOUR LIFE IS AS VALUEBLE AS A SUMMER ANT. BECAUSE YOU Failed to load ROM: " << romPath << std::endl;
        return;
    }

    // Load ROM into memory (we assume ROM is small enough to fit in memory)
    romFile.read(reinterpret_cast<char*>(memory.data()), memory.size());
    romFile.close();

    // Set the Program Counter to the entry point (first address)
    PC = 0x060000;  // Typically the entry point for Genesis ROMs
}

void CPU::emulateCycle() {
    // Fetch, decode, and execute one cycle
    uint8_t opcode = fetchOpcode();  // Fetch next opcode
    handleOpcode(opcode);            // Decode and execute the opcode
}

void CPU::reset() {
    initialize();  // Reset registers and memory
    PC = 0x060000; // Reset the PC to the entry point for ROMs
}

uint8_t CPU::fetchOpcode() {
    // Fetch the opcode from the current program counter (PC)
    uint8_t opcode = memory[PC];
    PC++;  // Increment program counter to next instruction
    return opcode;
}

void CPU::handleOpcode(uint8_t opcode) {
    // Decode and execute the opcode. For now, we'll just print the opcode.
    switch (opcode) {
    case 0x00:  // NOP (No operation)
        std::cout << "NOP (No operation)" << std::endl;
        break;
    case 0x01:  // Example opcode, you will implement more opcodes
        std::cout << "Unknown opcode 0x01" << std::endl;
        break;
        // Add more opcodes as necessary
    default:
        std::cerr << "Unhandled opcode: 0x" << std::hex << (int)opcode << std::endl;
        break;
    }
}

uint16_t CPU::getPC() const {
    return PC;
}

uint32_t CPU::getA(int index) const {
    if (index >= 0 && index < 8) {
        return A[index];  // Return the value of the address register A0 to A7
    }
    return 0;
}

uint32_t CPU::getD(int index) const {
    if (index >= 0 && index < 8) {
        return D[index];  // Return the value of the data register D0 to D7
    }
    return 0;
}
