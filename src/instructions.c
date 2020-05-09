#include "instructions.h"
#include "cpu.h"
#include <stdio.h>

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
    {"ASL", ACC, asl_a}, // 0x0a
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
    {"ROL", ACC, rol_a}, // 0x2a
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
    {"LSR", ACC, lsr_a}, // 0x4a
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
    {"ROR", ACC, ror_a}, // 0x6a
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

void execute_op(instruction_t *instruction)
{
    uint16_t eff_addr;
    uint8_t zpg_addr;
    uint8_t adl;
    uint8_t adh;

    switch (instruction->mode)
    {
    case IND:
        eff_addr = MEM(read_short());
        break;
    case IND_X:
        zpg_addr = read_byte();
        adl = MEM((zpg_addr + REG_X) % 0xff);
        adh = MEM((zpg_addr + REG_X + 1) % 0xff);
        eff_addr = WORD(adl, adh);
        break;
    case IND_Y:
        zpg_addr = read_byte();
        adl = MEM(zpg_addr);
        adh = MEM(zpg_addr + 1);
        eff_addr = WORD(adl, adh) + REG_Y;
        break;
    case ZPG:
        eff_addr = read_byte();
        break;
    case ZPG_X:
        eff_addr = read_byte() + REG_X;
        break;
    case ZPG_Y:
        eff_addr = read_byte() + REG_Y;
        break;
    case ABS:
        eff_addr = read_short();
        break;
    case ABS_X:
        eff_addr = read_short() + REG_X;
        break;
    case ABS_Y:
        eff_addr = read_short() + REG_Y;
        break;
    case REL:
        eff_addr = (int8_t)read_byte();
        break;
    case IMM:
        eff_addr = (uint8_t)read_byte();
        break;
    case ACC:
    case IMP:
        eff_addr = 0;
        break;
    default:
        printf("Invalid addressing mode\n");
        return;
    }

    if (eff_addr)
    {
        ((void (*)(uint16_t))instruction->fun)(eff_addr);
    }
    else
    {
        ((void (*)(void))instruction->fun)();
    }
}

/**
 * Load and store group
 */
void lda(uint16_t eff_addr)
{
    uint8_t val = MEM(eff_addr);
    REG_A = val;
    FLAG_Z = (REG_A == 0);
    FLAG_N = ((REG_A >> 7) & 1);
}

void ldy(uint16_t eff_addr)
{
    uint8_t val = MEM(eff_addr);
    REG_Y = val;
    FLAG_Z = (REG_Y == 0);
    FLAG_N = ((REG_Y >> 7) & 1);
}

void ldx(uint16_t eff_addr)
{
    uint8_t val = MEM(eff_addr);
    REG_X = val;
    FLAG_Z = (REG_X == 0);
    FLAG_N = ((REG_X >> 7) & 1);
}

void sta(uint16_t eff_addr)
{
    MEM(eff_addr) = REG_A;
}

void sty(uint16_t eff_addr)
{
    MEM(eff_addr) = REG_Y;
}

void stx(uint16_t eff_addr)
{
    MEM(eff_addr) = REG_X;
}

/**
 * Arithmetic group
 */
void adc(uint16_t eff_addr)
{
    uint8_t val = MEM(eff_addr);
    uint16_t sum = REG_A + val + FLAG_C;
    uint8_t carry = sum > 0xff;
    uint8_t overflow = ~(REG_A ^ val) & (REG_A ^ sum) & 0x80;
    REG_A = sum & 0xff;
    FLAG_C = carry;
    FLAG_V = overflow;
    FLAG_Z = (REG_A == 0);
    FLAG_N = ((REG_A >> 7) & 1);
}

void sbc(uint16_t eff_addr)
{
    uint8_t val = MEM(eff_addr) ^ 0x00ff;
    val ^= 0x00FF;
    uint16_t sum = REG_A + val + FLAG_C;
    uint8_t carry = sum > 0xff;
    uint8_t overflow = ~(REG_A ^ val) & (REG_A ^ sum) & 0x80;
    REG_A = sum & 0xff;
    FLAG_C = carry;
    FLAG_V = overflow;
    FLAG_Z = (REG_A == 0);
    FLAG_N = ((REG_A >> 7) & 1);
}

/**
 * Increment and decrement group 
 */
void inc(uint16_t eff_addr)
{
    uint8_t *val = &MEM(eff_addr);
    *val++;
    FLAG_Z = (*val == 0);
    FLAG_N = ((*val >> 7) & 1);
}

void inx()
{
    REG_X++;
    FLAG_Z = (REG_X == 0);
    FLAG_N = ((REG_X >> 7) & 1);
}

void iny()
{
    REG_Y++;
    FLAG_Z = (REG_Y == 0);
    FLAG_N = ((REG_Y >> 7) & 1);
}

