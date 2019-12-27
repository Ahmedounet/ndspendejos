

#include "graphics_main.h"
#include "ingredient.h"
#include <nds.h>



int main(void) {
	//Graphics
    initGraphicsMain();
    ingredient* tab = initIngredientTab();
	initSpriteHandler();
	//consoleDemoInit();

    while(1)
    {

    	setIngredient(tab[COFFEE]);
    	swiWaitForVBlank();
    	//printf("%d, %d \n",tab[COFFEE].x, tab[COFFEE].y);
    	oamUpdate(&oamMain);
    }
}
