#include <stdio.h>

#include "chip8.h"

int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf("Please enter rom path!!\n");
		return -1;
	}

 	chip8_init(argv[1]);

	while(!chip8.quit) {
		chip8_run();
	}
	
	chip8_quit();
	return 0;
}

