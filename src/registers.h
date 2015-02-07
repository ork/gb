#pragma once

#include <stdint.h>

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

/* Bits in the flag register
 * ┌─┬─┬─┬─┬─┬─┬─┬─┐
 * │7│6│5│4│3│2│1│0│
 * ├─┼─┼─┼─┼─┼─┼─┼─┤
 * │Z│N│H│C│0│0│0│0│
 * └─┴─┴─┴─┴─┴─┴─┴─┘
 */

enum _flag_offset {
    C = 0b00010000, // Carry
    H = 0b00100000, // Half Carry
    N = 0b01000000, // Subtract
    Z = 0b10000000, // Zero
};
typedef enum _flag_offset flag_offset_t;

