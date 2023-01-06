#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "types.h"
#include "chip8.h"

//sys_addr ignored on modern emulators
void cls();
void ret();
void jp_addr(u16);
void call_addr(u16);
void se_vx_byte(u8, u8);
void sne_vx_byte(u8, u8);
void se_vx_vy(u8, u8);
void ld_vx_byte(u8, u8);
void add_vx_byte(u8, u8);
void ld_vx_vy(u8, u8);
void or_vx_vy(u8, u8);
void and_vx_vy(u8, u8);
void xor_vx_vy(u8, u8);
void add_vx_vy(u8, u8);
void sub_vx_vy(u8, u8);
void shr_vx(u8);
void subn_vx_vy(u8, u8);
void shl_vx(u8);
void sne_vx_vy(u8, u8);
void ld_i_addr(u16);
void jp_xnn(u16);
void rnd_vx_byte(u8, u8);
void drw(u8, u8, u8);
void skp_vx(u8);
void sknp_vx(u8);
void ld_vx_dt(u8);
void ld_vx_k(u8);
void ld_dt_vx(u8);
void ld_st_vx(u8);
void add_i_vx(u8);
void ld_f_vx(u8);
void ld_bcd_vx(u8);
void ld_i_vx(u8);
void ld_vx_i(u8);

#endif
