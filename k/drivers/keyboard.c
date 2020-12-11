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

#define BUFFER_SIZE 255

static u8 front, rear, size = 0;
static u8 buffer[BUFFER_SIZE + 1];

int is_buffer_empty()
{
    return size == 0;
}

int is_buffer_full()
{
    return size == BUFFER_SIZE;
}

void enqueue_key(u8 scancode)
{
    if (is_buffer_full()) {
        front = (front + 1) % BUFFER_SIZE;
    } else {
        size++;
    }

    rear = (rear + 1) % BUFFER_SIZE;
    buffer[rear] = scancode;
}

int getkey()
{
    if (is_buffer_empty())
        return -1;
    
    u8 value = buffer[front];
    front = (front + 1) % BUFFER_SIZE;
    size--;

    return value;
}

void keyboard_handler(regs_t *regs)
{
    (void) regs;
    u8 scancode;

    if (inb(KEY_STATUS) & 0x01) {
        scancode = inb(KEY_BUFFER);

        if (scancode & 0x80)
            return;

        enqueue_key(scancode);
    }
}

void keyboard_install()
{
    irq_install_handler(KEY_IRQ, keyboard_handler);
}