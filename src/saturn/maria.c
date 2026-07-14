// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "richter.h"

INCLUDE_ASM("asm/saturn/maria/data", d60A5000, d_060A5000);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A5060, func_060A5060);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A5154, func_060A5154);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A5208, func_060A5208);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A54F0, func_060A54F0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A5884, func_060A5884);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A59A8, func_060A59A8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A5AD4, func_060A5AD4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A5BE8, func_060A5BE8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A6624, func_060A6624);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A66C8, func_060A66C8);

enum MariaInputChecks {
    CHECK_GROUND = 1,
    CHECK_FALL = 4,
    CHECK_FACING = 8,
    CHECK_JUMP = 0x10,
    CHECK_CRASH = 0x40,
    CHECK_80 = 0x80,
    CHECK_GRAVITY_HIT = 0x200,
    CHECK_ATTACK = 0x1000,
    CHECK_CROUCH = 0x2000,
    CHECK_GRAVITY_FALL = 0x8000,
    CHECK_GRAVITY_JUMP = 0x10000,
    CHECK_GROUND_AFTER_HIT = 0x20000,
    CHECK_SLIDE = 0x40000,
    CHECK_UNK = 0x80000
};

extern int MariaCheckInput(s32 checks);
extern s32 MariaCheckFacing(void);

#define MariaSetSpeedX(speed)                                                  \
    do {                                                                       \
        s32 _tmp_speed = (speed);                                              \
        if (g_CurrentEntity->facingLeft == 1)                                  \
            _tmp_speed = -_tmp_speed;                                          \
        g_CurrentEntity->velocityX = _tmp_speed;                               \
    } while (0)

void MariaStepWalk(void) {
    // CHECK_UNK extra
    if (!MariaCheckInput(CHECK_UNK | CHECK_FALL | CHECK_FACING | CHECK_JUMP |
                         CHECK_CRASH | CHECK_ATTACK | CHECK_CROUCH)) {
        MariaDecelerateX(FIX(0.15625)); // altered
        if (MariaCheckFacing() == 0) {
            MariaSetStand(0);
            return;
        }
        if (PLAYER.step_s != 0) {
            if (PLAYER.step_s) {
            }
        } else {
            MariaSetSpeedX(FIX(1.59375)); // altered
        }
    }
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A6A94, func_060A6A94);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A6B90, func_060A6B90);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A70B4, func_060A70B4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A714C, func_060A714C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A7508, func_060A7508);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A75AC, func_060A75AC);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A7DF4, func_060A7DF4);
// function, splitter bugs
INCLUDE_ASM("asm/saturn/maria/data", d60A7F70, d_060A7F70);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8248, func_060A8248);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8308, func_060A8308);

// func_060A83C8
void RicStepHydrostorm(void) {
    if (PLAYER.poseTimer < 0) {
        RicSetStand(0);
        g_Player.unk46 = 0;
    }

    if ((g_Player.vram_flag & TOUCHING_GROUND) == 0) {
        RicSetFall();
        g_Player.unk46 = 0;
    }
}

// func_060A841C
void RicStepGenericSubwpnCrash(void) {
    if (g_Player.unk4E) {
        RicSetStand(0);
        g_Player.unk46 = 0;
    }

    if (!(g_Player.vram_flag & TOUCHING_GROUND)) {
        RicSetFall();
        g_Player.unk46 = 0;
    }
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8470, func_060A8470);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8534, func_060A8534);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8860, func_060A8860);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8A38, func_060A8A38);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8AE8, func_060A8AE8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8C14, func_060A8C14);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8E34, func_060A8E34);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8F2C, func_060A8F2C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9064, func_060A9064);

void func_060A9130(void) { func_060AA4BC(0xf0); }

AnimationFrame D_80155950[];
AnimationFrame D_8015591C[];
// func_060A8EB8
void MariaSetInit(s32 step_s) {
    PLAYER.step = PL_S_INIT;
    PLAYER.step_s = step_s;
    PLAYER.pose = PLAYER.poseTimer = 0;
    if (step_s & 1) {
        PLAYER.anim = D_80155950;
    } else {
        PLAYER.anim = D_8015591C;
    }
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9194, func_060A9194);

