/*
 * gameplay_main.h
 *
 *  Created on: Jan 5, 2020
 *      Author: nds
 */

#ifndef GAMEPLAY_MAIN_H_
#define GAMEPLAY_MAIN_H_

#include <nds.h>


#define HOME_SCREEN 0
#define MAZE_SCREEN 1
#define WIN_SCREEN 2
#define LOSE_SCREEN 3

#define FROM_HOME 0
#define FROM_MAZE 1

#define SCREEN_WIDTH	256
#define	SCREEN_HEIGHT	192

#define	SPRITE_WIDTH	32
#define	SPRITE_HEIGHT	32

#define MAZE_LOST 2
#define MAZE_WON 1
#define MAZE_ONGOING 0

 u16 priorities[4];

 void losing_screen (bool origin);
 void winning_display(int *x, int *y);
 void go_maze(int keys_held,int *x, int *y);
 void reset_home();
 void move_cup(int keys_held, int * x, int * y, int priority);
 int check_maze(int x, int y);
 //void finite_state_machine(int keys,int *x, int *y, int maze);
 void set_priorities();
 void init_main_screen();
 void game_main_screen(int keys,int keys_held,int *x,int * y,int * maze);


#endif /* GAMEPLAY_MAIN_H_ */
