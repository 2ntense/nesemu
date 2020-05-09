#include "cpu.h"
#include <string.h>
#include "instructions.h"
#include <stdio.h>

cpu_t cpu;

void init_cpu()
{
    memset(&cpu, 0, sizeof(cpu));

    REG_P = 0x34;
    REG_SP = 0xfd;
    REG_PC = ADDR_PRG_ROM_LOWER_BANK_START;
}

void load_rom(char *rom_path)
{
    int ret;
    FILE *rom_file = fopen(rom_path, "rb");
    if (rom_file == NULL)
    {
        printf("Invalid rom file path.\n");
        return;
    }
    ret = fseek(rom_file, 0, SEEK_END) != 0;
    if (ret != 0)
    {
        printf("fseek failed.\n");
        return;
    }
    size_t rom_size = ftell(rom_file);
    rewind(rom_file);
    ret = fread(cpu.mem + ADDR_PRG_ROM_LOWER_BANK_START, 1, rom_size, rom_file);
    printf("%d / %lu\n", ret, rom_size);
    if (ret != rom_size)
    {
        printf("Reading rom failed.\n");
    }
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
    execute_op(instruction);
}

void step()
{
    uint8_t opcode = fetch_opcode();
    instruction_t *instruction = decode_opcode(opcode);
    execute_opcode(instruction);
}