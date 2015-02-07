#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basic.h"

memory_basic_t * mem_basic_new(uint8_t *rom, size_t rom_size, uint8_t *ram, size_t ram_size) {
    memory_basic_t * mem = NULL;

    if ((mem = malloc(sizeof(memory_basic_t *))) == NULL) {
        return NULL;
    }

    // TODO: Single malloc
    mem->rom = malloc(sizeof(uint8_t *) * rom_size);
    mem->ram = malloc(sizeof(uint8_t *) * ram_size);

    memcpy(mem->rom, rom, rom_size);
    memcpy(mem->ram, ram, ram_size);

    return mem;
}

void mem_basic_free(memory_basic_t * mem) {
    free(mem->rom);
    free(mem->ram);
    free(mem);
    mem = NULL;
}

uint8_t mem_basic_read(memory_basic_t * mem, uint16_t address) {
    switch (address) {
    case 0x0000 ... 0x8000:
        return mem->rom[address];
    case 0xA000 ... 0xBFFF:
        return mem->rom[address - 0xA000];
    default:
        fprintf(stderr, "Invalid memory read : %x\n", address);
        return 0;
    }
}

void mem_basic_write(memory_basic_t * mem, uint16_t address, uint8_t val) {
    switch (address) {
    case 0xA000 ... 0xBFFF:
        mem->rom[address - 0xA000] = val;
        break;
    default:
        fprintf(stderr, "Invalid memory write : %x\n", address);
        break;
    }
}

