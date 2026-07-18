// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../cen/cen.h"

extern s32 g_CutsceneFlags;
extern s32 D_psp_091CE570; // dra bss

// bss
PlayerState g_Maria;
static s32 D_pspeu_09295E18;
static s32 think_step;
// some kind of subweapon based timer?
static s32 D_pspeu_09295E08;
// timer?
static s32 D_pspeu_09295E00;
s32 subweaponIdx;
static s32 facing_dir;
static s32 hm;
static s32 maria_scrollX;
static s32 player_scrollX;
static s32 distance_to_player_x;
static s32 distance_to_player_y;
// timer?
static s32 D_pspeu_09295DC0;
static u32 move_dir;
// timer?
static s32 D_pspeu_09295DB0;
// timer?
static s32 D_pspeu_09295DA8;
// timer?
static s32 D_pspeu_09295DA0;
static s32 sfx;
static s32 cutscene_flags;
static s8 metMaria;

static s32 D_pspeu_09285B28[] = {52, 88, 80, 24, 68};
static u32 D_pspeu_09285B40[] = {32, 260, 32, 24, 40};

void func_pspeu_09251548(void) {
    if (MARIA.facingLeft) {
        g_Maria.padSim = PAD_R1;
    } else {
        g_Maria.padSim = PAD_L1;
    }
}

void func_pspeu_09251580(void) {
    if (MARIA.facingLeft) {
        g_Maria.padSim = PAD_L1;
    } else {
        g_Maria.padSim = PAD_R1;
    }
}

static u16 PadSimFacingDirectional(void) {
    u16 padSim = 0;

    if (MARIA.facingLeft) {
        padSim = PAD_LEFT;
    } else {
        padSim = PAD_RIGHT;
    }

    return padSim;
}

static void func_pspeu_09251600(s32 subweapon) {
    subweaponIdx = subweapon;
    g_Maria.padSim = PAD_SQUARE | PAD_UP;
    think_step = 2;
    D_pspeu_09295E08 = D_pspeu_09285B28[subweapon];
}

void func_pspeu_09251658(s32 unused, s32 arg1, s32 arg2) {
    g_Maria.padSim = PAD_SQUARE;
    think_step = arg1;
    D_pspeu_09295E08 = arg2;
}

void MarSetSfx(s32 arg0);

void func_pspeu_09251698(s32 subweaponIndex, s32 arg1, s32 arg2, s32 sfxId) {
    func_pspeu_09251600(subweaponIndex);
    g_Maria.unk68 = 1;
    think_step = arg1;
    D_pspeu_09295E08 = arg2;
    MarSetSfx(sfxId);
}

void func_pspeu_09251A28(s32 arg0, s32 arg1);
void func_pspeu_09251700(s32 arg0, s32 arg1, s32 arg2) {
    func_pspeu_09251A28(arg0, 0);
    think_step = arg1;
    D_pspeu_09295E08 = arg2;
}

void func_pspeu_09251750(void) { think_step = 0x19; }

static void func_pspeu_09251768(void) { think_step = 0x25; }

s32 func_pspeu_09251780(s32 arg0) {
    if (!--D_pspeu_09295E08) {
        think_step = arg0;
        return 1;
    }

    return 0;
}

void func_pspeu_092517D0() {
    s8 subweaponChoiceOne[5] = {0, 2, 4, 2, 4};
    s8 subweaponChoiceTwo[2] = {2, 4};
    s32 subweaponIndex;

    if (g_Maria.vram_flag & TOUCHING_GROUND) {
        subweaponIndex = subweaponChoiceOne[rand() % 5U];
        if (subweaponIndex != 0) {
            func_pspeu_09251600(subweaponIndex);
            return;
        }

        func_pspeu_09251600(subweaponIndex);
        return;
    }

    subweaponIndex = subweaponChoiceTwo[rand() % 2U];
    func_pspeu_09251600(subweaponIndex);
}

void func_pspeu_092518C8() {
    s8 subweaponChoice[5] = {2, 4, 2, 4, 100};
    s32 subweaponIndex;

    if (!(g_Maria.vram_flag & TOUCHING_GROUND)) {
        return;
    }

    D_pspeu_09295DB0--;
    if (D_pspeu_09295DB0 <= 0) {
        func_pspeu_09251750();
        D_pspeu_09295DB0 = (rand() % 3) + 4;
        return;
    }

    subweaponIndex = subweaponChoice[rand() % 5U];
    if (subweaponIndex == 100) {
        func_pspeu_09251768();
    } else if (subweaponIndex != 0) {
        func_pspeu_09251600(subweaponIndex);
    } else {
        func_pspeu_09251600(subweaponIndex);
    }
}

