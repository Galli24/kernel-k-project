#ifndef IRQ_H_
#define IRQ_H_

#include "sys.h"

// PIC

#define PIC_MASTER          0x20
#define PIC_MASTER_COMMAND  PIC_MASTER
#define PIC_MASTER_OFFSET   0x20
#define PIC_MASTER_DATA     (PIC_MASTER + 1)

#define PIC_SLAVE           0xA0
#define PIC_SLAVE_COMMAND   PIC_SLAVE
#define PIC_SLAVE_OFFSET    0x28
#define PIC_SLAVE_DATA      (PIC_SLAVE + 1)

#define PIC_EOI             0x20

#define PIC_WAIT() \
    asm volatile("jmp 1f\n\t" \
                    "1:\n\t" \
                    "    jmp 2f\n\t" \
                    "2:");

// OFFSETS

#define ICW1_ICW4           0x01        /* ICW4 (not) needed */
#define ICW1_SINGLE         0x02        /* Single (cascade) mode */
#define ICW1_INTERVAL4      0x04        /* Call address interval 4 (8) */
#define ICW1_LEVEL          0x08        /* Level triggered (edge) mode */
#define ICW1_INIT           0x10        /* Initialization - required! */

#define ICW4_8086           0x01        /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO           0x02        /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE      0x08        /* Buffered mode/slave */
#define ICW4_BUF_MASTER     0x0C        /* Buffered mode/master */
#define ICW4_SFNM           0x10        /* Special fully nested (not) */

// Functions

void irq_init();
void irq_handler(regs_t *regs);

#endif /* !IRQ_H_ */