// func_060A9210
extern AnimationFrame ric_anim_stand[];
extern AnimationFrame ric_anim_stand_alt[];
// new alt animation
void RicSetStand(s32 velocityX) {
    PLAYER.velocityX = velocityX;
    PLAYER.velocityY = 0;
    g_Player.unk44 = 0;

    RicSetStep(PL_S_STAND);

    if (g_Player.vram_flag & IN_AIR_OR_EDGE)
        RicSetAnimation(ric_anim_stand_alt);
    else
        RicSetAnimation(ric_anim_stand);
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A926C, func_060A926C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9304, func_060A9304);

// _RicSetFall
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A939C, func_060A939C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9474, func_060A9474);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A955C, func_060A955C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9608, func_060A9608);

// func_060A96D4
static s32 MariaCheckSubwpnChainLimit(s16 subwpnId, s16 limit) {
    Entity* entity;
    s32 i;
    s32 nFound;
    s32 nEmpty;

    // Iterate through entities 32-48 (which hold subweapons)
    // Any that match the proposed ID increments the count.
    // If at any point the count reaches the limit, return -1.
    entity = &g_Entities[32];
    for (i = 0, nFound = 0, nEmpty = 0; i < 16; i++, entity++) {
        if (!entity->entityId) {
            nEmpty++;
        }
        if (entity->ext.subweapon.subweaponId &&
            entity->ext.subweapon.subweaponId == subwpnId) {
            nFound++;
        }
        if (nFound >= limit) {
            return -1;
        }
    }
    // This will indicate that there is an available entity slot
    // to hold the subweapon we're trying to spawn.
    // At the end, if this is zero, there are none available so return
    // -1 to indicate there is no room for the proposed subweapon.
    if (nEmpty) {
        return 0;
    }
    return -1;
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A973C, func_060A973C);

u8 d_060c1980[1];

int func_060A9958(int param_1) {
    int iVar2;

    iVar2 = (int)(char)d_060c1980[param_1];
    if (!(iVar2 <= g_Status.mp)) {
        iVar2 = 0;
    } else {
        g_Status.mp -= iVar2;
    }
    return iVar2;
}

const u32 pad_060a998c = 0xAAAAAAAB;

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9990, func_060A9990);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9BC4, func_060A9BC4);

s32 func_060A9CE8(void) {
    s32 pad[5];
    return 1;
}

void func_060A9CF8(void) { func_060AA4BC(0x16); }

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9D10, func_060A9D10);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9DA4, func_060A9DA4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9E40, func_060A9E40);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9EC4, func_060A9EC4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9F84, func_060A9F84);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA0A0, func_060AA0A0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA260, func_060AA260);

// RicSetStep
void func_060AA4BC(s16 step) {
    PLAYER.step = step;
    PLAYER.step_s = 0;
}

void RicSetAnimation(AnimationFrame* anim) {
    g_CurrentEntity->anim = anim;
    g_CurrentEntity->poseTimer = 0;
    g_CurrentEntity->pose = 0;
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA4FC, func_060AA4FC);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA608, func_060AA608);

// func_060AA754
void RicDecelerateX(s32 speed) {
    if (g_CurrentEntity->velocityX < 0) {
        g_CurrentEntity->velocityX += speed;
        if (g_CurrentEntity->velocityX > 0) {
            g_CurrentEntity->velocityX = 0;
        }
    } else {
        g_CurrentEntity->velocityX -= speed;
        if (g_CurrentEntity->velocityX < 0)
            g_CurrentEntity->velocityX = 0;
    }
}

// func_060AA784
void RicDecelerateY(s32 speed) {
    if (g_CurrentEntity->velocityY < 0) {
        g_CurrentEntity->velocityY += speed;
        if (g_CurrentEntity->velocityY > 0) {
            g_CurrentEntity->velocityY = 0;
        }
    } else {
        g_CurrentEntity->velocityY -= speed;
        if (g_CurrentEntity->velocityY < 0) {
            g_CurrentEntity->velocityY = 0;
        }
    }
}

