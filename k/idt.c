#include <stdio.h>

#include "idt.h"
#include "interrupt_handler.h"

static idt_entry_t idt[IDT_ENTRY_COUNT];

void print_idt_entry(size_t index)
{
    printf("IDT ENTRY %u\r\n", index);
}

void set_idt_entry(size_t index, u32 offset, u16 selector, u8 type, u8 attributes)
{
    idt[index].offset_1 = (u16)offset;
    idt[index].selector = selector;
    idt[index].zero = 0;
    idt[index].type_attributes = type | attributes;
    idt[index].offset_2 = (u16)(offset >> 16);
}

void idt_init()
{
    for (size_t i = 0; i < IDT_ENTRY_COUNT; i++)
        set_idt_entry(i, i, 0x8, INT, 0x80);
    
    idtr_t idtr;
    idtr.base = (u32)idt;
    idtr.limit = sizeof(idt) - 1;

    // LIDT
    asm volatile ("lidt %0\n" : /* No output */ : "m"(idtr) : "memory");
}