#ifndef TIMER_H_
#define TIMER_H_

#define COUNTER0        0x40
#define COUNTER1        0x41
#define COUNTER2        0x42
#define CONTROL         0x43
#define TIMER_IRQ          0

#define INTERNAL_FREQ   1193182
#define DESIRED_FREQ    100

void timer_install();
unsigned long gettick();

#endif /* !TIMER_H_ */