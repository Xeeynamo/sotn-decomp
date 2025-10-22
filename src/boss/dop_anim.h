// SPDX-License-Identifier: AGPL-3.0-or-later
void SetDopplegangerStep(s16 step) {
    DOPPLEGANGER.step = step;
    DOPPLEGANGER.step_s = 0;
}

static u8 g_afterImageTimerTable[] = {
    10, 8, 8, 6, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 255, 255, 0, 0};

extern PlayerState g_Dop;

// Same function in RIC is func_8015C4AC (InitRicAfterImage)
void OVL_EXPORT(InitPlayerAfterImage)(void) {
    byte stackpad[40];
    Primitive* prim;
    s32 i;

    if (g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
            .ext.afterImage.disableFlag) {
        return;
    }

    switch (DOPPLEGANGER.ext.player.anim) {
    case 0x5E:
    case 0x5D:
    case 0x60:
    case 0x61:
    case 0x62:
        g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].ext.afterImage.index =
            10;
        return;
    }

    if ((g_Dop.padTapped & GAMEBUTTONS) ||
        ((g_Dop.padHeld ^ g_Dop.padPressed) & g_Dop.padHeld & GAMEBUTTONS) ||
        (DOPPLEGANGER.velocityY > FIX(0.5))) {
        g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].ext.afterImage.index =
            0;
        g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].ext.afterImage.timer =
            0;
    } else {
        if (g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
                .ext.afterImage.index >= MaxAfterImageIndex) {
            return;
        }
        if (g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
                .ext.afterImage.timer == 0) {
            g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
                .ext.afterImage.timer = g_afterImageTimerTable
                [g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
                     .ext.afterImage.index];
        }
        if (--g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
                  .ext.afterImage.timer == 0) {
            g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
                .ext.afterImage.index++;
            g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
                .ext.afterImage.timer = g_afterImageTimerTable
                [g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
                     .ext.afterImage.index];
        }
    }
    if (g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].pose) {
        g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].pose--;
        return;
    }
    prim =
        &g_PrimBuf[g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].primIndex];
    i = 0;
    while (prim) {
        if (i == g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].entityId) {
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

    g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].pose = 2;
    g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].entityId++;
    if (g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].entityId >=
        MaxAfterImages) {
        g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].entityId = 0;
    }
}

static u8 g_shadowOpacityReductionTable[] = {
    4, 4, 4, 4, 6, 6, 6, 6, 8, 8, 16, 16, 16, 16, 16, 16};
static u8 g_D_800ACF3C[] = {
    8, 12, 16, 20, 24, 28, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32};

// Equivalent in RIC is func_8015C6D4 (DrawRicAfterImage)
void OVL_EXPORT(DrawPlayerAfterImage)(void) {
    PlayerDraw pad;
    PlayerDraw* plDraw;
    Primitive* prim;
    s32 i;
    u8 temp_t0;
    u8 temp_t1;
    u8 temp_t2;

    temp_t2 = g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
                  .ext.afterImage.resetFlag;
    prim =
        &g_PrimBuf[g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].primIndex];
    plDraw = &g_PlayerDraw[9];
    temp_t1 = g_shadowOpacityReductionTable
        [g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].ext.afterImage.index];
    temp_t0 = g_D_800ACF3C[g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
                               .ext.afterImage.index];

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

        g_Entities[STAGE_ENTITY_START + (i / 2) + E_AFTERIMAGE_1].posX.i.hi =
            prim->x0;
        g_Entities[STAGE_ENTITY_START + (i / 2) + E_AFTERIMAGE_1].posY.i.hi =
            prim->y0;
        g_Entities[STAGE_ENTITY_START + (i / 2) + E_AFTERIMAGE_1].animCurFrame =
            prim->x1;
        g_Entities[STAGE_ENTITY_START + (i / 2) + E_AFTERIMAGE_1].drawMode =
            prim->y1;
        g_Entities[STAGE_ENTITY_START + (i / 2) + E_AFTERIMAGE_1].facingLeft =
            prim->x2;
        g_Entities[STAGE_ENTITY_START + (i / 2) + E_AFTERIMAGE_1].palette =
            prim->y2;
        g_Entities[STAGE_ENTITY_START + (i / 2) + E_AFTERIMAGE_1].zPriority =
            DOPPLEGANGER.zPriority - 2;
        if (temp_t2) {
            g_Entities[STAGE_ENTITY_START + (i / 2) + E_AFTERIMAGE_1]
                .animCurFrame = 0;
            prim->x1 = 0;
        }

        PBLU(plDraw) = PGRN(plDraw) = prim->b0;
        PRED(plDraw) = prim->r0;
        plDraw->enableColorBlend = true;
        plDraw++;
    }
}

void OVL_EXPORT(func_8010DA2C)(AnimationFrame* frames) {
    g_CurrentEntity->anim = frames;
    g_CurrentEntity->poseTimer = 0;
    g_CurrentEntity->pose = 0;
}

void SetDopplegangerAnim(u8 anim) {
    g_CurrentEntity->ext.player.anim = anim;
    g_CurrentEntity->poseTimer = 0;
    g_CurrentEntity->pose = 0;
}

extern AnimationFrame* g_DopAnimationFrames[];

