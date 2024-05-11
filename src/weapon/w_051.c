// Weapon ID #51. Used by weapons:
// Estoc, Claymore, Flamberge, Zwei hander, Obsidian sword, Great Sword,
// Unknown#182, Unknown#183, Unknown#184, Unknown#185
#include "weapon_private.h"
#include "shared.h"

typedef struct {
    /* 0x00 */ u16** frames;
    /* 0x04 */ s8* frameProps;
    /* 0x08 */ u16 palette;
    /* 0x0A */ u16 sfxId;
    /* 0x0C */ u8 unk0C;
    /* 0x0D */ u8 animFrameIdx;
    /* 0x0E */ s16 unused;
} WeaponProperties;

extern s32 D_169000_8017C0E0;
extern WeaponProperties D_169000_8017ACD8[4];
extern WeaponProperties D_169000_8017AD18[4];
extern u16 D_169000_8017AD54[];
extern u16 D_169000_8017AD58[];
extern u16 D_169000_8017AD5C[];

extern s16 D_169000_8017AD68; // R
extern s16 D_169000_8017AD6A; // B
extern s16 D_169000_8017AD6C; // G
extern s16 D_169000_8017AD6E; // step?
extern s16 D_169000_8017AD70; // A
extern s32 D_169000_8017AD74[];

void func_169000_8017B1DC(s32 arg0) {
    RECT rect;
    s32 colorsChanged;
    s32 palIndex;
    u16 color;

    colorsChanged = 0;
    switch (D_169000_8017AD6E) {
    case 0:
        D_169000_8017AD68 += 2;
        D_169000_8017AD6C += 2;
        D_169000_8017AD6A += 2;
        if (D_169000_8017AD68 >= D_169000_8017AD74[arg0 * 8 + 4]) {
            colorsChanged++;
            D_169000_8017AD68 = D_169000_8017AD74[arg0 * 8 + 4];
        }
        if (D_169000_8017AD6C >= D_169000_8017AD74[arg0 * 8 + 5]) {
            colorsChanged++;
            D_169000_8017AD6C = D_169000_8017AD74[arg0 * 8 + 5];
        }
        if (D_169000_8017AD6A >= D_169000_8017AD74[arg0 * 8 + 6]) {
            colorsChanged++;
            D_169000_8017AD6A = D_169000_8017AD74[arg0 * 8 + 6];
        }
        if (!D_169000_8017AD68 && !D_169000_8017AD6C && !D_169000_8017AD6A) {
            D_169000_8017AD70 = 0;
        } else {
            D_169000_8017AD70 = 1;
        }
        if (colorsChanged == 3) {
            D_169000_8017AD6E++;
        }
        break;
    case 1:
        D_169000_8017AD68 -= 2;
        D_169000_8017AD6C -= 2;
        D_169000_8017AD6A -= 2;
        if (D_169000_8017AD68 <= D_169000_8017AD74[arg0 * 8]) {
            colorsChanged++;
            D_169000_8017AD68 = D_169000_8017AD74[arg0 * 8];
        }
        if (D_169000_8017AD6C <= D_169000_8017AD74[arg0 * 8 + 1]) {
            colorsChanged++;
            D_169000_8017AD6C = D_169000_8017AD74[arg0 * 8 + 1];
        }
        if (D_169000_8017AD6A <= D_169000_8017AD74[arg0 * 8 + 2]) {
            colorsChanged++;
            D_169000_8017AD6A = D_169000_8017AD74[arg0 * 8 + 2];
        }
        if (!D_169000_8017AD68 && !D_169000_8017AD6C && !D_169000_8017AD6A) {
            D_169000_8017AD70 = 0;
        } else {
            D_169000_8017AD70 = 1;
        }
        if (colorsChanged == 3) {
            D_169000_8017AD6E++;
        }
        break;
    case 2:
        return;
    }

    color = D_169000_8017AD68 + (D_169000_8017AD6C << 5) +
            (D_169000_8017AD6A << 10) + (D_169000_8017AD70 << 15);
    palIndex = (g_HandId * 0x180);
    palIndex += arg0 << 5;
    D_8006EDCC[0][0x2B + palIndex] = color;

    rect.x = 0;
    rect.y = 0xF1;
    rect.w = 256;
    rect.h = 3;
    LoadImage(&rect, (u_long*)D_8006EDCC);
}

