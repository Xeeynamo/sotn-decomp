#include "sattypes.h"

// Initial values for the SPR and SCL globals aliased in zero_user_syms.txt.
const u16 g_SaturnSdkInitialState[] = {
#include "sys_initial_state.inc"
};
