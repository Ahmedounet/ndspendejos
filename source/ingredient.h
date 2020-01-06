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

ingredient ingTab[3];

ingredient orderTab[3];


/**
 * \brief Sets the sprite for the ingredient
 */
void setIngredient(ingredient ing);

/**
 * \brief Initiates the sprite handler on the Main engine, activates and configures the VRAM, and allocates the sprite memory
 */
void configureSprites_sub();

/**
 * \brief Initializes an array containing 3 ingredients, these will be represented by the sprites to be dropped into the cup.
 */
void initIngredientTab(void);
/**
 * \brief Generates a new order of 3 random ingredients. These are the sprites in the top left corner of the screen.
 */
void newOrder();


void resetIngredientPos(ingredient* ing);

void resetIngredientTab();

#endif /* INGREDIENT_H_ */
