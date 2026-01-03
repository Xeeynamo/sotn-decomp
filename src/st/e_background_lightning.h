// SPDX-License-Identifier: AGPL-3.0-or-later

#ifdef VERSION_PSP
extern s32 E_ID(LIGHTNING_THUNDER);
extern s32 E_ID(LIGHTNING_CLOUD);
#endif

#if defined(STAGE_IS_NO3)
static u8 D_80180EA0[] = {
    0x09, 0x04, 0x27, 0x28, 0x2A, 0x2C, 0x2F, 0x32, 0x36, 0x3F, 0x4A, 0x56,
    0x62, 0x6E, 0x7A, 0x00, 0x0C, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
    0x37, 0x40, 0x4B, 0x57, 0x63, 0x6F, 0x7B, 0x01, 0x0E, 0x05, 0x05, 0x05,
    0x05, 0x05, 0x05, 0x05, 0x38, 0x41, 0x4C, 0x58, 0x64, 0x70, 0x7C, 0x02,
    0x0F, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x39, 0x42, 0x4D, 0x59,
    0x65, 0x71, 0x7D, 0x03, 0x02, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12,
    0x3A, 0x43, 0x4E, 0x5A, 0x66, 0x72, 0x7E, 0x0A, 0x03, 0x12, 0x12, 0x12,
    0x12, 0x12, 0x12, 0x12, 0x12, 0x44, 0x4F, 0x5B, 0x67, 0x73, 0x7F, 0x0B,
    0x04, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x50, 0x5C,
    0x68, 0x74, 0x80, 0x0C, 0x0A, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12,
    0x12, 0x45, 0x51, 0x5D, 0x69, 0x75, 0x81, 0x0D, 0x0B, 0x12, 0x12, 0x12,
    0x12, 0x2E, 0x31, 0x34, 0x3C, 0x46, 0x52, 0x5E, 0x6A, 0x76, 0x82, 0x0E,
    0x10, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x35, 0x3D, 0x47, 0x53, 0x5F,
    0x6B, 0x77, 0x83, 0x0F, 0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12,
    0x3E, 0x48, 0x54, 0x60, 0x6C, 0x78, 0x84, 0x10, 0x12, 0x12, 0x12, 0x12,
    0x12, 0x12, 0x12, 0x12, 0x12, 0x49, 0x55, 0x61, 0x6D, 0x79, 0x85, 0x11};
#endif

static u8 lightningClutIndices[] = {
#if defined(STAGE_IS_NO3)
    0x09, 0x04, 0x07, 0x00, 0x0C, 0x05, 0x08, 0x01, 0x0E, 0x05, 0x08, 0x02,
    0x0F, 0x06, 0x09, 0x03, 0x02, 0x12, 0x12, 0x0A, 0x03, 0x12, 0x12, 0x0B,
    0x04, 0x12, 0x12, 0x0C, 0x0A, 0x12, 0x12, 0x0D, 0x0B, 0x12, 0x12, 0x0E,
    0x10, 0x12, 0x12, 0x0F, 0x11, 0x12, 0x12, 0x10, 0x12, 0x12, 0x12, 0x11,
#endif
    0x15, 0x17, 0x18, 0x17, 0x5C, 0x13, 0x14, 0x13, 0x5E, 0x15, 0x16, 0x15,
    0x17, 0x86, 0x87, 0x86, 0x49, 0x88, 0x89, 0x88, 0x14, 0x8A, 0x8B, 0x8A,
    0xFF, 0x00, 0x00, 0x00};

static u16 lightningAnim[] = {
    0x0104, 0x0002, 0x0102, 0x0002, 0x0102, 0x0002, 0x00FF, 0x0000};
#if defined(STAGE_IS_NO3)
static u16 D_80180FBC[] = {
    0x0108, 0x0208, 0x0308, 0x0408, 0x0508, 0x0608, 0x0708, 0x0808,
    0x0908, 0x0A08, 0x0B08, 0x0C08, 0x0D08, 0x0E08, 0x0F08, 0x00FF};
#endif
static u8 lightningThunderXY[][2] = {
    {0x88, 0x6C}, {0xC8, 0x30}, {0x30, 0x44}, {0x88, 0x6C}};