void dec(uint16_t eff_addr)
{
    uint8_t *val = &MEM(eff_addr);
    *val--;
    FLAG_Z = (*val == 0);
    FLAG_N = ((*val >> 7) & 1);
}

void dex()
{
    REG_X--;
    FLAG_Z = (REG_X == 0);
    FLAG_N = ((REG_X >> 7) & 1);
}

void dey()
{
    REG_Y--;
    FLAG_Z = (REG_Y == 0);
    FLAG_N = ((REG_Y >> 7) & 1);
}

/**
 * Register transfer group
 */
void tax()
{
    REG_X = REG_A;
    FLAG_Z = (REG_X == 0);
    FLAG_N = ((REG_X >> 7) & 1);
}

void tay()
{
    REG_Y = REG_A;
    FLAG_Z = (REG_Y == 0);
    FLAG_N = ((REG_Y >> 7) & 1);
}

void txa()
{
    REG_A = REG_X;
    FLAG_Z = (REG_A == 0);
    FLAG_N = ((REG_A >> 7) & 1);
}

void tya()
{
    REG_Y = REG_A;
    FLAG_Z = (REG_Y == 0);
    FLAG_N = ((REG_Y >> 7) & 1);
}

/**
 * Logical group
 */
void and (uint16_t eff_addr)
{
    uint8_t val = MEM(eff_addr);
    REG_A &= val;
    FLAG_Z = (REG_A == 0);
    FLAG_N = ((REG_A >> 7) & 1);
}

void eor(uint16_t eff_addr)
{
    uint8_t val = MEM(eff_addr);
    REG_A ^= val;
    FLAG_Z = (REG_A == 0);
    FLAG_N = (REG_A >> 7 & 1);
}

void ora(uint16_t eff_addr)
{
    uint8_t val = MEM(eff_addr);
    REG_A |= val;
    FLAG_Z = (REG_A == 0);
    FLAG_N = (REG_A >> 7 & 1);
}

/**
 * Compare and bit test group
 */
void cmp(uint16_t eff_addr)
{
    uint8_t val = MEM(eff_addr);
    uint8_t diff = REG_A - val;
    FLAG_C = (REG_A >= val);
    FLAG_Z = (REG_A == val);
    FLAG_N = ((diff >> 7) & 1);
}

void cpx(uint16_t eff_addr)
{
    uint8_t val = MEM(eff_addr);
    uint8_t diff = REG_X - val;
    FLAG_C = (REG_X >= val);
    FLAG_Z = (REG_X == val);
    FLAG_N = ((diff >> 7) & 1);
}

void cpy(uint16_t eff_addr)
{
    uint8_t val = MEM(eff_addr);
    uint8_t diff = REG_Y - val;
    FLAG_C = (REG_Y >= val);
    FLAG_Z = (REG_Y == val);
    FLAG_N = ((diff >> 7) & 1);
}

void bit(uint16_t eff_addr)
{
    uint8_t val = MEM(eff_addr);
    FLAG_Z = (REG_A & val == 0);
    FLAG_N = ((val >> 7) & 1);
    FLAG_V = ((val >> 6) & 1);
}

/**
 * Shift and rotate group
 */
void asl(uint16_t eff_addr)
{
    uint8_t *val = &MEM(eff_addr);
    FLAG_C = (*val >> 7 & 1);
    *val <<= 1;
    FLAG_N = (*val >> 7 & 1);
    FLAG_Z = (*val == 0) ? 1 : FLAG_C;
}

void asl_a(void)
{
    FLAG_C = (REG_A >> 7 & 1);
    REG_A <<= 1;
    FLAG_N = (REG_A >> 7 & 1);
    FLAG_Z = (REG_A == 0) ? 1 : FLAG_C;
}

void lsr(uint16_t eff_addr)
{
    uint8_t *val = &MEM(eff_addr);
    FLAG_C = (*val & 1);
    *val >>= 1;
    FLAG_N = 0;
    FLAG_Z = (*val == 0);
}

void lsr_a()
{
    FLAG_C = (REG_A & 1);
    REG_A >>= 1;
    FLAG_N = 0;
    FLAG_Z = (REG_A == 0);
}

void rol(uint16_t eff_addr)
{
    uint8_t *val = &MEM(eff_addr);
    uint8_t old_msb = (*val >> 7) & 1;
    *val <<= 1;
    *val |= FLAG_C;
    FLAG_C = old_msb;
    FLAG_Z = (*val == 0);
    FLAG_N = ((*val >> 7) & 1);
}

void rol_a()
{
    uint8_t old_msb = (REG_A >> 7) & 1;
    REG_A <<= 1;
    REG_A |= FLAG_C;
    FLAG_C = old_msb;
    FLAG_Z = (REG_A == 0);
    FLAG_N = ((REG_A >> 7) & 1);
}

