
#include"graphics_sub.h"

#include <nds.h>
#include <stdio.h>

int main(void) {
	//Graphics
    initGraphicsSub();
    while(1)
        swiWaitForVBlank();	
}
