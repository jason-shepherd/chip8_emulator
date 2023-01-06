#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include "SDL.h"

#include "types.h"

#define SCALER 20

static struct Screen {
	SDL_Window* window;
	SDL_Renderer* renderer;
} screen;

int display_init(u8[64][32]);
void display_render(u8[64][32]);
void display_quit();
void display_print(u8[64][32]);

#endif
