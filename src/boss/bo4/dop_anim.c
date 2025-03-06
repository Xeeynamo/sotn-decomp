// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"

void SetPlayerStep(s16 step) {
    DOPPLEGANGER.step = step;
    DOPPLEGANGER.step_s = 0;
}

static u8 g_D_800ACF18[] = {
    10, 8, 8, 6, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 255, 255, 0, 0};

extern s32 g_Dop_padPressed;
extern s32 g_Dop_padTapped;
extern s32 g_Dop_padHeld;

// Same function in RIC is func_8015C4AC
void func_8010D59C(void) {
    byte stackpad[40];
    Primitive* prim;
    s32 i;

    if (g_Entities[STAGE_ENTITY_START + 1].ext.entSlot1.unk0) {
        return;
    }

    switch (DOPPLEGANGER.ext.player.anim) {
    case 0x5E:
    case 0x5D:
    case 0x60:
    case 0x61:
    case 0x62:
        g_Entities[STAGE_ENTITY_START + 1].ext.entSlot1.unk2 = 10;
        return;
    }

    if ((g_Dop_padTapped & GAMEBUTTONS) ||
        ((g_Dop_padHeld ^ g_Dop_padPressed) & g_Dop_padHeld & GAMEBUTTONS) ||
        (DOPPLEGANGER.velocityY > FIX(0.5))) {
        g_Entities[STAGE_ENTITY_START + 1].ext.entSlot1.unk2 = 0;
        g_Entities[STAGE_ENTITY_START + 1].ext.entSlot1.unk3 = 0;
    } else {
        if (g_Entities[STAGE_ENTITY_START + 1].ext.entSlot1.unk2 >= 10) {
            return;
        }
        if (g_Entities[STAGE_ENTITY_START + 1].ext.entSlot1.unk3 == 0) {
            g_Entities[STAGE_ENTITY_START + 1].ext.entSlot1.unk3 =
                g_D_800ACF18[g_Entities[STAGE_ENTITY_START + 1]
                                 .ext.entSlot1.unk2];
        }
        if (--g_Entities[STAGE_ENTITY_START + 1].ext.entSlot1.unk3 == 0) {
            g_Entities[STAGE_ENTITY_START + 1].ext.entSlot1.unk2++;
            g_Entities[STAGE_ENTITY_START + 1].ext.entSlot1.unk3 =
                g_D_800ACF18[g_Entities[STAGE_ENTITY_START + 1]
                                 .ext.entSlot1.unk2];
        }
    }
    if (g_Entities[STAGE_ENTITY_START + 1].animFrameIdx) {
        g_Entities[STAGE_ENTITY_START + 1].animFrameIdx--;
        return;
    }
    prim = &g_PrimBuf[g_Entities[STAGE_ENTITY_START + 1].primIndex];
    i = 0;
    while (prim) {
        if (i == g_Entities[STAGE_ENTITY_START + 1].entityId) {
            prim->r0 = prim->g0 = prim->b0 = 0x80;
            prim->x0 = DOPPLEGANGER.posX.i.hi;
            prim->y0 = DOPPLEGANGER.posY.i.hi;
            prim->x1 = DOPPLEGANGER.animCurFrame;
            prim->y1 = 0;
            prim->x2 = DOPPLEGANGER.facingLeft;
            prim->y2 = DOPPLEGANGER.palette;
        }
        i++;
        prim = prim->next;
    }

    g_Entities[STAGE_ENTITY_START + 1].animFrameIdx = 2;
    g_Entities[STAGE_ENTITY_START + 1].entityId++;
    if (g_Entities[STAGE_ENTITY_START + 1].entityId >= 6) {
        g_Entities[STAGE_ENTITY_START + 1].entityId = 0;
    }
}

static u8 g_shadowOpacityReductionTable[] = {
    4, 4, 4, 4, 6, 6, 6, 6, 8, 8, 16, 16, 16, 16, 16, 16};
static u8 g_D_800ACF3C[] = {
    8, 12, 16, 20, 24, 28, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32};

