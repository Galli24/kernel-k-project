#include <stdio.h>

#include "gdt.h"

static gdt_entry_t gdt[6];

void print_gdt_entry(size_t index)
{
    printf("GDT ENTRY %u\r\n", index);
    printf("LIMIT: %x\r\n", gdt[index].limit);
    printf("BASE_1: %x\r\n", gdt[index].base_1);
    printf("BASE_2: %x\r\n", gdt[index].base_2);
    printf("ACCESS: %x\r\n", gdt[index].access);
    printf("LIMIT_FLAGS: %x\r\n", gdt[index].limit_flags);
    printf("BASE_3: %x\r\n\r\n", gdt[index].base_3);
}

void set_gdt_entry(size_t index, u32 base, u32 limit, u8 access, u8 flags)
{
    gdt[index].base_1       = (u16)base;
    gdt[index].base_2       = (u8)(base >> 16);
    gdt[index].base_3       = (u8)(base >> 24);
    gdt[index].limit        = (u16)limit;
    gdt[index].access       = access;
    gdt[index].limit_flags  = ((limit >> 16) & 0x0F) | (flags & 0xF0);
}

void gdt_init()
{
    // NULL Entry
    set_gdt_entry(0, 0, 0, 0, 0);

    // Kernel Code
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    // Kernel Data
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // User Code
    set_gdt_entry(3, 0, 0, 0, 0);
    // User Data
    set_gdt_entry(4, 0, 0, 0, 0);

    // TSS
    set_gdt_entry(5, 0, 0, 0, 0);

    size_t i = 0;
    while (i < 6)
        print_gdt_entry(i++);

    gdtr_t gdtr;
    gdtr.base = (u32)gdt;
    gdtr.limit = sizeof(gdt) - 1;

    // LGDT
    asm volatile ("lgdt %0\n" : /* No output */ : "m"(gdtr) : "memory");

    // Enable PE
    asm volatile ("movl %cr0, %eax");
    asm volatile ("or $1, %al");
    asm volatile ("movl %eax, %cr0");

    // Segments
    asm volatile ("movw $0x10, %ax");
    asm volatile ("movw %ax, %ds");
    asm volatile ("movw %ax, %es");
    asm volatile ("movw %ax, %fs");
    asm volatile ("movw %ax, %gs");
    asm volatile ("movw %ax, %ss");

    // Switch
    asm volatile ("ljmp $0x08, $1f");
    asm volatile ("1:");
}