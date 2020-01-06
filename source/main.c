

#include "graphics_sub.h"
#include "graphics_main.h"
#include "timer_management.h"
#include "gameplay_main.h"
#include "gameplay_sub.h"
#include "sound.h"



#define SPRITE_WIDTH 32
#define SPRITE_HEIGHT 32







int main(void) {
	//Graphics
    initGraphicsSub();
    initIngredientTab();
	initSound();
	init_main_screen();
	musicOn();
	resetGameplaySub();// initializes everything for the main screen!
	//srand(clock());

	u16  keys;
	int x=0,y=0, maze=0;
	u16 keys_held;


	//consoleDemoInit();


    while(1)
    {

    	scanKeys();
    	keys = keysDown();
    	keys_held=keysHeld();
    	//end reading of keys for main screen purposes
    	game_main_screen(keys,keys_held,&x,&y,&maze); //the main screen game is all in this function!
    	if(!priorities[HOME_SCREEN])
    		gameplaySub();

    	swiWaitForVBlank();



    }
}
