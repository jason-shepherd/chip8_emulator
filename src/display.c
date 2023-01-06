#include <stdio.h>
#include <string.h>

#include "display.h"

int display_init(u8 display[64][32]) {
	memset(display, 0, 64 * 32);
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		printf("Error: %s\n", SDL_GetError());
		return 1;
	}	

	screen.window = SDL_CreateWindow("Chip8 Emulator", 100, 100, 64 * SCALER, 32 * SCALER, SDL_WINDOW_SHOWN);
	if (screen.window == NULL){
		printf("Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	screen.renderer = SDL_CreateRenderer(screen.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (screen.renderer == NULL){
		SDL_DestroyWindow(screen.window);
		printf("Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	
	return 0;
}

void display_render(u8 display[64][32]) {
	SDL_SetRenderDrawColor(screen.renderer, 0, 0, 0, 255);
	SDL_RenderClear(screen.renderer);
	SDL_SetRenderDrawColor(screen.renderer, 255, 255, 255, 255);

	for(int i = 0; i < 64; i++) {
		for(int j = 0; j < 32; j++) {
			if(display[i][j]) {
				SDL_Rect pixel = {
					i * SCALER,
					j * SCALER,
					SCALER,
					SCALER
				};

				SDL_RenderFillRect(screen.renderer, &pixel);
			}
		}
	}

	SDL_RenderPresent(screen.renderer);
}

void display_quit() {
	SDL_DestroyRenderer(screen.renderer);
	SDL_DestroyWindow(screen.window);
	SDL_Quit();
}

void display_print(u8 display[64][32]) {
	for(int j = 0; j < 32; j++) {
		for(int i = 0; i < 64; i++) {
			char c = display[ i ][ j ] == 1 ? 64 : ' ';
			printf("%c%c", c, c);
		}
		printf("\n");
	}
	printf("\n\n");
}
