#pragma once

#include "memory.h"

struct _memory_simple {
    uint8_t *rom;
};
typedef struct _memory_simple memory_simple_t;

uint8_t mem_simple_read_rom(memory_t *mem, uint16_t address);
uint8_t mem_simple_read_ram(memory_t *mem, uint16_t address);
void mem_simple_write_rom(memory_t *mem, uint16_t address, uint8_t val);
void mem_simple_write_ram(memory_t *mem, uint16_t address, uint8_t val);

memory_t *mem_simple_new(uint8_t *rom, size_t rom_size);
void mem_simple_del(memory_t *mem);

