#include <stdio.h>
#include <stdlib.h>
#include "rom.h"

uint8_t* rom_read(const char* filename) {
    FILE *fp = NULL;
    size_t file_size, rom_size, ram_size;
    uint8_t *data = NULL;
    uint8_t checksum = 0;

    // Open file
    if ((fp = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "Could not open rom '%s'\n", filename);
        goto cleanup;
    }

    // Compute rom size
    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    // Read full rom
    if ((data = malloc(file_size)) == NULL) {
        fprintf(stderr, "Could not allocate memory to read rom\n");
        goto cleanup;
    }
    fread(data, 1, file_size, fp);
    fclose(fp);

    // Check the checksum
    for (size_t i = 0x134; i < 0x14D; ++i) {
        checksum += checksum - data[i] - 1;
    }
    if (data[0x14D] != checksum) {
        fprintf(stderr, "Bad checksum\n");
        goto cleanup;
    }

    // Determine the cartridge type
    switch (data[0x147]) {
    case 0x00: // No MBC
        break;
    default:
        fprintf(stderr, "Unhandled MBC: %x\n", data[0x147]);
        goto cleanup;
    }

    // Determine the ROM size
    switch (data[0x0148]) {
    case 0x00:
        rom_size = 32 * 1024;
        break;
    case 0x01:
        rom_size = 64 * 1024;
        break;
    case 0x02:
        rom_size = 128 * 1024;
        break;
    case 0x03:
        rom_size = 256 * 1024;
        break;
    case 0x04:
        rom_size = 512 * 1024;
        break;
    case 0x05:
        rom_size = 1024 * 1024;
        break;
    case 0x06:
        rom_size = 2 * 1024 * 1024;
        break;
    default:
        fprintf(stderr, "Unhandled ROM size: %x\n", data[0x148]);
        goto cleanup;
    }

    // Determine the RAM size
    switch (data[0x0149]) {
    case 0x00:
        ram_size = 0;
        break;
    case 0x01:
        ram_size = 2 * 1024;
        break;
    case 0x02:
        ram_size = 8 * 1024;
        break;
    case 0x03:
        ram_size = 32 * 1024;
        break;
    case 0x04:
        ram_size = 128 * 1024;
        break;
    default:
        fprintf(stderr, "Unhandled RAM size: %x\n", data[0x149]);
        goto cleanup;
    }

    return data;

    cleanup:
    if(data != NULL) {
        free(data);
    }
    return data;
}