static AnimationFrame* OVL_EXPORT(func_8010DA70)(AnimationFrame** frames) {
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
                subanim =
                    (u16*)g_DopAnimationFrames[(&anim[idx * 2])[1] & 0xFF];
                if ((&subanim[idxSub * 2])[0] == 0xFFFF) {
                    idx++;
                    // Probably fake. Makes PSP registers match.
                    idxSub = idxSub;
                    break;
                }
                if (var_s1 == g_CurrentEntity->pose) {
                    return (AnimationFrame*)&subanim[idxSub * 2];
                }
            }
        } else if (var_s1 == g_CurrentEntity->pose) {
            return (AnimationFrame*)(anim + idx * 2);
        } else {
            var_s1++;
            idx++;
        }
    }
}

s32 OVL_EXPORT(UpdateUnarmedAnim)(s8* frameProps, u16** frames) {
    u16* frameIndex;

    frameIndex = frames[g_CurrentEntity->ext.player.anim] + DOPPLEGANGER.pose;
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
    if (DOPPLEGANGER.poseTimer < 0) {
        return -1;
    } else {
        return 0;
    }
}

void OVL_EXPORT(PlayAnimation)(s8* frameProps, AnimationFrame** frames) {
    AnimationFrame* animFrame;

    animFrame = OVL_EXPORT(func_8010DA70)(frames);
    if (g_CurrentEntity->poseTimer != -1) {
        if (g_CurrentEntity->poseTimer == 0) {
            g_CurrentEntity->poseTimer = animFrame->duration;
        } else if (--g_CurrentEntity->poseTimer == 0) {
            g_CurrentEntity->pose++;
            animFrame = OVL_EXPORT(func_8010DA70)(frames);
            // Using a switch doesn't work
            if (animFrame->duration == 0x0) {
                g_CurrentEntity->pose = animFrame->pose;
                animFrame = OVL_EXPORT(func_8010DA70)(frames);
                g_CurrentEntity->poseTimer = animFrame->duration;
            } else if (animFrame->duration == 0xFFFF) {
                g_CurrentEntity->pose--;
                g_CurrentEntity->poseTimer = -1;
                animFrame = OVL_EXPORT(func_8010DA70)(frames);
            } else if (animFrame->duration == 0xFFFE) {
                g_CurrentEntity->ext.player.anim = animFrame->pose & 0xFF;
                g_CurrentEntity->pose = animFrame->pose >> 8;
                animFrame = OVL_EXPORT(func_8010DA70)(frames);
                g_CurrentEntity->poseTimer = animFrame->duration;
            } else {
                g_CurrentEntity->poseTimer = animFrame->duration;
            }
        }
    }

    if (frameProps != NULL) {
        // This is ugly - theoretically the type for frameProps should be
        // FrameProperty* but anything besides this where we assign this big
        // expression fails.

        // Please check function UpdateAnim down below
        frameProps = &frameProps[((animFrame->pose >> 9) & 0x7F) * 4];
        g_CurrentEntity->hitboxOffX = *frameProps;
        frameProps++;
        g_CurrentEntity->hitboxOffY = *frameProps;
        frameProps++;
        g_CurrentEntity->hitboxWidth = *frameProps;
        frameProps++;
        g_CurrentEntity->hitboxHeight = *frameProps;
    }
    g_CurrentEntity->animCurFrame = animFrame->pose & 0x1FF;
}

// Nasty casting. This is just
// g_CurrentEntity->anim[g_CurrentEntity->pose] But PSP is weird and
// does odd stuff with the struct indexing. So we cast the pointer to u16, index
// off of pose*2, and cast back to AnimationFrame.
#define CURRANIM                                                               \
    (*((AnimationFrame*)(&(                                                    \
        ((u16*)g_CurrentEntity->anim)[g_CurrentEntity->pose * 2]))))

u32 OVL_EXPORT(UpdateAnim)(s8* hitboxes, AnimationFrame** anims) {
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

    if (g_CurrentEntity->poseTimer == -1) {
        ret = -1;
    } else if (g_CurrentEntity->poseTimer == 0) {
        g_CurrentEntity->poseTimer = CURRANIM.duration;
        ret = 0;
    } else if ((--g_CurrentEntity->poseTimer) == 0) {
        g_CurrentEntity->pose++;
        // Effectively a switch statement, but breaks if I actually use one.
        if (CURRANIM.duration == 0) {
            g_CurrentEntity->pose = CURRANIM.pose;
            g_CurrentEntity->poseTimer = CURRANIM.duration;
            ret = 0;
        } else if (CURRANIM.duration == 0xFFFF) {
            g_CurrentEntity->pose--;
            g_CurrentEntity->poseTimer = -1;
            ret = -1;
        } else if (CURRANIM.duration == 0xFFFE) {
            g_CurrentEntity->anim = anims[CURRANIM.pose];
            g_CurrentEntity->pose = 0;
            g_CurrentEntity->poseTimer = CURRANIM.duration;
            ret = -2;
        } else {
            g_CurrentEntity->poseTimer = CURRANIM.duration;
        }
    }
    if (hitboxes) {
        // This is ugly - theoretically the type for frameProps should be
        // FrameProperty* but anything besides this where we assign this big
        // expression fails.
        hitboxes = &hitboxes[((CURRANIM.pose >> 9) & 0x7F) << 2];
        g_CurrentEntity->hitboxOffX = *hitboxes;
        hitboxes++;
        g_CurrentEntity->hitboxOffY = *hitboxes;
        hitboxes++;
        g_CurrentEntity->hitboxWidth = *hitboxes;
        hitboxes++;
        g_CurrentEntity->hitboxHeight = *hitboxes;
    }
    g_CurrentEntity->animCurFrame = CURRANIM.pose & 0x1FF;
    return ret;
}
