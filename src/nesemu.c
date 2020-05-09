#include "cpu.h"

int main(int argc, char** argv)
{
    init_cpu();
    load_rom(argv[1]);
    while (1)
    {
        step();
    }
}