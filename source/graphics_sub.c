/*
 * graphics_sub.c
 *
 *  Created on: 22 Dec 2019
 *      Author: Dev
 */

#include "SubBG.h"

#include "graphics_sub.h"



void initGraphicsSub(void)
{
	REG_DISPCNT_SUB = MODE_0_2D | DISPLAY_BG0_ACTIVE; //Configure the Sub engine
	VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG; // Activate the VRAM bank


	BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1) | BG_PRIORITY_3; //Configure BG0 for the static BG

	//Copy into proper addresses
	dmaCopy(SubBGMap,(u8*)BG_MAP_RAM_SUB(0),SubBGMapLen);
	dmaCopy(SubBGPal,(u8*)BG_PALETTE_SUB,SubBGPalLen);
	dmaCopy(SubBGTiles,(u8*)BG_TILE_RAM_SUB(1),SubBGTilesLen);

}



