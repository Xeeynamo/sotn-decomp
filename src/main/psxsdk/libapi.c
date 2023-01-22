#include "common.h"
#include <game.h>

extern u8 CD_status;
extern u8 CD_mode;
extern u8 CD_com;

int CdStatus(void) { return CD_status; }

int CdMode(void) { return CD_mode; }

int CdLastCom(void) { return CD_com; }
