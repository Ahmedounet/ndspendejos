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
					ing.id%3, // This allows us to retrieve the correct palette from the hashed ID for all sprites.
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

void configureSprites_sub()
{
	VRAM_D_CR = VRAM_ENABLE | VRAM_D_SUB_SPRITE;
	oamInit(&oamSub,SpriteMapping_1D_64,false);


	ingTab[COFFEE].gfx = oamAllocateGfx(&oamSub,SpriteSize_32x32, SpriteColorFormat_16Color);
	ingTab[SUGAR].gfx = oamAllocateGfx(&oamSub,SpriteSize_32x32, SpriteColorFormat_16Color);
	ingTab[CREAM].gfx = oamAllocateGfx(&oamSub,SpriteSize_32x32, SpriteColorFormat_16Color);

	dmaCopy(beanTiles,ingTab[COFFEE].gfx,beanTilesLen);
	dmaCopy(beanPal,SPRITE_PALETTE_SUB,beanPalLen);
	dmaCopy(cubeTiles,ingTab[SUGAR].gfx,cubeTilesLen);
	dmaCopy(cubePal,(u8*)(SPRITE_PALETTE_SUB+16),cubePalLen);
	dmaCopy(creamTiles,ingTab[CREAM].gfx,creamTilesLen);
	dmaCopy(creamPal,(u8*)(SPRITE_PALETTE_SUB+32),creamPalLen);


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

void resetIngredientTab()
{
	initIng(&ingTab[COFFEE],COFFEE,COFFEE_X,COFFEE_Y,ING_SIZE,ING_SIZE);
	initIng(&ingTab[SUGAR],SUGAR,SUGAR_X,SUGAR_Y,ING_SIZE,ING_SIZE);
	initIng(&ingTab[CREAM],CREAM,CREAM_X,CREAM_Y,ING_SIZE,ING_SIZE);
	setIngredient(ingTab[COFFEE]);
	setIngredient(ingTab[SUGAR]);
	setIngredient(ingTab[CREAM]);
}

void  initIngredientTab()
{
	configureSprites_sub();
	resetIngredientTab();

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



void newOrder()
{
	int i;
	int randId;
	for(i=0 ; i<3 ; i++)
	{
		//oamClearSprite(&oamSub,orderTab[i].id);
		orderTab[i].visible = false;
		setIngredient(orderTab[i]);
		initIng(&orderTab[i],0,i*ING_SIZE,0,ING_SIZE,ING_SIZE); // The 0 in the id field is a temporary placeholder. The proper ID is calculated in the function "newOrder"
		randId = rand()%3;
		orderTab[i].gfx = ingTab[randId].gfx;
		orderTab[i].id = randId+3*(i+1); // The id is hashed to be unique for every sprite, yet indicate the correct palette to use for each ingredient.
		setIngredient(orderTab[i]);
	}
}


