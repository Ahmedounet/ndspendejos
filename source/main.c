
#include <nds.h>
#include <stdio.h>
#include "graphics_main.h"

int main(void) {
	//Graphics
    initGraphicsMain();
    while(1)
        swiWaitForVBlank();	
}
