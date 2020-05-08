#include "instructions.h"
#include "cpu.h"
#include <stdio.h>

#define SET_FLAG_C(X) cpu.p.flags.c = (X)
#define SET_FLAG_Z(X) cpu.p.flags.z = (X)
#define SET_FLAG_I(X) cpu.p.flags.i = (X)
#define SET_FLAG_D(X) cpu.p.flags.d = (X)
#define SET_FLAG_B(X) cpu.p.flags.b = (X)
#define SET_FLAG_V(X) cpu.p.flags.v = (X)
#define SET_FLAG_N(X) cpu.p.flags.n = (X)

// #define SET_FLAG_C cpu.p.flags.c = 1
// #define SET_FLAG_Z cpu.p.flags.z = 1
// #define SET_FLAG_I cpu.p.flags.i = 1
// #define SET_FLAG_D cpu.p.flags.d = 1
// #define SET_FLAG_B cpu.p.flags.b = 1
// #define SET_FLAG_V cpu.p.flags.v = 1
// #define SET_FLAG_N cpu.p.flags.n = 1
// #define CLEAR_FLAG_C cpu.p.flags.c = 0
// #define CLEAR_FLAG_Z cpu.p.flags.z = 0
// #define CLEAR_FLAG_I cpu.p.flags.i = 0
// #define CLEAR_FLAG_D cpu.p.flags.d = 0
// #define CLEAR_FLAG_B cpu.p.flags.b = 0
// #define CLEAR_FLAG_V cpu.p.flags.v = 0
// #define CLEAR_FLAG_N cpu.p.flags.n = 0

