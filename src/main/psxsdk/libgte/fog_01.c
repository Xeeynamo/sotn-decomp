#include "common.h"

void SetFogNear(long a, long h) {
    SetDQA(-(a * 0x140) / h);
    SetDQB(0x01400000);
}
