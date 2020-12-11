#ifndef SERIAL_H_
#define SERIAL_H_

#include "../io.h"

// COM Ports
#define COM1_BASE 0x3F8

void serial_init();
char read_serial();
void write_serial(char c);

#endif /* !SERIAL_H_ */