// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

void SetReleaseRate1(void) {
    D_80138FB4->voice = 0;
    D_80138FB4->mask = SPU_VOICE_ADSR_RR;
    D_80138FB4->rr = 14;
    SpuSetVoiceAttr(D_80138FB4);
    g_KeyOffChannels = 0;
    InitSoundVars2();
}

void SetReleaseRate2(void) {
    D_80138FB4->voice = 0;
    D_80138FB4->mask = SPU_VOICE_ADSR_RR;
    D_80138FB4->rr = 8;
    SpuSetVoiceAttr(D_80138FB4);
    g_KeyOffChannels = 0;
    InitSoundVars2();
}

// requires AdvanceCdSoundCommandQueue to be static in the
// same file, https://decomp.me/scratch/t0j7W
INCLUDE_ASM("dra_psp/psp/dra_psp/65F50", CdSoundCommand10);
