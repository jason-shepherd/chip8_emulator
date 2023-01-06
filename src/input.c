#include "input.h"
#include "chip8.h"
#include "SDL.h"

#include <stdio.h>

int input_update() {
	SDL_Event event;

	SDL_PollEvent(&event);
	u8 mapped = input_map(event.key.keysym.sym);
	switch(event.type)
	{
		case SDL_QUIT:
			printf("Quit triggered\n");
			chip8.quit = 1;
			break;
		case SDL_KEYDOWN:
			if(mapped <= 0xF) {
				keyboard[mapped] = 1;
				return mapped;
			}
			break;
		case SDL_KEYUP:
			if(mapped <= 0xF)
				keyboard[mapped] = 0;
			break;
	}

	return -1;
}

u8 input_wait_key() {	
	int key;
	while(!chip8.quit) {
		key = input_update();
		if(key > 0) {
				return key;
		}
	}
}

u8 input_map(int keycode) {
	for(int i = 0; i < 16; i++) {
		if(keycode == KEYMAP[i]) {
			return i;
		}
	}

	return 0xFF;
}

u8 input_getkey(u8 key) {
	return keyboard[key];
}
