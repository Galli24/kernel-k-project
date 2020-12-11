#include <stdio.h>

#include "idt.h"
#include "isr.h"

#define ISR_COUNT   32
#define SYSCALL_ISR 127

#define EXTERN(x) \
    extern void _isr##x();

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
EXTERN(16)
EXTERN(17)
EXTERN(18)
EXTERN(19)
EXTERN(20)
EXTERN(21)
EXTERN(22)
EXTERN(23)
EXTERN(24)
EXTERN(25)
EXTERN(26)
EXTERN(27)
EXTERN(28)
EXTERN(29)
EXTERN(30)
EXTERN(31)
EXTERN(127)

#define HANDLER(x) (unsigned)_isr##x

void isrs_init()
{
    set_idt_entry(0, HANDLER(0), 0x08, 0x8E);
    set_idt_entry(1, HANDLER(1), 0x08, 0x8E);
    set_idt_entry(2, HANDLER(2), 0x08, 0x8E);
    set_idt_entry(3, HANDLER(3), 0x08, 0x8E);
    set_idt_entry(4, HANDLER(4), 0x08, 0x8E);
    set_idt_entry(5, HANDLER(5), 0x08, 0x8E);
    set_idt_entry(6, HANDLER(6), 0x08, 0x8E);
    set_idt_entry(7, HANDLER(7), 0x08, 0x8E);
    set_idt_entry(8, HANDLER(8), 0x08, 0x8E);
    set_idt_entry(9, HANDLER(9), 0x08, 0x8E);
    set_idt_entry(10, HANDLER(10), 0x08, 0x8E);
    set_idt_entry(11, HANDLER(11), 0x08, 0x8E);
    set_idt_entry(12, HANDLER(12), 0x08, 0x8E);
    set_idt_entry(13, HANDLER(13), 0x08, 0x8E);
    set_idt_entry(14, HANDLER(14), 0x08, 0x8E);
    set_idt_entry(15, HANDLER(15), 0x08, 0x8E);
    set_idt_entry(16, HANDLER(16), 0x08, 0x8E);
    set_idt_entry(17, HANDLER(17), 0x08, 0x8E);
    set_idt_entry(18, HANDLER(18), 0x08, 0x8E);
    set_idt_entry(19, HANDLER(19), 0x08, 0x8E);
    set_idt_entry(20, HANDLER(20), 0x08, 0x8E);
    set_idt_entry(21, HANDLER(21), 0x08, 0x8E);
    set_idt_entry(22, HANDLER(22), 0x08, 0x8E);
    set_idt_entry(23, HANDLER(23), 0x08, 0x8E);
    set_idt_entry(24, HANDLER(24), 0x08, 0x8E);
    set_idt_entry(25, HANDLER(25), 0x08, 0x8E);
    set_idt_entry(26, HANDLER(26), 0x08, 0x8E);
    set_idt_entry(27, HANDLER(27), 0x08, 0x8E);
    set_idt_entry(28, HANDLER(28), 0x08, 0x8E);
    set_idt_entry(29, HANDLER(29), 0x08, 0x8E);
    set_idt_entry(30, HANDLER(30), 0x08, 0x8E);
    set_idt_entry(31, HANDLER(31), 0x08, 0x8E);
    set_idt_entry(SYSCALL_ISR, HANDLER(127), 0x08, 0x8E);
}

void isr_handler(regs_t *regs)
{
    printf("Received ISR nb: %d\r\n", regs->int_no);
}
