// SPDX-License-Identifier: MIT
#include "bios.h"
#include <kernel.h>

void ExitCriticalSection() { SYSCALL(2) }
