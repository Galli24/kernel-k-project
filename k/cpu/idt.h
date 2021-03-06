#ifndef IDT_H_
#define IDT_H_

#include <k/kfs.h>
#include <k/types.h>

#define IDT_ENTRY_COUNT 256

struct idt_entry {
    u16 offset_1;
    u16 selector;
    u8 zero;
    u8 type_attributes;
    u16 offset_2;
} __packed;
typedef struct idt_entry idt_entry_t;

struct idtr {
    u16 limit;
    u32 base;
} __packed;
typedef struct idtr idtr_t;

void set_idt_entry(size_t index, u32 offset, u16 selector, u8 flags);
void idt_init();

#endif /* !IDT_H_ */