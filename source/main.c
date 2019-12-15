/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>

int main(void) {
	
    consoleDemoInit();
    printf("\n7aidar, il fallait build\n");

    while(1)
        swiWaitForVBlank();	
}
