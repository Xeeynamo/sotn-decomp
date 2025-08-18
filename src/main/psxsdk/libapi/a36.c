// SPDX-License-Identifier: MIT
#include "bios.h"
#include <kernel.h>

void EnterCriticalSection() { SYSCALL(1) }