instruction_t instructions[0x100] = {
    {"BRK", IMP, brk},   // 0x00
    {"ORA", IND_X, ora}, // 0x01
    {NULL, 0, NULL},     // 0x02
    {NULL, 0, NULL},     // 0x03
    {NULL, 0, NULL},     // 0x04
    {"ORA", ZPG, ora},   // 0x05
    {"ASL", ZPG, asl},   // 0x06
    {NULL, 0, NULL},     // 0x07
    {"PHP", IMP, php},   // 0x08
    {"ORA", IMM, ora},   // 0x09
    {"ASL", ACC, asl},   // 0x0a
    {NULL, 0, NULL},     // 0x0b
    {NULL, 0, NULL},     // 0x0c
    {"ORA", ABS, ora},   // 0x0d
    {"ASL", ABS, asl},   // 0x0e
    {NULL, 0, NULL},     // 0x0f
    {"BPL", REL, bpl},   // 0x10
    {"ORA", IND_Y, ora}, // 0x11
    {NULL, 0, NULL},     // 0x12
    {NULL, 0, NULL},     // 0x13
    {NULL, 0, NULL},     // 0x14
    {"ORA", ZPG_X, ora}, // 0x15
    {"ASL", ZPG_X, asl}, // 0x16
    {NULL, 0, NULL},     // 0x17
    {"CLC", IMP, clc},   // 0x18
    {"ORA", ABS_Y, ora}, // 0x19
    {NULL, 0, NULL},     // 0x1a
    {NULL, 0, NULL},     // 0x1b
    {NULL, 0, NULL},     // 0x1c
    {"ORA", ABS_X, ora}, // 0x1d
    {"ASL", ABS_X, asl}, // 0x1e
    {NULL, 0, NULL},     // 0x1f
    {"JSR", ABS, jsr},   // 0x20
    {"AND", IND_X, and}, // 0x21
    {NULL, 0, NULL},     // 0x22
    {NULL, 0, NULL},     // 0x23
    {"BIT", ZPG, bit},   // 0x24
    {"AND", ZPG, and},   // 0x25
    {"ROL", ZPG, rol},   // 0x26
    {NULL, 0, NULL},     // 0x27
    {"PLP", IMP, plp},   // 0x28
    {"AND", IMM, and},   // 0x29
    {"ROL", ACC, rol},   // 0x2a
    {NULL, 0, NULL},     // 0x2b
    {"BIT", ABS, bit},   // 0x2c
    {"AND", ABS, and},   // 0x2d
    {"ROL", ABS, rol},   // 0x2e
    {NULL, 0, NULL},     // 0x2f
    {"BMI", REL, bmi},   // 0x30
    {"AND", IND_Y, and}, // 0x31
    {NULL, 0, NULL},     // 0x32
    {NULL, 0, NULL},     // 0x33
    {NULL, 0, NULL},     // 0x34
    {"AND", ZPG_X, and}, // 0x35
    {"ROL", ZPG_X, rol}, // 0x36
    {NULL, 0, NULL},     // 0x37
    {"SEC", IMP, sec},   // 0x38
    {"AND", ABS_Y, and}, // 0x39
    {NULL, 0, NULL},     // 0x3a
    {NULL, 0, NULL},     // 0x3b
    {NULL, 0, NULL},     // 0x3c
    {"AND", ABS_X, and}, // 0x3d
    {"ROL", ABS_X, rol}, // 0x3e
    {NULL, 0, NULL},     // 0x3f
    {"RTI", IMP, rti},   // 0x40
    {"EOR", IND_X, eor}, // 0x41
    {NULL, 0, NULL},     // 0x42
    {NULL, 0, NULL},     // 0x43
    {NULL, 0, NULL},     // 0x44
    {"EOR", ZPG, eor},   // 0x45
    {"LSR", ZPG, lsr},   // 0x46
    {NULL, 0, NULL},     // 0x47
    {"PHA", IMP, pha},   // 0x48
    {"EOR", IMM, eor},   // 0x49
    {"LSR", ACC, lsr},   // 0x4a
    {NULL, 0, NULL},     // 0x4b
    {"JMP", ABS, jmp},   // 0x4c
    {"EOR", ABS, eor},   // 0x4d
    {"LSR", ABS, lsr},   // 0x4e
    {NULL, 0, NULL},     // 0x4f
    {"BVC", REL, bvc},   // 0x50
    {"EOR", IND_Y, eor}, // 0x51
    {NULL, 0, NULL},     // 0x52
    {NULL, 0, NULL},     // 0x53
    {NULL, 0, NULL},     // 0x54
    {"EOR", ZPG_X, eor}, // 0x55
    {"LSR", ZPG_X, lsr}, // 0x56
    {NULL, 0, NULL},     // 0x57
    {"CLI", IMP, cli},   // 0x58
    {"EOR", ABS_Y, eor}, // 0x59
    {NULL, 0, NULL},     // 0x5a
    {NULL, 0, NULL},     // 0x5b
    {NULL, 0, NULL},     // 0x5c
    {"EOR", ABS_X, eor}, // 0x5d
    {"LSR", ABS_X, lsr}, // 0x5e
    {NULL, 0, NULL},     // 0x5f
    {"RTS", IMP, rts},   // 0x60
    {"ADC", IND_X, adc}, // 0x61
    {NULL, 0, NULL},     // 0x62
    {NULL, 0, NULL},     // 0x63
    {NULL, 0, NULL},     // 0x64
    {"ADC", ZPG, adc},   // 0x65
    {"ROR", ZPG, ror},   // 0x66
    {NULL, 0, NULL},     // 0x67
    {"PLA", IMP, pla},   // 0x68
    {"ADC", IMM, adc},   // 0x69
    {"ROR", ACC, ror},   // 0x6a
    {NULL, 0, NULL},     // 0x6b
    {"JMP", IND, jmp},   // 0x6c
    {"ADC", ABS, adc},   // 0x6d
    {"ROR", ABS, ror},   // 0x6e
    {NULL, 0, NULL},     // 0x6f
    {"BVS", REL, bvs},   // 0x70
    {"ADC", IND_Y, adc}, // 0x71
    {NULL, 0, NULL},     // 0x72
    {NULL, 0, NULL},     // 0x73
    {NULL, 0, NULL},     // 0x74
    {"ADC", ZPG_X, adc}, // 0x75
    {"ROR", ZPG_X, ror}, // 0x76
    {NULL, 0, NULL},     // 0x77
    {"SEI", IMP, sei},   // 0x78
    {"ADC", ABS_Y, adc}, // 0x79
    {NULL, 0, NULL},     // 0x7a
    {NULL, 0, NULL},     // 0x7b
    {NULL, 0, NULL},     // 0x7c
    {"ADC", ABS_X, adc}, // 0x7d
    {"ROR", ABS_X, ror}, // 0x7e
    {NULL, 0, NULL},     // 0x7f
    {NULL, 0, NULL},     // 0x80
    {"STA", IND_X, sta}, // 0x81
    {NULL, 0, NULL},     // 0x82
    {NULL, 0, NULL},     // 0x83
    {"STY", ZPG, sty},   // 0x84
    {"STA", ZPG, sta},   // 0x85
    {"STX", ZPG, stx},   // 0x86
    {NULL, 0, NULL},     // 0x87
    {"DEY", IMP, dey},   // 0x88
    {NULL, 0, NULL},     // 0x89
    {"TXA", IMP, txa},   // 0x8a
    {NULL, 0, NULL},     // 0x8b
    {"STY", ABS, sty},   // 0x8c
    {"STA", ABS, sta},   // 0x8d
    {"STX", ABS, stx},   // 0x8e
    {NULL, 0, NULL},     // 0x8f
    {"BCC", REL, bcc},   // 0x90
    {"STA", IND_Y, sta}, // 0x91
    {NULL, 0, NULL},     // 0x92
    {NULL, 0, NULL},     // 0x93
    {"STY", ZPG_X, sty}, // 0x94
    {"STA", ZPG_X, sta}, // 0x95
    {"STX", ZPG_Y, stx}, // 0x96
    {NULL, 0, NULL},     // 0x97
    {"TYA", IMP, tya},   // 0x98
    {"STA", ABS_Y, sta}, // 0x99
    {"TXS", IMP, txs},   // 0x9a
    {NULL, 0, NULL},     // 0x9b
    {NULL, 0, NULL},     // 0x9c
    {"STA", ABS_X, sta}, // 0x9d
    {NULL, 0, NULL},     // 0x9e
    {NULL, 0, NULL},     // 0x9f
    {"LDY", IMM, ldy},   // 0xa0
    {"LDA", IND_X, lda}, // 0xa1
    {"LDX", IMM, ldx},   // 0xa2
    {NULL, 0, NULL},     // 0xa3
    {"LDY", ZPG, ldy},   // 0xa4
    {"LDA", ZPG, lda},   // 0xa5
    {"LDX", ZPG, ldx},   // 0xa6
    {NULL, 0, NULL},     // 0xa7
    {"TAY", IMP, tay},   // 0xa8
    {"LDA", IMM, lda},   // 0xa9
    {"TAX", IMP, tax},   // 0xaa
    {NULL, 0, NULL},     // 0xab
    {"LDY", ABS, ldy},   // 0xac
    {"LDA", ABS, lda},   // 0xad
    {"LDX", ABS, ldx},   // 0xae
    {NULL, 0, NULL},     // 0xaf
    {"BCS", REL, bcs},   // 0xb0
    {"LDA", IND_Y, lda}, // 0xb1
    {NULL, 0, NULL},     // 0xb2
    {NULL, 0, NULL},     // 0xb3
    {"LDY", ZPG_X, ldy}, // 0xb4
    {"LDA", ZPG_X, lda}, // 0xb5
    {"LDX", ZPG_Y, ldx}, // 0xb6
    {NULL, 0, NULL},     // 0xb7
    {"CLV", IMP, clv},   // 0xb8
    {"LDA", ABS_Y, lda}, // 0xb9
    {"TSX", IMP, tsx},   // 0xba
    {NULL, 0, NULL},     // 0xbb
    {"LDY", ABS_X, ldy}, // 0xbc
    {"LDA", ABS_X, lda}, // 0xbd
    {"LDX", ABS_Y, ldx}, // 0xbe
    {NULL, 0, NULL},     // 0xbf
    {"CPY", IMM, cpy},   // 0xc0
    {"CMP", IND_X, cmp}, // 0xc1
    {NULL, 0, NULL},     // 0xc2
    {NULL, 0, NULL},     // 0xc3
    {"CPY", ZPG, cpy},   // 0xc4
    {"CMP", ZPG, cmp},   // 0xc5
    {"DEC", ZPG, dec},   // 0xc6
    {NULL, 0, NULL},     // 0xc7
    {"INY", IMP, iny},   // 0xc8
    {"CMP", IMM, cmp},   // 0xc9
    {"DEX", IMP, dex},   // 0xca
    {NULL, 0, NULL},     // 0xcb
    {"CPY", ABS, cpy},   // 0xcc
    {"CMP", ABS, cmp},   // 0xcd
    {"DEC", ABS, dec},   // 0xce
    {NULL, 0, NULL},     // 0xcf
    {"BNE", REL, bne},   // 0xd0
    {"CMP", IND_Y, cmp}, // 0xd1
    {NULL, 0, NULL},     // 0xd2
    {NULL, 0, NULL},     // 0xd3
    {NULL, 0, NULL},     // 0xd4
    {"CMP", ZPG_X, cmp}, // 0xd5
    {"DEC", ZPG_X, dec}, // 0xd6
    {NULL, 0, NULL},     // 0xd7
    {"CLD", IMP, cld},   // 0xd8
    {"CMP", ABS_Y, cmp}, // 0xd9
    {NULL, 0, NULL},     // 0xda
    {NULL, 0, NULL},     // 0xdb
    {NULL, 0, NULL},     // 0xdc
    {"CMP", ABS_X, cmp}, // 0xdd
    {"DEC", ABS_X, dec}, // 0xde
    {NULL, 0, NULL},     // 0xdf
    {"CPX", IMM, cpx},   // 0xe0
    {"SBC", IND_X, sbc}, // 0xe1
    {NULL, 0, NULL},     // 0xe2
    {NULL, 0, NULL},     // 0xe3
    {"CPX", ZPG, cpx},   // 0xe4
    {"SBC", ZPG, sbc},   // 0xe5
    {"INC", ZPG, inc},   // 0xe6
    {NULL, 0, NULL},     // 0xe7
    {"INX", IMP, inx},   // 0xe8
    {"SBC", IMM, sbc},   // 0xe9
    {"NOP", IMP, nop},   // 0xea
    {NULL, 0, NULL},     // 0xeb
    {"CPX", ABS, cpx},   // 0xec
    {"SBC", ABS, sbc},   // 0xed
    {"INC", ABS, inc},   // 0xee
    {NULL, 0, NULL},     // 0xef
    {"BEQ", REL, beq},   // 0xf0
    {"SBC", IND_Y, sbc}, // 0xf1
    {NULL, 0, NULL},     // 0xf2
    {NULL, 0, NULL},     // 0xf3
    {NULL, 0, NULL},     // 0xf4
    {"SBC", ZPG_X, sbc}, // 0xf5
    {"INC", ZPG_X, inc}, // 0xf6
    {NULL, 0, NULL},     // 0xf7
    {"SED", IMP, sed},   // 0xf8
    {"SBC", ABS_Y, sbc}, // 0xf9
    {NULL, 0, NULL},     // 0xfa
    {NULL, 0, NULL},     // 0xfb
    {NULL, 0, NULL},     // 0xfc
    {"SBC", ABS_X, sbc}, // 0xfd
    {"INC", ABS_X, inc}, // 0xfe
    {NULL, 0, NULL},     // 0xff
};

