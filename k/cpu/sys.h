#ifndef SYS_H_
#define SYS_H_

#include <k/types.h>

struct regs {
	u32 gs, fs, es, ds;
	u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
	u32 int_no, err_code;
	u32 eip, cs, eflags, useresp, ss;
};
typedef struct regs regs_t;

#endif /* !SYS_H_ */
