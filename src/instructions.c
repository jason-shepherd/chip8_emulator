#include <stdlib.h> 

#include "instructions.h"
#include "display.h"
#include "chip8.h"
#include "input.h"

void cls() {
	for(int i = 0; i < 64; i++) {
		for(int j = 0; j < 32; j++) {
			chip8.display[i][j] = 0;
		}
	}
}

void ret() {
	chip8.PC = chip8.stack[--chip8.SP];
}

void jp_addr(u16 addr) {
	chip8.PC = addr;
}

void call_addr(u16 addr) {
	chip8.stack[chip8.SP++] = chip8.PC;
	chip8.PC = addr;
}

void se_vx_byte(u8 vx, u8 byte) {
	chip8.PC += 2 * (chip8.registers[vx] == byte);
}

void sne_vx_byte(u8 vx, u8 byte) {
	chip8.PC += 2 * (chip8.registers[vx] != byte);
}

void se_vx_vy(u8 vx, u8 vy) {
	chip8.PC += 2 * (chip8.registers[vx] == chip8.registers[vy]);
}

void ld_vx_byte(u8 vx, u8 byte) {
	chip8.registers[vx] = byte;
}

void add_vx_byte(u8 vx, u8 byte) {
	chip8.registers[vx] += byte;
}

void ld_vx_vy(u8 vx, u8 vy) {
	chip8.registers[vx] = chip8.registers[vy];
}

void or_vx_vy(u8 vx, u8 vy) {
	chip8.registers[vx] |= chip8.registers[vy];
}

void and_vx_vy(u8 vx, u8 vy) {
	chip8.registers[vx] &= chip8.registers[vy];
}

void xor_vx_vy(u8 vx, u8 vy) {
	chip8.registers[vx] ^= chip8.registers[vy];
}

void add_vx_vy(u8 vx, u8 vy) {
	u8 flag = chip8.registers[vx] + chip8.registers[vy] > 255;
	chip8.registers[vx] += chip8.registers[vy];
	chip8.registers[CARRY_FLAG] = flag;
}

void sub_vx_vy(u8 vx, u8 vy) {
	u8 flag = chip8.registers[vx] > chip8.registers[vy];
	chip8.registers[vx] -= chip8.registers[vy];
	chip8.registers[CARRY_FLAG] = flag;
}

void shr_vx(u8 vx) {
	u8 flag = chip8.registers[vx] & 0x1;
	chip8.registers[vx] >>= 1;
	chip8.registers[CARRY_FLAG] = flag;
}

void subn_vx_vy(u8 vx, u8 vy) {
	u8 flag = chip8.registers[vy] > chip8.registers[vx];
	chip8.registers[vx] = chip8.registers[vy] - chip8.registers[vx];
	chip8.registers[CARRY_FLAG] = flag;
}

void shl_vx(u8 vx) {
	u8 flag = (chip8.registers[vx] >> 7) & 0x1;
	chip8.registers[vx] <<= 1;
	chip8.registers[CARRY_FLAG] = flag;
}

void sne_vx_vy(u8 vx, u8 vy) {
	chip8.PC += 2 * (chip8.registers[vx] != chip8.registers[vy]);
}

void ld_i_addr(u16 addr) {
	chip8.I = addr;
}

void jp_xnn(u16 addr) {
	chip8.PC = addr + chip8.registers[(addr & 0x0F00) >> 8];
}

void rnd_vx_byte(u8 vx, u8 byte) {
	chip8.registers[vx] = rand() & byte;
}

void drw(u8 vx, u8 vy, u8 size) {
	u8 start_x = chip8.registers[vx] % 64;
	u8 start_y = chip8.registers[vy] % 32;

	u8 flag = 0;
	for(u8 y = 0; y < size; y++) {
		u8 row = chip8.memory[chip8.I + y];
		for(u8 x = 0; x < 8; x++) {
			if(start_x + x >= 64 || start_y + y >= 32)
				continue;

			u8 old = chip8.display[(start_x + x)][(start_y + y)];
			u8 new = (row & (0x80 >> x)) == 0 ? 0 : 1;
			chip8.display[start_x + x][start_y + y] = old ^ new;

			flag |= (old && new);
		}
	}

	chip8.registers[CARRY_FLAG] = flag;
}

void skp_vx(u8 vx) {
	chip8.PC += 2 * input_getkey(chip8.registers[vx]);
}

void sknp_vx(u8 vx) {
	chip8.PC += 2 * !input_getkey(chip8.registers[vx]);
}

void ld_vx_dt(u8 vx) {
	chip8.registers[vx]	= chip8.DT;
}
void ld_vx_k(u8 vx) {
	chip8.registers[vx] = input_wait_key();
}

void ld_dt_vx(u8 vx) {
	chip8.DT = chip8.registers[vx];
}

void ld_st_vx(u8 vx) {
	chip8.ST = chip8.registers[vx];
}

void add_i_vx(u8 vx) {
	chip8.I += chip8.registers[vx];
}

void ld_f_vx(u8 vx) {
	chip8.I = chip8.registers[vx] * 5;
}

void ld_bcd_vx(u8 vx) {
	chip8.memory[chip8.I + 2] =  chip8.registers[vx] % 10;
	chip8.memory[chip8.I + 1] = (chip8.registers[vx] / 10) % 10;
	chip8.memory[chip8.I]     =  chip8.registers[vx] / 100;
}

void ld_i_vx(u8 vx) {
	for(int i = 0; i <= vx; i++) {
		chip8.memory[chip8.I + i] = chip8.registers[i];
	}
}
void ld_vx_i(u8 vx) {
	for(int i = 0; i <= vx; i++) {
		chip8.registers[i] = chip8.memory[chip8.I + i];
	}
}
