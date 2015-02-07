#pragma once

#include "memory.h"

struct _memory_simple {
    uint8_t *rom;
};
typedef struct _memory_simple memory_simple_t;

uint8_t mem_simple_read_rom(struct _memory *mem, uint16_t address);
uint8_t mem_simple_read_ram(struct _memory *mem, uint16_t address);
void mem_simple_write_rom(struct _memory *mem, uint16_t address, uint8_t val);
void mem_simple_write_ram(struct _memory *mem, uint16_t address, uint8_t val);

