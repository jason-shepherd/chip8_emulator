#ifndef CLOCK_H
#define CLOCK_H

#include "types.h"
#include "SDL.h"

typedef struct Clock {
	u16 clock_speed;
	u8 run;
	Uint64 now;
	Uint64 last;
	double deltatime;
} Clock;

void clock_init(Clock*, u16);
void clock_update(Clock*);

#endif
