#include <stdio.h>
#include <stdlib.h>
#include "rom.h"

cartridge_t* rom_new(const char* filename) {
    cartridge_t * cart = NULL;
    FILE *fp = NULL;
    size_t file_size;

    if((cart = malloc(sizeof(cartridge_t))) == NULL) {
        fprintf(stderr, "Could not allocate memory for the cartridge\n");
        return NULL;
    }

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
    if ((cart->rom = malloc(file_size)) == NULL) {
        fprintf(stderr, "Could not allocate memory to read rom\n");
        goto cleanup;
    }
    fread(cart->rom, 1, file_size, fp);
    fclose(fp);

    uint8_t checksum = 0;
    // Check the checksum
    for (size_t i = 0x134; i < 0x14D; ++i) {
        checksum += checksum - cart->rom[i] - 1;
    }
    if (cart->rom[0x14D] != checksum) {
        fprintf(stderr, "Bad checksum\n");
        goto cleanup;
    }

    // Determine the cartridge type
    switch (cart->rom[0x147]) {
    case CT_ROM_ONLY:
        break;
    default:
        fprintf(stderr, "Unhandled MBC: %x\n", cart->rom[0x147]);
        goto cleanup;
    }

    // Determine the ROM size
    switch (cart->rom[0x0148]) {
    case 0x00:
        cart->rom_size = 32 * 1024;
        break;
    case 0x01:
        cart->rom_size = 64 * 1024;
        break;
    case 0x02:
        cart->rom_size = 128 * 1024;
        break;
    case 0x03:
        cart->rom_size = 256 * 1024;
        break;
    case 0x04:
        cart->rom_size = 512 * 1024;
        break;
    case 0x05:
        cart->rom_size = 1024 * 1024;
        break;
    case 0x06:
        cart->rom_size = 2 * 1024 * 1024;
        break;
    default:
        fprintf(stderr, "Unhandled ROM size: %x\n", cart->rom[0x148]);
        goto cleanup;
    }

    // Determine the RAM size
    switch (cart->rom[0x0149]) {
    case 0x00:
        cart->ram_size = 0;
        break;
    case 0x01:
        cart->ram_size = 2 * 1024;
        break;
    case 0x02:
        cart->ram_size = 8 * 1024;
        break;
    case 0x03:
        cart->ram_size = 32 * 1024;
        break;
    case 0x04:
        cart->ram_size = 128 * 1024;
        break;
    default:
        fprintf(stderr, "Unhandled RAM size: %x\n", cart->rom[0x149]);
        goto cleanup;
    }

    return cart;

cleanup:
    if(cart != NULL) {
        free(cart->rom);
    }
    free(cart);
    return NULL;
}
