#pragma once

#include <stdint.h>

#define SCREEN_W 160
#define SCREEN_H 144
#define VRAM_SIZE 8192
#define OAM_SIZE 160

struct _gpu {
    uint8_t RAM[VRAM_SIZE]; // 8kB Video RAM
    uint8_t OAM[OAM_SIZE];  // 160B Sprite Attribute Table

    // LCD Control
    bool lcd_on;            // LCD Display Enable
    uint16_t win_tilemap;   // Window Tile Map Display Select
    bool win_on;            // Window Display Enable
    uint16_t tile_data;     // BG & Window Tile Data Select
    uint16_t bg_tilemap;    // BG Tile Map Display Select
    size_t sprite_size;     // OBJ (Sprite) Size
    bool sprite_on;         // OBJ (Sprite) Display Enable
    bool lcdc0;             // LCDC0 (see pandocs)
};
typedef struct _gpu gpu_t;
