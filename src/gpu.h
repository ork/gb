#pragma once

#include <stdint.h>
#include <stdbool.h>

#define SCREEN_W 160
#define SCREEN_H 144
#define VRAM_SIZE 8192
#define OAM_SIZE 160

enum _gpu_mode_flag {
    DURING_H_BLANK    = 0x00, // During H-Blank
    DURING_V_BLANK    = 0x01, // During V-Blank
    DURING_OAM_SEARCH = 0x02, // During Searching OAM
    DURING_DATA_XFER  = 0x03, // During Transferring Data to LCD Driver
};
typedef enum _gpu_mode_flag gpu_mode_flag;

struct _gpu {
    uint8_t RAM[VRAM_SIZE]; // 8kB Video RAM
    uint8_t OAM[OAM_SIZE];  // 160B Sprite Attribute Table

    // LCD Control
    bool lcd_on;            // LCD Display Enable
    uint16_t win_tilemap;   // Window Tile Map Display Select
    bool win_on;            // Window Display Enable
    uint16_t tile_data;     // BG & Window Tile Data Select
    uint16_t bg_tilemap;    // BG Tile Map Display Select
    uint8_t sprite_size;    // OBJ (Sprite) Size
    bool sprite_on;         // OBJ (Sprite) Display Enable
    bool lcdc0;             // LCDC0 (see pandocs)

    // LCD Status
    bool lyc_int;           // LY Coincidence Interrupt
    bool mode2_int;         // Mode 2 OAM Interrupt
    bool mode1_int;         // Mode 1 V-Blank Interrupt
    bool mode0_int;         // Mode 0 H-Blank Interrupt
    bool lyc_flag;          // Coincidence Flag
    gpu_mode_flag mode;     // Mode Flag
};
typedef struct _gpu gpu_t;
