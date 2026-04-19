case CSOP_CLOSE_DIALOG:
    if (g_SkipCutscene) {
        continue;
    }
    g_Dialogue.portraitAnimTimer = 0x18;
    self->step = 6; // DIALOGUE_CLOSE_DIALOG_BOX;
    return;