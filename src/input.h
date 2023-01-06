#ifndef INPUT_H
#define INPUT_H

#include "types.h"
#include "SDL.h"

static u8 keyboard[16];
const static u8 KEYMAP[16] = {
    SDLK_x, // 0
    SDLK_1, // 1
    SDLK_2, // 2
    SDLK_3, // 3
    SDLK_q, // 4
    SDLK_w, // 5
    SDLK_e, // 6
    SDLK_a, // 7
    SDLK_s, // 8
    SDLK_d, // 9
    SDLK_z, // A
    SDLK_c, // B
    SDLK_4, // C
    SDLK_r, // D
    SDLK_f, // E
    SDLK_v  // F
};

int input_update();
u8 input_wait_key();
u8 input_map(int);
u8 input_getkey(u8);

#endif
