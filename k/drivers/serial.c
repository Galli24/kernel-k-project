#include "serial.h"

void serial_init()
{
    // THR empty interrupt
    outb(COM1_BASE + 1, 0x02);
    // DLAB on
    outb(COM1_BASE + 3, 0x80); 
    // Baud rate to 38400, DLL 0x03, DLM 0x00
    outb(COM1_BASE + 0, 0x03);
    outb(COM1_BASE + 1, 0x00);
    // 8 bits + no parity + one stop bit (clears DLAB)
    outb(COM1_BASE + 3, 0x03);
    // Enable and clear FIFO , 14 byte FIFO interrupt
    outb(COM1_BASE + 2, 0xC7);
    // Data terminal ready, Request to send and Aux output 2
    outb(COM1_BASE + 4, 0x0B);
}

int serial_received()
{
    // Check LSR if data is available
    return inb(COM1_BASE + 5) & 0x01;
}

char read_serial()
{
    while (serial_received() == 0);
    return inb(COM1_BASE);
}

int is_transmit_ready()
{
    // Check LSR if THR is empty
    return inb(COM1_BASE + 5) & 0x20;
}

void write_serial(char c)
{
    while (is_transmit_ready() == 0);
    outb(COM1_BASE, c);
}