// func_060AA7B4
s32 RicCheckFacing(void) {
    if (g_Player.unk44 & 2) {
        return 0;
    }

    if (PLAYER.facingLeft == 1) {
        if (g_Player.padPressed & PAD_RIGHT) {
            PLAYER.facingLeft = 0;
            g_Player.unk4C = 1;
            return -1;
        } else if (g_Player.padPressed & PAD_LEFT) {
            return 1;
        }
    } else {
        if (g_Player.padPressed & PAD_RIGHT) {
            return 1;
        }
        if (g_Player.padPressed & PAD_LEFT) {
            PLAYER.facingLeft = 1;
            g_Player.unk4C = 1;
            return -1;
        }
    }
    return 0;
}

// func_060AA830
int func_8015CAAC(s32 speed) {
    if (PLAYER.entityRoomIndex == 1)
        speed = -speed;
    PLAYER.velocityX = speed;
    return speed;
}

// func_060AA854
void RicSetInvincibilityFrames(s32 kind, s16 invincibilityFrames) {
    if (!kind) {
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x15), 0);
        if (g_Player.timers[PL_T_INVINCIBLE_SCENE] <= invincibilityFrames) {
            g_Player.timers[PL_T_INVINCIBLE_SCENE] = invincibilityFrames;
        }
    } else if (g_Player.timers[PL_T_INVINCIBLE] <= invincibilityFrames) {
        g_Player.timers[PL_T_INVINCIBLE] = invincibilityFrames;
    }
}

// DisableAfterImage

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA8AC, func_060AA8AC);

// func_060AA948
void func_8015CC28(void) {
    g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag =
        g_Entities[E_AFTERIMAGE_1].ext.afterImage.resetFlag =
            g_Entities[E_AFTERIMAGE_1].ext.afterImage.index =
                g_Entities[E_AFTERIMAGE_1].ext.afterImage.timer = 0;
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA974, func_060AA974);

s32 func_060aa608(u32, u32);
s32 d_060c37cc;
s32 d_060c28a0;
s32 d_0605c5c0[1];
s32* d_0605c6e0;
s32 d_060997f8;

void func_060AA9EC(void) {
    d_0605c6e0 = &d_060997f8;
    if (d_0605c5c0[0x28 / 4] == 4) {
        func_060aa608(&d_060c37cc, &d_060c28a0);
    }
}

s32 func_060AAA2C(void) {
    s32 ret = 0;

    if (g_Player.unk3FC > 300) {
        ret = 3;
    } else if (g_Player.unk3FC > 200) {
        ret = 2;
    } else if (g_Player.unk3FC > 100) {
        ret = 1;
    }

    return ret;
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AAA68, func_060AAA68);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AB088, func_060AB088);

extern Point32 g_RicSensorsCeiling[NUM_HORIZONTAL_SENSORS];
extern Point32 g_RicSensorsFloor[NUM_HORIZONTAL_SENSORS];
extern Point32 g_RicSensorsWall[NUM_VERTICAL_SENSORS * 2];

// func_060AB258
void RicGetPlayerSensor(Collider* col) {
    col->unk14 = g_RicSensorsWall[0].x;
    col->unk1C = g_RicSensorsWall[0].y;
    col->unk18 = g_RicSensorsFloor[1].y - FIX(1);
    col->unk20 = g_RicSensorsCeiling[1].y + FIX(1);
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AB294, func_060AB294);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AB6C4, func_060AB6C4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ABAA4, func_060ABAA4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ABC54, func_060ABC54);

