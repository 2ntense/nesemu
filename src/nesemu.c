#include "cpu.h"
#include "cartridge.h"

int main(int argc, char** argv)
{
    init_rom("roms/smb.nes");
    print_header();
    // close_rom();

    init_cpu();
    load_prg_rom();
    init_pc();

    // load_rom(argv[1]);
    while (1)
    {
        step();
    }

    close_rom();
}