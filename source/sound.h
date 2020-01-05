/*
 * sound.h
 *
 *  Created on: 28 Dec 2019
 *      Author: Dev
 */

#ifndef SOUND_H_
#define SOUND_H_

#include <nds.h>
#include <maxmod9.h>
#include <mm_types.h>

#include "soundbank.h"
#include "soundbank_bin.h"


void initSound(void);

void plop(void);

void musicOn(void);

void shutUp(void);


#endif /* SOUND_H_ */