void func_pspeu_092519E8(void) {
    if (D_pspeu_09295E18 == 0) {
        func_pspeu_092517D0();
        return;
    }
    func_pspeu_092518C8();
}

static void func_pspeu_09251A28(s32 subweapon, s32 arg1) {
    if (g_Maria.vram_flag & TOUCHING_GROUND) {
        subweaponIdx = subweapon;
        if (arg1 != 0) {
            think_step = 0x16;
        } else {
            g_Maria.padSim |= PAD_TRIANGLE;
            think_step = 2;
        }
        D_pspeu_09295E08 = D_pspeu_09285B40[subweapon];
    }
}

s32 func_pspeu_09251AC0(void) {
    if (!(rand() % 20)) {
        func_pspeu_09251A28(0, 0);
        D_pspeu_09295E00 = 0x3C;
        return 1;
    }

    g_Maria.padSim |= PAD_SQUARE;
    D_pspeu_09295E00 = 0x3C;
    return 0;
}

static s32 func_pspeu_09251B40(void) {
    if (g_Maria.vram_flag & TOUCHING_GROUND) {
        return func_pspeu_09251AC0();
    }
    g_Maria.padSim |= PAD_SQUARE;
    D_pspeu_09295E00 = 0x3C;
    return 0;
}

static s32 func_pspeu_09251BA0(void) {
    s32 ret = 0;

    if (MARIA.facingLeft != facing_dir) {
        if (facing_dir != 0) {
            g_Maria.padSim = PAD_LEFT;
            ret = 1;
        } else {
            g_Maria.padSim = PAD_RIGHT;
            ret = 1;
        }
    }
    return ret;
}

s16 func_pspeu_09251C18(void) {
    s32 var_s0;
    s32 var_s1;

    var_s1 = think_step;
    if (distance_to_player_y > 0x30) {
        if (hm < 0x68) {
            func_pspeu_09251600(1);
        } else if (!(rand() & 7)) {
            think_step = 8;
        }
    } else if (hm > 0x90) {
        if (facing_dir != 0) {
            think_step = 0x18;
            D_pspeu_09295DC0 = (rand() % 4) + 6;
            move_dir = g_Maria.padSim = PAD_LEFT;
        } else {
            think_step = 0x18;
            D_pspeu_09295DC0 = (rand() % 4) + 6;
            move_dir = g_Maria.padSim = PAD_RIGHT;
        }
    } else if (hm < 0x48) {
        if (distance_to_player_x < 0x40 &&
            ((maria_scrollX < 0x146 && MARIA.facingLeft == 0) ||
             (maria_scrollX > 0x1B9 && MARIA.facingLeft))) {
            D_pspeu_09295E08 = 0x20;
            think_step = 3;
        } else if ((maria_scrollX > 0x145 || MARIA.facingLeft != 0) &&
                   (maria_scrollX <= 0x1B9 || !MARIA.facingLeft)) {
            func_pspeu_09251548();
        }
    } else {
        D_pspeu_09295E08 = 0x10;
        think_step = 1;
    }
    if (var_s1 != think_step) {
        var_s0 = 1;
    } else {
        var_s0 = 0;
    }
    return var_s0;
}

s16 func_pspeu_09251EB0(void) {
    s32 var_s0;
    s32 var_s1;

    var_s1 = think_step;
    if (D_pspeu_09295DA8 > 0) {
        D_pspeu_09295DA8--;
    }
    if (distance_to_player_y > 0x30) {
        if (hm < 0x68) {
            func_pspeu_09251600(1);
        } else if (!(rand() & 7)) {
            g_Maria.padSim = PAD_NONE;
            g_Maria.padSim |= PAD_CROSS;
            think_step = 0xB;
        }
    } else if (hm > 0x90) {
        if (facing_dir != 0) {
            think_step = 0x18;
            D_pspeu_09295DC0 = (rand() % 4) + 6;
            move_dir = g_Maria.padSim = PAD_LEFT;
        } else {
            think_step = 0x18;
            D_pspeu_09295DC0 = (rand() % 4) + 6;
            move_dir = g_Maria.padSim = PAD_RIGHT;
        }
    } else if (hm < 0x48) {
        if (distance_to_player_x < 0x40 &&
            ((maria_scrollX < 0x146 && MARIA.facingLeft == 0) ||
             (maria_scrollX > 0x1B9 && MARIA.facingLeft))) {
            D_pspeu_09295DA0 = 0x2D;
            if (D_pspeu_09295DA8 != 0) {
                think_step = 0x2B;
                D_pspeu_09295DA8 = 0;
                D_pspeu_09295DA0 = 0;
            }
        } else if ((maria_scrollX > 0x145 || MARIA.facingLeft != 0) &&
                   (maria_scrollX <= 0x1B9 || !MARIA.facingLeft)) {
            func_pspeu_09251548();
        }
    } else {
        D_pspeu_09295E08 = 0x10;
        think_step = 1;
    }
    if (var_s1 != think_step) {
        var_s0 = 1;
    } else {
        var_s0 = 0;
    }
    return var_s0;
}

