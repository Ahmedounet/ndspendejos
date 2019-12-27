/*
 * ingredient.c
 *
 *  Created on: 22 Dec 2019
 *      Author: Dev
 */

#include "ingredient.h"
#include "bean.h"
#include <stdbool.h>

#define ING_SIZE 32

void setIngredient(ingredient ing)
{
	oamSet(&oamMain,
					ing.id,
					ing.x,
					ing.y,
					0,
					0,
					SpriteSize_32x32,
					SpriteColorFormat_16Color,
					ing.gfx,
					-1,
					false,
					false,
					false,
					false,
					false);
}

void initSpriteHandler(void)
{
	VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE;
	oamInit(&oamMain,SpriteMapping_1D_64,false);

	//test
	ingredient* tab = initIngredientTab();
	tab[COFFEE].gfx = oamAllocateGfx(&oamMain,SpriteSize_32x32, SpriteColorFormat_16Color);
	dmaCopy(beanTiles,tab[COFFEE].gfx,beanTilesLen);
	dmaCopy(beanPal,SPRITE_PALETTE,beanPalLen);


}

ingredient*  initIngredientTab()
{
	ingredient* tab = malloc(3*sizeof(ingredient));
	initIng(&tab[COFFEE],COFFEE,37,122,ING_SIZE,ING_SIZE);
	initIng(&tab[SUGAR],SUGAR,98,139,ING_SIZE,ING_SIZE);
	initIng(&tab[CREAM],CREAM,172,122,ING_SIZE,ING_SIZE);
	return tab;
}


void initIng(ingredient* i,ingType id,int  x,int y,int h,int w)
{
	i->id = id;
	i->x = x;
	i->y = y;
	i->height = h;
	i->width = w;
	i->visible = true;
	i->selected = false;
}
