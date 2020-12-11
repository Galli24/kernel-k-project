#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#define KEY_BUFFER      0x60
#define KEY_STATUS      0x64
#define KEY_IRQ            1

void keyboard_install();
int getkey();

#endif /* !KEYBOARD_H_ */