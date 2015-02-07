#pragma once

struct _registers {
    uint8_t a; // Accumulator
    uint8_t f; // Flags
    uint8_t b; // Counter
    uint8_t c; // Counter
    uint8_t d; // Destination
    uint8_t e; // Destination
    uint8_t h; // Indirect addressing
    uint8_t l; // Indirect addressing

    uint16_t pc; // Program counter
    uint16_t sp; // Stage pointer
};
typedef struct _registers registers_t;

