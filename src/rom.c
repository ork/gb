#include <stdio.h>
#include <stdlib.h>
#include "rom.h"

uint8_t* rom_read(const char* filename) {
    FILE *fp = NULL;
    size_t rom_size;
    uint8_t *data = NULL;
    uint8_t checksum = 0;

    // Open file
    if ((fp = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "Could not open rom '%s'\n", filename);
        goto cleanup;
    }

    // Compute rom size
    fseek(fp, 0L, SEEK_END);
    rom_size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    // Read full rom
    if ((data = malloc(rom_size)) == NULL) {
        fprintf(stderr, "Could not allocate memory to read rom\n");
        goto cleanup;
    }
    fread(data, 1, rom_size, fp);
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

    return data;

    cleanup:
    if(data != NULL) {
        free(data);
    }
    return data;
}