void ror(uint16_t eff_addr)
{
    uint8_t *val = &MEM(eff_addr);
    uint8_t old_lsb = *val & 1;
    *val >>= 1;
    if (FLAG_C)
    {
        *val |= 0x80;
    }
    FLAG_C = old_lsb;
    FLAG_Z = (*val == 0);
    FLAG_N = ((*val >> 7) & 1);
}

void ror_a()
{
    uint8_t old_lsb = REG_A & 1;
    REG_A >>= 1;
    if (FLAG_C)
    {
        REG_A |= 0x80;
    }
    FLAG_C = old_lsb;
    FLAG_Z = (REG_A == 0);
    FLAG_N = ((REG_A >> 7) & 1);
}

/**
 * Jump and branch group
 */
void jmp(uint16_t eff_addr)
{
    REG_PC = eff_addr;
}

void bcc(uint16_t eff_addr)
{
    if (FLAG_C == 0)
    {
        REG_PC += (int8_t)eff_addr;
    }
    else
    {
        REG_PC++;
    }
}

void bcs(uint16_t eff_addr)
{
    if (FLAG_C == 1)
    {
        REG_PC += (int8_t)eff_addr;
    }
    else
    {
        REG_PC++;
    }
}

void beq(uint16_t eff_addr)
{
    if (FLAG_Z)
    {
        REG_PC += (int8_t)eff_addr;
    }
    else
    {
        REG_PC++;
    }
}

void bmi(uint16_t eff_addr)
{
    if (FLAG_N)
    {
        REG_PC += (int8_t)eff_addr;
    }
    else
    {
        REG_PC++;
    }
}

void bne(uint16_t eff_addr)
{
    if (FLAG_Z == 0)
    {
        REG_PC += (int8_t)eff_addr;
    }
    else
    {
        REG_PC++;
    }
}

void bpl(uint16_t eff_addr)
{
    if (FLAG_N == 0)
    {
        REG_PC += (int8_t)eff_addr;
    }
    else
    {
        REG_PC++;
    }
}

void bvc(uint16_t eff_addr)
{
    if (FLAG_V == 0)
    {
        REG_PC += (int8_t)eff_addr;
    }
    else
    {
        REG_PC += 1;
    }
}

void bvs(uint16_t eff_addr)
{
    if (FLAG_V)
    {
        REG_PC += (int8_t)eff_addr;
    }
    else
    {
        REG_PC++;
    }
}

/**
 * Stack group
 */

void tsx()
{
    REG_X = REG_SP;
    FLAG_Z = (REG_X == 0);
    FLAG_N = ((REG_X >> 7) & 1);
}

void txs()
{
    REG_X = REG_SP;
    FLAG_Z = (REG_X == 0);
    FLAG_N = ((REG_X >> 7) & 1);
}

void pha()
{
    stack_push(REG_A);
}

void php()
{
    stack_push(REG_P);
}

void pla()
{
    REG_A = stack_pop();
    FLAG_Z = (REG_A == 0);
    FLAG_N = ((REG_A >> 7) & 1);
}

void plp()
{
    REG_P = stack_pop();
    FLAG_B = 0;
}

/**
 * Status flag change group
 */
void clc()
{
    FLAG_C = 0;
}

void cld()
{
    FLAG_D = 0;
}

void cli()
{
    FLAG_I = 0;
}

void clv()
{
    FLAG_V = 0;
}

void sec()
{
    FLAG_C = 1;
}

void sed()
{
    FLAG_D = 1;
}

void sei()
{
    FLAG_I = 1;
}

/**
 * Subroutine and interrupt group
 */
void jsr(uint16_t eff_addr)
{
    uint16_t ret_addr = REG_PC + 1;
    stack_push(BYTE_HI(ret_addr));
    stack_push(BYTE_LO(ret_addr));
    REG_PC = eff_addr;
}

void rts()
{
    REG_PC = WORD(stack_pop(), stack_pop()) + 1;
}

void brk()
{
    uint16_t ret_addr = REG_PC + 1; // ???
    stack_push(BYTE_HI(ret_addr));
    stack_push(BYTE_LO(ret_addr));
    FLAG_B = 1;
    stack_push(REG_P);
    uint8_t new_pcl = MEM(VEC_IRQ_LO);
    uint8_t new_pch = MEM(VEC_IRQ_HI);
    REG_PC = WORD(new_pcl, new_pch);
}

void rti()
{
    REG_P = stack_pop();
    FLAG_B = 0;
    REG_PC = WORD(stack_pop(), stack_pop()) + 1;
}

void nop()
{
    REG_PC++;
}