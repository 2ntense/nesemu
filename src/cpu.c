#include "cpu.h"
#include <string.h>
#include "instructions.h"

cpu_t cpu;

void init_cpu()
{
    memset(&cpu, 0, sizeof(cpu));

    cpu.sp = 0xff;
}

// void pc_inc(uint8_t count)
// {
//     cpu.pc += count;
// }

void stack_push(uint8_t val)
{
    uint16_t push_addr = 0x0100 | cpu.sp;
    if (push_addr >= 0x0100 && push_addr <= 0x1ff)
    {
        cpu.mem[push_addr] = val;
        cpu.sp--;
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
    if (pop_addr >= 0x0100 && pop_addr <= 0x1ff)
    {
        return cpu.mem[pop_addr];
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