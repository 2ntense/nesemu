#include "cpu.h"
#include <string.h>
#include "instructions.h"

cpu_t cpu;

void init_cpu()
{
    memset(&cpu, 0, sizeof(cpu));

    cpu.sp = 0x0200;
}

// void pc_inc(uint8_t count)
// {
//     cpu.pc += count;
// }

void stack_push(uint8_t val)
{
    cpu.sp--;
    if (cpu.sp >= 0x0100 && cpu.sp <= 0x1ff)
    {
        cpu.mem[cpu.sp] = val;
    }
    else
    {
        // TODO: stack pointer out of range
    }
}

uint8_t read_byte()
{
    return cpu.mem[cpu.pc++];
}

uint16_t read_short()
{
    uint8_t ll = read_byte();
    uint8_t hh = read_byte();

    return (hh << 8) | ll;
}

static uint8_t fetch_opcode()
{
    return read_byte();
}

static instruction_t *decode_opcode(uint8_t opcode)
{
    return &instructions[opcode];
}

static void execute_instruction(instruction_t *instruction)
{
    invoke(instruction);
}

void step()
{
    /*
    fetch
    decode
    execute
    */
    uint8_t opcode = fetch_opcode();
    instruction_t *instruction = decode_opcode(opcode);
    execute_instruction(instruction);
}