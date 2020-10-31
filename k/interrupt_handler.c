#include <stdio.h>

#include "interrupt_handler.h"

void global_c_handler(u8 nb)
{
    printf("Received interrupt nb: %d\r\n", nb);
}