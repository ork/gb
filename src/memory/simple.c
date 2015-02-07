#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simple.h"

uint8_t mem_simple_read_rom(memory_t *mem, uint16_t address) {
    memory_simple_t *internal = mem->internal;

    switch (address) {
    case 0x0000 ... 0x8000:
        return internal->rom[address];
    case 0xA000 ... 0xBFFF:
        return internal->rom[address - 0xA000];
    default:
        fprintf(stderr, "Invalid memory read : %x\n", address);
        return 0;
    }
}

uint8_t mem_simple_read_ram(__attribute__((unused)) memory_t *mem,
                            __attribute__((unused)) uint16_t address) {
    return 0;
}

void mem_simple_write_rom(memory_t *mem, uint16_t address, uint8_t val) {
    memory_simple_t *internal = mem->internal;

    switch (address) {
    case 0xA000 ... 0xBFFF:
        internal->rom[address - 0xA000] = val;
        break;
    default:
        fprintf(stderr, "Invalid memory write : %x\n", address);
        break;
    }
}

void mem_simple_write_ram(__attribute__((unused)) memory_t *mem,
                          __attribute__((unused)) uint16_t address,
                          __attribute__((unused)) uint8_t val) {
    return;
}

memory_t *mem_simple_new(uint8_t *rom, size_t rom_size) {
    memory_t *mem = malloc(sizeof(memory_t *));
    mem->internal = malloc(sizeof(memory_simple_t *));
    memory_simple_t *internal = mem->internal;

    // Function pointers assignation
    mem->read_rom = mem_simple_read_rom;
    mem->read_ram = mem_simple_read_ram;
    mem->write_rom = mem_simple_write_rom;
    mem->write_ram = mem_simple_write_ram;

    internal->rom = malloc(sizeof(uint8_t *) * rom_size);

    memcpy(internal->rom, rom, rom_size);

    return mem;
}

void mem_simple_del(memory_t *mem) {
    memory_simple_t *internal = mem->internal;

    free(internal->rom);
    free(internal);
    free(mem);
    mem = NULL;
}

