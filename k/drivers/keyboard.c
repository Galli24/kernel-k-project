#include <stdio.h>

#include "../cpu/sys.h"
#include "../cpu/irq.h"

#include "../io.h"

#include "keyboard.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

void keyboard_handler(regs_t *regs)
{
    (void) regs;
    u8 scancode;
    u8 key;

    if (inb(KEY_STATUS) & 0x01) {
        scancode = inb(KEY_BUFFER);

        key = scancode & 0x7F;

        printf("Key: %d "BYTE_TO_BINARY_PATTERN"\r\n", key, BYTE_TO_BINARY(scancode));
    }
}

void keyboard_install()
{
    irq_install_handler(KEY_IRQ, keyboard_handler);
}