#include "registers.h"

uint16_t registers_get_af(registers_t *reg) {
    return (((uint16_t) reg->a) << 8 | (uint16_t) (reg->f & 0xF0));
}

uint16_t registers_get_bc(registers_t *reg) {
    return (((uint16_t) reg->b) << 8 | (uint16_t) reg->c);
}

uint16_t registers_get_de(registers_t *reg) {
    return (((uint16_t) reg->d) << 8 | (uint16_t) reg->e);
}

uint16_t registers_get_hl(registers_t *reg) {
    return (((uint16_t) reg->h) << 8 | (uint16_t) reg->l);
}

void registers_set_af(registers_t *reg, const uint16_t val) {
    reg->a = (uint8_t) (val >> 8);
    reg->f = (uint8_t) (val & 0x00F0);
}

void registers_set_bc(registers_t *reg, const uint16_t val) {
    reg->b = (uint8_t) (val >> 8);
    reg->c = (uint8_t) (val & 0x00F0);
}

void registers_set_de(registers_t *reg, const uint16_t val) {
    reg->d = (uint8_t) (val >> 8);
    reg->e = (uint8_t) (val & 0x00F0);
}

void registers_set_hl(registers_t *reg, const uint16_t val) {
    reg->h = (uint8_t) (val >> 8);
    reg->l = (uint8_t) (val & 0x00F0);
}

bool registers_get_flag(registers_t *reg, flag_offset_t flag) {
    return (reg->f & (uint8_t) flag) > 0;
}

void registers_set_flag(registers_t *reg, flag_offset_t flag, bool bit) {
    if (bit) {
        reg->f |= (uint8_t) flag;
    } else {
        reg->f &= (uint8_t) !flag;
    }
    // Reset the second nibble to zero
    reg->f &= 0b11110000;
}
