/*
 * touchHandler.c
 *
 *  Created on: 25 Dec 2019
 *      Author: Dev
 */

#include "touchHandler.h"
#include "sound.h"

#include <stdbool.h>
#include<math.h>

#define POT_CENTRE_X  123
#define POT_CENTRE_Y  81
#define ELLIPSE_2A  96
#define F1_X  81
#define F2_X  165
#define NONE -1



int selectedIndex = NONE;

void selectIngredient( int num, ingredient tab[num])
{

	scanKeys();
	if(keysDown() & KEY_TOUCH)
	{
		//printf("TOUCHED \n");
		touchPosition tp;
		touchRead(&tp);
		int i;
		for(i=0;i<num;i++)
		{
			if(tp.px >= tab[i].x && tp.px < tab[i].x + tab[i].width &&
			   tp.py >= tab[i].y && tp.py < tab[i].y + tab[i].height)
			{
				tab[i].selected =  true;
				selectedIndex = i;
				//printf("SELECTED: %d\n", tab[i].id);
			}
				else
				tab[i].selected =  false;
		}
	}
}


double distance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x1-x2,2) + pow(y1-y2,2));
}

/**
 * \brief Checks whether the selected ingredient was dropped in the cup or outside. Then acts accordingly
 */
void handleSelected(ingredient* ing)
{
	scanKeys();
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
		{
			plop();
			//printf("DROPPED IN THE CUP\n");
			//@TODO selected ingredient dropped into cup
		}
			ing->selected = false;
			//printf("DROPPED\n");
			selectedIndex = NONE;
			resetIngredientPos(ing);
	}
}


void handleTouch(int num, ingredient tab[num])
{

	if(selectedIndex == NONE)
		selectIngredient(num,tab);
	else
		handleSelected(&tab[selectedIndex]);
}
