#ifndef CPU_MACRO_H
#define CPU_MACRO_H

#define ADDR_PRG_ROM_LOWER_BANK_START 0x8000
#define ADDR_PRG_ROM_LOWER_BANK_END 0xC000 - 1
#define ADDR_PRG_ROM_UPPER_BANK_START 0xC000
#define ADDR_PRG_ROM_UPPER_BANK_END 0x10000 - 1

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

#define BYTE_LO(W) ((W) & 0xff)
#define BYTE_HI(W) (((W) >> 8) & 0xff)
#define WORD(LL, HH) (uint16_t)(((HH) << 8) | (LL))
#define MEM(A) cpu.mem[(A)]


#endif