#define E_NONE 0
// func_060AB980
static Entity* RicGetFreeEntity(s16 start, s16 end) {
    Entity* entity = &g_Entities[start];
    s16 i;

    for (i = start; i < end; i++, entity++) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

// func_060AB9C0
static Entity* RicGetFreeEntityReverse(s16 start, s16 end) {
    Entity* entity = &g_Entities[end - 1];
    s16 i;
    for (i = end - 1; i >= start; i--, entity--) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

#define LEN(x) ((s32)(sizeof(x) / sizeof(*(x))))
s32 D_80174F80[11];
// func_060ABA08
// extra loop vs. ric version
void func_8015F9F0(Entity* entity) {
    s32 i;
    s32 enemyId;
    if (entity < &g_Entities[32]) {
        for (i = 0;; i++) {
            for (enemyId = 3; enemyId < LEN(D_80174F80) - 4; enemyId++) {
                if (D_80174F80[enemyId] == i) {
                    D_80174F80[enemyId] = i + 1;
                    entity->enemyId = enemyId;
                    return;
                }
            }
        }
    } else {
        for (i = 0;; i++) {
            for (enemyId = 7; enemyId < LEN(D_80174F80); enemyId++) {
                if (D_80174F80[enemyId] == i) {
                    D_80174F80[enemyId] = i + 1;
                    entity->enemyId = enemyId;
                    return;
                }
            }
        }
    }
}

extern u8 D_80154674[][4];
extern u8 D_80174FAC;
extern u8 D_80174FB0;
extern u8 D_80174FB4;
extern u8 D_80174FB8;

// func_060ABEF8
void func_8015FA5C(s32 arg0) {
    D_80174FAC = D_80154674[arg0][0];
    D_80174FB0 = D_80154674[arg0][1];
    D_80174FB4 = D_80154674[arg0][2];
    D_80174FB8 = D_80154674[arg0][3];
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ABF40, func_060ABF40);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ABFF0, func_060ABFF0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AC09C, func_060AC09C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AC148, func_060AC148);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AC1FC, func_060AC1FC);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AC458, func_060AC458);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AC604, func_060AC604);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AC850, func_060AC850);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AC90C, func_060AC90C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AC9E0, func_060AC9E0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ACD98, func_060ACD98);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ACE84, func_060ACE84);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ACF8C, func_060ACF8C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AD048, func_060AD048);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AD0E8, func_060AD0E8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AD248, func_060AD248);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AD3A8, func_060AD3A8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AD7D8, func_060AD7D8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AE014, func_060AE014);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AE2C8, func_060AE2C8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AE3C0, func_060AE3C0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AE730, func_060AE730);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AE8D8, func_060AE8D8);

void func_060AEAB8() {}

#define E_WEAPON 0x10
#define STAGE_ENTITY_START 64

// func_060AEAC4
bool func_80162E9C(Entity* entity) {
    Entity* e;
    s32 i;
    s16 objId;
    s16 params;

    objId = entity->entityId;
    params = entity->params;
    for (e = &g_Entities[E_WEAPON], i = E_WEAPON; i < STAGE_ENTITY_START; e++,
        i++) {
        if (objId == e->entityId && params == e->params && e != entity) {
            return true;
        }
    }
    return false;
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AEB18, func_060AEB18);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AEFB4, func_060AEFB4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AF17C, func_060AF17C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AF444, func_060AF444);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AFAB4, func_060AFAB4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AFBA4, func_060AFBA4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B0220, func_060B0220);
// function, bugs
INCLUDE_ASM("asm/saturn/maria/data", d60B0474, d_060B0474);
// function, splitter bugs
INCLUDE_ASM_NO_ALIGN("asm/saturn/maria/data", d60B08DA, d_060B08DA);

void func_060B099C(Entity* self) { DestroyEntity(self); }

void func_060B09B4() {}

const u16 pad_60B09BC = 0;

s32 func_060B09C0() { return 0; }

const u16 pad_60B09C8 = 0;

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B09CC, func_060B09CC);
// function, splitter bugs
INCLUDE_ASM_NO_ALIGN("asm/saturn/maria/data", d60B1872, d_060B1872);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B18C8, func_060B18C8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B199C, func_060B199C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B1A58, func_060B1A58);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B1E78, func_060B1E78);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B2474, func_060B2474);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B2604, func_060B2604);

// func_060B295C
void MariaEntityCrashReboundStoneParticles(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->ext.subweapon.subweaponId = PL_W_CRASH_REBOUND_STONE;
        MariaSetSubweaponParams(entity);
        entity->hitboxWidth = 5;
        entity->hitboxHeight = 4;
        entity->step++;
        break;
    case 1:
        entity->ext.subweapon.timer++;
        if (entity->ext.subweapon.timer > 3) {
            DestroyEntity(entity);
        }
        break;
    }
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B29D4, func_060B29D4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B2F8C, func_060B2F8C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B2FC8, func_060B2FC8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B30BC, func_060B30BC);

