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

void invoke(instruction_t *instruction);

void brk();
void ora(addr_mode *mode);
void asl(addr_mode *mode);
void php();
void bpl(addr_mode *mode);
void clc();
void and(addr_mode *mode);
void bit(addr_mode *mode);
void rol(addr_mode *mode);
void plp();
void bmi(addr_mode *mode);
void sec();
void rti();
void eor(addr_mode *mode);
void lsr(addr_mode *mode);
void pha();
void bvc(addr_mode *mode);
void jmp(addr_mode *mode);
void jsr(addr_mode *mode);
void cli();
void rts();
void adc(addr_mode *mode);
void ror(addr_mode *mode);
void pla();
void bvs(addr_mode *mode);
void sei();
void sta(addr_mode *mode);
void sty(addr_mode *mode);
void stx(addr_mode *mode);
void dey();
void txa();
void bcc(addr_mode *mode);
void tya();
void txs();
void ldy(addr_mode *mode);
void lda(addr_mode *mode);
void ldx(addr_mode *mode);
void tay();
void tax();
void bcs(addr_mode *mode);
void clv();
void tsx();
void cpy(addr_mode *mode);
void cmp(addr_mode *mode);
void dec(addr_mode *mode);
void iny();
void dex();
void bne(addr_mode *mode);
void cld();
void cpx(addr_mode *mode);
void sbc(addr_mode *mode);
void inc(addr_mode *mode);
void inx();
void nop();
void beq(addr_mode *mode);
void sed();

#endif