void invoke(instruction_t *instruction)
{
    if (instruction->mode != IMP)
    {
        ((void (*)(addr_mode))instruction->fun)(instruction->mode);
    }
    else
    {
        ((void (*)(void))instruction->fun)();
    }
}

// TODO
void brk()
{

    SET_FLAG_B(1);
}

void ora(addr_mode *mode)
{
    uint16_t target_addr;
    uint8_t ll;
    uint8_t hh;

    uint8_t op0;
    uint16_t ops;

    uint16_t tmp;
    uint8_t carry;

    uint16_t eff_addr;

    switch (*mode)
    {
    case IND_X:
        op0 = read_byte();
        target_addr = cpu.mem[(cpu.x + op0) % 0xff];
        ll = cpu.mem[target_addr];
        hh = cpu.mem[target_addr + 1];
        cpu.a |= (hh << 8) | ll;
        break;
    case ZPG:
        op0 = read_byte();
        cpu.a |= (cpu.mem[op0 & 0xff]);
        break;
    case IMM:
        op0 = read_byte();
        cpu.a |= op0;
        break;
    case ABS:
        ops = read_short();
        cpu.a |= cpu.mem[ops];
        break;
    case IND_Y:
        carry = 0;
        tmp = read_byte() + cpu.y;
        if (tmp > 0xff)
        {
            tmp %= 0xff;
            carry = 1;
        }
        ll = cpu.mem[tmp];
        hh = cpu.mem[tmp + 1 + carry];
        eff_addr = (hh << 8) | ll;
        cpu.a |= cpu.mem[eff_addr];
        break;
    default:
        break;
    }

    SET_FLAG_Z(!cpu.a);
    SET_FLAG_N(cpu.a >> 7 & 1);
}

