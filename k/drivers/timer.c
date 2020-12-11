#include <k/types.h>

#include "../cpu/sys.h"
#include "../cpu/irq.h"

#include "../io.h"

#include "timer.h"

static unsigned long ticks = 0;

unsigned long gettick()
{
    return ticks * 10;
}

void timer_handler(regs_t *regs)
{
    (void) regs;
    ticks++;
}

void timer_install()
{
    outb(CONTROL, 0x34);

    u16 divider = INTERNAL_FREQ / DESIRED_FREQ;
    outb(COUNTER0, (u8)divider);
    outb(COUNTER0, divider >> 8);

    irq_install_handler(TIMER_IRQ, timer_handler);
}