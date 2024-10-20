#include "common.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/cdread2", CdRead2);

void StCdInterrupt();

void StCdInterrupt2(void) { StCdInterrupt(); }
