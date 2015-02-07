#pragma once

#include <stdint.h>

struct _memory_basic {
    uint8_t *rom;
    uint8_t *ram;
};
typedef struct _memory_basic memory_basic_t;

memory_basic_t * mem_basic_new(uint8_t *rom, size_t rom_size, uint8_t *ram, size_t ram_size);

void mem_basic_free(memory_basic_t * mem);

uint8_t mem_basic_read(memory_basic_t * mem, uint16_t address);

void mem_basic_write(memory_basic_t * mem, uint16_t address, uint8_t val);

