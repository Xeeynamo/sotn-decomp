#ifndef CSA1_ANIM_TIMER
// amazingly, writing "24" here yields different byte output sometimes.
#define CSA1_ANIM_TIMER 0x18
#endif // CSA1_ANIM_TIMER

#ifndef CSA1_V_SKIPCUTSCENE
#define CSA1_V_SKIPCUTSCENE g_SkipCutscene
#endif // CSA1_V_SKIPCUTSCENE

// ---------------------------------------------

case CSOP_CLOSE_DIALOG:
    if (CSA1_V_SKIPCUTSCENE) {
        continue;
    }
    g_Dialogue.portraitAnimTimer = CSA1_ANIM_TIMER;
    self->step = DIALOGUE_CLOSE_DIALOG_BOX;
    return;