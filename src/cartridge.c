#include "cartridge.h"
#include <string.h>

rom_t rom;

void init_rom(char *rom_file)
{
    open_rom(rom_file);
    decode_header();
}

FILE *open_rom(char *path)
{
    rom.file = fopen(path, "rb");
    return rom.file;
}

void close_rom()
{
    fclose(rom.file);
}

void read_rom(uint8_t *dest, size_t n)
{
    fread(dest, 1, n, rom.file);
}

size_t read_prg_rom_bank(uint8_t *dest, uint8_t i)
{
    if (i >= rom.header_data.len_prg_rom)
    {
        printf("PRG-ROM out of range\n");
        return 0;
    }
    uint16_t addr = 0x10;
    if (rom.header_data.has_trainer)
    {
        addr += 0x200;
    }
    if (fseek(rom.file, addr + (EXT_PRG_ROM_LOWER_SIZE * i), SEEK_SET) != 0)
    {
        printf("fseek failed\n");
        return 0;
    }
    return fread(dest, 1, EXT_PRG_ROM_LOWER_SIZE, rom.file);
}

void decode_header()
{
    char header[HEADER_SIZE];
    rewind(rom.file);
    if (fread(header, 1, HEADER_SIZE, rom.file) != HEADER_SIZE)
    {
        printf("Failed to read cartridge header.\n");
        return;
    }
    const char magic_number[] = {'N', 'E', 'S', 0x1a};
    if (memcmp(header, magic_number, sizeof(magic_number)) != 0)
    {
        printf("Magic number invalid.\n");
        return;
    }
    bitfield bitfield = {.byte = header[6]};
    rom.header_data.len_prg_rom = header[4];
    rom.header_data.len_chr_rom = header[5];
    rom.header_data.mirroring = bitfield.bits.b0;
    rom.header_data.has_batt_ram = bitfield.bits.b1;
    rom.header_data.has_trainer = bitfield.bits.b2;
    rom.header_data.four_scr = bitfield.bits.b3;
    rom.header_data.rom_map_type = bitfield.byte >> 4;
    rom.header_data.vs = header[7] & 1;
    rom.header_data.rom_map_type |= header[7] & 0xf0;
    rom.header_data.len_prg_ram = header[8];
    rom.header_data.tv_sys = header[9] & 1;
}

void print_header()
{
    printf("PRG-ROM banks: %d\n", rom.header_data.len_prg_rom);
    printf("PRG-RAM banks: %d\n", rom.header_data.len_prg_ram);
    printf("CHR-ROM banks: %d\n", rom.header_data.len_chr_rom);
    printf("Mapper type: %d\n", rom.header_data.rom_map_type);
    printf("Mirroring: %d\n", rom.header_data.mirroring);
    printf("Battery-backed ram: %d\n", rom.header_data.has_batt_ram);
    printf("Trainer: %d\n", rom.header_data.has_trainer);
    printf("Four-screen mirroring: %d\n", rom.header_data.four_scr);
    printf("VS-system %d\n", rom.header_data.vs);
    printf("TV-system %d\n", rom.header_data.tv_sys);
}