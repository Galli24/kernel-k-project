#include <stdio.h>
#include <string.h>

#include "idt.h"

idt_entry_t idt[IDT_ENTRY_COUNT];

void print_idt_entry(size_t index)
{
    printf("IDT ENTRY %u\r\n", index);
}

void set_idt_entry(size_t index, u32 offset, u16 selector, u8 flags)
{
    idt[index].offset_1 = (u16)offset;
    idt[index].selector = selector;
    idt[index].zero = 0;
    idt[index].type_attributes = flags | 0x60;
    idt[index].offset_2 = (u16)(offset >> 16);
}

void idt_init()
{
    idtr_t idtr;
    idtr.base = (u32)idt;
    idtr.limit = sizeof(idt) - 1;
    memset(idt, 0, sizeof(idt));

    // LIDT
    asm volatile ("lidt %0\n" : /* No output */ : "m"(idtr) : "memory");
}