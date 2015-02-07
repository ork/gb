#pragma once

#include <stdint.h>

//Interface for the memory subsystems

struct _memory;

typedef uint8_t (*mem_read_rom)(struct _memory *mem, uint16_t address);
typedef uint8_t (*mem_read_ram)(struct _memory *mem, uint16_t address);
typedef void (*mem_write_rom)(struct _memory *mem, uint16_t address, uint8_t val);
typedef void (*mem_write_ram)(struct _memory *mem, uint16_t address, uint8_t val);

struct _memory {
    void* internal;
    mem_read_rom read_rom;
    mem_read_ram read_ram;
    mem_write_rom write_rom;
    mem_write_ram write_ram;
};
typedef struct _memory memory_t;

