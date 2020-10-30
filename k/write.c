#include <k/types.h>

#include "serial.h"

int write(const char *s, size_t nb)
{
    size_t i = 0;

    while (i < nb)
        write_serial(s[i++]);
    return nb;
}