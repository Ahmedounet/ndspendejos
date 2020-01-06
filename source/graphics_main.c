/*
 * graphics_main.c
 *
 *  Created on: Jan 5, 2020
 *      Author: nds
 */

#include "graphics_main.h"
#include "MainBG.h"
#include "ball.h"

void configure_graphics_main() {
	// Activate main engine and backgrounds 0, 1 and 2 in standard tiled mode
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
	REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE| DISPLAY_BG1_ACTIVE | DISPLAY_BG2_ACTIVE |DISPLAY_BG3_ACTIVE;
	BGCTRL[0] = BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1) | BG_32x32;
	BGCTRL[1] = BG_COLOR_256 | BG_MAP_BASE(1) | BG_TILE_BASE(1) | BG_32x32;
	BGCTRL[2] = BG_COLOR_256 | BG_MAP_BASE(2) | BG_TILE_BASE(1) | BG_32x32;
	BGCTRL[3] = BG_COLOR_256 | BG_MAP_BASE(3) | BG_TILE_BASE(1) | BG_32x32;

	//Copy tiles and palette (shared by all backgrounds in this case)
	swiCopy(MainBGTiles, BG_TILE_RAM(1), MainBGTilesLen/2);
	swiCopy(MainBGPal, BG_PALETTE, MainBGPalLen/2);
	//Copy maps (32x24 components of 2 bytes for each of the map bases)
	swiCopy(&MainBGMap[0], BG_MAP_RAM(0), 32*24);
	swiCopy(&MainBGMap[32*24], BG_MAP_RAM(1), 32*24);
	swiCopy(&MainBGMap[32*48], BG_MAP_RAM(2), 32*24);
	swiCopy(&MainBGMap[32*(72)], BG_MAP_RAM(3), 32*24);

}

void change_bckg_priority(u16 bckg, u16 priority) {
	//Sanity check
	if((bckg >= 4) || (priority >= 4))
		return;
	//Set up the priority of the background
	BGCTRL[bckg] = (BGCTRL[bckg] & 0xFFFC) | priority;
}


void configureSprites() {
	//Set up memory bank to work in sprite mode (offset since we are using VRAM A for backgrounds)
	VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE_0x06400000;

	//Initialize sprite manager and the engine
	oamInit(&oamMain, SpriteMapping_1D_32, false);

	//Allocate space for the graphic to show in the sprite
	gfx = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

	//Copy data for the graphic (palette and bitmap)
	swiCopy(ballPal, SPRITE_PALETTE, ballPalLen/2);
	swiCopy(ballTiles, gfx, ballTilesLen/2);
}
