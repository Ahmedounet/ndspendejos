/*
 * finite_state_machine.c
 *
 *  Created on: Jan 6, 2020
 *      Author: nds
 */

#include "finite_state_machine.h"

void finite_state_machine(int *x, int *y,int maze)
{
	u16 keys = keysDown();
	if(!priorities[HOME_SCREEN] )
		{
		    if(gameSubDone)
		    {
		    	go_maze(keys,x,y);
		    }

		    if(keys == KEY_UP)
		    {
		    	losing_screen(FROM_HOME);
		    }
		}


		if(!priorities[MAZE_SCREEN])
		{
			if(maze==MAZE_WON)
				winning_display(x, y);

			if(maze==MAZE_LOST)
				losing_screen(FROM_MAZE);
		}

		if(!priorities[WIN_SCREEN] && (keys == KEY_A) )
		{
			reset_home();
			resetGameplaySub();
		}


		if(!priorities[LOSE_SCREEN] && (keys == KEY_A) )
		{
			if(priorities[MAZE_SCREEN]==1)
				go_maze(keys,x,y);

			else
			{
				reset_home();
				resetGameplaySub();
			}
		}

		if(keys & KEY_START)
		{
			reset_home();
			resetGameplaySub();
		}

}
