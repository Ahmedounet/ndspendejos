/*
 * graphics_sub.c
 *
 *  Created on: 22 Dec 2019
 *      Author: Dev
 */

#include "MainBG.h"
#include "graphics_main.h"


void initGraphicsMain(void)
{
	REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE; //Configure the Main engine
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG; // Activate the VRAM banks


	BGCTRL[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1); //Configure BG0 for the static BG
	//Copy into proper addresses
	dmaCopy(MainBGMap,(u8*)BG_MAP_RAM(0),MainBGMapLen);
	dmaCopy(MainBGPal,(u8*)BG_PALETTE,MainBGPalLen);
	dmaCopy(MainBGTiles,(u8*)BG_TILE_RAM(1),MainBGTilesLen);

}
