#ifndef GDT_H_
#define GDT_H_

#include <k/kfs.h>
#include <k/types.h>

struct gdt_entry {
    u16 limit;
    u16 base_1;
    u8 base_2;
    u8 access;
    u8 limit_flags;
    u8 base_3;
} __packed;
typedef struct gdt_entry gdt_entry_t;

struct gdtr {
    u16 limit;
    u32 base;
} __packed;
typedef struct gdtr gdtr_t;

void gdt_init();

#endif /* !GDT_H_ */