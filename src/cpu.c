#include "cpu.h"
#include <string.h>
#include "instructions.h"

cpu_t cpu;

void init_cpu()
{
    memset(&cpu, 0, sizeof(cpu));

    cpu.sp = 0xff;
}

void stack_push(uint8_t val)
{
    uint16_t push_addr = 0x0100 | cpu.sp;
    if (push_addr >= 0x0100 && push_addr <= 0x01ff) // 0x100 <= addr <= 0x1ff
    {
        MEM(push_addr) = val;
        REG_SP--;
    }
    else
    {
        // TODO: stack pointer out of range
    }
}

uint8_t stack_pop()
{
    cpu.sp++;
    uint16_t pop_addr = 0x100 | cpu.sp;
    if (pop_addr >= 0x0100 && pop_addr <= 0x01ff)
    {
        return MEM(pop_addr);
    }
    else
    {
        // TODO: stack pointer out of range
    }
}

uint8_t get_byte(uint16_t addr)
{
    return MEM(addr);
}

uint8_t read_byte()
{
    return MEM(cpu.pc++);
}

uint16_t read_short()
{
    return WORD(read_byte(), read_byte());
}

static uint8_t fetch_opcode()
{
    return read_byte();
}

static instruction_t *decode_opcode(uint8_t opcode)
{
    return &instructions[opcode];
}

static void execute_opcode(instruction_t *instruction)
{
    invoke(instruction);
}

void step()
{
    uint8_t opcode = fetch_opcode();
    instruction_t *instruction = decode_opcode(opcode);
    execute_opcode(instruction);
}