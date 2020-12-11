#ifndef ISRS_H_
#define ISRS_H_

#include "sys.h"

void isrs_init();
void isr_handler(regs_t *regs);

#endif /* !ISRS_H_ */