// Equivalent in RIC is func_8015C6D4
void func_8010D800(void) {
    PlayerDraw pad;
    PlayerDraw* plDraw;
    Primitive* prim;
    s32 i;
    u8 temp_t0;
    u8 temp_t1;
    u8 temp_t2;

    temp_t2 = g_Entities[STAGE_ENTITY_START + 1].ext.entSlot1.unk1;
    prim = &g_PrimBuf[g_Entities[STAGE_ENTITY_START + 1].primIndex];
    plDraw = &g_PlayerDraw[9];
    temp_t1 = g_shadowOpacityReductionTable[g_Entities[STAGE_ENTITY_START + 1]
                                                .ext.entSlot1.unk2];
    temp_t0 =
        g_D_800ACF3C[g_Entities[STAGE_ENTITY_START + 1].ext.entSlot1.unk2];

    for (i = 0; prim != NULL; i++, prim = prim->next) {
        if (prim->b0 > temp_t0) {
            prim->b0 -= temp_t1;
        }
        if (prim->b0 < 112 && prim->r0 < 240) {
            prim->r0 += 6;
        }
        if (prim->b0 < 88) {
            prim->y1 = 16;
        } else {
            prim->y1 = 0;
        }
        if (prim->b0 <= temp_t0) {
            prim->x1 = 0;
        }
        if (!((i ^ g_Timer) & 1)) {
            continue;
        }

        g_Entities[STAGE_ENTITY_START + (i / 2) + 1].posX.i.hi = prim->x0;
        g_Entities[STAGE_ENTITY_START + (i / 2) + 1].posY.i.hi = prim->y0;
        g_Entities[STAGE_ENTITY_START + (i / 2) + 1].animCurFrame = prim->x1;
        g_Entities[STAGE_ENTITY_START + (i / 2) + 1].drawMode = prim->y1;
        g_Entities[STAGE_ENTITY_START + (i / 2) + 1].facingLeft = prim->x2;
        g_Entities[STAGE_ENTITY_START + (i / 2) + 1].palette = prim->y2;
        g_Entities[STAGE_ENTITY_START + (i / 2) + 1].zPriority =
            DOPPLEGANGER.zPriority - 2;
        if (temp_t2) {
            g_Entities[STAGE_ENTITY_START + (i / 2) + 1].animCurFrame = 0;
            prim->x1 = 0;
        }

        PGRN(plDraw) = PBLU(plDraw) = prim->b0;
        PRED(plDraw) = prim->r0;
        plDraw->enableColorBlend = true;
        plDraw++;
    }
}

void func_8010DA2C(AnimationFrame* frames) {
    g_CurrentEntity->anim = frames;
    g_CurrentEntity->animFrameDuration = 0;
    g_CurrentEntity->animFrameIdx = 0;
}

void SetPlayerAnim(u8 anim) {
    g_CurrentEntity->ext.player.anim = anim;
    g_CurrentEntity->animFrameDuration = 0;
    g_CurrentEntity->animFrameIdx = 0;
}

extern AnimationFrame* D_800B0594[];

AnimationFrame* func_8010DA70(AnimationFrame** frames) {
    u16* anim;
    s32 idx;
    u16* subanim;
    s32 var_s1;
    s32 idxSub;

    anim = (u16*)frames[g_CurrentEntity->ext.player.anim];
    idx = 0;
    var_s1 = 0;
    while (true) {
        if ((&anim[idx * 2])[0] == 0xFFFD) {
            for (idxSub = 0; true; idxSub++, var_s1++) {
                subanim = (u16*)D_800B0594[(&anim[idx * 2])[1] & 0xFF];
                if ((&subanim[idxSub * 2])[0] == 0xFFFF) {
                    idx++;
                    // Probably fake. Makes PSP registers match.
                    idxSub = idxSub;
                    break;
                }
                if (var_s1 == g_CurrentEntity->animFrameIdx) {
                    return (AnimationFrame*)&subanim[idxSub * 2];
                }
            }
        } else if (var_s1 == g_CurrentEntity->animFrameIdx) {
            return (AnimationFrame*)(anim + idx * 2);
        } else {
            var_s1++;
            idx++;
        }
    }
}

u32 UpdateUnarmedAnim(s8* frameProps, u16** frames) {
    u16* frameIndex;

    frameIndex =
        frames[g_CurrentEntity->ext.player.anim] + DOPPLEGANGER.animFrameIdx;
    if (*frameIndex == 0xFFFF) {
        return -1;
    }
    if (frameProps != NULL) {
        frameProps = &frameProps[((*frameIndex >> 9) & 0x7F) << 2];
        g_CurrentEntity->hitboxOffX = *frameProps;
        frameProps++;
        g_CurrentEntity->hitboxOffY = *frameProps;
        frameProps++;
        g_CurrentEntity->hitboxWidth = *frameProps;
        frameProps++;
        g_CurrentEntity->hitboxHeight = *frameProps;
    }
    g_CurrentEntity->animCurFrame = *frameIndex & 0x1FF;
    if (DOPPLEGANGER.animFrameDuration < 0) {
        return -1;
    } else {
        return 0;
    }
}

