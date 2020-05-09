#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "cpu_macro.h"

typedef union
{
    struct {
        uint8_t c:1;
        uint8_t z:1;
        uint8_t i:1;
        uint8_t d:1;
        uint8_t b:1;
        uint8_t _:1;
        uint8_t v:1;
        uint8_t n:1;
    } flags;
    uint8_t byte;
} processor_status; //status register

typedef struct cpu {
    uint8_t mem[0x10000]; // 64K
    // special purpose registers
    uint16_t pc;
    uint8_t sp;
    processor_status p;

    // general purpose registers
    uint8_t a;
    uint8_t x;
    uint8_t y;
} cpu_t;

extern cpu_t cpu;

extern void init_cpu();
void load_rom(char *rom_path);
void stack_push(uint8_t val);
uint8_t stack_pop();
uint8_t read_byte();
uint16_t read_short();
extern void step();

#endif