void func_060B3678() {}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B3684, func_060B3684);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B382C, func_060B382C);

// func_060B4470
void MariaEntityStopwatchCrashLightning(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->ext.subweapon.subweaponId = PL_W_30;
        MariaSetSubweaponParams(entity);
        entity->hitboxWidth = 10;
        entity->hitboxHeight = 8;
        entity->step++;
        break;
    case 1:
        entity->ext.subweapon.timer++;
        if (entity->ext.subweapon.timer > 4) {
            DestroyEntity(entity);
        }
        break;
    }
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B44E8, func_060B44E8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B4598, func_060B4598);

void func_060B46A0(Entity* self) { DestroyEntity(self); }

// should be able to remove when next function is decompiled
const u16 pad_060B46B8 = 0xAAAA;
const u16 pad_060B46BA = 0xAAAB;

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B46BC, func_060B46BC);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B4B80, func_060B4B80);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B4CF4, func_060B4CF4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B5C3C, func_060B5C3C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B5E28, func_060B5E28);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B626C, func_060B626C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B668C, func_060B668C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B6C94, func_060B6C94);
// function, splitter bugs
INCLUDE_ASM_NO_ALIGN("asm/saturn/maria/data", d60B761E, d_060B761E);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B776C, func_060B776C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B7A48, func_060B7A48);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B7E08, func_060B7E08);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B7F50, func_060B7F50);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B805C, func_060B805C);

void func_060B82AC() {}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B82B8, func_060B82B8);
// function, splitter bugs
INCLUDE_ASM_NO_ALIGN("asm/saturn/maria/data", d60B8666, d_060B8666);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B868C, func_060B868C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B89F0, func_060B89F0);

#define EFFECT_UNK_0002 1 << 1

// func_060B8AC4
s32 func_8016840C(s32 y, s32 x) {
    Collider collider;
    s32 xShift;
    if (g_CurrentEntity->velocityX == 0) {
        return 0;
    }
    CheckCollision(g_CurrentEntity->posX.val + x, g_CurrentEntity->posY.val + y,
                   &collider, 0);
    if (g_CurrentEntity->velocityX > 0) {
        xShift = collider.unk14;
    } else {
        xShift = collider.unk1C;
    }
    if (collider.effects & EFFECT_UNK_0002) {
        g_CurrentEntity->posX.val += xShift;
        return 2;
    }
    return 0;
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B8B24, func_060B8B24);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B9048, func_060B9048);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B9404, func_060B9404);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B96C0, func_060B96C0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B99A8, func_060B99A8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B9B88, func_060B9B88);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B9D88, func_060B9D88);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B9FE0, func_060B9FE0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BA148, func_060BA148);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BA32C, func_060BA32C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BA4BC, func_060BA4BC);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BA6E8, func_060BA6E8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BA914, func_060BA914);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BABE0, func_060BABE0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BAC78, func_060BAC78);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BADA8, func_060BADA8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BAFF0, func_060BAFF0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BB334, func_060BB334);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BB6E8, func_060BB6E8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BB724, func_060BB724);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BB868, func_060BB868);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BBEF8, func_060BBEF8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BC024, func_060BC024);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BC0F4, func_060BC0F4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BC23C, func_060BC23C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BC320, func_060BC320);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BCBD8, func_060BCBD8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BCCE8, func_060BCCE8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BCFF4, func_060BCFF4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BD0D0, func_060BD0D0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BD150, func_060BD150);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BD244, func_060BD244);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BD474, func_060BD474);

void func_060BB330();

s32 DAT_060c4118;
s32 DAT_060c411c;

void func_060BACA4(void) {
    memset(&DAT_060c4118, 0, 4);
    memcpy(0x002B2000, &DAT_060c411c, 0x9600);

    func_060BB330();
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BD638, func_060BD638);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BD81C, func_060BD81C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BD9E8, func_060BD9E8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BDAD0, func_060BDAD0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BDC7C, func_060BDC7C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BDDA0, func_060BDDA0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BDED8, func_060BDED8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE064, func_060BE064);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE258, func_060BE258);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE308, func_060BE308);