static s32 func_pspeu_092521A8(void) {
    if (D_pspeu_09295E18 == 0) {
        func_pspeu_09251C18();
        return;
    }
    func_pspeu_09251EB0();
}

void func_pspeu_092521E8(void) {
    player_scrollX = g_Tilemap.scrollX.i.hi + PLAYER.posX.i.hi;
    maria_scrollX = g_Tilemap.scrollX.i.hi + MARIA.posX.i.hi;
    distance_to_player_x = abs(MARIA.posX.i.hi - PLAYER.posX.i.hi);
    distance_to_player_y = abs(MARIA.posY.i.hi - PLAYER.posY.i.hi);
    g_Maria.demo_timer = 1;
    g_Maria.padSim = PAD_NONE;

    if (g_Maria.status & PLAYER_STATUS_DEAD) {
        think_step = 0x14;
    }

    if (g_Maria.status & PLAYER_STATUS_UNK10000) {
        think_step = 0;
    }

    if (g_Maria.status & PLAYER_STATUS_STONE) {
        think_step = 0x13;
    }

    MarSetSfx(-1);
    facing_dir = 0;
    if ((MARIA.posX.i.hi - PLAYER.posX.i.hi) >= 0) {
        facing_dir = 1;
    }

    g_Maria.unk68 = 0;
    if (D_pspeu_09295DA0 > 0) {
        D_pspeu_09295DA0--;
    }

    if (D_pspeu_09295DA0 && MARIA.step == 0xA) {
        D_pspeu_09295DA8 = 0x1E;
    }

    hm = abs(MARIA.posX.i.hi - PLAYER.posX.i.hi);
    FntPrint("hm:%02x\n", hm);
    FntPrint("think_step:%02x\n", think_step);
    FntPrint("dir %02x abs_posi:%04x %04x %04x %04x\n", MARIA.facingLeft,
             maria_scrollX, player_scrollX, distance_to_player_x,
             distance_to_player_y);

    switch (think_step) {
    case 0:
        if (!(g_Maria.status & PLAYER_STATUS_UNK10000)) {
            if ((D_pspeu_09295E18 == 0) && (MARIA.hitPoints < 0xC8)) {
                if (func_pspeu_09251BA0() == 0) {
                    D_pspeu_09295E18 = 1;
                    D_pspeu_09295DB0 = 4;
                    D_pspeu_09295DA0 = 0;
                    func_pspeu_09251A28(1, 1);
                }
            } else if (!func_pspeu_092521A8()) {
                D_pspeu_09295E08 = 0x10;
                think_step = 1;
            }
        }
        break;
    case 1:
        if (func_pspeu_09251BA0() == 0) {
            func_pspeu_092519E8();
        }
        break;
    case 2:
        if (!--D_pspeu_09295E08) {
            think_step = 0;
            D_pspeu_09295E08 = 0x70;
        }
        break;
    case 3:
        g_Maria.padSim = PAD_DOWN;
        if (!--D_pspeu_09295E08) {
            think_step = 4;
        }
        break;
    case 4:
        g_Maria.demo_timer = 2;
        g_Maria.padSim = PAD_CROSS | PAD_DOWN;
        D_pspeu_09295E08 = 0x18;
        think_step = 5;
        break;
    case 5:
        if (!--D_pspeu_09295E08) {
            g_Maria.demo_timer = 2;
            g_Maria.padSim = PAD_CROSS | PAD_DOWN;
            think_step = 6;
            D_pspeu_09295E08 = 0x4B;
        }
        break;
    case 6:
        if (func_pspeu_09251780(0) != 0) {
            func_pspeu_09251BA0();
        }
        break;
    case 7:
        if (!--D_pspeu_09295E08 || !(g_Maria.status & PLAYER_STATUS_CROUCH)) {
            think_step = 0;
            D_pspeu_09295E00 = 0x3C;
        }

        func_pspeu_09251BA0();
        g_Maria.padSim |= PAD_DOWN;
        if (hm < 0x38) {
            if (D_pspeu_09295E00 != 0) {
                D_pspeu_09295E00--;
            } else {
                func_pspeu_09251B40();
            }
        }
        break;
    case 11:
        if (g_Maria.vram_flag & TOUCHING_GROUND) {
            think_step = 0;
            break;
        }

        g_Maria.padSim |= PAD_CROSS;
        if (!(g_GameTimer % 0x20)) {
            g_Maria.padSim |= PAD_CIRCLE | PAD_UP;
        }

        if (!--D_pspeu_09295E08) {
            think_step = 0xC;
            g_Maria.padSim = PAD_NONE;
            D_pspeu_09295E08 = 0x12;
            break;
        }
        break;
    case 12:
        if (g_Maria.vram_flag & TOUCHING_GROUND) {
            think_step = 0;
            break;
        }

        g_Maria.padSim |= PAD_CROSS;
        if (!--D_pspeu_09295E08) {
            func_pspeu_09251580();
            think_step = 0xE;
        }
        break;
    case 8:
        D_pspeu_09295E08 = 0x13;
        g_Maria.padSim = PAD_CROSS;
        think_step = 9;
        break;
    case 9:
        g_Maria.padSim = PAD_CROSS;
        if (D_pspeu_09295E08 > 0) {
            D_pspeu_09295E08 -= 1;
            break;
        }
        if (g_Maria.vram_flag & TOUCHING_GROUND) {
            D_pspeu_09295E08 = 5;
            think_step = 0xA;
            break;
        }
        break;
    case 10:
        if (D_pspeu_09295E08 > 0) {
            D_pspeu_09295E08--;
        } else {
            func_pspeu_09251600(1);
        }
        break;
    case 13:
        if (MARIA.posY.i.hi < PLAYER.posY.i.hi) {
            if (distance_to_player_x < 0x28) {
                g_Maria.padSim = PAD_CROSS | PAD_DOWN;
            } else {
                g_Maria.padSim =
                    PadSimFacingDirectional() | (PAD_CROSS | PAD_DOWN);
            }
        } else {
            func_pspeu_092519E8();
        }
        think_step = 0xE;
        // fallthrough
    case 14:
        if (g_Maria.vram_flag & TOUCHING_GROUND) {
            func_pspeu_09251BA0();
            think_step = 0;
        }
        break;
    case 15:
        if (!(g_Maria.vram_flag & TOUCHING_GROUND) && MARIA.velocityY > -8 &&
            MARIA.posY.i.hi > (PLAYER.posY.i.hi + 0x30)) {
            g_Maria.padSim = PAD_NONE;
            think_step = 0x10;
            D_pspeu_09295E08 = 0xA;
            if (MARIA.facingLeft) {
                g_Maria.padSim = PAD_LEFT;
            } else {
                g_Maria.padSim = PAD_RIGHT;
            }
            break;
        }
        D_pspeu_09295E08 = 0;
        // fallthrough
    case 16:
        if (g_Maria.vram_flag & TOUCHING_GROUND) {
            think_step = 0;
            break;
        }

        if (hm > 0x10) {
            if (MARIA.facingLeft) {
                g_Maria.padSim = PAD_LEFT;
            } else {
                g_Maria.padSim = PAD_RIGHT;
            }
        }

        g_Maria.padSim |= PAD_CROSS;
        if (D_pspeu_09295E08 > 0) {
            D_pspeu_09295E08--;
        }

        if ((D_pspeu_09295E08 == 0) && (MARIA.velocityY > 0)) {
            func_pspeu_09251B40();
        }

        break;
    case 18:
        func_pspeu_09251548();
        think_step = 0;
        break;
    case 19:
        if (!(g_Maria.status & PLAYER_STATUS_STONE)) {
            think_step = 0;
        }

        if (!(g_GameTimer & 0xF)) {
            g_Maria.padSim = PAD_UP;
        }
        break;
    case 20:
        if (!(g_Maria.status & PLAYER_STATUS_DEAD)) {
            think_step = 0;
        }

        g_Maria.padSim = PAD_UP;
        // TODO: Should these have separate Maria statuses?
        if (g_Maria.status & PLAYER_STATUS_BAT_FORM) {
            g_Maria.padSim = PAD_BAT;
        }

        if (g_Maria.status & PLAYER_STATUS_MIST_FORM) {
            g_Maria.padSim = PAD_R2;
        }
        break;
    case 22:
        func_pspeu_09251548();
        D_pspeu_09295E08 = 0x10;
        think_step = 0x17;
        break;
    case 23:
        if (!--D_pspeu_09295E08) {
            think_step = 2;
            func_pspeu_09251A28(subweaponIdx, 0);
        }
        break;
    case 21:
        if (MARIA.step == 0) {
            D_pspeu_09295E00 = 0x40;
        }
        break;
    case 24:
        g_Maria.padSim = move_dir;
        if (!--D_pspeu_09295DC0) {
            think_step = 0;
        }
        break;
    case 25:
        func_pspeu_09251658(4, 0x1A, 0x3C);
        break;
    case 26:
        func_pspeu_09251780(0x1B);
        break;
    case 27:
        func_pspeu_09251698(4, 0x1C, 0x23, SFX_VO_MAR_8EB + MAR_SFX_OFFSET);
        break;
    case 28:
        func_pspeu_09251780(0x1D);
        break;
    case 29:
        func_pspeu_09251698(4, 0x1E, 0x23, 0);
        break;
    case 30:
        func_pspeu_09251780(0x1F);
        break;
    case 31:
        func_pspeu_09251698(4, 0x20, 0x37, 0);
        break;
    case 32:
        func_pspeu_09251780(0x21);
        break;
    case 33:
        func_pspeu_09251698(2, 0x22, 0x3C, 0);
        break;
    case 34:
        func_pspeu_09251780(0x23);
        break;
    case 35:
        func_pspeu_09251698(1, 0x24, 0x78, 0);
        break;
    case 36:
        func_pspeu_09251780(0);
        break;
    case 37:
        func_pspeu_09251658(4, 0x26, 0x55);
        break;
    case 38:
        func_pspeu_09251780(0x27);
        break;
    case 39:
        func_pspeu_09251698(2, 0x28, 0x12, SFX_VO_MAR_8E9 + MAR_SFX_OFFSET);
        break;
    case 40:
        func_pspeu_09251780(0x29);
        break;
    case 41:
        if (distance_to_player_x > 0x55) {
            func_pspeu_09251698(4, 0x2A, 0x5A, 0);
        } else {
            D_pspeu_09295E08 = 0x28;
            think_step = 0x2A;
        }
        break;
    case 42:
        func_pspeu_09251780(0);
        break;
    case 43:
        func_pspeu_09251700(0, 0x2C, 0x5A);
        break;
    case 44:
        func_pspeu_09251780(0x2D);
        break;
    case 45:
        if (rand() & 1) {
            D_pspeu_09295E08 = 0x40;
            think_step = 3;
        } else {
            g_Maria.padSim |= 0x4000;
            D_pspeu_09295E08 = 0x13;
            think_step = 0xB;
        }
        break;
    }
}

