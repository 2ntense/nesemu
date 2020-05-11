#ifndef CPU_MACRO_H
#define CPU_MACRO_H

#define INT_RAM_START 0x0000
#define INT_RAM_SIZE 0x800
#define INT_RAM_END INT_RAM_START + INT_RAM_SIZE - 1
#define INT_PPU_REG_START 0x2000
#define INT_PPU_REG_SIZE 0x8
#define INT_PPU_REG_END INT_PPU_REG_START + INT_PPU_REG_SIZE - 1
#define INT_APU_REG_START 0x4000
#define INT_APU_REG_SIZE 0x20
#define INT_APU_REG_END INT_APU_REG_START + INT_APU_REG_SIZE - 1
#define EXT_EXP_ROM_START 0x4020
#define EXT_EXP_ROM_SIZE 0x1fdf
#define EXT_EXP_ROM_END EXT_EXP_ROM_START + EXT_EXP_ROM_SIZE - 1
#define EXT_SRAM_START 0x6000
#define EXT_SRAM_SIZE 0x2000
#define EXT_SRAM_END EXT_SRAM_START + EXT_SRAM_SIZE - 1
#define EXT_PRG_ROM_LOWER_START 0x8000
#define EXT_PRG_ROM_LOWER_SIZE 0x4000
#define EXT_PRG_ROM_LOWER_END EXT_PRG_ROM_LOWER_START + EXT_PRG_ROM_LOWER_SIZE - 1
#define EXT_PRG_ROM_UPPER_START 0xc000
#define EXT_PRG_ROM_UPPER_SIZE 0x4000
#define EXT_PRG_ROM_UPPER_END EXT_PRG_ROM_UPPER_START + EXT_PRG_ROM_UPPER_SIZE - 1

#define VEC_NMI_LO 0xfffa
#define VEC_NMI_HI 0xfffb
#define VEC_RST_LO 0xfffc
#define VEC_RST_HI 0xfffd
#define VEC_IRQ_LO 0xfffe
#define VEC_IRQ_HI 0xffff

#define REG_PC cpu.pc
#define REG_SP cpu.sp
#define REG_P cpu.p.byte
#define REG_A cpu.a
#define REG_X cpu.x
#define REG_Y cpu.y

#define FLAG_C cpu.p.flags.c
#define FLAG_Z cpu.p.flags.z
#define FLAG_I cpu.p.flags.i
#define FLAG_D cpu.p.flags.d
#define FLAG_B cpu.p.flags.b
#define FLAG_V cpu.p.flags.v
#define FLAG_N cpu.p.flags.n

#define BYTE_LO(W) ((W)&0xff)
#define BYTE_HI(W) (((W) >> 8) & 0xff)
#define WORD(LL, HH) (uint16_t)(((HH) << 8) | (LL))
#define MEM(A) cpu.mem[(A)]

#endif