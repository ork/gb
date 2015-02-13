#pragma once

#include <stdint.h>

enum _cart_type {
    CT_ROM_ONLY          = 0x00,
    CT_ROM_MBC1          = 0x01,
    CT_ROM_MBC1_RAM      = 0x02,
    CT_ROM_MBC1_RAM_BATT = 0x03,
};
typedef enum _cart_type cart_type_t;

struct _cartridge {
    uint8_t *rom;
    size_t rom_size;
    size_t ram_size;
};
typedef struct _cartridge cartridge_t;

// Open rom file and read contents
cartridge_t* rom_new(const char* filename);
