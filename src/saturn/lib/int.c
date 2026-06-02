#include "sattypes.h"
#include "inc_asm.h"

#include "int.h"

void INT_SetScuFunc(int n, interrupt_t handler) {
    SYS_SetUintMacSave((Uint32)n, (void*)handler);
}

interrupt_t INT_GetScuFunc(int n) {
    return (interrupt_t)SYS_GetUintMacSave((Uint32)n);
}
