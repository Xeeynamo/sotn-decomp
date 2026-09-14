// SPDX-License-Identifier: AGPL-3.0-or-later
//! PSPO=4,p
#include "dra.h"

#define FADE_DONE (-1)

typedef struct {
    s32 fadePrim; // four square on top of everything to make the fade working
    s32 mapPrim;  // map texture when pressing the SELECT button
    s32 step;
    s32 stepFollowup;
} FadeProps;

// BSS
static FadeProps fade;

void InitFade(void) {
    Primitive* prim;
    s32 x;

    fade.fadePrim = AllocPrimitives(PRIM_TILE, 4);
    prim = &g_PrimBuf[fade.fadePrim];
    for (x = 0; prim != NULL; x++) {
        prim->x0 = (x & 1) * 128;
        prim->u0 = 0x80;
        prim->v0 = 0xF0;
        prim->priority = 0x1FD;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
    fade.stepFollowup = 0;
    fade.step = 0;
    fade.mapPrim = AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[fade.mapPrim];
    prim->u0 = 0;
    prim->v0 = 0;
    prim->u1 = 0xFF;
    prim->v1 = 0;
    prim->u2 = 0;
    prim->v2 = 0xFF;
    prim->u3 = 0xFF;
    prim->v3 = 0xFF;
    prim->tpage = 0x1D;
    prim->clut = 0x1C0;
    prim->priority = 0x1FE;
    prim->drawMode = DRAW_HIDE;
}

s32 func_801025F4(void) {
    Primitive* prim = &g_PrimBuf[fade.fadePrim];
    return prim->clut;
}

void SetFadeWidth(s32 fadeWidth) {
    Primitive* prim;
    s32 i;

    prim = &g_PrimBuf[fade.fadePrim];
    for (i = 0; prim != NULL; i++) {
        prim->x0 = fadeWidth / 2 * (i & 1);
        prim->y0 = 0;
        prim->u0 = fadeWidth / 2;
        prim->v0 = 0xF0;
        prim->b0 = 0;
        prim->g0 = 0;
        prim->r0 = 0;
        prim->priority = 0x1FD;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

static void SetMapOpacity(s32 opacity) {
    Primitive* prim = &g_PrimBuf[fade.mapPrim];

    if (opacity == 0) {
        prim->drawMode = DRAW_HIDE;
        return;
    } else if (!(g_StageId & STAGE_INVERTEDCASTLE_FLAG)) {
        SetPrimRect(prim, 0, 1, 255, 255);
    } else {
        prim->x0 = prim->x2 = 255;
        prim->x1 = prim->x3 = 0;
        prim->y0 = prim->y1 = 240;
        prim->y2 = prim->y3 = -15;
    }

    func_80107250(prim, opacity * 2);
    if (opacity == 0x40) {
        prim->drawMode = DRAW_DEFAULT;
    } else {
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
    }
}

void HideMap(void) { SetMapOpacity(0); }

void SetFadeMode(FadeModes fadeMode) {
    Primitive* prim1;
    Primitive* prim2;

    prim1 = &g_PrimBuf[fade.fadePrim];
    prim2 = prim1->next;
    switch (fadeMode) {
    case FADE_NONE:
    case FADE_BLUE_TINT:
        prim1 = prim1->next;
        prim1 = prim1->next;
        prim1->x1 = 0;
        prim1->clut = 0;
        fade.stepFollowup = (s32)fadeMode + 1;
        break;
    case FADE_TO_BLACK:
    case FADE_FROM_BLACK:
    case FADE_TO_BLACK_SLOW:
    case FADE_SHOW_MAP:
    case FADE_HIDE_MAP:
        prim1->x1 = 0;
        prim1->clut = 0;
        fade.step = (s32)fadeMode + 1;
        break;
    case FADE_TO_BLACK_FAST:
        prim1->x1 = 0xFF;
        prim1->clut = 1;
        fade.step = 2;
        prim1->r0 = prim1->g0 = prim1->b0 = prim2->r0 = prim2->g0 = prim2->b0 =
            prim1->x1;
        prim1->drawMode = prim2->drawMode =
            DRAW_MENU | DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
        break;
    }
}

#ifdef VERSION_PSP
#define IFSTATEMENT prim1->y1-- == 0
#else
#define IFSTATEMENT --prim1->y1 == -1
#endif

void UpdateFade(bool skipFollowup) {
    Primitive* prim1;
    Primitive* prim2;
    s32 prim1clut;

    prim1 = &g_PrimBuf[fade.fadePrim];
    prim2 = prim1->next;
    prim1clut = prim1->clut;
    switch (fade.step - 1) {
    case FADE_DONE:
        prim2->drawMode = prim1->drawMode = DRAW_HIDE;
        break;
    case FADE_TO_BLACK:
    case FADE_TO_BLACK_SLOW:
    case FADE_SHOW_MAP:
        PGREY(prim1, 0) = PGREY(prim2, 0) = prim1->x1;
        if (prim1clut == 0) {
            if (fade.step - 1 == 1) {
                prim1->x1 += 0x20;
            } else if (fade.step - 1 == 6) {
                prim1->x1 += 8;
            } else {
                prim1->x1 += 2;
            }
            if ((fade.step - 1) == 6) {
                if (prim1->x1 >= 0x40) {
                    prim1->clut++;
                    prim1->x1 = 0x40;
                }
                SetMapOpacity(prim1->x1);
            } else {
                if (prim1->x1 >= 0x100) {
                    prim1->clut++;
                    prim1->x1 = 0xFF;
                }
            }
        }
        prim1->drawMode = prim2->drawMode =
            DRAW_MENU | DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
        break;
    case FADE_HIDE_MAP:
        PGREY(prim1, 0) = PGREY(prim2, 0) = 0x40 - prim1->x1;
        if (prim1clut == 0) {
            prim1->x1 += 8;
            if (prim1->x1 >= 0x40) {
                prim1->clut++;
                prim1->x1 = 0x40;
            }
            SetMapOpacity(0x40 - prim1->x1);
        } else {
            SetMapOpacity(0);
            fade.step = 0;
        }
        prim1->drawMode = prim2->drawMode =
            DRAW_MENU | DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
        break;
    case FADE_FROM_BLACK:
        PGREY(prim1, 0) = PGREY(prim2, 0) = 0xFF - prim1->x1;
        if (prim1clut == 0) {
            prim1->x1 += 0x20;
            if (prim1->x1 >= 0x100) {
                prim1->clut++;
                prim1->x1 = 0xFF;
            }
        } else {
            fade.step = 0;
        }
        prim1->drawMode = prim2->drawMode =
            DRAW_MENU | DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
        break;
    }
    if (skipFollowup) {
        return;
    }

    prim1 = prim2->next;
    prim2 = prim1->next;
    prim1clut = prim1->clut;
    switch (fade.stepFollowup - 1) {
    case FADE_DONE:
        prim2->drawMode = prim1->drawMode = DRAW_HIDE;
        break;
    case FADE_NONE:
        PGREY(prim1, 0) = PGREY(prim2, 0) = prim1->x1;
        if (prim1clut == 0) {
            prim1->x1 += 8;
            if (prim1->x1 >= 0x100) {
                prim1->clut++;
                prim1->x1 -= 8;
                prim1->y1 = 4;
            }
            prim1->drawMode = prim2->drawMode =
                DRAW_ABSPOS | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        } else if (prim1clut == 1) {
#ifdef VERSION_PSP
            if (prim1->y1-- == 0) {
#else
            if (--prim1->y1 == -1) {
#endif
                prim1->clut++;
            }
        } else {
            prim1->x1 -= 4;
            if (prim1->x1 < 0) {
                prim1->drawMode = prim2->drawMode = DRAW_HIDE;
                fade.stepFollowup = 0;
            }
        }
        break;
    case 3:
        prim1->b0 = prim2->b0 = 0;
        prim1->r0 = prim1->g0 = prim2->r0 = prim2->g0 = prim1->x1;
        if (prim1clut == 0) {
            if (++prim1->x1 >= 0x20) {
                prim1->clut++;
                prim1->x1--;
                prim1->y1 = 0xA0;
            }
            prim1->drawMode = prim2->drawMode =
                DRAW_ABSPOS | DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
        } else if (prim1clut == 1) {
#ifdef VERSION_PSP
            if (prim1->y1-- == 0) {
#else
            if (--prim1->y1 == -1) {
#endif
                prim1->clut++;
            }
        } else if (--prim1->x1 < 0) {
            prim1->drawMode = prim2->drawMode = DRAW_HIDE;
            fade.stepFollowup = 0;
        }
    }
}

/* BEGIN CAMERA SHAKE HANDLING SYSTEM
These functions manipulate g_cameraOffsetX and g_cameraOffsetY to make the
camera shake. This often happens when big things hit the ground, or similar.
A function makes a call to g_api.ShakeCamera which registers a request and
saves it into the shakeRequest. There is only one shakeRequest, so it is
possible for it to be overwritten if that function is called multiple times.
When called, it saves the request "type", an instance of the enum that I am
calling "cameraShakeTypes". This controls two things. 1) it selects a pattern
from shake_patterns and 2) it selects a step in UpdateCameraShake to process the
pattern.
Every frame, the game calls UpdateCameraShake in the main loop. That function
checks if there is an active request. If there is, it processes the request.
It steps through the individual steps in the chosen shake_pattern, and moves
the camera by the prescribed number of pixels. The camera movement direction
(X or Y) is hard-coded into the steps of UpdateCameraShake. The combination of
patterns and X/Y values was used to determine the names for cameraShakeTypes.
You will notice that types #1 and #3 both choose the shake_small pattern, and
both choose the Y axis. In fact, only #2 selects the X axis. This feels like
some sort of error. But we do find that #1 and #3 are both used in the retail
game, so it's not clear what the deal is there.
*/

static struct {
    u16 type;     // Index used to select one of 7 shakes (index 0-6)
    s16 i;        // Current step that we are on within the current shake
    s16* pattern; // The array describing the sequence of shake steps
    s16 amount;   // How much we are moving during the current shake step
} shakeRequest;

#define COORD_TERMINATOR 0x7FFF

// These program different shake patterns of how much the camera is offset
// The patterns simply wiggle back and forth with decreasing amplitude.
static s16 shake_small[] = {
    3, -3, 2, -2, 1, -1, COORD_TERMINATOR,
};
static s16 shake_medium[] = {
    3, -3, 3, -3, 2, -2, 2, -2, 1, -1, 1, -1, COORD_TERMINATOR,
};
static s16 shake_heavy[] = {
    6,  -6, 6,  -6, 5,
    -5, 5,  -5, 4,  -4,
    4,  -4, 3,  -3, 3,
    -3, 2,  -2, 2,  -2,
    1,  -1, 1,  -1, COORD_TERMINATOR,
};
static s16* shake_patterns[] = {
    shake_small,  // SHAKE_NONE
    shake_small,  // SHAKE_Y_SMALL
    shake_medium, // SHAKE_X_MEDIUM
    shake_small,  // SHAKE_Y_SMALL2
    shake_medium, // SHAKE_Y_MEDIUM
    shake_medium, // SHAKE_5_NULL
    shake_heavy,  // SHAKE_Y_HEAVY
};

void ShakeCamera(cameraShakeTypes type) {
    shakeRequest.type = type;
    shakeRequest.i = 0;
    shakeRequest.pattern = shake_patterns[type];
}

void StepShakeRequest(void) {
    shakeRequest.amount = shakeRequest.pattern[shakeRequest.i];
    shakeRequest.i++;
    if (shakeRequest.pattern[shakeRequest.i] == COORD_TERMINATOR) {
        shakeRequest.type = SHAKE_NONE;
        shakeRequest.amount = 0;
    }
}

void UpdateCameraShake(void) {
    switch (shakeRequest.type) {
    case SHAKE_NONE:
        break;
    case SHAKE_Y_SMALL:
        StepShakeRequest();
        g_cameraOffsetY = shakeRequest.amount;
        break;
    case SHAKE_X_MEDIUM:
        StepShakeRequest();
        g_cameraOffsetX = shakeRequest.amount;
        break;
    case SHAKE_Y_SMALL2:
        StepShakeRequest();
        g_cameraOffsetY = shakeRequest.amount;
        break;
    case SHAKE_Y_MEDIUM:
        StepShakeRequest();
        g_cameraOffsetY = shakeRequest.amount;
        break;
    case SHAKE_5_NULL:
        break;
    case SHAKE_Y_HEAVY:
        StepShakeRequest();
        g_cameraOffsetY = shakeRequest.amount;
        break;
    }
}
