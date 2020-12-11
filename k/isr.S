#define ISR_ALIGN 16

.altmacro

.macro ISR_NO_ERROR nb
.align ISR_ALIGN
    .global _isr\nb
    _isr\nb:
        cli
        push $0
        push $\nb
        jmp isr_common
.endm

.macro ISR_ERROR nb
.align ISR_ALIGN
    .global _isr\nb
    _isr\nb:
        cli
        push $\nb
        jmp isr_common
.endm

isr_common:
    pusha

    push %ds
    push %es
    push %fs
    push %gs
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    cld

    push %esp
    call isr_handler
    addl $4, %esp

    pop %gs
    pop %fs
    pop %es
    pop %ds

    popa

    addl $8, %esp
    iret

ISR_NO_ERROR 0
ISR_NO_ERROR 1
ISR_NO_ERROR 2
ISR_NO_ERROR 3
ISR_NO_ERROR 4
ISR_NO_ERROR 5
ISR_NO_ERROR 6
ISR_NO_ERROR 7
ISR_ERROR 8
ISR_NO_ERROR 9
ISR_ERROR 10
ISR_ERROR 11
ISR_ERROR 12
ISR_ERROR 13
ISR_ERROR 14
ISR_ERROR 15
ISR_NO_ERROR 16
ISR_ERROR 17
ISR_NO_ERROR 18
ISR_NO_ERROR 19
ISR_NO_ERROR 20
ISR_NO_ERROR 21
ISR_NO_ERROR 22
ISR_NO_ERROR 23
ISR_NO_ERROR 24
ISR_NO_ERROR 25
ISR_NO_ERROR 26
ISR_NO_ERROR 27
ISR_NO_ERROR 28
ISR_NO_ERROR 29
ISR_NO_ERROR 30
ISR_NO_ERROR 31
ISR_NO_ERROR 127