void PlayAnimation(s8* frameProps, AnimationFrame** frames) {
    AnimationFrame* animFrame;

    animFrame = func_8010DA70(frames);
    if (g_CurrentEntity->animFrameDuration != -1) {
        if (g_CurrentEntity->animFrameDuration == 0) {
            g_CurrentEntity->animFrameDuration = animFrame->duration;
        } else if (--g_CurrentEntity->animFrameDuration == 0) {
            g_CurrentEntity->animFrameIdx++;
            animFrame = func_8010DA70(frames);
            // Using a switch doesn't work
            if (animFrame->duration == 0x0) {
                g_CurrentEntity->animFrameIdx = animFrame->unk2;
                animFrame = func_8010DA70(frames);
                g_CurrentEntity->animFrameDuration = animFrame->duration;
            } else if (animFrame->duration == 0xFFFF) {
                g_CurrentEntity->animFrameIdx--;
                g_CurrentEntity->animFrameDuration = -1;
                animFrame = func_8010DA70(frames);
            } else if (animFrame->duration == 0xFFFE) {
                g_CurrentEntity->ext.player.anim = animFrame->unk2 & 0xFF;
                g_CurrentEntity->animFrameIdx = animFrame->unk2 >> 8;
                animFrame = func_8010DA70(frames);
                g_CurrentEntity->animFrameDuration = animFrame->duration;
            } else {
                g_CurrentEntity->animFrameDuration = animFrame->duration;
            }
        }
    }

    if (frameProps != NULL) {
        // This is ugly - theoretically the type for frameProps should be
        // FrameProperty* but anything besides this where we assign this big
        // expression fails.

        // Please check function UpdateAnim down below
        frameProps = &frameProps[((animFrame->unk2 >> 9) & 0x7F) * 4];
        g_CurrentEntity->hitboxOffX = *frameProps;
        frameProps++;
        g_CurrentEntity->hitboxOffY = *frameProps;
        frameProps++;
        g_CurrentEntity->hitboxWidth = *frameProps;
        frameProps++;
        g_CurrentEntity->hitboxHeight = *frameProps;
    }
    g_CurrentEntity->animCurFrame = animFrame->unk2 & 0x1FF;
}

// Nasty casting. This is just
// g_CurrentEntity->anim[g_CurrentEntity->animFrameIdx] But PSP is weird and
// does odd stuff with the struct indexing. So we cast the pointer to u16, index
// off of animFrameIdx*2, and cast back to AnimationFrame.
#define CURRANIM                                                               \
    (*((AnimationFrame*)(&(                                                    \
        ((u16*)g_CurrentEntity->anim)[g_CurrentEntity->animFrameIdx * 2]))))

u32 UpdateAnim(s8* frameProps, AnimationFrame** anims) {
#if defined(VERSION_PC)
    s32 ret = 0;
#else
    s32 ret;
#endif

#if defined(VERSION_PSP)
    if (!g_CurrentEntity->anim) {
        return -1;
    }
#endif

    if (g_CurrentEntity->animFrameDuration == -1) {
        ret = -1;
    } else if (g_CurrentEntity->animFrameDuration == 0) {
        g_CurrentEntity->animFrameDuration = CURRANIM.duration;
        ret = 0;
    } else if ((--g_CurrentEntity->animFrameDuration) == 0) {
        g_CurrentEntity->animFrameIdx++;
        // Effectively a switch statement, but breaks if I actually use one.
        if (CURRANIM.duration == 0) {
            g_CurrentEntity->animFrameIdx = CURRANIM.unk2;
            g_CurrentEntity->animFrameDuration = CURRANIM.duration;
            ret = 0;
        } else if (CURRANIM.duration == 0xFFFF) {
            g_CurrentEntity->animFrameIdx--;
            g_CurrentEntity->animFrameDuration = -1;
            ret = -1;
        } else if (CURRANIM.duration == 0xFFFE) {
            g_CurrentEntity->anim = anims[CURRANIM.unk2];
            g_CurrentEntity->animFrameIdx = 0;
            g_CurrentEntity->animFrameDuration = CURRANIM.duration;
            ret = -2;
        } else {
            g_CurrentEntity->animFrameDuration = CURRANIM.duration;
        }
    }
    if (frameProps != NULL) {
        // This is ugly - theoretically the type for frameProps should be
        // FrameProperty* but anything besides this where we assign this big
        // expression fails.
        frameProps = &frameProps[((CURRANIM.unk2 >> 9) & 0x7F) << 2];
        g_CurrentEntity->hitboxOffX = *frameProps;
        frameProps++;
        g_CurrentEntity->hitboxOffY = *frameProps;
        frameProps++;
        g_CurrentEntity->hitboxWidth = *frameProps;
        frameProps++;
        g_CurrentEntity->hitboxHeight = *frameProps;
    }
    g_CurrentEntity->animCurFrame = CURRANIM.unk2 & 0x1FF;
    return ret;
}
