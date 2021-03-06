#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mbc1.h"

uint8_t mem_mbc1_read_rom(memory_t *mem, uint16_t address) {
    memory_mbc1_t *internal = mem->internal;

    if (address < 0x4000) {
        // ROM Bank 00
	    return internal->rom[address];
    } else {
        return internal->rom[internal->selected_rom_bank * 0x4000 | (address & 0x3FFF)];
    }
}

uint8_t mem_mbc1_read_ram(memory_t *mem, uint16_t address) {
    memory_mbc1_t *internal = mem->internal;
    uint32_t ram_bank;

    if (!internal->ram_on) {
        return 0;
    }

    switch (internal->ram_mode) {
    case RAM_MODE_16Mb_ROM_8KB_RAM:
        ram_bank = 0;
        break;
    case RAM_MODE_4Mb_ROM_32KB_RAM:
        ram_bank = internal->selected_ram_bank;
        break;
    }

    return internal->ram[(ram_bank * 0x2000) | (address & 0x1FFF)];
}

void mem_mbc1_write_rom(memory_t *mem, uint16_t address, uint8_t val) {
    memory_mbc1_t *internal = mem->internal;

    switch (address) {
    case 0x0000 ... 0x1FFF: // RAM Enable
        internal->ram_on = (val == 0x0A);
        break;
    case 0x2000 ... 0x3FFF: // ROM Bank Number
        internal->selected_rom_bank = ((internal->selected_ram_bank & 0x60) | ((val & 0x1F) ? val & 0x1F : 0));
        break;
    case 0x4000 ... 0x5FFF: // RAM Bank Number - or - Upper Bits of ROM Bank Number
        switch (internal->ram_mode) {
        case RAM_MODE_16Mb_ROM_8KB_RAM:
            internal->selected_rom_bank = ((internal->selected_rom_bank & 0x1F) | ((val & 0x03) << 5));
            break;
        case RAM_MODE_4Mb_ROM_32KB_RAM:
            internal->selected_ram_bank = (val & 0x03);
            break;
        }
        break;
    case 0x6000 ... 0x7FFF: // ROM/RAM Mode Select
        internal->ram_mode = ((val & 0x01) == 0x01) ? RAM_MODE_16Mb_ROM_8KB_RAM : RAM_MODE_4Mb_ROM_32KB_RAM;
        break;
    default:
        fprintf(stderr, "Invalid memory write : %x\n", address);
        break;
    }
}

void mem_mbc1_write_ram(memory_t *mem, uint16_t address, uint8_t val) {
    memory_mbc1_t *internal = mem->internal;
    uint32_t ram_bank;

    if (!internal->ram_on) {
        return;
    }

    switch (internal->ram_mode) {
    case RAM_MODE_16Mb_ROM_8KB_RAM:
        ram_bank = 0;
        break;
    case RAM_MODE_4Mb_ROM_32KB_RAM:
        ram_bank = internal->selected_ram_bank;
        break;
    }

    internal->ram[(ram_bank * 0x2000) | (address & 0x1FFF)] = val;
}

memory_t *mem_mbc1_new(uint8_t *rom, size_t rom_size, size_t ram_size) {
    memory_t *mem = malloc(sizeof(memory_t));

    // Function pointers assignation
    mem->read_rom = mem_mbc1_read_rom;
    mem->read_ram = mem_mbc1_read_ram;
    mem->write_rom = mem_mbc1_write_rom;
    mem->write_ram = mem_mbc1_write_ram;

    // Internal structure allocation
    mem->internal = malloc(sizeof(memory_mbc1_t));
    memory_mbc1_t *internal = mem->internal;
    internal->rom = malloc(sizeof(uint8_t) * rom_size);
    internal->ram = malloc(sizeof(uint8_t) * ram_size);

    // Internal structure init
    memcpy(internal->rom, rom, sizeof(uint8_t) * rom_size);
    memset(internal->ram, 0, sizeof(uint8_t) * ram_size);
    internal->ram_on = false;
    internal->ram_mode = RAM_MODE_16Mb_ROM_8KB_RAM;
    internal->selected_rom_bank = 0x01;
    internal->selected_ram_bank = 0x00;

    return mem;
}

void mem_mbc1_del(memory_t *mem) {
    memory_mbc1_t *internal = mem->internal;

    free(internal->rom);
    free(internal->ram);
    free(internal);
    free(mem);
    mem = NULL;
}

