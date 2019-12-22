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

typedef struct
{
	u8 x,y;
	u8 width,height;
	bool visible;
	bool selected;
} ingredient;

void setIngredient(ingredient ing);

void initSpriteHandler(void);


#endif /* INGREDIENT_H_ */