void asl(addr_mode *mode)
{
    uint8_t op0;
    uint16_t ops;
    uint8_t *val;

    switch (*mode)
    {
    case ZPG:
        // op0 = read_byte();
        // SET_FLAG_C(cpu.mem[op0 & 0xff] >> 7 & 1);
        // cpu.mem[op0 & 0xff] <<= 1;
        op0 = read_byte();
        val = &cpu.mem[op0];
        break;
    case ACC:
        // SET_FLAG_C(cpu.a >> 7 & 1);
        // cpu.a <<= 1;

        val = &cpu.a;
        break;
    case ABS:
        ops = read_short();
        val = &cpu.mem[ops];
        break;
    default:
        break;
    }

    SET_FLAG_C(*val >> 7 & 1);
    SET_FLAG_Z(!cpu.a);
    SET_FLAG_N(cpu.a >> 7 & 1);
    *val <<= 1;
}

void php()
{
    stack_push(cpu.p.byte);
}

void bpl()
{
    // should only process relative addressing mode
   if (cpu.p.flags.n == 0)
   {
       cpu.pc += (int8_t)read_byte();
   } 
}
void clc() {}
void and (addr_mode * mode) {}
void bit(addr_mode *mode) {}
void rol(addr_mode *mode) {}
void plp() {}
void bmi() {}
void sec() {}
void rti() {}
void eor(addr_mode *mode) {}
void lsr(addr_mode *mode) {}
void pha() {}
void bvc() {}
void jmp(addr_mode *mode) {}
void jsr(addr_mode *mode) {}
void cli() {}
void rts() {}
void adc(addr_mode *mode) {}
void ror(addr_mode *mode) {}
void pla() {}
void bvs(addr_mode *mode) {}
void sei() {}
void sta(addr_mode *mode) {}
void sty(addr_mode *mode) {}
void stx(addr_mode *mode) {}
void dey() {}
void txa() {}
void bcc(addr_mode *mode) {}
void tya() {}
void txs() {}
void ldy(addr_mode *mode) {}
void lda(addr_mode *mode) {}
void ldx(addr_mode *mode) {}
void tay() {}
void tax() {}
void bcs(addr_mode *mode) {}
void clv() {}
void tsx() {}
void cpy(addr_mode *mode) {}
void cmp(addr_mode *mode) {}
void dec(addr_mode *mode) {}
void iny() {}
void dex() {}
void bne(addr_mode *mode) {}
void cld() {}
void cpx(addr_mode *mode) {}
void sbc(addr_mode *mode) {}
void inc(addr_mode *mode) {}
void inx() {}
void nop() {}
void beq(addr_mode *mode) {}
void sed() {}
