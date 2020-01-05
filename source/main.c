

#include "ingredient.h"
#include "touchHandler.h"
#include "graphics_sub.h"
#include "sound.h"









int main(void) {
	//Graphics
    initGraphicsSub();
    ingredient* tab = initIngredientTab();
	configureSprites(tab);
	initSound();

	//consoleDemoInit();

	musicOn();

    while(1)
    {
    	swiWaitForVBlank();
    	handleTouch(3,tab);
    	setIngredient(tab[COFFEE]);
    	setIngredient(tab[SUGAR]);
    	setIngredient(tab[CREAM]);
    	//printf("%d, %d \n",tab[COFFEE].gfx, tab[SUGAR].gfx);
    	oamUpdate(&oamSub);
    }
}
