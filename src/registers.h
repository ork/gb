#pragma once

#include <stdbool.h>
#include <stdint.h>

/* Registers mapping
 * ┌─────┬─────┐
 * │15..8│7..0 │
 * ├─────┼─────┤
 * │  A  │  F  │
 * ├─────┼─────┤
 * │  B  │  C  │
 * ├─────┼─────┤
 * │  D  │  E  │
 * ├─────┼─────┤
 * │  H  │  L  │
 * ├─────┼─────┤
 * │  A  │  F  │
 * ├─────┴─────┤
 * │    SP     │
 * ├───────────┤
 * │    PC     │
 * └───────────┘
 */
struct _registers {
    uint8_t a; // Accumulator
    uint8_t f; // Flags
    uint8_t b; // Counter
    uint8_t c; // Counter
    uint8_t d; // Destination
    uint8_t e; // Destination
    uint8_t h; // Indirect addressing
    uint8_t l; // Indirect addressing

    uint16_t sp; // Stack pointer
    uint16_t pc; // Program counter
};
typedef struct _registers registers_t;

// Get A and F as a 16 bits register
uint16_t registers_get_af(registers_t *reg);
// Get B and C as a 16 bits register
uint16_t registers_get_bc(registers_t *reg);
// Get D and E as a 16 bits register
uint16_t registers_get_de(registers_t *reg);
// Get H and L as a 16 bits register
uint16_t registers_get_hl(registers_t *reg);

// Set A and F as a 16 bits register
void registers_set_af(registers_t *reg, uint16_t val);
// Set B and C as a 16 bits register
void registers_set_bc(registers_t *reg, uint16_t val);
// Set D and E as a 16 bits register
void registers_set_de(registers_t *reg, uint16_t val);
// Set H and L as a 16 bits register
void registers_set_hl(registers_t *reg, uint16_t val);

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

// Get the value of the bit of the specified flag
bool registers_get_flag(registers_t *reg, flag_offset_t flag);
// Set the value of the bit of the specified flag
void registers_set_flag(registers_t *reg, flag_offset_t flag, bool bit);

