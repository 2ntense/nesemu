#include "cpu.h"
#include <string.h>
#include "instructions.h"
#include <stdio.h>
#include "cartridge.h"

cpu_t cpu;

void init_cpu()
{
    memset(&cpu, 0, sizeof(cpu));

    REG_P = 0x34;
    REG_SP = 0xfd;
}

void init_pc()
{
    REG_PC = WORD(mem_read(VEC_RST_LO), mem_read(VEC_RST_HI));
}

// void load_rom(char *rom_path)
// {
//     int ret;
//     FILE *rom_file = fopen(rom_path, "rb");
//     if (rom_file == NULL)
//     {
//         printf("Invalid rom file path.\n");
//         return;
//     }
//     ret = fseek(rom_file, 0, SEEK_END) != 0;
//     if (ret != 0)
//     {
//         printf("fseek failed.\n");
//         return;
//     }
//     size_t rom_size = ftell(rom_file);
//     size_t to_write = rom_size > PRG_ROM_LOWER_BANK_SIZE ? PRG_ROM_LOWER_BANK_SIZE : rom_size;
//     rewind(rom_file);
//     ret = fread(cpu.mem + PRG_ROM_LOWER_BANK_START, 1, to_write, rom_file);
//     if (ret != to_write)
//     {
//         printf("Reading rom failed.\n");
//         return;
//     }
// #ifdef DEBUG
//     printf("Rom loaded.\n");
// #endif
// }

void load_prg_rom()
{
    size_t written = 0;
    switch (rom.header_data.len_prg_rom)
    {
    case 0:
        printf("No prg rom.\n");
        return;
    case 1:
        written += read_prg_rom_bank(cpu.mem + EXT_PRG_ROM_LOWER_START, 0);
        memcpy(cpu.mem + EXT_PRG_ROM_UPPER_START, cpu.mem + EXT_PRG_ROM_LOWER_START, EXT_PRG_ROM_LOWER_SIZE);
        written += EXT_PRG_ROM_LOWER_SIZE;
        break;
    case 2:
        written += read_prg_rom_bank(cpu.mem + EXT_PRG_ROM_LOWER_START, 0);
        written += read_prg_rom_bank(cpu.mem + EXT_PRG_ROM_UPPER_START, 1);
        break;
    default:
        break;
    }
    if (written != (EXT_PRG_ROM_LOWER_SIZE * 2))
    {
        printf("PRG-ROM write failed, written %d/%d\n", written, EXT_PRG_ROM_LOWER_SIZE * 2);
        return;
    }
}

void stack_push(uint8_t val)
{
    uint16_t push_addr = 0x0100 | cpu.sp;
    if (push_addr >= 0x0100 && push_addr <= 0x01ff) // 0x100 <= addr <= 0x1ff
    {
        mem_write(push_addr, val);
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
        return mem_read(pop_addr);
    }
    else
    {
        // TODO: stack pointer out of range
    }
}

uint8_t mem_read(uint16_t addr)
{
    // if (addr >= 0x800 && addr < 0x2000)
    // {
    //     addr = INT_RAM_START + (addr % INT_RAM_SIZE);
    // }
    // else if(addr >= 0x2008 && addr < 0x4000)
    // {
    //     addr = INT_PPU_REG_START + (addr % INT_PPU_REG_SIZE);
    // }
    return MEM(addr);
}

void mem_write(uint16_t addr, uint8_t val)
{
    if (addr >= INT_RAM_START && addr <= INT_RAM_END)
    {
        for (uint8_t i = 0; addr < 0x2000; i++, addr += i * INT_RAM_SIZE)
        {
            MEM(addr) = val;
        }
    }
    else if (addr >= 0x800 && addr < 0x2000)
    {
        mem_write(INT_RAM_START + (addr % INT_RAM_SIZE), val);
    }
    else if (addr >= INT_PPU_REG_START && addr <= INT_PPU_REG_END)
    {
        for (uint16_t i = 0; addr < 0x4000; i++, addr += i * INT_PPU_REG_SIZE)
        {
            MEM(addr) = val;
        }
    }
    else if (addr >= 0x2008 && addr <= 0x4000)
    {
        mem_write(INT_PPU_REG_START + (addr % INT_PPU_REG_SIZE), val);
    }
    else
    {
        MEM(addr) = val;
    }
}

uint8_t read_pc_byte()
{
    return mem_read(REG_PC++);
}

uint16_t read_pc_word()
{
    return WORD(read_pc_byte(), read_pc_byte());
}

void step()
{
    uint8_t opcode = read_pc_byte();
    instruction_t *instruction = &instructions[opcode];
#ifdef DEBUG
    printf("[0x%02x][%s]\n", opcode, instruction->mnemonic);
#endif
    execute_op(instruction);
}