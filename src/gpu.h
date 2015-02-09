#pragma once

#include <stdint.h>

#define SCREEN_W 160
#define SCREEN_H 144
#define VRAM_SIZE 8192
#define OAM_SIZE 160

struct _gpu {
    uint8_t RAM[VRAM_SIZE]; // 8kB Video RAM
    uint8_t OAM[OAM_SIZE]; // 160B Sprite Attribute Table

    uint8_t LCDC;
    uint8_t SCX;
    uint8_t SCY;
    uint8_t LY;
    uint8_t LYC;
    uint8_t BGP;
    uint8_t OBP0;
    uint8_t OBP1;
    uint8_t WX;
    uint8_t WY;
};
typedef struct _gpu gpu_t;
