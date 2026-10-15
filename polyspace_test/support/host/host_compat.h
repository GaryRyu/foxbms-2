#ifndef REDUNDANCY_PST_HOST_COMPAT_H
#define REDUNDANCY_PST_HOST_COMPAT_H
#include <stdint.h>
/* Simulated location token only: never a TI program counter. */
static inline uintptr_t __curpc(void) { return (uintptr_t)0; }
#endif