void EntityUnused(Entity* self);

void EntityMaria(Entity* self) {
    Entity* entity = self;
    self = &MARIA;
    if (g_PlayableCharacter != PLAYER_ALUCARD) {
        DestroyEntity(self);
        return;
    }

    if (g_CastleFlags[INVERTED_CASTLE_UNLOCKED]) {
        DestroyEntity(self);
        return;
    }

    if (!self->ext.factory.paramsBase) {
        if (g_CastleFlags[MET_MARIA_IN_CEN]) {
            metMaria = true;
            InitializeEntity(g_EInitSpawner);
            self->flags = FLAG_POS_CAMERA_LOCKED;
            self->animSet = ANIMSET_EN_MARIA;
            self->animCurFrame = 0xA;
            self->unk5A = 0x48;
            self->palette = 0x210;
            self->zPriority = 0x80;
            D_pspeu_09295DB0 = 4;
            D_pspeu_09295DA0 = 0;
        } else {
            MarInit(0);
        }
        self->ext.factory.paramsBase = 1;
    }

    if (metMaria) {
        EntityUnused(self);
        return;
    }

    if (!self->ext.factory.incParamsKind && (g_CutsceneFlags & 0x10)) {
        if (!(cutscene_flags & 0x10)) {
            think_step = 0;
            self->ext.factory.incParamsKind = 1;
        }
    } else if (!self->ext.factory.incParamsKind) {
        g_Maria.demo_timer = 2;
        g_Maria.padSim = PAD_NONE;
        subweaponIdx = 0;
        think_step = 0x15;
        D_pspeu_09295E18 = 0;
    }

    if (D_psp_091CE570 != 0) {
        LoadMariaImage();
        LoadOwlImage();
        LoadTurtleImage();
        LoadCatImage();
        LoadCardinalImage();
        LoadDragonImage();
        LoadDollImage();
    }

    func_pspeu_092521E8();
    MarMain();
    MarUpdatePlayerEntities();

    g_Maria.unk6C = g_Maria.unk6A;
    cutscene_flags = g_CutsceneFlags;
}

void EntityUnused(Entity* self) {}

static void MarSetSfx(s32 sfxId) { sfx = sfxId; }

s32 MarGetSfx(void) { return sfx; }
