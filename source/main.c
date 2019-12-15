

#include <nds.h>
#include <stdio.h>

int main(void) {
	//Graphics
    consoleDemoInit();
    printf("\n7aidar, il fallait build\n");

    while(1)
        swiWaitForVBlank();	
}
