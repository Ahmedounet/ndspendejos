/*
 * touchHandler.h
 *
 *  Created on: 25 Dec 2019
 *      Author: Dev
 */

#ifndef GAMEPLAY_SUB_H_
#define GAMEPLAY_SUB_H_
#include "ingredient.h"

#include <nds.h>

//void selectIngredient(int num, ingredient tab[num]);
bool gameSubDone;

void resetGameplaySub();

void gameplaySub();

void gameLostSub();


#endif /* GAMEPLAY_SUB_H_ */
