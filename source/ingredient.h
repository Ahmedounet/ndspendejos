/*
 * spriteHandler.h
 *
 *  Created on: 22 Dec 2019
 *      Author: Dev
 */

#ifndef INGREDIENT_H_
#define INGREDIENT_H_
#include <nds.h>
#include <stdbool.h>

typedef enum  {COFFEE, SUGAR, CREAM} ingType;

typedef struct
{
	ingType id;
	u8 x,y;
	u8 width,height;
	u16* gfx;
	bool visible;
	bool selected;
} ingredient;

/**
 * \brief Sets the sprite for the ingredient
 */
void setIngredient(ingredient ing);

/**
 * \brief Initiates the sprite handler on the Main engine, activates and configures the VRAM, and allocates the sprite memory
 */
void configureSprites(ingredient* tab);

ingredient * initIngredientTab(void);


#endif /* INGREDIENT_H_ */
