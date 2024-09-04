#include "cen.h"
#include "game.h"
#include "sfx.h"

extern u32 D_8019D424;
extern s32 D_8019D428;

// tile layout
static s16 D_8018068C[] = {
    0x014A, 0x014B, 0x014E, 0x014F, 0x014C, 0x014D, 0x0150, 0x0151, 0x00F5,
    0x00F6, 0x012B, 0x012C, 0x00FC, 0x00FD, 0x012F, 0x0130, 0x0101, 0x00FF,
    0x0201, 0x00FF, 0x0201, 0x0307, 0x0407, 0x0507, 0x0607, 0x0707, 0x0807,
    0x0907, 0x0A10, 0x00FF, 0x0A01, 0x0B06, 0x0C06, 0x0D06, 0x0E10, 0x0F0A,
    0x0E0A, 0x0F0A, 0x0E20, 0x00FF, 0x0E01, 0x1004, 0x1104, 0x120B, 0x00FF,
    0x0000, 0x1301, 0x00FF, 0x1201, 0x00FF, 0x1220, 0x1103, 0x1003, 0x1403,
    0x1503, 0x1640, 0x1506, 0x0D05, 0x0C05, 0x0B05, 0x0A20, 0x00FF, 0x0A10,
    0x1710, 0x0A08, 0x00FF, 0x0A01, 0x0B02, 0x0C02, 0x1806, 0x1906, 0x1850,
    0x0C03, 0x0B03, 0x0A08, 0x00FF, 0x0A01, 0x0B03, 0x0C03, 0x0D03, 0x0E03,
    0x1B06, 0x1A10, 0x1B20, 0x0E03, 0x0D03, 0x0C03, 0x00FF, 0x1C04, 0x1D04,
    0x1E04, 0x1F04, 0x00FF, 0x0000, 0x2002, 0x2104, 0x2204, 0x2304, 0x2404,
    0x2504, 0x2604, 0x2704, 0x2002, 0x0000, 0x2808, 0x2908, 0x2A60, 0x00FF,
    0x0C01, 0x00FF,
};

static u8 D_80180768[] = {
    0x08, 0x03, 0x04, 0x04, 0x04, 0x05, 0x04, 0x06, 0x04, 0x07, 0x04, 0x08,
    0x04, 0x09, 0x02, 0x0A, 0x01, 0x0B, 0x10, 0x0A, 0xFF, 0x00, 0x00, 0x00,
};

static u8 D_80180780[] = {
    0x04, 0x0A, 0x04, 0x09, 0x04, 0x08, 0x04, 0x07, 0x04, 0x06, 0x04, 0x05,
    0x04, 0x04, 0x04, 0x03, 0x02, 0x0C, 0x04, 0x03, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00,
    0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01,
};

void func_8018F890(s16 arg0) {
    s16 temp_v0 = arg0 - g_Tilemap.height;

REDACTED
        g_Tilemap.height++;
    } else if (temp_v0 < -1) {
        g_Tilemap.height--;
    } else {
        g_Tilemap.height = arg0;
    }
}
REDACTED
void func_8018F8EC(u16 index) {
    Tilemap* tilemap = &g_Tilemap;
    u16 tilePos = 0x5B6;
    u16* tileLayoutPtr = &D_8018068C[index * 8];
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            tilemap->fg[tilePos] = *tileLayoutPtr;
            tileLayoutPtr++;
            tilePos++;
        }
        tilePos += 0x2C;
    }
}
REDACTED
REDACTED
REDACTED
    Tilemap* tilemap = &g_Tilemap;
