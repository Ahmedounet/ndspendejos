/*
 * touchHandler.c
 *
 *  Created on: 25 Dec 2019
 *      Author: Dev
 */

#include "touchHandler.h"

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
	u16 keys = keysDown();
	if(keys & KEY_TOUCH)
	{
		printf("TOUCHED \n");
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
				printf("SELECTED: %d\n", tab[i].id);
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


void dropSelected(ingredient ing)
{
	scanKeys();
	u16 keys = keysDown();
	if(keys & KEY_TOUCH)
	{
		touchPosition tp;
		touchRead(&tp);
		int x = tp.px;
		int y = tp.py;
		if(distance(x,y,F1_X,POT_CENTRE_Y) + distance(x,y,F2_X,POT_CENTRE_Y) <= ELLIPSE_2A)
		{
			//play plop
			printf("DROPPED IN THE POT\n");
			//selected ingredient dropped into pot
		}
			ing.selected = false;
			printf("DROPPED\n");
			selectedIndex = NONE;
	}
}


void handleTouch(int num, ingredient tab[num])
{

	if(selectedIndex == NONE)
		selectIngredient(num,tab);
	else
		dropSelected(tab[selectedIndex]);
}
