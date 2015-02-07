#pragma once

#include <stdbool.h>
#include "memory.h"

// Memory Bank Controller 1

enum _mbc1_ram_mode {
    RAM_MODE_16Mb_ROM_8KB_RAM,
    RAM_MODE_4Mb_ROM_32KB_RAM
};
typedef enum _mbc1_ram_mode mbc1_ram_mode_t;

struct _memory_mbc1 {
    uint8_t *rom;
    uint8_t *ram;
    bool ram_on;
    mbc1_ram_mode_t ram_mode;
    uint32_t selected_rom_bank;
    uint32_t selected_ram_bank;
};
typedef struct _memory_mbc1 memory_mbc1_t;

uint8_t mem_mbc1_read_rom(memory_t *mem, uint16_t address);
uint8_t mem_mbc1_read_ram(memory_t *mem, uint16_t address);
void mem_mbc1_write_rom(memory_t *mem, uint16_t address, uint8_t val);
void mem_mbc1_write_ram(memory_t *mem, uint16_t address, uint8_t val);

memory_t *mem_mbc1_new(uint8_t *rom, size_t rom_size);
void mem_mbc1_del(memory_t *mem);
