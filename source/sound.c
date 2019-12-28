/*
 * sound.c
 *
 *  Created on: 28 Dec 2019
 *      Author: Dev
 */

#include "sound.h"

void initSound(void)
{
	mmInitDefaultMem((mm_addr)soundbank_bin);
	mmLoad(MOD_COFFEE);
	mmLoadEffect(SFX_PLOP);
}

void plop(void)
{
	mmEffect(SFX_PLOP);
}

void musicOn(void)
{
	mmStart(MOD_COFFEE,MM_PLAY_LOOP);
}

void shutUp(void)
{
	mmStop();
}
