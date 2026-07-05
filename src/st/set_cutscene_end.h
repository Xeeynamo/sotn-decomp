// SPDX-License-Identifier: AGPL-3.0-or-later

#ifdef VERSION_PC
static
#endif

    void
    SetCutsceneEnd(u8* ptr) {
#if !defined(VERSION_PSP)
    OVL_EXPORT(Dialogue).scriptEnd = ptr + 0x100000;
#else
    OVL_EXPORT(Dialogue).scriptEnd = ptr;
#endif
    OVL_EXPORT(Dialogue).timer = 0;
    OVL_EXPORT(Dialogue).unk3C = 1;
}