void EntityWeaponAttack(Entity* self) {
    WeaponProperties* props;
    s16 subType;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;
    subType = self->params & 0x7FFF;
    subType >>= 8;
    props = &D_169000_8017ACD8[subType];
    if (PLAYER.ext.player.unkAC < props->unk0C ||
        PLAYER.ext.player.unkAC >= props->unk0C + 7 || !g_Player.unk46) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        self->animSet = 10;
        self->palette = 0x110;
        self->unk5A = 100;
        if (g_HandId) {
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->palette += props->palette;
        self->flags = FLAG_UNK_20000 | FLAG_UNK_40000;
        self->zPriority = PLAYER.zPriority - 2;
        if (subType == 1) {
            self->drawMode = 0x30;
        }
        if (subType == 2) {
            self->drawMode = 0x30;
        }
        if (subType == 3) {
            self->drawMode = 0x10;
        }
        if (subType != 0) {
            D_169000_8017AD68 = D_169000_8017AD58[subType * 0x10 - 2];
            D_169000_8017AD6C = D_169000_8017AD58[subType * 0x10];
            D_169000_8017AD6A = D_169000_8017AD58[subType * 0x10 + 2];
            D_169000_8017AD6E = 0;
            D_169000_8017AD70 = 0;
        }
        SetWeaponProperties(self, 0);
        self->step++;
        break;
    }
    self->ext.generic.unkAC = PLAYER.ext.player.unkAC - props->unk0C;
    if (PLAYER.animFrameDuration == 1 &&
        PLAYER.animFrameIdx == props->animFrameIdx) {
        g_api.PlaySfx(props->sfxId);
    }
    if (g_api.UpdateUnarmedAnim(props->frameProps, props->frames) < 0) {
        DestroyEntity(self);
        return;
    }
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
    if (subType != 0) {
        func_169000_8017B1DC(subType - 1);
    }
}

void func_ptr_80170004(Entity* self) {
    WeaponProperties* props;
    s16 subType;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;
    subType = self->params & 0x7FFF;
    subType >>= 8;
    props = &D_169000_8017AD18[subType];
    if (PLAYER.ext.player.unkAC < 0xD6 || PLAYER.ext.player.unkAC >= 0xD8) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        self->animSet = 10;
        self->palette = 0x110;
        self->unk5A = 100;
        if (g_HandId) {
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->palette += subType * 2;
        self->zPriority = PLAYER.zPriority - 2;
        if (subType == 1) {
            self->drawMode = 0x30;
        }
        if (subType == 2) {
            self->drawMode = 0x30;
        }
        if (subType == 3) {
            self->drawMode = 0x10;
        }
        if (subType != 0) {
            D_169000_8017AD68 = D_169000_8017AD58[subType * 0x10 - 2];
            D_169000_8017AD6C = D_169000_8017AD58[subType * 0x10];
            D_169000_8017AD6A = D_169000_8017AD58[subType * 0x10 + 2];
            D_169000_8017AD6E = 0;
            D_169000_8017AD70 = 0;
        }
        D_169000_8017C0E0 = 0;
        self->flags = FLAG_UNK_20000 | FLAG_UNK_40000;
        SetWeaponProperties(self, 0);
        self->step++;
        break;
    }
    self->ext.generic.unkAC = PLAYER.ext.player.unkAC - props->unk0C;
    if (g_api.UpdateUnarmedAnim(props->frameProps, props->frames) < 0) {
        DestroyEntity(self);
        return;
    }
    if (PLAYER.animFrameIdx == 1 && PLAYER.animFrameDuration == 1) {
        g_api.CreateEntFactoryFromEntity(
            self, ((g_HandId + 1) * 4096) | 0x3E, 0);
    }
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
    if (subType != 0 &&
        (((u16)PLAYER.animFrameIdx != 4) || (D_169000_8017AD6E == 0))) {
        func_169000_8017B1DC(subType - 1);
    }
}

INCLUDE_ASM("weapon/nonmatchings/w_051", func_ptr_80170008);

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

void func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 51; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