s32 d_06086390;
s32 d_060476A0;
s32 d_060476A4;
s32 d_060cd748;
s32 d_060cd74c;
void func_060BB9BC(s32*);
s32* func_060784A8();

void func_060BBA88(void) {
    s32* iVar2;
    iVar2 = func_060784A8();
    func_060BB9BC(iVar2);
    d_060476A0 = d_060cd748;
    d_060476A4 = d_060cd74c;
}

// same sequence of funcs as in richter

s32 d_06086390;
void func_060BE414(void) {
    s32* iVar2;
    d_06086390 = 0;
    iVar2 = func_060784A8();
    iVar2[0x4500] = 0xffffffff;
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE440, func_060BE440);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE54C, func_060BE54C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE618, func_060BE618);

void func_060BE6D4(void) {
    int* iVar2;
    d_06086390 = 4;
    iVar2 = func_060784A8();
    iVar2[0x4500] = 0xffffffff;
}

void func_060BE700(void) {
    int* iVar2;
    d_06086390 = 5;
    iVar2 = func_060784A8();
    iVar2[0x4500] = 0xffffffff;
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE72C, func_060BE72C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE854, func_060BE854);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE994, func_060BE994);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BEA54, func_060BEA54);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BEB74, func_060BEB74);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BEE30, func_060BEE30);

s16 PTR_DAT_060bf174[1];
void func_060BF0F4(u32 param_1) {
    int first;
    int cur;
    int offset;
    int i;
    u8* ptr;

    if (param_1 == 6)
        offset = 0x28;
    else if (param_1 & 1)
        offset = 0x28;
    else
        offset = 0;

    first = PTR_DAT_060bf174[param_1];

    for (cur = first; cur < first + 4; cur++) {
        int tile = cur << 6;

        ptr = (u8*)tile;
        ptr += (u32)0x25E58000 + offset;

        for (i = 0; i < 0x20; i++)
            *ptr++ = 0;

        if (offset == 0x28) {
            ptr = (u8*)(0x25E58800 + tile);

            for (i = 0; i < 0x10; i++)
                *ptr++ = 0;
        }
    }
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BF180, func_060BF180);

struct Unk0605cd70 {
    u16 unk0;
    u16 unk2;
    u32 unk4;
    u32 unk8;
};

struct Unk0605cd70 d_0605cd70;
u32 d_06085534;
u16 d_0605c672;
u8 d_06057f68;

s32 func_060732E4(u16);
void func_060BF180(void);

void func_060BF35C(void) {
    if (d_0605cd70.unk8 != 0) {
        if (d_0605cd70.unk8 == 1) {
            goto after;
        }
        return;
    } else {
        func_060732E4(d_0605cd70.unk0);
        d_0605cd70.unk8 += 1;
    }
after:
    if ((d_06057f68 == 0) && ((d_0605c672 & 0x100) != 0)) {
        d_06085534 = 6;
        d_06057f68 = 4;
    }
    func_060BF180();
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BF3D0, func_060BF3D0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BF704, func_060BF704);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BF7B0, func_060BF7B0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BFA68, func_060BFA68);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BFBF8, func_060BFBF8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BFD24, func_060BFD24);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BFE38, func_060BFE38);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BFECC, func_060BFECC);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60C00B4, func_060C00B4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60C0428, func_060C0428);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60C0920, func_060C0920);

u32* d_06086234;
u32* d_06086250;
u32* d_0605D784;

void func_060C0A5C(void) {
    if (d_06086234 == 0) {
        memset((void*)0x25e58288, 0, 0xC);
        memset((void*)0x25e582C8, 0, 0xC);
    }

    if (d_06086250 == 0) {
        memset((void*)0x25e58348, 0, 0xC);
        memset((void*)0x25e58388, 0, 0xC);
    }

    if (d_0605D784 == 0) {
        memset((void*)0x25e584C8, 0, 0x10);
        memset((void*)0x25e58508, 0, 0x10);
    }
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60C0AE4, func_060C0AE4);
INCLUDE_ASM("asm/saturn/maria/data", d60C16B8, d_060C16B8);
