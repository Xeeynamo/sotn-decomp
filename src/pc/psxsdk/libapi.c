#include <unistd.h>
#include <common.h>
#include "../log.h"

int VSync(int mode) {
    usleep((1001.0 / 60.0) * 1000.0); // 59.94 fps (16.68 ms)
    return 0;
}
