// TODO: try and unify calling code so we can get rid of these CSA_xxxx vars.
//       they just deal with some minor code and compiler differences.

#ifndef CSA1_ANIM_TIMER
// amazingly, writing "24" here yields different byte output sometimes.
#define CSA1_ANIM_TIMER 0x18
#endif // CSA1_ANIM_TIMER

#ifndef CSA1_V_SKIPCUTSCENE
#define CSA1_V_SKIPCUTSCENE g_SkipCutscene
#endif // CSA1_V_SKIPCUTSCENE

#ifndef CSA1_V_NEXTCHAR
#define CSA1_V_NEXTCHAR nextChar
#endif // CSA1_V_NEXTCHAR


// ---------------------------------------------

case CSOP_CLOSE_DIALOG:
    if (CSA1_V_SKIPCUTSCENE) {
        continue;
    }
    g_Dialogue.portraitAnimTimer = CSA1_ANIM_TIMER;
    self->step = DIALOGUE_CLOSE_DIALOG_BOX;
    return;


case CSOP_PLAY_SOUND:
    if (CSA1_V_SKIPCUTSCENE) {
        // psp and psx refuse to agree on this particular increment
        #ifdef VERSION_PSP
            g_Dialogue.scriptCur += 2;
        #else
            g_Dialogue.scriptCur++;
            g_Dialogue.scriptCur++;
        #endif
        continue;
    }
    CSA1_V_NEXTCHAR = *g_Dialogue.scriptCur++;
    CSA1_V_NEXTCHAR <<= 4;
    CSA1_V_NEXTCHAR |= *g_Dialogue.scriptCur++;
    g_api.PlaySfx(CSA1_V_NEXTCHAR);  // usually: music track ID
    continue;