/*
 * touchHandler.c
 *
 *  Created on: 25 Dec 2019
 *      Author: Dev
 */

#include "sound.h"

#include <stdbool.h>
#include<math.h>
#include "gameplay_sub.h"
#include "timer_management.h"

#define POT_CENTRE_X  123
#define POT_CENTRE_Y  81
#define ELLIPSE_2A  96
#define F1_X  81
#define F2_X  165
#define NONE -1



int selectedIndex;

int correctIngredients;


void resetGameplaySub()
{
	newOrder();
	resetIngredientTab();
	correctIngredients = 0;
	selectedIndex = NONE;
	gameSubDone = false;
	reset_timer();
}


void selectIngredient()
{
	if(keysDown() & KEY_TOUCH)
	{
		//printf("TOUCHED \n");
		touchPosition tp;
		touchRead(&tp);
		int i;
		for(i=0;i<3;i++)
		{
			if(tp.px >= ingTab[i].x && tp.px < ingTab[i].x + ingTab[i].width &&
			   tp.py >= ingTab[i].y && tp.py < ingTab[i].y + ingTab[i].height)
			{
				ingTab[i].selected =  true;
				selectedIndex = i;
				//printf("SELECTED: %d\n", tab[i].id);
			}
				else
				ingTab[i].selected =  false;
		}
	}
}


double distance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x1-x2,2) + pow(y1-y2,2));
}



void ingredientChosen(ingredient *ing)
{
	if(ing->id == orderTab[correctIngredients].id%3)
	{
		orderTab[correctIngredients].visible = false;
		setIngredient(orderTab[correctIngredients++]);
		plop();
	}
	if (correctIngredients == 3 )
	{
		int i;
		for (i=0 ; i<3; i++)
		{
			ingTab[i].visible = false;
			setIngredient(ingTab[i]);
		}
		gameSubDone = true;
	}

}


/**
 * \brief Checks whether the selected ingredient was dropped in the cup or outside. Then acts accordingly
 */
void handleSelected(ingredient* ing)
{

	if(keysHeld() & KEY_TOUCH) // drag and drop
	{
		touchPosition tp;
		touchRead(&tp);
		ing->x = tp.px;
		ing-> y = tp.py;
	}
	else
	{
		// Inside the ellipse representing the coffee cup
		if(distance(ing->x,ing->y,F1_X,POT_CENTRE_Y) + distance(ing->x,ing->y,F2_X,POT_CENTRE_Y) <= ELLIPSE_2A)
			ingredientChosen(ing);

		ing->selected = false;
			//printf("DROPPED\n");
		selectedIndex = NONE;
		resetIngredientPos(ing);
	}
	setIngredient(*ing);
}


void gameplaySub()
{
	if(selectedIndex == NONE)
		selectIngredient();
	else
		handleSelected(&ingTab[selectedIndex]);

   	oamUpdate(&oamSub);
}

void gameLostSub()
{
	int i;
	for(i=0 ; i<3 ; i++)
	{
		ingTab[i].visible = false;
		orderTab[i].visible = false;
		setIngredient(ingTab[i]);
		setIngredient(orderTab[i]);
	}
}


