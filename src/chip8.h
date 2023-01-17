#ifndef CHIP8_H
#define CHIP8_H

#define CHIP8_DEBUG 0
#define CHIP8_DEBUG_REGISTERS 0
#define CHIP8_DEBUG_STACK 0
#define CHIP8_DEBUG_MEMORY 0
#define START_ADDR 0x200
#define CARRY_FLAG 0xF
#define CLOCKSPEED 760

#include "types.h"
#include "clock.h"

typedef struct Chip8 {
	u8 redraw;
	u8 quit;
	Clock clock;
	Clock timer_clock;
	u8 display[64][32];
	u8 registers[16];
	u8 memory[4096];
	u16 stack[16];
	u16 I;
	u16 PC;
	u8 SP;
	u8 DT;
	u8 ST;
} Chip8;

extern Chip8 chip8;

void chip8_load_rom(char*);
void chip8_init(char*);
void chip8_run();
void chip8_execute(u16);
void chip8_update_timers();
void chip8_quit();

void chip8_print_debug(u16);
void chip8_print_stack();
void chip8_print_memory(u16, u16);
void chip8_print_registers();

#endif
