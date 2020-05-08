#include "cpu.h"

int main()
{
    init_cpu();

    while (1)
    {
        step();
    }
}