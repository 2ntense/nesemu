#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>

typedef enum address_mode
{
    NONE,
    IMP,
    REL,
    ACC,
    IMM,
    IND,
    IND_X,
    IND_Y,
    ABS,
    ABS_X,
    ABS_Y,
    ZPG,
    ZPG_X,
    ZPG_Y,
} addr_mode;

typedef struct instruction
{
    char *mnemonic;
    addr_mode mode;
    void *fun;
} instruction_t;

extern instruction_t instructions[0x100];

void execute_op(instruction_t *instruction);

// Load and store group
void lda(uint16_t eff_addr);
void ldx(uint16_t eff_addr);
void ldy(uint16_t eff_addr);
void sta(uint16_t eff_addr);
void stx(uint16_t eff_addr);
void sty(uint16_t eff_addr);
// Arithmetic group
void adc(uint16_t eff_addr);
void sbc(uint16_t eff_addr);
// Increment and decrement group
void inc(uint16_t eff_addr);
void inx();
void iny();
void dec(uint16_t eff_addr);
void dex();
void dey();
// Register transfer group
void tax();
void tay();
void txa();
void tya();
// Logical group
void and(uint16_t eff_addr);
void eor(uint16_t eff_addr);
void ora(uint16_t eff_addr);
// Compare and bit test group
void cmp(uint16_t eff_addr);
void cpx(uint16_t eff_addr);
void cpy(uint16_t eff_addr);
void bit(uint16_t eff_addr);
// Shift and rotate group
void asl(uint16_t eff_addr);
void asl_a(void);
void lsr(uint16_t eff_addr);
void lsr_a(void);
void rol(uint16_t eff_addr);
void rol_a(void);
void ror(uint16_t eff_addr);
void ror_a(void);
// Jump and branch group
void jmp(uint16_t eff_addr);
void bcc(uint16_t eff_addr);
void bcs(uint16_t eff_addr);
void beq(uint16_t eff_addr);
void bmi(uint16_t eff_addr);
void bne(uint16_t eff_addr);
void bpl(uint16_t eff_addr);
void bvc(uint16_t eff_addr);
void bvs(uint16_t eff_addr);
// Stack group
void tsx();
void txs();
void pha();
void php();
void pla();
void plp();
// Status flag change group
void clc();
void cld();
void cli();
void clv();
void sec();
void sed();
void sei();
// Subroutine and interrupt group
void jsr(uint16_t eff_addr);
void rts();
void brk();
void rti();
void nop();

#endif