REDACTED
REDACTED
    s16 primIndex;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    temp_a1 = GetPlayerCollisionWith(self, 0x20, 0x11, 4);
    temp_s1 = player->posX.i.hi + g_Tilemap.scrollX.i.hi;
    temp_v0 = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex != -1) {
            InitializeEntity(g_EInitGeneric);
            self->animSet = ANIMSET_OVL(2);
REDACTED
REDACTED
REDACTED
            if (g_CastleFlags[216] != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->flags |= FLAG_HAS_PRIMS;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = 2;
REDACTED
REDACTED
REDACTED
REDACTED
        if ((GetDistanceToPlayerX() < 32) &&
REDACTED
REDACTED
            g_unkGraphicsStruct.unk0 = 1;
            if (g_Player.unk0C & PLAYER_STATUS_BAT_FORM) {
                g_Player.padSim = PAD_R1;
            } else if (g_Player.unk0C & PLAYER_STATUS_MIST_FORM) {
                g_Player.padSim = PAD_L1;
            } else if (g_Player.unk0C & PLAYER_STATUS_WOLF_FORM) {
                g_Player.padSim = PAD_R2;
REDACTED
                g_Player.padSim = PAD_LEFT;
REDACTED
                g_Player.padSim = PAD_RIGHT;
REDACTED
                g_Player.padSim = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        g_Player.padSim = 0;
        if (g_Player.unk0C & PLAYER_STATUS_TRANSFORM) {
            if (g_Timer & 1) {
                if (g_Player.unk0C & PLAYER_STATUS_BAT_FORM) {
                    g_Player.padSim = PAD_R1;
                } else if (g_Player.unk0C & PLAYER_STATUS_MIST_FORM) {
                    g_Player.padSim = PAD_L1;
                } else if (g_Player.unk0C & PLAYER_STATUS_WOLF_FORM) {
                    g_Player.padSim = PAD_R2;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                    g_Player.padSim = PAD_LEFT;
REDACTED
                    g_Player.padSim = PAD_RIGHT;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_Player.padSim == 0x8000) {
REDACTED
                g_Player.padSim = 0;
REDACTED
        } else if ((g_Player.padSim == 0x2000) && (temp_s1 >= 384)) {
            g_Player.padSim = 0;
REDACTED
        if (g_Player.padSim == 0) {
            g_Player.padSim = PAD_LEFT;
            player->posX.i.hi = 384 - tilemap->scrollX.i.hi;
REDACTED
            g_api.PlaySfx(SFX_METAL_CLANG_A);
REDACTED
            tilemap->height = ((s16)tilemap->scrollY.i.hi + 0x100);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        g_Player.padSim = 0;
REDACTED
        player->posX.i.hi = 384 - tilemap->scrollX.i.hi;
REDACTED
REDACTED
REDACTED
            D_80097488.y.i.hi--;
REDACTED
            g_api.PlaySfx(SFX_DOOR_CLOSE_A);
            if (player->facingLeft == 0) {
                g_Player.padSim = PAD_LEFT;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        g_Player.padSim = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_api.PlaySfx(SFX_METAL_CLANG_A);
REDACTED
        g_Player.padSim = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            D_80097488.x.i.hi++;
REDACTED
REDACTED
            if (g_unkGraphicsStruct.unk0 != 0) {
                g_unkGraphicsStruct.unk0 = 0;
REDACTED
REDACTED
REDACTED
            g_api.PlaySfx(SFX_DOOR_CLOSE_A);
REDACTED
REDACTED
        g_Player.padSim = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (tilemap->height == 0x300) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    prim = &g_PrimBuf[self->primIndex];
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    prim->y2 = prim->y3 = 0x268 - tilemap->scrollY.i.hi;
REDACTED
REDACTED
// Black layer that covers room interior and lights up when cutscene starts
REDACTED
REDACTED
    s16 primIndex;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        /* Has player seen Maria Holy Glasses Cutscene? */
        if (g_CastleFlags[216] != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            InitializeEntity(g_EInitGeneric);
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->flags |= FLAG_HAS_PRIMS;
            temp_v1 = 0x178 - g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = 0x57;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = 0x57;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim->drawMode = DRAW_HIDE;
REDACTED
        prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
void EntityMaria(Entity* self) {
    if (self->step == 0) {
        /* Has player seen Maria Holy Glasses Cutscene? */
        if (g_CastleFlags[216] != 0) {
REDACTED
REDACTED
REDACTED
        InitializeEntity(D_80180428);
        self->flags = FLAG_UNK_08000000;
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 10;
        self->unk5A = 0x48;
        self->palette = 0x210;
        self->zPriority = 0x80;
    }
}
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    prim->drawMode = 2;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
s16 func_801904B8(Primitive* prim, s16 arg1) {
    prim->u0 = prim->u2 = 0x50;
    prim->u1 = prim->u3 = 0x60;
    prim->drawMode = 2;
    prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi - 8;
    prim->x1 = prim->x3 = g_CurrentEntity->posX.i.hi + 8;
    prim->y2 = prim->y3 = arg1;
    arg1 -= 32;
    prim->v2 = prim->v3 = 38;
    prim->v0 = prim->v1 = 6;
    prim->y0 = prim->y1 = arg1;
    return arg1;
}
REDACTED
// Elevator when not moving (ID 1A)
REDACTED
REDACTED
REDACTED
    s16 primIndex;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        CreateEntityFromCurrentEntity(E_ID_1B, &self[-1]);
REDACTED
        CreateEntityFromCurrentEntity(E_ID_1B, &self[-2]);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED
        if ((s16)(player->posY.i.hi + g_Tilemap.scrollY.i.hi) < 80) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                if (abs(posX) < 8) {
REDACTED
REDACTED
                    g_Player.padSim = 0;
                    PLAYER.velocityX = 0;
                    PLAYER.velocityY = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        g_Player.padSim = 0;
REDACTED
REDACTED
            self->posY.val += FIX(0.5);
REDACTED
            posY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if ((g_Timer % 16) == 0) {
                PlaySfxPositional(SFX_METAL_CLANG_A);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (AnimateEntity(D_80180780, self) == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (self->animFrameIdx == 4 && self->animFrameDuration == 0) {
                g_api.PlaySfx(SFX_LEVER_METAL_BANG);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        g_Player.padSim = 0;
REDACTED
REDACTED
REDACTED
            if (AnimateEntity(D_80180768, self) == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
            if (self->animFrameIdx == 4 && self->animFrameDuration == 0) {
                g_api.PlaySfx(SFX_LEVER_METAL_BANG);
            }
            break;

        case 1:
            self->posY.val -= FIX(0.5);
            if ((g_Timer % 16) == 0) {
                PlaySfxPositional(SFX_METAL_CLANG_A);
            }
            break;

        case 2:
            if (AnimateEntity(D_80180780, self) == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    prim->drawMode = 2;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED
    if (abs(self->posY.i.hi) > 384) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->ext.generic.unk80.modeS8.unk0 =
                GetPlayerCollisionWith(self, 12, 8, 4);
REDACTED
REDACTED
            self->ext.generic.unk80.modeS8.unk0 =
                GetPlayerCollisionWith(self, 12, 8, 6);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
// Elevator when moving, fixes player into position (ID 1C)
REDACTED
REDACTED
REDACTED
    s16 primIndex;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        g_Player.padSim = 0;
        self->posY.val += FIX(0.5);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        g_Player.padSim = 0;
        self->posY.val -= FIX(0.5);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    prim->drawMode = 2;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED
    if (abs(self->posY.i.hi) > 384) {
REDACTED
REDACTED
REDACTED
