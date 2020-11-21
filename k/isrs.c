#include <stdio.h>

#include "idt.h"
#include "isrs.h"

void isrs_init()
{
    for (size_t i = 0; i < IDT_ENTRY_COUNT; i++)
        set_idt_entry(i, (unsigned)generic_c_handler, 0x08, INT, 0x80);
}

void generic_c_handler(u8 nb)
{
    printf("Received interrupt nb: %d\r\n", nb);
}