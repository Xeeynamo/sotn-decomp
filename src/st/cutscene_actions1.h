// SPDX-License-Identifier: AGPL-3.0-or-later
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
g_api.PlaySfx(CSA1_V_NEXTCHAR); // usually: music track ID
continue;

case CSOP_WAIT_FOR_SOUND:
if (CSA1_V_SKIPCUTSCENE) {
    continue;
}
// "has music track started playing?"
if (g_api.func_80131F68() != false) {
    // yes: playing, go to next step
    continue;
}
// no: music not playing yet, so repeat this step
*g_Dialogue.scriptCur--;
return;

case CSOP_SCRIPT_UNKNOWN_11:
if (CSA1_V_SKIPCUTSCENE) {
    continue;
}
// "has music track stopped playing?"
if (g_api.func_80131F68() != true) {
    // yes: nothing is playing, go to next step
    continue;
}
// no: still waiting for playback to stop, repeat this step
*g_Dialogue.scriptCur--;
return;

// ---------------------------------------------------

#ifndef CSA1_V_OVL_CUTSCENE_SCRIPT_PTR
#define CSA1_V_OVL_CUTSCENE_SCRIPT_PTR OVL_EXPORT(cutscene_script_ptr)
#endif // CSA1_V_OVL_CUTSCENE_SCRIPT_PTR

// ---------------------------------------------------

#ifndef CSA1_NO_EMIT_CSOP_SET_END
case CSOP_SET_END:
#ifndef CSA1_IGNORE_CSOP_END
ptr = (u_long)*g_Dialogue.scriptCur++;
ptr <<= 4;
ptr |= (u_long)*g_Dialogue.scriptCur++;
ptr <<= 4;
ptr |= (u_long)*g_Dialogue.scriptCur++;
ptr <<= 4;
ptr |= (u_long)*g_Dialogue.scriptCur++;
#ifdef VERSION_PSP
ptr += (u_long)CSA1_V_OVL_CUTSCENE_SCRIPT_PTR;
#endif // VERSION_PSP
SetCutsceneEnd((u8*)ptr);
#endif // CSA1_IGNORE_CSOP_END
continue;
#endif // CSA1_NO_EMIT_CSOP_SET_END

case CSOP_SCRIPT_UNKNOWN_13:
continue;
