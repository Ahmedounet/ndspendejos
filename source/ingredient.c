/*
 * ingredient.c
 *
 *  Created on: 22 Dec 2019
 *      Author: Dev
 */

#include "ingredient.h"
#include "bean.h"
#include "cube.h"
#include "cream.h"
#include <stdbool.h>

#define ING_SIZE 32
#define COFFEE_X 37
#define COFFEE_Y 122
#define SUGAR_X 98
#define SUGAR_Y 139
#define CREAM_X 172
#define CREAM_Y 122


void setIngredient(ingredient ing)
{
	oamSet(&oamSub,
					ing.id,
					ing.x,
					ing.y,
					0,
					ing.id,
					SpriteSize_32x32,
					SpriteColorFormat_16Color,
					ing.gfx,
					-1,
					false,
					!ing.visible,
					false,
					false,
					false);
}

void configureSprites(ingredient *tab)
{
	VRAM_D_CR = VRAM_ENABLE | VRAM_D_SUB_SPRITE;
	oamInit(&oamSub,SpriteMapping_1D_64,false);


	tab[COFFEE].gfx = oamAllocateGfx(&oamSub,SpriteSize_32x32, SpriteColorFormat_16Color);
	tab[SUGAR].gfx = oamAllocateGfx(&oamSub,SpriteSize_32x32, SpriteColorFormat_16Color);
	tab[CREAM].gfx = oamAllocateGfx(&oamSub,SpriteSize_32x32, SpriteColorFormat_16Color);

	dmaCopy(beanTiles,tab[COFFEE].gfx,beanTilesLen);
	dmaCopy(beanPal,SPRITE_PALETTE_SUB,beanPalLen);
	dmaCopy(cubeTiles,tab[SUGAR].gfx,cubeTilesLen);
	dmaCopy(cubePal,(u8*)(SPRITE_PALETTE_SUB+16),cubePalLen);
	dmaCopy(creamTiles,tab[CREAM].gfx,creamTilesLen);
	dmaCopy(creamPal,(u8*)(SPRITE_PALETTE_SUB+32),creamPalLen);

}

ingredient*  initIngredientTab()
{
	ingredient* tab = malloc(3*sizeof(ingredient));
	initIng(&tab[COFFEE],COFFEE,COFFEE_X,COFFEE_Y,ING_SIZE,ING_SIZE);
	initIng(&tab[SUGAR],SUGAR,SUGAR_X,SUGAR_Y,ING_SIZE,ING_SIZE);
	initIng(&tab[CREAM],CREAM,CREAM_X,CREAM_Y,ING_SIZE,ING_SIZE);
	configureSprites(tab);
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

void resetIngredientPos(ingredient* ing)
{
	switch (ing->id)
	{
		case COFFEE :
			ing->x = COFFEE_X;
			ing->y = COFFEE_Y;
			break;
		case SUGAR:
			ing->x = SUGAR_X;
			ing->y = SUGAR_Y;
			break;
		case CREAM:
			ing->x = CREAM_X;
			ing->y = CREAM_Y;
			break;
		default:
			printf("Well, this is awkward XD");
	}

}
