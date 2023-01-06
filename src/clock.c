#include <stdio.h>

#include "clock.h"

void clock_init(Clock* clock, u16 clock_speed) {
	clock->clock_speed = clock_speed;

	clock->now = 0;
	clock->last = 0;
	clock->deltatime = 0;
	clock->run = 1;	
}

void clock_update(Clock* clock) {
	clock->run = 0;
	clock->now = SDL_GetPerformanceCounter();
	clock->deltatime = (double)((clock->now - clock->last) * 1000 / (double)SDL_GetPerformanceFrequency());

	if(clock->deltatime > (1000.0 / clock->clock_speed)) {
		clock->run = 1;
		clock->last = clock->now;
		clock->deltatime = 0;
	}
}
