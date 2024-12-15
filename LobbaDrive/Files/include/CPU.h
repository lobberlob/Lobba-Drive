#ifndef CPU_H
#define CPU_H

#include <vector>
#include <string>
#include <cstdint>

class CPU {
public:
    // Constructor and Destructor
    CPU();
    ~CPU();

    // Initializes the CPU
    void initialize();

    // Loads a ROM into memory
    void loadROM(const std::string& romPath);

    // Emulates a single CPU cycle
    void emulateCycle();

    // Resets the CPU (optional)
    void reset();

    // Returns the current value of the program counter (PC)
    uint16_t getPC() const;

    // Returns the current state of registers (you can expand this)
    uint32_t getA(int index) const;  // Get address registers (A0 to A7)
    uint32_t getD(int index) const;  // Get data registers (D0 to D7)

private:
    // Registers (68000 has 8 data registers and 8 address registers)
    uint32_t D[8];  // Data registers D0 to D7
    uint32_t A[8];  // Address registers A0 to A7
    uint16_t PC;    // Program counter (16-bit)
    uint16_t SR;    // Status register (16-bit)
    uint16_t CCR;   // Condition code register (16-bit)

    // Memory (1MB for Sega Genesis, but can be expanded for real emulation)
    std::vector<uint8_t> memory;

    // Helper functions
    void fetch();
    void decode();
    void execute();

    // Example method to simulate opcode fetching
    uint8_t fetchOpcode();
    void handleOpcode(uint8_t opcode);
};

#endif  // CPU_H
