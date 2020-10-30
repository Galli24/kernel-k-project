#include "gdt.h"

static gdt_entry_t gdt[6];

void set_entry(size_t index, u32 base, u32 limit, u8 access, u8 flags)
{
    gdt[index].base_1       = (u16)base;
    gdt[index].base_2       = (u8)(base >> 16);
    gdt[index].base_3       = (u8)(base >> 24);
    gdt[index].limit        = (u16)limit;
    gdt[index].access       = access;
    gdt[index].limit_flags  = ((limit >> 12) & 0xF0) | (flags & 0xF);
}

void gdt_init()
{
    // NULL Entry
    set_entry(0, 0, 0, 0, 0);

    // Kernel Code
    set_entry(1, 0, 0xFFFFFFFF, 0x5A, 0xC);
    // Kernel Data
    set_entry(2, 0, 0xFFFFFFFF, 0x53, 0xC);

    // User Code
    set_entry(3, 0, 0, 0, 0);
    // User Data
    set_entry(4, 0, 0, 0, 0);

    // TSS
    set_entry(5, 0, 0, 0, 0);

    gdtr_t gdtr;
    gdtr.base = (u32)gdt;
    gdtr.limit = sizeof(gdt) - 1;

    // LGDT
    asm volatile ("lgdt %0\n" : /* No output */ : "m"(gdtr) : "memory");

    // Enable PE
    asm volatile ("movl %cr0, %eax");
    asm volatile ("or $1, %al");
    asm volatile ("movl %eax, %cr0");

    /*// Segments
    asm volatile ("xor %ax, %ax");
    asm volatile ("movw %ax, %ds");
    asm volatile ("movw %ax, %fs");
    asm volatile ("movw %ax, %gs");
    asm volatile ("movw %ax, %ss");

    // Switch
    asm volatile ("pushl $0");
    asm volatile ("pushl $1f");
    asm volatile ("lret");
    asm volatile ("1:");*/
}