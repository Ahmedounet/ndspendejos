/*
 * graphics_sub.c
 *
 *  Created on: 22 Dec 2019
 *      Author: Dev
 */

#include "SubBG.h"
#include "selected.h"

#include "graphics_sub.h"

const u8 EMPTY_TILE[64] = {0}; // C automatically initializes the rest to 0;

void createBG1Map(void)
{
	int i;
	for(i = 0; i<4; i++)
		BG_MAP_RAM_SUB(1)[i] = selectedMap[i];
	for(i = 4; i<32*24; i++)
		BG_MAP_RAM_SUB(1)[i] = selectedTilesLen/64; // The empty tile is copied right after the SELECTED tiles, so in the address selectedTilesLen (by byte)
}


void initGraphicsSub(void)
{
	REG_DISPCNT_SUB = MODE_0_2D | DISPLAY_BG0_ACTIVE; //Configure the Sub engine
	VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG; // Activate the VRAM banks


	BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(2) | BG_PRIORITY_3; //Configure BG0 for the static BG

	//Copy into proper addresses
	dmaCopy(SubBGMap,(u8*)BG_MAP_RAM_SUB(0),SubBGMapLen);
	dmaCopy(SubBGPal,(u8*)BG_PALETTE_SUB,SubBGPalLen);
	dmaCopy(SubBGTiles,(u8*)BG_TILE_RAM_SUB(2),SubBGTilesLen);

	dmaCopy(selectedPal,(u8*)(BG_PALETTE_SUB + SubBGPalLen), selectedPalLen);
	dmaCopy(selectedTiles,(u8*)BG_TILE_RAM_SUB(1),selectedTilesLen);
	dmaCopy(EMPTY_TILE,(u8*)BG_TILE_RAM_SUB(1)+selectedTilesLen,64);
	createBG1Map();
}



