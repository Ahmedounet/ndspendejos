/*
 * graphics_main.h
 *
 *  Created on: Jan 5, 2020
 *      Author: nds
 */

#ifndef GRAPHICS_MAIN_H_
#define GRAPHICS_MAIN_H_

#include <nds.h>

void configure_graphics_main();

void change_bckg_priority(u16 bckg, u16 priority);

void configureSprites();

u16* gfx;

#endif /* GRAPHICS_MAIN_H_ */
