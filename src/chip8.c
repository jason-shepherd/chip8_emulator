#include <stdio.h>
#include <string.h>

#include "chip8.h"
#include "instructions.h"
#include "display.h"
#include "input.h"

Chip8 chip8;

void chip8_load_rom(char* filepath) {
	FILE* file = fopen(filepath, "rb");

	if(file == NULL) {
		printf("Could not open ROM.\n");
		chip8.quit = 1;
	}
	
	fread(chip8.memory + START_ADDR, 1, 4096 - START_ADDR, file);
	fclose(file);
}

void chip8_init(char* rom_path) {
	chip8.redraw = 0;
	chip8.quit = 0;

	chip8.I = 0;
	chip8.PC = 0;
	chip8.SP = 0;
	chip8.DT = 0;
	chip8.ST = 0;

	u8 font[80] = {
	  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	  0x20, 0x60, 0x20, 0x20, 0x70, // 1
	  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};
	memcpy(chip8.memory, font, 80);

	chip8_load_rom(rom_path);
	chip8.PC = START_ADDR;

 	display_init(chip8.display);
	clock_init(&chip8.clock, CLOCKSPEED);
	clock_init(&chip8.timer_clock, 60);
}

void chip8_run() {
  input_update();
	clock_update(&chip8.clock);
	clock_update(&chip8.timer_clock);
	chip8_update_timers();

	if(chip8.clock.run) {
		u16 instruction = (chip8.memory[chip8.PC] << 8) | chip8.memory[chip8.PC + 1];

		if(CHIP8_DEBUG)
			chip8_print_debug(instruction);

		chip8_execute(instruction);

		if(chip8.redraw)
			display_render(chip8.display);
	}
}

void chip8_execute(u16 instruction) {
	u8 opcode = (instruction & 0xF000) >> 12; //first nibble
  u8 vx = (instruction & 0x0F00) >> 8; //second nibble
  u8 vy = (instruction & 0x00F0) >> 4; //third nibble
  u8 k = instruction & 0x000F; //fourth nibble
  u8 kk = instruction & 0x00FF; //second byte
  u16 addr = instruction & 0x0FFF; //first 12 bits of instruction
	
	chip8.redraw = 0;
	chip8.PC += 2;	
	switch(opcode) {
		case 0x0:
			if(kk == 0xE0) {
				cls();
				chip8.redraw = 1;
			} else if (kk == 0xEE) {
				ret();
			}
			break;
		case 0x1:
			jp_addr(addr);
			break;
		case 0x2:
			call_addr(addr);
			break;
		case 0x3:
			se_vx_byte(vx, kk);
			break;
		case 0x4:
			sne_vx_byte(vx, kk);
			break;
		case 0x5:
			se_vx_vy(vx, vy);
			break;
		case 0x6:
			ld_vx_byte(vx, kk);
			break;
		case 0x7:
			add_vx_byte(vx, kk);
			break;
		case 0x8:
			switch(k) {
				case 0x0:
					ld_vx_vy(vx, vy);
					break;
				case 0x1:
					or_vx_vy(vx, vy);
					break;
				case 0x2:
					and_vx_vy(vx, vy);
					break;
				case 0x3:
					xor_vx_vy(vx, vy);
					break;
				case 0x4:
					add_vx_vy(vx, vy);
					break;
				case 0x5:
					sub_vx_vy(vx, vy);
					break;
				case 0x6: 
					shr_vx(vx);
					break;
				case 0x7:
					subn_vx_vy(vx, vy);
					break;
				case 0xE:
					shl_vx(vx);
					break;
			}
			break;	
		case 0x9:
			sne_vx_vy(vx, vy);
			break;
		case 0xA:
			ld_i_addr(addr);
			break;
		case 0xB:
			jp_xnn(addr);
			break;
		case 0xC:
			rnd_vx_byte(vx, kk);
			break;
		case 0xD:
			drw(vx, vy, k);
			chip8.redraw = 1;
			break;
		case 0xE:
			if(kk == 0x9E) {
				skp_vx(vx);
			}
			else if(kk == 0xA1) {
				sknp_vx(vx);
			}
			break;
		case 0xF:
			switch(kk) {
				case 0x07:
					ld_vx_dt(vx);
					break;
				case 0x0A:
					ld_vx_k(vx);
					break;
				case 0x15:
					ld_dt_vx(vx);
					break;
				case 0x18:
					ld_st_vx(vx);
					break;
				case 0x1E:
					add_i_vx(vx);
					break;
				case 0x29:
					ld_f_vx(vx);
					break;
				case 0x33:
					ld_bcd_vx(vx);
					break;
				case 0x55:
					ld_i_vx(vx);
					break;
				case 0x65:
					ld_vx_i(vx);
					break;
			}
			break;
		default:
			printf("Instruction: %04x not implemented.", instruction);
			break;
	}
}

void chip8_update_timers() {
	if(!chip8.timer_clock.run)
		return;

	if(chip8.DT)
		chip8.DT--;

	if(chip8.ST)
		chip8.ST--;
}

void chip8_print_debug(u16 instruction) {
	printf("| OP : %04x | PC: %04x | I:  %04x | DT: %04x | ST: %04x |\n",
					instruction, chip8.PC, chip8.I, chip8.DT, chip8.ST);

	if(CHIP8_DEBUG_REGISTERS)
		chip8_print_registers();

	if(CHIP8_DEBUG_STACK)
		chip8_print_stack();
	
	if(CHIP8_DEBUG_MEMORY)
		chip8_print_memory(START_ADDR, 4096);
}

void chip8_print_stack() {
	for(int i = 0; i < 16; i++) {
		printf("| %04x | ", chip8.stack[i]);
		if(chip8.SP == i)
			printf("<- SP");

		printf("\n");
	}
} 

void chip8_print_memory(u16 start, u16 end) {
	printf("| %04x: %02x |", start, chip8.memory[start]);
	for(int i = start + 1; i < end; i++) {
		printf(" %04x: %02x |", i, chip8.memory[i]);
		if(i % 10 == 0) {
			printf("\n");
		}
	}
	printf("\n");
}

void chip8_print_registers() {
	printf("| V0: %04x | ", chip8.registers[0]);
	for(int i = 1; i < 16; i++) {
		printf(" V%x: %04x | ", i, chip8.registers[i]);
	}
	printf("\n");
}
