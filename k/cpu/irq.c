#include <stdio.h>

#include "idt.h"
#include "irq.h"
#include "../io.h"

#define EXTERN(x) \
    extern void _irq##x();

#define IRQ_NB_TO_BYTE(x) (x + 32)

EXTERN(0)
EXTERN(1)
EXTERN(2)
EXTERN(3)
EXTERN(4)
EXTERN(5)
EXTERN(6)
EXTERN(7)
EXTERN(8)
EXTERN(9)
EXTERN(10)
EXTERN(11)
EXTERN(12)
EXTERN(13)
EXTERN(14)
EXTERN(15)

#define HANDLER(x) (unsigned)_irq##x

void PIC_remap()
{
    // Init in cascade mode
    outb(PIC_MASTER_COMMAND, ICW1_INIT | ICW1_ICW4);
    PIC_WAIT();
    outb(PIC_SLAVE_COMMAND, ICW1_INIT | ICW1_ICW4);
    PIC_WAIT();

    // Remap
    outb(PIC_MASTER_DATA, PIC_MASTER_OFFSET);
    PIC_WAIT();
    outb(PIC_SLAVE_DATA, PIC_SLAVE_OFFSET);
    PIC_WAIT();

    // Cascade
    outb(PIC_MASTER_DATA, 0x04);
    PIC_WAIT();
    outb(PIC_SLAVE_DATA, 0x02);
    PIC_WAIT();

    // Init 8086 mode
    outb(PIC_MASTER_DATA, ICW4_8086);
    PIC_WAIT();
    outb(PIC_SLAVE_DATA, ICW4_8086);
    PIC_WAIT();
}

void PIC_send_EOI(unsigned char irq)
{
    if (irq >= 8)
        outb(PIC_SLAVE_COMMAND, PIC_EOI);
    outb(PIC_MASTER_COMMAND, PIC_EOI);
}

void irq_init()
{
    PIC_remap();
    
    set_idt_entry(IRQ_NB_TO_BYTE(0), HANDLER(0), 0x08, 0x8E);
    set_idt_entry(IRQ_NB_TO_BYTE(1), HANDLER(1), 0x08, 0x8E);
    set_idt_entry(IRQ_NB_TO_BYTE(2), HANDLER(2), 0x08, 0x8E);
    set_idt_entry(IRQ_NB_TO_BYTE(3), HANDLER(3), 0x08, 0x8E);
    set_idt_entry(IRQ_NB_TO_BYTE(4), HANDLER(4), 0x08, 0x8E);
    set_idt_entry(IRQ_NB_TO_BYTE(5), HANDLER(5), 0x08, 0x8E);
    set_idt_entry(IRQ_NB_TO_BYTE(6), HANDLER(6), 0x08, 0x8E);
    set_idt_entry(IRQ_NB_TO_BYTE(7), HANDLER(7), 0x08, 0x8E);
    set_idt_entry(IRQ_NB_TO_BYTE(8), HANDLER(8), 0x08, 0x8E);
    set_idt_entry(IRQ_NB_TO_BYTE(9), HANDLER(9), 0x08, 0x8E);
    set_idt_entry(IRQ_NB_TO_BYTE(10), HANDLER(10), 0x08, 0x8E);
    set_idt_entry(IRQ_NB_TO_BYTE(11), HANDLER(11), 0x08, 0x8E);
    set_idt_entry(IRQ_NB_TO_BYTE(12), HANDLER(12), 0x08, 0x8E);
    set_idt_entry(IRQ_NB_TO_BYTE(13), HANDLER(13), 0x08, 0x8E);
    set_idt_entry(IRQ_NB_TO_BYTE(14), HANDLER(14), 0x08, 0x8E);
    set_idt_entry(IRQ_NB_TO_BYTE(15), HANDLER(15), 0x08, 0x8E);
}

void irq_handler(regs_t *regs)
{
    printf("Received IRQ nb: %d\r\n", regs->int_no - 32);
    PIC_send_EOI(regs->int_no - 32);
}