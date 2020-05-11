#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <stdint.h>
#include <stdio.h>
#include "cpu_macro.h"

#define HEADER_SIZE 16

typedef union {
    struct
    {
        uint8_t b0 : 1;
        uint8_t b1 : 1;
        uint8_t b2 : 1;
        uint8_t b3 : 1;
        uint8_t b4 : 1;
        uint8_t b5 : 1;
        uint8_t b6 : 1;
        uint8_t b7 : 1;
    } bits;
    uint8_t byte;
} bitfield;

typedef struct header_data
{
    uint8_t len_prg_rom;
    uint8_t len_prg_ram;
    uint8_t len_chr_rom;
    uint8_t rom_map_type;
    uint8_t mirroring : 1;
    uint8_t has_batt_ram : 1;
    uint8_t has_trainer : 1;
    uint8_t four_scr : 1;
    uint8_t vs : 1;
    uint8_t tv_sys : 1;

} header_data_t;

typedef struct rom
{
    FILE *file;
    header_data_t header_data;
} rom_t;
extern rom_t rom;

FILE *open_rom(char *path);
void close_rom();
void read_rom(uint8_t *dest, size_t n);
size_t read_prg_rom_bank(uint8_t *dest, uint8_t i);
void decode_header();
void print_header();
void init_rom(char *rom_file);
#endif