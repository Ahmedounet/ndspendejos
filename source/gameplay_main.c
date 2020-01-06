/*
 * gameplay_main.c
 *
 *  Created on: Jan 5, 2020
 *      Author: nds
 */


#include "gameplay_main.h"
#include "graphics_main.h"
#include "timer_management.h"
#include "finite_state_machine.h"




void reset_home()
{
	change_bckg_priority(HOME_SCREEN,HOME_SCREEN);
	change_bckg_priority(MAZE_SCREEN,MAZE_SCREEN);
	change_bckg_priority(WIN_SCREEN,WIN_SCREEN);
	change_bckg_priority(LOSE_SCREEN,LOSE_SCREEN);

	priorities[MAZE_SCREEN]=1;
	priorities[WIN_SCREEN]=2;
	priorities[LOSE_SCREEN]=3;
	priorities[HOME_SCREEN]=0;

	reset_timer();
	irqEnable(IRQ_TIMER1);


}

void go_maze(int keys_held,int *x, int *y)
{
	*x=0; *y=0;
	change_bckg_priority(HOME_SCREEN,1);
	change_bckg_priority(MAZE_SCREEN,0);
	change_bckg_priority(WIN_SCREEN,3);
	change_bckg_priority(LOSE_SCREEN,2);
	priorities[MAZE_SCREEN]=0;
	priorities[WIN_SCREEN]=3;
	priorities[LOSE_SCREEN]=2;
	priorities[HOME_SCREEN]=1;



}

void winning_display(int *x, int *y)
{
	*x=0; *y=0;
	change_bckg_priority(WIN_SCREEN,0);
	change_bckg_priority(HOME_SCREEN,1);
	change_bckg_priority(LOSE_SCREEN,2);
	change_bckg_priority(MAZE_SCREEN,3);
	priorities[MAZE_SCREEN]=1;
	priorities[WIN_SCREEN]=0;
	priorities[LOSE_SCREEN]=2;
	priorities[HOME_SCREEN]=3;
}

void losing_screen (bool origin)
{
	//change_bckg_priority(MAZE_SCREEN,1);
	//change_bckg_priority(HOME_SCREEN,3);
	change_bckg_priority(LOSE_SCREEN,0);
	change_bckg_priority(WIN_SCREEN,2);
	priorities[LOSE_SCREEN]=0;
	priorities[WIN_SCREEN]=2;
	if(origin==FROM_HOME)
	{
		change_bckg_priority(MAZE_SCREEN,3);
		change_bckg_priority(HOME_SCREEN,1);
		priorities[MAZE_SCREEN]=3;
		priorities[HOME_SCREEN]=1;
	}

	else if(origin==FROM_MAZE)
	{
		change_bckg_priority(MAZE_SCREEN,1);
		change_bckg_priority(HOME_SCREEN,3);
		priorities[MAZE_SCREEN]=1;
		priorities[HOME_SCREEN]=3;
	}
}


void move_cup(int keys_held, int * x, int * y,int priority)
{
	//Modify position of the sprite accordingly
	if(!priority)
	{
	    	if((keys_held & KEY_RIGHT) && (*x < (SCREEN_WIDTH - SPRITE_WIDTH))) *x+=2;
	    	if((keys_held & KEY_DOWN) && (*y < (SCREEN_HEIGHT - SPRITE_HEIGHT))) *y+=2;
	    	if((keys_held & KEY_LEFT) && (*x  > 0)) *x-=2;
	    	if((keys_held & KEY_UP) && (*y  > 0)) *y-=2;
	}
	oamSet(&oamMain, 	// oam handler
		   	0,				// Number of sprite
	 		*x, *y,			// Coordinates
	 		priority,				// Priority
		    0,				// Palette to use
	  		SpriteSize_32x32,			// Sprite size
	  		SpriteColorFormat_256Color,	// Color format
    		gfx,			// Loaded graphic to display
    		-1,				// Affine rotation to use (-1 none)
		    false,			// Double size if rotating
		   	false,			// Hide this sprite
	 		false, false,	// Horizontal or vertical flip
	  		false			// Mosaic
    		);

}



int check_maze(int x, int y)
{
	if(x<(77-SPRITE_WIDTH) && y>(116-SPRITE_HEIGHT)   || x<(77) && y>(116) || x<(77) && y>(116-SPRITE_HEIGHT) || x<(77-SPRITE_WIDTH)
					&& y>(116)) //left corner obstacle
			{
				return MAZE_LOST;
			}

			if(x>210 && y<88 || (x+SPRITE_WIDTH)>210 && (y+SPRITE_HEIGHT)<88 || (x+SPRITE_WIDTH)>210 && y<88 ||
					x>210 && (y+SPRITE_HEIGHT)<88  ) //line obstacle
			{
				return MAZE_LOST;

			}

			if(x>113 && x<163 && y>116 || (x+SPRITE_WIDTH)>113 && (x+SPRITE_WIDTH)<163 && y>116 ||  x>113 && x<163 && (y+SPRITE_HEIGHT)>116
					|| (x+SPRITE_WIDTH)>113 && (x+SPRITE_WIDTH)<163 && (y+SPRITE_HEIGHT)>116 ) //mid rectangle obstacle
			{
				return MAZE_LOST;
			}



			if(x>48 && x<202 && y>28 && y<60 || (x+SPRITE_WIDTH)>48 && (x+SPRITE_WIDTH)<202 && (y+SPRITE_HEIGHT)>28
					&& (y+SPRITE_HEIGHT)<60 ||(x+SPRITE_WIDTH)>48 && (x+SPRITE_WIDTH)<202 && y>28
					&& y<60 || x>48 && x<202 && (y+SPRITE_HEIGHT)>28
					&& (y+SPRITE_HEIGHT)<60) //mid rectangle obstacle
			{
				return MAZE_LOST;
			}

		if(x>255 && y>160 || (x+SPRITE_WIDTH)>255 && (y+SPRITE_HEIGHT)>160 || (x+SPRITE_WIDTH)>255 && y>160 ||
			x>255 && (y+SPRITE_HEIGHT)>160)
			{
				return MAZE_WON;
			}

		return MAZE_ONGOING;
}
void set_priorities()
{
priorities[MAZE_SCREEN]=1;
priorities[WIN_SCREEN]=2;
priorities[LOSE_SCREEN]=3;
priorities[HOME_SCREEN]=0;

}
void init_main_screen()
{
configure_graphics_main();
configureSprites();
set_priorities();
initTimer();
}

void game_main_screen(int keys,int keys_held,int *x,int * y,int * maze)
{
		*maze=check_maze(*x,*y);
		finite_state_machine(x, y,*maze);
		move_cup( keys_held, x, y,priorities[MAZE_SCREEN]);
		oamUpdate(&oamMain);
}