void EntityBackgroundLightning(Entity* self) {
    Entity* otherEnt;
    s32 animFrame;
    s32 randOf3;
    u8* clutIndices;
    s32 i;
#if defined(STAGE_IS_NO3)
    s32 clutDest;
    u8* var_s1;
    s32 playerRealX;
#endif

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->ext.backgroundLightning.timer = 0x80;
        self->animCurFrame = 15;
#if defined(STAGE_IS_NO3)
        var_s1 = &D_80180EA0[0];
        for (i = 0; i < 12; i++) {
            clutDest = var_s1[0];
            animFrame = 15;
            animFrame = var_s1[animFrame];
            g_ClutIds[clutDest] = g_ClutIds[animFrame + 0x200];
            var_s1 += 16;
        }
        if (self->params & 256) {
            self->step = 4;
            break;
        }
        if (g_CastleFlags[CASTLE_TURNED_ON]) {
            self->params = 0;
        }
#else
        g_CastleFlags[CASTLE_TURNED_ON] |= 1;
        if (self->params & FLAG_DEAD) {
            self->step = 4;
            break;
        }
#endif
    case 1:
        switch (self->step_s) {
#if !defined(STAGE_IS_NO3)
        default:
            break;
#endif
        case 0:
            otherEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (otherEnt != NULL) {
                CreateEntityFromCurrentEntity(
                    E_ID(LIGHTNING_THUNDER), otherEnt);
                randOf3 = Random() & 3;
                otherEnt->posX.i.hi = lightningThunderXY[randOf3][0];
                otherEnt->posY.i.hi = lightningThunderXY[randOf3][1];
            }
            otherEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (otherEnt != NULL) {
                CreateEntityFromCurrentEntity(E_ID(LIGHTNING_CLOUD), otherEnt);
                if (randOf3 > 2) {
                    randOf3 = 0;
                }
                otherEnt->params = randOf3;
            }
            self->step_s++;
            /* fallthrough */
        case 1:
            if (AnimateEntity(lightningAnim, self) == 0) {
                self->ext.backgroundLightning.timer = (Random() & 0x7F) + 0x40;
                self->step_s++;
            }
            clutIndices = &lightningClutIndices[0];
#if defined(STAGE_IS_NO3)
            if (!self->params) {
                clutIndices += 0x30;
            }
#endif
            for (animFrame = self->animCurFrame; *clutIndices != 0xFF;
                 clutIndices += 4) {
                i = *clutIndices;
                g_ClutIds[i] = g_ClutIds[(clutIndices + animFrame)[1] + 0x200];
            }

            if (animFrame == 1) {
                g_GpuBuffers[0].draw.r0 = 0x30;
                g_GpuBuffers[0].draw.g0 = 0x30;
                g_GpuBuffers[0].draw.b0 = 0x48;
                g_GpuBuffers[1].draw.r0 = 0x30;
                g_GpuBuffers[1].draw.g0 = 0x30;
                g_GpuBuffers[1].draw.b0 = 0x48;
            } else { // Same as case 2 right below
                g_GpuBuffers[0].draw.r0 = 0x10;
                g_GpuBuffers[0].draw.g0 = 8;
                g_GpuBuffers[0].draw.b0 = 0x38;
                g_GpuBuffers[1].draw.r0 = 0x10;
                g_GpuBuffers[1].draw.g0 = 8;
                g_GpuBuffers[1].draw.b0 = 0x38;
            }
            break;
        case 2:
            g_GpuBuffers[0].draw.r0 = 0x10;
            g_GpuBuffers[0].draw.g0 = 8;
            g_GpuBuffers[0].draw.b0 = 0x38;
            g_GpuBuffers[1].draw.r0 = 0x10;
            g_GpuBuffers[1].draw.g0 = 8;
            g_GpuBuffers[1].draw.b0 = 0x38;
            if (--self->ext.backgroundLightning.timer) {
                break;
            }
            SetSubStep(0);
            break;
        }
#if defined(STAGE_IS_NO3)
        if (self->params != 1) {
            break;
        }
        otherEnt = &PLAYER;
        playerRealX = g_Tilemap.scrollX.i.hi + otherEnt->posX.i.hi;
        if (playerRealX > 0x300) {
            g_CastleFlags[CASTLE_TURNED_ON] = 1;
            SetStep(2);
        }
#endif
        break;
#if defined(STAGE_IS_NO3)
    case 2:
        if (AnimateEntity(D_80180FBC, self) == 0) {
            self->params = 0;
            SetStep(1);
        }
        g_GpuBuffers[0].draw.r0 = 16;
        g_GpuBuffers[0].draw.g0 = 8;
        g_GpuBuffers[0].draw.b0 = 56;
        g_GpuBuffers[1].draw.r0 = 16;
        g_GpuBuffers[1].draw.g0 = 8;
        g_GpuBuffers[1].draw.b0 = 56;
        var_s1 = &D_80180EA0[0];
        for (i = 0; i < 12; i++) {
            clutDest = var_s1[0];
            animFrame = self->animCurFrame;
            animFrame = var_s1[animFrame];
            g_ClutIds[clutDest] = g_ClutIds[animFrame + 0x200];
            var_s1 += 16;
        }
        break;
#endif
    // careful, this is the outer switch!
    case 4:
        g_GpuBuffers[0].draw.r0 = 16;
        g_GpuBuffers[0].draw.g0 = 8;
        g_GpuBuffers[0].draw.b0 = 56;
        g_GpuBuffers[1].draw.r0 = 16;
        g_GpuBuffers[1].draw.g0 = 8;
        g_GpuBuffers[1].draw.b0 = 56;
    }
#if defined(STAGE_IS_NO3)
    if (self->params == 1) {
        switch (self->ext.backgroundLightning.unk84) {
        case 0:
            g_api.PlaySfx(SET_UNK_90);
            self->ext.backgroundLightning.unk84++;
            D_80097928 = 1;
#ifdef VERSION_PSP
            // TODO: SFX enum needs entries changed for PSP
            currentMusicId = 0x329;
#else
            currentMusicId = SE_INTRO_WIND_QUIET;
#endif
            break;
        case 1:
            if (g_api.func_80131F68() == false) {
                D_80097928 = 0;
                g_api.PlaySfx(currentMusicId);
                self->ext.backgroundLightning.unk84++;
            }
            break;
        case 2:
            otherEnt = &PLAYER;
            playerRealX = g_Tilemap.scrollX.i.hi + otherEnt->posX.i.hi;
            if (playerRealX > 0x300) {
                g_api.PlaySfx(SET_UNK_90);
                D_80097928 = 1;
                currentMusicId = MU_DRACULAS_CASTLE;
                self->ext.backgroundLightning.unk84++;
            }
            break;
        case 3:
            if (g_api.func_80131F68() == false) {
                D_80097928 = 0;
                g_api.PlaySfx(currentMusicId);
                self->ext.backgroundLightning.unk84++;
            }
            break;
        }
    }
#endif
}
