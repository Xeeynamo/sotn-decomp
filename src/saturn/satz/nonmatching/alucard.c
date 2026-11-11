// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stdint.h>
#include <string.h>
#include "../../alucard.h"
#define _SPR2_
#include "../../lib/spr/spr.h"
#include "../../zero/overlay.h"

s32 rcos(s32 angle);
s32 rsin(s32 angle);

#define s_CapePalette g_AlucardPaletteVariants[3]
#define DAT_060C8594 g_AlucardPaletteVariants[4]
extern s16 g_AlucardPaletteWork[6];
#define DAT_060C85B4 g_AlucardPaletteWork[0]
#define DAT_060C85B6 g_AlucardPaletteWork[1]
#define DAT_060C85B8 g_AlucardPaletteWork[2]
#define DAT_060C85BA g_AlucardPaletteWork[3]
#define DAT_060C85BC g_AlucardPaletteWork[4]
#define DAT_060C85BE g_AlucardPaletteWork[5]
extern const u16 DAT_060AF1AC[];
void func_060AF050(u16* palette);

#define CLOAK_TWILIGHT 0x39
#define CLOAK_RAINBOW 0x34
#define CLOAK_GLARING 0x35

extern s32 DAT_060CEB14;

EntryS060CE980 DAT_060CE8F0[8];

extern SaturnSpriteFrameHeader* AlucardSubFrames[];
extern const SaturnAnimationFrame* g_AlucardAnimationTable[];
extern s16* g_AlucardEffectSpriteMetadataTable[];
extern void* g_AlucardResidualAnimationTable[];
extern void* g_AlucardAnimationCommandTable[];
void func_060AF124(s32);
void func_060AC2F0(void);

extern s32 DAT_060CE7F0[32], DAT_060CE870[32];
void func_060A56AC(s32);
void func_060A6688(s32);
void func_060A7D3C(void);
void func_060AF550(void);

extern s16 DAT_060CE970, DAT_060CE974;
u32 CheckAndDoLevelUp(void);
bool IsRelicActive(s32 relicId);
s32 HandleTransformationMP(s32 form, s32 mode);
s32 func_060B0584(void);
s32 func_060AF8E0(void);
void func_060AF7F0(void);
void func_060B0638(void);
void func_060B0310(void);
void func_060AEEE4(void);
void func_060AC574(void);
void func_060ACF00(s32);
void func_060AC8F4(void);
void func_060ACB6C(void);
void func_060AF4B8(void);

void func_060AA0FC(void);

s32 HandleDamage(DamageParam* damage, s32 arg1, s32 amount);
extern DamageParam DAT_060CE7E0;

s32 func_060AE048(void);
s32 func_060AE184(void);
s32 func_060AE284(void);
s32 func_060AE6F4(void);
s32 func_060AE8E4(void);
s32 func_060AEAE8(void);
s32 func_060AECC4(void);
s32 func_060AE544(void);
s32 func_060AE36C(void);

#define COMBO_COMPLETE 0xFF
extern u16 DAT_060CE498;
s32 HandleGravityBootsMP(s32 mode);
void func_060A5D50(void);

extern u16 DAT_060CE49A;
extern s32 DAT_060CE49C;
s32 CastSpell(s32 spellId);
void LearnSpell(s32 spellId);
void func_060A5EA8(void);

extern s32 DAT_060CE4A0, DAT_060CE4A4;
void func_060A5F9C(void);
void func_060A605C(void);

extern s32 DAT_060CE4A8, DAT_060CE4AC;
void func_060A60EC(void);
void func_060A61B0(void);
void func_060A6248(void);

void func_060A81DC(void), func_060A9658(void), func_060A96A0(void),
    func_060A8DF4(void), func_060A8D78(void);
void func_060A972C(void), func_060AA23C(void), func_060AADE4(void),
    func_060AB814(void), func_060ABCF0(void);
void func_060B5C68(void), func_060B5920(void), func_060A9E3C(void),
    func_060ABFA4(void), func_060B9130(void);
void func_060B8F68(void), func_060AC0C8(void), func_060AB090(void),
    func_060AB0E8(void), func_060AB0BC(void);
void func_060AB308(void), func_060AB37C(void), func_060AB4A4(void),
    func_060AB558(void), func_060AB590(void);
void func_060B8FE0(void), func_060AB5E0(void), func_060AD524(void),
    func_060AD714(void);
void func_060B7BB4(DamageParam*, s16, s16);

void func_060B86F4(s32);

void func_060A7DD0(void);

extern s32 DAT_0605CA40;
extern u8 g_AlucardAnimationFrameMap[32];
#define DAT_060C891B (g_AlucardAnimationFrameMap - 0x41)

s32 func_060A69F4(void);
s32 func_060A67B8(void);
void func_060A5CD8(void);
void func_060A5E14(void);
void func_060A5938(void);

extern s32 g_AlucardSensorsFloorBat[4], g_AlucardSensorsCeilingBat[4],
    g_AlucardSensorsWallBat[7];
extern s32 g_AlucardSensorsFloorDefault[4], g_AlucardSensorsCeilingCrouch[4],
    g_AlucardSensorsWallCrouch[7];
extern s32 g_AlucardSensorsCeilingDefault[4], g_AlucardSensorsWallDefault[7];
void func_060B3024(void);
void func_060B349C(void);
void func_060B38B4(void);
void func_060B3A90(void);

void func_0600B12C(SpriteObject* dst, SpriteObject* src);
void func_0600AA18(s32);
void func_0600B104(SpritePart* part, s32 arg1, s32 count);
void SetParts(SpritePart* part, SaturnSpritePart* src, s32 count);

#define AFTER(i) ((SpriteObject*)DAT_060CEA80[i].unk4)
#define BODY ((SpriteObject*)DAT_060CE8F0[0].unk4)

extern u8 DAT_060CE4B3;
#define DAT_060C8588 g_AlucardPaletteVariants[3][10]

extern PfnEntityUpdate g_AlucardEntityFunctions[];
extern FrameProperty D_060CC9B8;
extern s8 D_060CC9F5, D_060CC9F6, D_060CC9F7;
#define g_AlucardMiscFrameProperties (&D_060CC9B8)
s32 func_060C175C(s8* frameProps, AnimationFrame** anims);
void func_800EA5AC(u16, u8, u8, u8);

typedef struct {
    s16 timer;
    s16 alpha;
    s16 scaleX;
    s16 scaleY;
    s16 spin;
} AluRingExt;
#define ALU_RING(e) ((AluRingExt*)&(e)->ext)

s32 AllocPrimitives(s32 type, s32 count);
extern const u8 pad_060BFAF4[];
extern s16 g_AlucardEffectAngles[];
extern s32 DAT_060CE5B4;

extern SaturnSpriteFrameHeader* DAT_060CE560;
extern s32 DAT_060CE564;
extern SaturnSpriteImage* DAT_060CE568;
extern SubweaponDef g_AlucardSubweaponDefs[];

typedef struct {
    u8 pad78[4];
    s16 timer;
    s16 angle;
    u8 pad80[6];
    s16 angleSpeed;
    u8 pad88[4];
    s16 strength;
    u8 pad8E[6];
    s16 wobble;
    s16 unk96;
    s16 wobbleAngle;
} AluBlinkExt;
#define ALU_BLINK(e) ((AluBlinkExt*)&(e)->ext)

typedef struct {
    s16 r, g, b, unk6, unk8;
} AluColorBlend;
extern AluColorBlend g_AlucardColorBlendConfigs[];

typedef struct {
    u8 pad78[4];
    s16 timer;
    u8 pad7E[0xE];
    s16 alpha;
} AluGlowExt;
#define ALU_GLOW(e) ((AluGlowExt*)&(e)->ext)

void func_060A56E4(s32 arg0, s32 velocityX);

extern AnimationFrame g_AlucardUnknownAnim11[], g_AlucardUnknownAnim12[];

typedef struct AluParticle {
    s16 type;
    s16 delay;
    s32 posX;
    s32 posY;
    s32 velX;
    s32 velY;
    s16 timer;
    u8 w;
    u8 h;
    u8 r, g, b;
    u8 pad1B;
    u16 pad1C;
    u16 drawMode;
    struct AluParticle* next;
} AluParticle;

static s32 sh2_div(s32 a, s32 b);

static void land(s32 vx);

static void set_anim(s32 anim);

static void hide_after_images(void);

static void sit_down(void);

static s32 pressing_back(void);
static void satz_chair(void);

void func_060A81DC(void);
void func_060A8DF4(void);

void func_060A972C(void);
void func_060AC0C8(void);

static void set_sensors(const s32* floor, const s32* ceiling, const s32* wall);
void func_060AD524(void);
void func_060AD714(void);
void func_060ADDDC(void);

static s32 combo_step(ButtonComboState* c, s32 ok, s16 timer, s16 next);

static s32 cast(
    ButtonComboState* c, s32 spell, void (*start)(void), s32 crouching);

static u16 rgb(s32 r, s32 g, s32 b);
static s32 can_transform(u16 step, u16 step_s, s32 bat);

static s32 arena_room(void);

static void wall_push(u32 flag, s32 dx);

static Entity* first_free(s32 start, s32 end);
void func_060BB070(Entity* self);

static u16 subweapon_def_a(SubweaponDef* d);
void func_060BBF5C(Primitive* prim);

static s32 colour_channel(s32 strength, s32 diff, s32 div);
void func_060BC01C(Entity* self);

static void glow_scale(Entity* self, s16 alpha, s16 grow);
void func_060BCD98(Entity* self);

void func_060BFB2C(Entity* self);

static PfnEntityUpdate player_entity_function(u16 id);

static s32 sh2_div(s32 a, s32 b) { return b ? a / b : 0; }

static void land(s32 vx) {
    s32 speed = vx < 0 ? -vx : vx;

    if (speed > 0x20000) {
        PlaySfx(0x647);
        func_060BAF44(g_CurrentEntity, 0, 0);
        func_060A580C(vx);
    } else {
        PlaySfx(0x64C);
        func_060A580C(0);
    }
}

s32 func_060A50E0(s32 checks) {
    s32 accel = 0;
    u16 b;

    if ((checks & 8) && !g_Player.unk46) {
        func_060A5060();
    }
    if (checks & 0x8000) {
        accel = 0x2C00;
    }
    if (checks & 0x10000) {
        accel = 0x2C00;
        if ((u32)(g_Entities[0].velocityY + 0x1FFF) <= 0x7FFE &&
            !(g_Player.unk44 & 0x20) && (g_Player.padPressed & 0x100)) {
            accel = 0x8CC;
        }
    }
    if (checks & 0x200) {
        accel = 0x2C00;
        if ((u32)(g_Entities[0].velocityY + 0x1FFF) <= 0x7FFE) {
            accel = 0x1600;
        }
    }
    if (g_unkGraphicsStruct.D_80097448 > 0x28) {
        accel /= 4;
    }
    g_Entities[0].velocityY += accel;
    if (g_Entities[0].velocityY > 0x70000) {
        g_Entities[0].velocityY = 0x70000;
    }
    if (g_Entities[0].velocityY >= 0) {
        if ((checks & 1) && (g_Player.vram_flag & 1)) {
            if (g_Player.unk46) {
                if ((g_Player.unk46 & 0x7FFF) == 0xFF) {
                    func_060A580C(0);
                    func_060A7D3C();
                    PlaySfx(0x64C);
                    return 1;
                }
                if (g_Entities[0].velocityY > 0x6E000) {
                    func_060A56E4(1, 0);
                    func_060BAF44(g_CurrentEntity, 0, 0);
                } else if (g_Player.unk44 & 0x10) {
                    if ((g_Player.unk44 & 0x200) && IsRelicActive(0x1E)) {
                        func_060A5938();
                    } else {
                        func_060A59E0(1);
                    }
                } else {
                    func_060A580C(0);
                }
                func_060A7D3C();
                return 1;
            }
            if (g_Entities[0].velocityY > 0x6E000) {
                if (g_Entities[0].step_s == 0x70 || g_Entities[0].step == 4) {
                    func_060A56E4(3, g_Entities[0].velocityX / 2);
                } else {
                    func_060A56E4(1, 0);
                }
                PlaySfx(0x647);
                func_060BAF44(g_CurrentEntity, 0, 0);
                return 1;
            }
            if (g_Player.unk44 & 0x10) {
                if ((g_Player.unk44 & 0x200) && IsRelicActive(0x1E)) {
                    func_060A5938();
                } else {
                    func_060A59E0(1);
                }
                PlaySfx(0x64C);
                return 1;
            }
            land(g_Entities[0].velocityX);
            return 1;
        }
        if ((checks & 0x20000) && (g_Player.vram_flag & 1)) {
            func_060A56E4(3, g_Entities[0].velocityX);
            PlaySfx(0x647);
            func_060BAF44(g_CurrentEntity, 0, 0);
            return 1;
        }
    }
    if ((checks & 4) && !(g_Player.vram_flag & 1)) {
        func_060A5AF0();
        return 1;
    }
    if (checks & 0x1000) {
        if ((g_Player.padPressed & 0x600) && func_060A69F4()) {
            return 1;
        }
        if ((g_Player.padTapped & 8) && func_060A67B8()) {
            return 1;
        }
    }
    if (g_Player.unk46 & 0x8000) {
        return 0;
    }
    if ((checks & 0x10) && (g_Player.padTapped & 0x100)) {
        func_060A5B94(1);
        return 1;
    }
    if ((checks & 0x20) && IsRelicActive(0xD) && (g_Player.padTapped & 0x100) &&
        !(g_Player.unk44 & 1)) {
        func_060A5CD8();
        return 1;
    }
    if ((checks & 0x2000) && (g_Player.padPressed & 0x2000)) {
        func_060A56E4(2, 0);
        return 1;
    }
    if ((checks & 0x40000) && g_Player.anim != 0xBC) {
        b = (g_Player.unk46 & 0x7FFF) ? g_Player.padPressed
                                      : g_Player.padTapped;
        if (b & 0x80) {
            func_060A5E14();
            return 1;
        }
    }
    return 0;
}

void func_060A580C(s32 velocityX) {
    s32 atLedge = ((u32)g_Player.vram_flag & 0x20) ? 1 : 0;
    s32 anim = -1;
    s32 speed;

    g_Entities[0].velocityX = velocityX;
    g_Entities[0].velocityY = 0;
    g_Entities[0].step = 0;
    g_Entities[0].step_s = 0;
    if (g_Player.unk48) {
        g_Entities[0].step_s = 2;
        atLedge = 0;
    }
    switch (g_Player.unk320) {
    case 1:
        if (g_Player.anim == 5) {
            anim = atLedge ? 3 : 2;
        } else if (g_Player.anim == 7) {
            g_Player.anim = atLedge ? 10 : 9;
        } else {
            anim = atLedge ? 1 : 12;
        }
        break;
    case 3:
    case 4:
        speed = g_Entities[0].velocityX < 0 ? -g_Entities[0].velocityX
                                            : g_Entities[0].velocityX;
        if (speed > 0x28000) {
            anim = atLedge ? 13 : 12;
        } else {
            anim = atLedge ? 24 : 23;
        }
        break;
    case 9:
        anim = 12;
        break;
    case 19:
        anim = atLedge ? 1 : 12;
        break;
    default:
        anim = atLedge ? 1 : 2;
        break;
    }
    if (anim >= 0) {
        g_Player.unk39D = (g_Player.unk39D & 0x9F) | 0x10;
        g_Player.anim = anim;
        g_Player.poseTimer = 0;
        g_Player.pose = 0;
    }
}

static void set_anim(s32 anim) {
    g_Player.unk39D = (g_Player.unk39D & 0x9F) | 0x10;
    g_Player.anim = anim;
    g_Player.poseTimer = 0;
    g_Player.pose = 0;
}

void func_060A59E0(s32 keepAnim) {
    if (g_Player.unk3E8 && !g_Player.runDisable && IsRelicActive(0x1E)) {
        func_060A5938();
        return;
    }
    g_Player.unk3E8 = 12;
    g_Entities[0].velocityX =
        g_Entities[0].facingLeft == 1 ? -0x1E000 : 0x1E000;
    g_Entities[0].velocityY = 0;
    g_Entities[0].step = 1;
    g_Entities[0].step_s = 0;
    if (keepAnim) {
        if (g_Player.anim != 0xB) {
            set_anim(0xB);
        }
    } else {
        func_060BAF44(g_CurrentEntity, 0x50001, 0);
        set_anim(g_Player.unk4C ? 7 : 5);
    }
    if (g_Player.unk320 == 2) {
        g_Player.poseTimer = 4;
    }
}

void func_060A5AF0(void) {
    g_Entities[0].step = 3;
    g_Entities[0].step_s = 0;
    g_Player.unk39D = (g_Player.unk39D & 0x9F) | 0x10;
    g_Player.anim = 0xC3;
    g_Player.poseTimer = 0;
    g_Player.pose = 0;
    if (g_Player.unk320 != 0x13) {
        g_Entities[0].velocityX = 0;
    }
    g_Entities[0].velocityY = 0x20000;
    g_Player.unk3E8 = 0;
    g_Player.timers[6] = 8;
    g_Player.timers[5] = (g_Player.unk04 & 1) ? 8 : 0;
    g_Player.unk44 = 0x10;
}

static void hide_after_images(void) {
    u16 i;

    g_Player.unk39C = 0xFF;
    if (DAT_060CEA80[0].unk8 == (AnimationFrame*)AlucardFrames) {
        for (i = 0; i < 6; i++) {
            *DAT_060CEA80[i].unk4 = 0;
        }
    }
    g_Player.timers[15] = 8;
}

static void sit_down(void) {
    switch ((s32)g_Player.unk14) {
    case 1:
        func_060A5674(0xD8);
        g_Entities[0].facingLeft = 0;
        break;
    case 2:
        func_060A5674(0xD8);
        g_Entities[0].facingLeft = 1;
        break;
    case 3:
        func_060A5674(0xD9);
        g_Entities[0].facingLeft = 0;
        break;
    default:
        func_060A5674(0xD9);
        g_Entities[0].facingLeft = 1;
        break;
    }
    g_Entities[0].step_s = 4;
    D_060C84E4 = 0x1800;
}

int ReduceWeapon(s32 hand);

s32 func_0606FC80(SubweaponDef* subwpn, s16 subweaponId, s16 useHearts);
void func_060C1618(Entity* self);

static void alu_attack_voice(void) {
    s16 sfx[4] = {0x708, 0x709, 0x70A, 0x70B};
    u32 r = (MTH_GetRand() >> 7) & 3;

    if (r <= 3) {
        PlaySfx(sfx[r]);
    }
}

static void alu_attack_pose(Equipment* item, s32 anim) {
    set_anim(anim);
    g_Player.unk46 = (u8)item->unk10 + 0x8001;
    g_Player.unk54 = item->lockDuration;
    PLAYER.step_s = (u8)item->unk10 + 0x40;
    g_Player.timers[9] = 4;
}

s32 func_060A6420(void) {
    SubweaponDef sub;
    s32 atLedge = 0, i, nFound, nEmpty, r;
    s16 id;
    Entity* e;

    if (!(g_Player.padPressed & 0x1000)) {
        return 1;
    }
    if (g_Player.vram_flag & 0x20) {
        atLedge = 1;
    }
    id = func_0606FC80(&sub, 0, 0);
    if (!id) {
        return 1;
    }
    if (id == 6 && g_unkGraphicsStruct.pauseEnemies) {
        return 4;
    }
    e = &g_Entities[32];
    for (i = 0, nFound = 0, nEmpty = 0;;) {
        s16 other = e->ext.factory.argHigh;
        if (!e->entityId) {
            nEmpty++;
        }
        if (other && other == id) {
            nFound++;
        }
        i++;
        if (nFound >= sub.chainLimit) {
            r = -1;
            break;
        }
        e++;
        if (i > 15) {
            r = nEmpty ? 0 : -1;
            break;
        }
    }
    if (r < 0) {
        return 2;
    }
    id = func_0606FC80(&sub, 0, 1);
    if (!id) {
        return 3;
    }
    func_060BAF44(g_CurrentEntity, sub.blueprintNum, (s16)(id << 9));
    g_Player.timers[10] = 4;
    if (PLAYER.step_s < 0x40) {
        if (PLAYER.step == 0) {
            set_anim(sub.anim + atLedge);
        }
        alu_attack_voice();
    }
    return 0;
}

void func_060A6688(s32 arg0) {
    PLAYER.step = 0x12;
    PLAYER.step_s = arg0;
    set_anim(arg0 & 1 ? 0xD7 : 0xD6);
    g_Player.padSim = 0;
    g_Player.demo_timer = 8;
    if (!arg0) {
        g_pads[0].pressed = 0;
    }
}

Entity* func_060A66FC(Equipment* item, s32 hand) {
    s32 equipId = g_Status.equipment[hand];
    Entity* e;
    s32 i;

    if (item->unk14 == 0x14) {
        if (PLAYER.step <= 1 || PLAYER.step == 0x13 || PLAYER.step == 2) {
            func_060A6688(0);
            ReduceWeapon(hand);
            return &g_Entities[0];
        }
        return NULL;
    }
    for (e = &g_Entities[32], i = 32; i < 64; i++, e++) {
        if (e->entityId == 0x27) {
            return NULL;
        }
    }
    return func_060BAF44(
        g_CurrentEntity, (((item->unk14 & 0x7F) + hand * 0x80) << 16) + 0x37,
        (s16)equipId);
}

s32 func_060A67B8(void) {
    s32 atLedge = (g_Player.vram_flag & 0x20) ? 1 : 0;
    s32 equipId = g_Status.equipment[2];
    Equipment* item = &g_EquipDefs[equipId];
    Entity* made = NULL;
    Entity* e;
    s32 anim;
    s32 n;
    s32 i;

    for (e = &g_Entities[16], i = 16, n = 0; i < 64; i++, e++) {
        if (e->ext.weapon.equipId == equipId && ++n >= item->chainLimit) {
            return 0;
        }
    }
    if (item->unk13 == 0x37) {
        made = func_060A66FC(item, 2);
        if (made == &g_Entities[0]) {
            return 1;
        }
        if (PLAYER.step_s < 0x40 && PLAYER.step == 0) {
            set_anim(item->playerAnim + atLedge);
        }
    } else if (item->unk13 == 0x80) {
        for (e = &g_Entities[32], i = 32, n = 0; i < 64; i++, e++) {
            if (e->entityId == 0x48) {
                n++;
            }
        }
        if (n > 1) {
            return 0;
        }
        made =
            func_060BAF44(g_CurrentEntity, ((item->unk14 & 0x7F) << 16) | 0x80,
                          (s16)g_Status.equipment[2]);
        if (PLAYER.step_s < 0x40) {
            anim = item->playerAnim;
            if (PLAYER.step == 0) {
                set_anim(anim + atLedge);
            } else if (PLAYER.step == 2) {
                if (g_Player.unk72) {
                    set_anim(anim + 2);
                } else if (PLAYER.step_s == 2) {
                    PLAYER.step = 0;
                    PLAYER.step_s = 0;
                    set_anim(anim + atLedge);
                } else {
                    set_anim(anim + 2);
                }
            }
        }
    }
    if (made == NULL) {
        return 0;
    }
    if (made != &g_Entities[0]) {
        ReduceWeapon(2);
    }
    return 1;
}

s32 func_060A69F4(void) {
    Equipment props;
    s32 both = 0, atLedge = 0, variant = 0;
    u32 buttons;
    s32 hand = 0, i, n, s;
    Equipment* item = NULL;
    u16 id = 0;
    s32 anim;
    Entity* ent;
    Entity* e;

    if (g_Player.vram_flag & 0x20) {
        atLedge = 1;
    }
    buttons = g_Player.padTapped & 0x600;
    if (buttons && !func_060A6420()) {
        return 1;
    }
    if (!g_Player.unk48) {
        if (GetEquipItemCategory(0) == 9 && (g_Player.padPressed & 0x400)) {
            buttons |= 0x400;
        }
        if (GetEquipItemCategory(1) == 9 && (g_Player.padPressed & 0x200)) {
            buttons |= 0x200;
        }
    }
    switch (buttons) {
    case 0:
        return 0;
    case 0x200:
        hand = 1;
        g_Player.D_80072EF8 = 0x200;
        break;
    case 0x400:
        hand = 0;
        g_Player.D_80072EF8 = 0x400;
        break;
    case 0x600:
        if (!g_Player.unk72 && D_8013AEE4) {
            s = (u16)D_8013AEE4;
            if (s) {
                item = &g_EquipDefs[s];
                id = s;
            }
            g_Player.D_80072EF8 = 0x400;
            hand = (D_8013AEE4 & 0x80000000) ? 1 : 0;
            if (func_060A637C(id, hand) >= 0 &&
                !HasEnoughMp(g_EquipDefs[id].mpUsage, 0)) {
                both = 1;
                goto make;
            }
        }
        g_Player.D_80072EF8 = 0x400;
        hand = 0;
        break;
    }
    item = &g_EquipDefs[g_Status.equipment[hand]];
    id = g_Status.equipment[hand];
    if (item->unk17 == item->specialMove && item->unk17) {
        if (g_Entities[16].ext.weapon.equipId == id) {
            id = item->unk17;
            item = &g_EquipDefs[id];
            if (func_060A637C(id, hand) >= 0) {
                goto make;
            }
        } else if (g_Entities[16].ext.weapon.equipId == item->unk17 &&
                   func_060A637C(id, hand) >= 0) {
            goto make;
        }
    }
    if (DAT_060CE7A0[1].buttonsCorrect == COMBO_COMPLETE) {
        s = g_EquipDefs[g_Status.equipment[hand]].specialMove;
        if (s &&
            ((u16)g_Status.equipment[hand] != 0x11 ||
             (g_Player.vram_flag & 0x41) == 1) &&
            (g_Player.vram_flag & 1)) {
            id = s;
            item = &g_EquipDefs[s];
            if (func_060A637C(id, hand) >= 0 &&
                !HasEnoughMp(g_EquipDefs[id].mpUsage, 0)) {
                goto make;
            }
        }
    }
    if (DAT_060CE7A0[2].buttonsCorrect == COMBO_COMPLETE) {
        s = g_EquipDefs[g_Status.equipment[hand]].unk17;
        if (s) {
            id = s;
            item = &g_EquipDefs[s];
            if (func_060A637C(id, hand) >= 0) {
                goto make;
            }
        }
    }
    item = &g_EquipDefs[g_Status.equipment[hand]];
    id = g_Status.equipment[hand];
    if (func_060A637C(id, hand) < 0) {
        return 0;
    }
make:
    if (!id) {
        ent = func_060BAF44(g_CurrentEntity, (hand << 23) + 0x2A + hand, 0);
    } else if (item->unk13 == 0x37) {
        ent = func_060A66FC(item, hand);
        if (ent == &g_Entities[0]) {
            return 1;
        }
    } else if (item->unk13 == 0x80) {
        for (n = 0, e = &g_Entities[32], i = 32; i < 64; i++, e++) {
            if (e->entityId == 0x48) {
                n++;
            }
        }
        if (n > 1) {
            return 0;
        }
        ent = func_060BAF44(
            g_CurrentEntity, ((item->unk14 & 0x7F) << 16) | 0x80, (s16)id);
    } else if (g_Player.timers[1]) {
        func_060BAF44(g_CurrentEntity, 0x10039, 0);
        goto cursed;
    } else if (!both) {
        ent = func_060BAF44(g_CurrentEntity,
                            item->unk13 + ((hand + 1) << 12) +
                                (((item->unk14 & 0x7F) + (hand << 7)) << 16),
                            (s16)id);
    } else {
        ent = func_060BAF44(g_CurrentEntity,
                            item->unk13 + ((hand + 1) << 14) +
                                (((item->unk14 & 0x7F) + (hand << 7)) << 16),
                            (s16)id);
    }
    if (!ent) {
        return 0;
    }
    ReduceWeapon(hand);
    if (both) {
        ReduceWeapon((hand + 1) & 1);
    }
    HasEnoughMp(g_EquipDefs[id].mpUsage, 1);
    if (id == 0x61 && g_Player.unk72) {
        return 0;
    }
    g_Player.unk3E8 = 0;
    anim = item->playerAnim;
    switch ((u8)item->unk10) {
    case 0x1D:
        GetEquipProperties(hand, &props, id);
        if (props.attack > 10) {
            goto swing;
        }
    case 0xD:
        if ((rand() & 7) != 3) {
            goto swing;
        }
    cursed:
        switch (PLAYER.step) {
        case 0:
        case 1:
        case 0x13:
            set_anim(0xAF);
            PLAYER.step = 0;
            break;
        case 2:
            set_anim(0xB0);
            PLAYER.step = 2;
            break;
        case 3:
        case 4:
            set_anim(0xB1);
            PLAYER.step = 4;
            break;
        }
        g_Player.unk46 = 0x8012;
        g_Player.unk54 = 0xFF;
        PLAYER.step_s = 0x51;
        PlaySfx(0x701);
        return 1;
    case 0xC:
        if (func_060A637C(item->specialMove, hand) >= 0 &&
            func_060A637C(item->specialMove, (hand + 1) & 1) >= 0) {
            goto swing;
        }
        item = &g_EquipDefs[0];
        func_060BAF44(g_CurrentEntity, (hand << 23) + 0x2A + hand, 0);
        anim = item->playerAnim;
        goto swing;
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
        PLAYER.step = 0;
        DAT_0605CA40 = 0x28;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(0x709);
        goto pose;
    case 0x1C:
        PLAYER.step = 0;
        DAT_0605CA40 = 10;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(0x709);
        goto pose;
    case 0x17:
    case 0x20:
        PLAYER.step = 0;
        func_060A5060();
        g_CurrentEntity->velocityX =
            g_CurrentEntity->facingLeft == 1 ? -0x64000 : 0x64000;
        g_CurrentEntity->velocityY = 0;
        PlaySfx(0x709);
        goto pose;
    case 0x1B:
        func_060A5060();
        g_CurrentEntity->velocityX =
            g_CurrentEntity->facingLeft == 1 ? -0x50000 : 0x50000;
        PLAYER.velocityX >>= 1;
        PlaySfx(0x709);
        variant = atLedge;
        if (g_Player.vram_flag & 1) {
            PLAYER.step = 0;
            g_CurrentEntity->velocityY = 0;
        } else {
            PLAYER.step = 4;
        }
        alu_attack_pose(item, anim + variant);
        return 1;
    case 0x18:
        PLAYER.step = (u16)(PLAYER.step - 3) <= 1 ? 4 : 0;
        DAT_0605CA40 = 0x80;
        g_CurrentEntity->velocityY = 0;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(0x709);
        goto pose;
    case 0x1A:
    case 0x21:
        PLAYER.step = 0;
        DAT_0605CA40 = 0x28;
        g_CurrentEntity->velocityY = 0;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(0x709);
        goto pose;
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 6:
    case 7:
    case 0xB:
    case 0xE:
    case 0xF:
    case 0x10:
    case 0x12:
    swing:
        alu_attack_voice();
    case 8:
    case 9:
    case 0xA:
    case 0x19:
    pose:
        switch (PLAYER.step) {
        case 0:
        case 1:
        case 0x13:
            g_CurrentEntity->velocityX >>= 1;
            PLAYER.step = 0;
            variant = atLedge;
            break;
        case 2:
            variant = 2;
            if (g_Player.padPressed & 0xC000) {
                variant = 3;
            }
            if (!g_Player.unk72 && PLAYER.step_s == 2) {
                variant = atLedge;
                PLAYER.step = 0;
            }
            break;
        case 3:
        case 4:
            variant = 4;
            if (PLAYER.velocityY > 0) {
                variant = 5;
                if ((u8)item->unk10 == 0) {
                    if ((g_Player.padPressed & 0xC000) &&
                        (g_Player.padPressed & 0x2000)) {
                        variant = 6;
                    }
                } else if (g_Player.padPressed & 0x2000) {
                    variant = 6;
                }
            }
            break;
        }
        alu_attack_pose(item, anim + variant);
        return 1;
    case 5:
        switch (PLAYER.step) {
        case 0:
        case 1:
        case 2:
        case 0x13:
            g_CurrentEntity->velocityX >>= 1;
            set_anim(anim + atLedge);
            g_Player.unk46 = (u8)item->unk10 + 0x8001;
            g_Player.unk54 = item->lockDuration;
            PLAYER.step = 0;
            PLAYER.step_s = (u8)item->unk10 + 0x40;
            g_CurrentEntity->velocityX = 0;
            break;
        }
        alu_attack_voice();
        return 1;
    case 0x80:
        switch (PLAYER.step) {
        case 0:
            PLAYER.step_s = 2;
            set_anim(anim + atLedge);
            break;
        case 2:
            PLAYER.step_s = 0;
            set_anim(anim + 2);
            break;
        }
        return 1;
    case 0x86:
        func_060A7D68(1, 0x20);
    case 0x81:
    case 0x82:
        alu_attack_voice();
    case 0x84:
        if (PLAYER.step_s <= 0x3F) {
            switch (PLAYER.step) {
            case 0:
                set_anim(anim + atLedge);
                break;
            case 2:
                variant = 2;
                if (!g_Player.unk72 && PLAYER.step_s == 2) {
                    variant = atLedge;
                    PLAYER.step = 0;
                    PLAYER.step_s = 0;
                }
                set_anim(anim + variant);
                break;
            }
        }
        return 1;
    case 0x83:
        if (PLAYER.step_s <= 0x3F && PLAYER.step == 0) {
            set_anim(anim + atLedge);
        }
        return 1;
    case 0x87:
        PlaySfx(0x70A);
        g_Player.timers[9] = 4;
        PLAYER.velocityY = 0;
        PLAYER.velocityX = 0;
        PLAYER.step = 0xF;
        PLAYER.step_s = 0;
        set_anim(anim);
        func_060BAF44(g_CurrentEntity, 0x14003D, 0);
        g_Player.unk48 = 0;
        return 1;
    }
    return 1;
}

static s32 pressing_back(void) {
    return (g_Entities[0].facingLeft && (g_Player.padPressed & 0x8000)) ||
           (!g_Entities[0].facingLeft && (g_Player.padPressed & 0x4000));
}

static void satz_chair(void) {
    static int chair = -2;
    if (chair == -2) {
        const char* v = getenv("SOTN_SATZ_CHAIR");
        chair = v ? atoi(v) : -1;
    }
    if (chair >= 0) {
        g_Player.unk14 = chair;
    }
}

void func_060A7D3C(void) {
    DestroyEntity(&g_Entities[16]);
    g_Player.unk46 = 0;
}

void func_060A81DC(void) {
    u16 flags = 3;
    s32 atLedge = (g_Player.vram_flag & 0x20) ? 1 : 0;
    s16 dx;

    satz_chair();
    if ((g_Entities[0].step_s == 0x57 || g_Entities[0].step_s == 0x5B) &&
        (s16)g_Player.poseTimer <= 4) {
        if (func_060A50E0(0x43018)) {
            return;
        }
        func_060A55B4(0x1400);
    } else {
        if (func_060A50E0(
                g_Entities[0].step_s == 0x60 && g_Player.poseTimer <= 15
                    ? 0x43018
                    : 0x4301C)) {
            return;
        }
        func_060A55B4(0x2800);
    }
    if (g_Entities[0].step < 0x40 && !g_Player.unk48) {
        if (D_060C84E0) {
            D_060C84E0--;
        } else if (g_unkGraphicsStruct.D_80097448 > 0x30) {
            dx = g_Entities[0].facingLeft ? -4 : 4;
            g_Entities[0].posX.i.hi += dx;
            g_Entities[0].posY.i.hi -= 0x10;
            func_060BAF44(g_CurrentEntity, 0xD0004, 0);
            g_Entities[0].posY.i.hi += 0x10;
            g_Entities[0].posX.i.hi -= dx;
            D_060C84E0 = 0x60;
        }
    }
    switch (g_Entities[0].step_s) {
    case 0:
        break;
    case 1:
        flags = 1;
        if ((s32)g_Player.unk14) {
            sit_down();
            flags |= 0x8000;
        } else if (!(g_Player.padPressed & 0x1000)) {
            flags = 5;
        }
        break;
    case 2:
        switch (g_Player.anim) {
        case 9:
        case 10:
        case 12:
        case 13:
            break;
        default:
            func_060A5674(0x5B);
        case 0x5B:
            if (!g_Player.unk48) {
                flags = 5;
            }
        }
        break;
    case 3:
        flags = 0;
        if (g_Player.anim == 0xBC) {
            if ((s16)g_Player.poseTimer > 3) {
                flags = 1;
            }
        } else if (g_Player.anim == 0xC) {
            if ((s16)g_Player.poseTimer > 6) {
                flags = 7;
            }
        } else if (g_Player.unk39D & 0x40) {
            flags = 7;
        }
        break;
    case 4:
        flags = 1;
        if (g_Player.anim == 0xD8 && --D_060C84E4 == 0) {
            if (*(u16*)&g_CurrentRoom == 1) {
                PlaySfx(0x803);
            }
            func_060BAF44(g_CurrentEntity, 0x7A, 0);
            D_060C84E4 = 0x200;
        }
        break;
    case 0x40:
    case 0x59:
        hide_after_images();
        if ((s16)g_Player.poseTimer < g_Player.unk54) {
            flags = 0;
            if ((s16)g_Player.poseTimer <= 1) {
                func_060A5060();
                if (g_Player.padPressed & 0x2000) {
                    g_Entities[0].step = 2;
                    g_Player.anim = 0x1D;
                }
            }
        } else {
            g_Player.unk46 &= 0x7FFF;
            flags = 0xB;
            if ((s16)g_Player.poseTimer == 7) {
                if (g_Player.padPressed & g_Player.D_80072EF8) {
                    g_Player.pose = 2;
                } else {
                    flags = 0xF;
                }
            }
        }
        break;
    case 0x47:
    case 0x49:
        if ((s16)g_Player.poseTimer == 6 &&
            (g_Player.padPressed & g_Player.D_80072EF8)) {
            g_Player.pose = 2;
        }
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x46:
    case 0x48:
    case 0x4A:
    case 0x4B:
    case 0x4C:
    case 0x4D:
    case 0x4E:
    case 0x4F:
    case 0x50:
    case 0x5D:
        hide_after_images();
        if ((s16)g_Player.poseTimer < g_Player.unk54) {
            flags = 0;
            if ((s16)g_Player.poseTimer <= 2) {
                func_060A5060();
                if (g_Player.padPressed & 0x2000) {
                    g_Player.anim = DAT_060C891B[g_Entities[0].step_s] + 2;
                    g_Entities[0].step = 2;
                }
            }
        } else {
            g_Player.unk46 &= 0x7FFF;
            flags = 0x1B;
            if (g_Player.unk39D & 0x40) {
                flags = 0xF;
            }
        }
        break;
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
    case 0x5C:
        hide_after_images();
        flags = 0;
        if ((s16)g_Player.poseTimer == 0) {
            g_Player.pose = --DAT_0605CA40 == 0 ? 1 : 2;
        }
        if ((s16)g_Player.poseTimer >= g_Player.unk54) {
            flags = 0x1B;
            g_Player.unk46 &= 0x7FFF;
        }
        if (g_Player.unk39D & 0x40) {
            flags = 0xF;
        }
        break;
    case 0x57:
    case 0x5B:
    case 0x60:
        hide_after_images();
        flags = 0;
        if ((s16)g_Player.poseTimer < g_Player.unk54 - 6 &&
            (g_Player.vram_flag & 1) && (g_GameTimer & 1)) {
            func_060BAF44(g_CurrentEntity, 0x10045, 0);
        }
        if ((s16)g_Player.poseTimer >= g_Player.unk54) {
            flags = 0x19;
            g_Player.unk46 &= 0x7FFF;
        }
        if (g_Player.unk39D & 0x40) {
            flags = 0xF;
        }
        if (g_Entities[0].step_s == 0x60) {
            if ((s16)g_Player.poseTimer == 0xF && !(g_Player.vram_flag & 1)) {
                g_Player.poseTimer = 5;
                g_Player.pose = 1;
                g_Player.anim = 0x64;
                g_Entities[0].step = 4;
                g_Player.unk44 = 1;
            }
        } else if ((g_Player.poseTimer == 4 && g_Player.pose == 1) &&
                   !(g_Player.vram_flag & 1)) {
            g_Player.poseTimer = 5;
            g_Player.anim = 0x64;
            g_Entities[0].step = 4;
            g_Player.unk44 = 1;
        }
        break;
    case 0x58:
        hide_after_images();
        if (DAT_0605CA40 > 0) {
            DAT_0605CA40--;
        }
        if ((g_Player.poseTimer == 4 && g_Player.pose == 1) && DAT_0605CA40) {
            g_Player.poseTimer = 2;
        }
        if ((s16)g_Player.poseTimer == 6 || (g_Player.padTapped & 0x2000) ||
            pressing_back()) {
            g_Entities[0].step_s = 0x40;
        }
        flags = 10;
        break;
    case 0x61:
        hide_after_images();
        if (DAT_0605CA40 > 0) {
            DAT_0605CA40--;
        }
        if ((g_Player.poseTimer == 4 && g_Player.pose == 1) && DAT_0605CA40) {
            g_Player.pose = 2;
        }
        if ((s16)g_Player.poseTimer == 7 || (g_Player.padTapped & 0x3000) ||
            pressing_back()) {
            g_Entities[0].step_s = 0x46;
        }
        flags = 0;
        break;
    case 0x5A:
        hide_after_images();
        if (DAT_0605CA40 > 0) {
            DAT_0605CA40--;
        }
        if ((g_Player.poseTimer == 6 && g_Player.pose == 1) && DAT_0605CA40) {
            g_Player.pose = 2;
        }
        if ((s16)g_Player.poseTimer == 0xA || (g_Player.padTapped & 0x3000) ||
            pressing_back()) {
            g_Entities[0].step_s = 0x50;
        }
        flags = 0;
        break;
    case 0x45:
    case 0x51:
        hide_after_images();
        flags = 0;
        if (g_Player.unk39D & 0x40) {
            flags = 0xF;
        }
        break;
    }
    if (flags & 4) {
        func_060A580C(0);
        flags |= 0x8000;
    }
    if ((flags & 2) && (g_Player.padPressed & 0x1000) && !g_Player.unk48) {
        func_060A5674(atLedge + 0x19);
        g_Entities[0].step_s = 1;
        flags |= 0x8000;
        if ((s32)g_Player.unk14) {
            sit_down();
        }
    }
    if ((flags & 1) && func_060A5060()) {
        func_060A59E0(0);
        flags |= 0x8000;
    }
    if ((flags & 0x8000) && (flags & 8)) {
        func_060A7D3C();
    }
}

void func_060AC2F0(void) {
    s32 i;
    s16 a, r;
    u8 flags;

    g_Entities[0].step_s = 0;
    g_Entities[0].step = 0;
    g_Player.unk39A = 0;
    g_Player.unk32C[0] = 27;
    g_Player.unk32C[2] = 29;
    g_Player.unk32C[1] = 29;
    g_Player.unk32C[3] = 31;
    g_Player.unk32C[4] = 32;
    g_Player.unk32C[5] = 33;
    flags = g_Player.unk39D;
    g_Player.unk39D = flags & 0xF7;
    g_Player.unk39B = 1;
    g_Player.unk32C[6] = 57;
    g_Player.unk32C[7] = 59;
    g_Player.unk32C[8] = 60;
    g_Player.unk32C[9] = 61;
    g_Player.unk32C[10] = 62;
    g_Player.unk32C[11] = 63;
    g_Player.unk39D = flags & 0xF3;
    func_060A5674(2);
    func_060A56AC(0);
    g_Player.unk39C = 6;
    g_Player.unk04 = 1;
    g_Player.vram_flag = 1;
    func_060A580C(0);
    for (i = 0; i < 32; i++) {
        a = (MTH_GetRand() & 0x3FF) + 0x100;
        r = (u8)MTH_GetRand() + 0x100;
        DAT_060CE7F0[i] = (rcos(a) * 16 * r) >> 8;
        DAT_060CE870[i] = -((rsin(a) * 16 * r) >> 7);
    }
    D_060C8508 = 16;
    g_Player.padSim = 0;
    g_Player.demo_timer = 16;
    D_060C84FC = 0;
    switch (D_80097C98) {
    case 4:
        func_060BAF44(g_CurrentEntity, 0x00030079, 0);
        func_060A6688(3);
        break;
    case 5:
        func_060BAF44(g_CurrentEntity, 0x00050079, 0);
        func_060A6688(5);
        break;
    case 6:
        func_060BAF44(g_CurrentEntity, 0x00010079, 0);
        func_060A6688(1);
        break;
    }
    g_CurrentEntity = &g_Entities[0];
    if (DAT_060D6018() == 0x2D && CheckEquipmentItemCount(25, 2)) {
        func_060A7D3C();
        ((void (**)(void))g_Weapon0OvlArea)[0]();
        g_Player.status |= 0x01000000;
        func_060A7D68(1, 10);
        func_060AF550();
    }
}

void func_060AC574(void) {
    u32 status;

    g_Player.unk320 = g_Entities[0].step;
    g_Player.unk322 = g_Entities[0].step_s;
    D_060C84F0 = g_Player.timers[11];
    func_060AD524();
    if (g_Player.unk3A8) {
        g_Player.unk3A8--;
    }
    switch (g_Entities[0].step) {
    case 0:
        func_060A81DC();
        break;
    case 1:
        func_060A9658();
        break;
    case 19:
        func_060A96A0();
        break;
    case 2:
        func_060A8DF4();
        break;
    case 3:
        func_060A8D78();
        break;
    case 4:
        func_060A972C();
        break;
    case 5:
        func_060AA23C();
        break;
    case 9:
        func_060AADE4();
        break;
    case 7:
        func_060AB814();
        break;
    case 14:
        func_060ABCF0();
        break;
    case 24:
        func_060B5C68();
        break;
    case 25:
        func_060B5920();
        break;
    case 8:
        func_060A9E3C();
        break;
    case 15:
        func_060ABFA4();
        break;
    case 10:
        func_060B7BB4(&DAT_060CE7E0, DAT_060CE970, DAT_060CE974);
        break;
    case 11:
        func_060B86F4(D_060C8510);
        break;
    case 12:
        func_060B9130();
        break;
    case 16:
        func_060B8B40(&DAT_060CE7E0, DAT_060CE970, DAT_060CE974);
        break;
    case 17:
        func_060B8F68();
        break;
    case 18:
        func_060AC0C8();
        break;
    case 32:
        func_060AB090();
        break;
    case 34:
        func_060AB0E8();
        break;
    case 33:
    case 35:
        func_060AB0BC();
        break;
    case 37:
        func_060AB308();
        break;
    case 39:
        func_060AB37C();
        break;
    case 48:
        func_060AB4A4();
        break;
    case 49:
        func_060AB558();
        break;
    case 50:
        func_060AB590();
        break;
    case 13:
        func_060B8FE0();
        break;
    case 6:
        func_060AB5E0();
        break;
    case 40:
        ((void (*)(Entity*))DAT_060D6004)(&g_Entities[0]);
        break;
    case 41:
        ((void (*)(Entity*))DAT_060D6008)(&g_Entities[0]);
        break;
    case 42:
        ((void (*)(Entity*))DAT_060D600C)(&g_Entities[0]);
        break;
    case 43:
        ((void (*)(Entity*))DAT_060D6010)(&g_Entities[0]);
        break;
    }
    g_unkGraphicsStruct.unk24 &= ~2;
    status = g_Player.status & ~8;
    g_Player.status = status;
    g_Player.unk08 = status;
    g_Status.D_80097BF8 &= ~1;
    func_060AD714();
    if (((u32)g_Player.unk08 & 0x10000) && !(g_Player.status & 0x50000)) {
        func_060AB44C(1, 12);
        if (!(g_Player.status & 0xC000)) {
            g_Player.timers[4] = 12;
            g_Player.timers[15] = 4;
            g_Entities[0].palette = 0;
        }
    }
}

void func_060AC8F4(void) {
    s32 t = g_Player.unk318;
    s32 i, n, depth;
    u16 clut;
    SpritePart* p;

    if ((s8)g_Player.unk39C < 0) {
        for (i = 0; i < 6; i++) {
            AFTER(i)->flags = 0;
        }
        return;
    }
    clut = AFTER(0)->clutBase;
    if ((u32)t % 3 == 0) {
        for (i = 5, depth = 5; depth > 0; i--, depth--) {
            func_0600B12C(AFTER(i), AFTER(i - 1));
            AFTER(i)->slotAndStreamId &= ~0x80;
            AFTER(i)->slotAndStreamId =
                (AFTER(i)->slotAndStreamId & ~0x7F) | ((depth + 0x40) & 0x7F);
            for (n = (AFTER(i)->flags >> 8) & 0x3F, p = AFTER(i)->parts; n; n--,
                p = p->next) {
                p->attributes =
                    (p->attributes & ~0x1F00) | (((depth >> 1) << 8) & 0x1F00);
            }
        }
        AFTER(5)->flags |= 0x80;
        AFTER(4)->flags |= 0x80;
        func_0600B12C(AFTER(0), BODY);
        AFTER(0)->slotAndStreamId &= ~0x80;
        AFTER(0)->clutBase = clut;
        AFTER(0)->slotAndStreamId = (AFTER(0)->slotAndStreamId & 0xFF80) | 0x40;
        func_0600AA18(1);
    }
    for (i = 0; i < 6; i++) {
        for (n = (AFTER(i)->flags >> 8) & 0x3F, p = AFTER(i)->parts; n; n--,
            p = p->next) {
            if ((t & 1) == (i & 1) && i < (s8)g_Player.unk39C) {
                p->attributes &= ~0x40;
            } else {
                p->attributes |= 0x40;
            }
        }
        AFTER(i)->posX -= DAT_0605c680.g_ScrollDeltaX;
        AFTER(i)->posY -= DAT_0605c680.g_ScrollDeltaY;
    }
}

void func_060ACB6C(void) {
    s32 set;
    SaturnAnimationFrame* frames;
    SaturnAnimationFrame* f;
    const FrameProperty* hb;
    SaturnSpriteFrameHeader* spr;
    SpriteObject* obj;
    SaturnSpriteResource* res;
    s16 pose;
    s32 n, i;
    u8 frame;
    u8 flags;

    if (!(g_Player.unk39D & 2)) {
        switch (g_Entities[0].animSet) {
        case 0xD:
            set = 2;
            break;
        case 0xF:
            set = 3;
            break;
        case 0x810:
            set = 5;
            break;
        default:
            set = 0;
            break;
        }
        frames =
            ((SaturnAnimationFrame**)DAT_060CE8F0[set].unkC)[g_Player.anim];
        pose = (s16)g_Player.poseTimer;
        f = &frames[pose];
        hb = &g_AlucardFrameProperties[f->hitbox];
        g_Entities[0].hitboxOffX = hb->offsetX;
        g_Entities[0].hitboxOffY = hb->offsetY;
        g_Entities[0].hitboxWidth = hb->hitboxWidth;
        g_Entities[0].hitboxHeight = hb->hitboxHeight;
        if (g_Player.unk39D & 0x10) {
            g_Player.pose = f->duration;
            g_Player.unk39D &= 0xEF;
        } else {
            flags = g_Player.unk39D & 0x9F;
            g_Player.unk39D = flags;
            if (--g_Player.pose <= 0) {
                g_Player.poseTimer = pose + 1;
                if (frames[pose + 1].duration == 0xFF) {
                    g_Player.unk39D = flags | 0x40;
                    if (frames[pose + 1].frame == 0xFF) {
                        g_Player.poseTimer = pose;
                        g_Player.unk39D = flags | 0x60;
                    } else {
                        g_Player.anim = frames[pose + 1].frame;
                        frames = ((SaturnAnimationFrame**)DAT_060CE8F0[set]
                                      .unkC)[g_Player.anim];
                        g_Player.poseTimer = 0;
                    }
                }
                f = &frames[(s16)g_Player.poseTimer];
                g_Player.pose = f->duration;
            }
        }
        frame = f->frame;
        g_Player.unk398 = frame;
        *(u8*)&DAT_060CE8F0[0].unk0 = frame;
        g_Entities[0].animCurFrame = frame;
        spr = ((SaturnSpriteFrameHeader**)DAT_060CE8F0[set].unk8)[frame];
        obj = BODY;
        if (set == 5) {
            ((void (*)(Entity*, SaturnSpriteFrameHeader*))DAT_060D6020)(
                &g_Entities[0], spr);
            spr = ((SaturnSpriteFrameHeader**)DAT_060CE8F0[set]
                       .unk8)[g_Player.unk398];
        } else {
            res = AlucardSpriteResourceTable[set];
            obj->charBase = res->allocationIndex;
            obj->clutBase = res->flags;
            obj->images = res->images;
            if (set == 2) {
                obj->clutBase = AlucardSpriteResources[0].flags;
            }
            for (i = 0; i < 6; i++) {
                AFTER(i)->charBase = obj->charBase;
                AFTER(i)->images = obj->images;
            }
        }
        obj->flags = spr->header;
        obj->slotAndStreamId =
            (obj->slotAndStreamId & ~0x7F) | (spr->commandFlags & 0x7F);
        if (g_Entities[0].facingLeft == 1) {
            obj->flags |= 0x10;
        } else {
            obj->flags &= ~0x10;
        }
        n = (obj->flags >> 8) & 0x3F;
        SetParts(obj->parts, (SaturnSpritePart*)(spr + 1), n);
        if ((g_Player.unk39D & 1) || g_Entities[0].palette == 0xFF) {
            func_0600B104(obj->parts, 0, n);
            obj->flags |= 8;
            g_Player.unk39E &= 0xBF;
        } else {
            if (g_Entities[0].palette) {
                if (g_Entities[0].palette & 0x40) {
                    obj->clutBase = (g_Entities[0].palette & 0xF) | 0x8000;
                } else {
                    func_0600B104(obj->parts, g_Entities[0].palette, n);
                }
            }
            g_Player.unk39E |= 0x40;
        }
        if (g_Player.unk39E & 0x80) {
            if (set != 5) {
                g_Entities[0].unk0->slotAndStreamId |= 0x20;
            }
            g_Player.unk39E &= 0x7F;
        }
        func_060ACACC((void*)(long)set, obj, n);
    }
    BODY->posX = g_Entities[0].posX.val + (g_Entities[0].unk24 << 16);
    BODY->posY = g_Entities[0].posY.val + (g_Entities[0].unk26 << 16);
}

static void set_sensors(const s32* floor, const s32* ceiling, const s32* wall) {
    s32 i;

    for (i = 0; i < 4; i++) {
        g_AlucardSensorsFloor[i].y = floor[i];
        g_AlucardSensorsCeiling[i].y = ceiling[i];
    }
    for (i = 0; i < 7; i++) {
        g_AlucardSensorsWall[i].y = wall[i];
        g_AlucardSensorsWall[i + 7].y = wall[i];
    }
}

void func_060ACF00(s32 updateSensors) {
    Collider col;
    s32 dx, x, y, i, ignoreFlag10;
    u32 prev, slope;
    u16 step = g_Entities[0].step;

    ignoreFlag10 = (g_Player.status & 2) || g_Entities[16].entityId == 0x22;
    g_Player.unk04 = g_Player.vram_flag;
    g_Player.vram_flag = 0;
    if (updateSensors) {
        if (step == 7 || step == 5) {
            set_sensors(g_AlucardSensorsFloorBat, g_AlucardSensorsCeilingBat,
                        g_AlucardSensorsWallBat);
        } else if (step == 2 || step == 24) {
            set_sensors(
                g_AlucardSensorsFloorDefault, g_AlucardSensorsCeilingCrouch,
                g_AlucardSensorsWallCrouch);
        } else {
            set_sensors(
                g_AlucardSensorsFloorDefault, g_AlucardSensorsCeilingDefault,
                g_AlucardSensorsWallDefault);
        }
    }
    prev = g_Player.unk04;
    slope = prev & 0xF000;
    dx = g_Entities[0].velocityX;
    if (g_Entities[0].velocityX < 0 && !(prev & 8)) {
        if (slope == 0xC000) {
            dx = dx * 10 >> 4;
        }
        if (slope == 0xD000) {
            dx = dx * 13 >> 4;
        }
        g_Entities[0].posX.val += dx;
    }
    if (g_Entities[0].velocityX > 0 && !(g_Player.unk04 & 4)) {
        if (slope == 0x8000) {
            dx = dx * 10 >> 4;
        }
        if (slope == 0x9000) {
            dx = dx * 13 >> 4;
        }
        g_Entities[0].posX.val += dx;
    }
    g_Entities[0].posY.val += g_Entities[0].velocityY;
    for (i = 0; i < 4; i++) {
        x = g_Entities[0].posX.val + g_AlucardSensorsFloor[i].x;
        y = g_Entities[0].posY.val + g_AlucardSensorsFloor[i].y;
        CheckCollision(x, y, &g_Player.colFloor[i], 0);
        if (g_Player.timers[7] && (g_Player.colFloor[i].effects & 0x40)) {
            CheckCollision(x, y + 0xC0000, &col, 0);
            if (!(col.effects & 1)) {
                g_Player.colFloor[i].effects = 0;
            }
        }
        if (ignoreFlag10 && (g_Player.colFloor[i].effects & 0x10)) {
            g_Player.colFloor[i].effects = 0;
        }
        if ((g_Entities[0].step == 5 || g_Entities[0].step == 7) &&
            (g_Player.colFloor[i].effects & 0xC0)) {
            g_Player.colFloor[i].effects = 0;
        }
    }
    func_060B3024();
    step = g_Entities[0].step;
    if ((step == 9 || step == 0xE || step == 0x19) &&
        (g_Player.colCeiling[1].effects & 0x41) == 1 &&
        (g_Player.colFloor[1].effects & 0x81) == 1) {
        g_Player.vram_flag = 3;
        g_Entities[0].posX.val -= dx;
        return;
    }
    for (i = 0; i < 4; i++) {
        CheckCollision(g_Entities[0].posX.val + g_AlucardSensorsCeiling[i].x,
                       g_Entities[0].posY.val + g_AlucardSensorsCeiling[i].y,
                       &g_Player.colCeiling[i], 0);
        if (ignoreFlag10 && (g_Player.colCeiling[i].effects & 0x10)) {
            g_Player.colCeiling[i].effects = 0;
        }
        if ((g_Entities[0].step == 5 || g_Entities[0].step == 7) &&
            (g_Player.colCeiling[i].effects & 0xC0)) {
            g_Player.colCeiling[i].effects = 0;
        }
    }
    func_060B349C();
    if ((g_Player.vram_flag & 1) && g_Entities[0].velocityY >= 0) {
        g_Entities[0].posY.i.lo = 0;
    }
    if ((g_Player.vram_flag & 2) && g_Entities[0].velocityY <= 0) {
        g_Entities[0].posY.i.lo = 0;
    }
    for (i = 0; i < 14; i++) {
        CheckCollision(g_Entities[0].posX.val + g_AlucardSensorsWall[i].x,
                       g_Entities[0].posY.val + g_AlucardSensorsWall[i].y,
                       &g_Player.colWall[i], 0);
        if (ignoreFlag10 && (g_Player.colWall[i].effects & 0x10)) {
            g_Player.colWall[i].effects = 0;
        }
    }
    func_060B38B4();
    func_060B3A90();
    if ((g_Player.vram_flag & 4) && g_Entities[0].velocityX > 0) {
        g_Entities[0].posX.i.lo = 0;
    }
    if ((g_Player.vram_flag & 8) && g_Entities[0].velocityX < 0) {
        g_Entities[0].posX.i.lo = 0;
    }
    if (g_Player.vram_flag & 0x8000) {
        g_Player.vram_flag |= 0x20;
    }
    if (!(g_Player.colFloor[1].effects & 1) ||
        !(g_Player.colFloor[2].effects & 1) ||
        !(g_Player.colFloor[3].effects & 1)) {
        g_Player.vram_flag |= 0x20;
    }
}

void func_060AD524(void) {
    u16 i;

    for (i = 0; i < 18; i++) {
        if (!g_Player.timers[i]) {
            continue;
        }
        switch (i) {
        case 2:
            g_Entities[0].palette = g_Player.damagePalette;
            break;
        case 3:
            g_Entities[0].palette = g_Player.high_jump_timer;
            g_Player.timers[15] = 12;
            break;
        case 15:
            func_060A7D68(0, 0);
            break;
        case 11:
            if (!D_060C84F0) {
                func_060AF124(1);
            }
            break;
        }
        if (--g_Player.timers[i] != 0) {
            continue;
        }
        switch (i) {
        case 0:
        case 1:
            if (!(g_Player.status & 0x8080)) {
                g_Player.timers[4] = 12;
                g_Player.timers[15] = 12;
                func_060AB44C(1, 12);
            }
            break;
        case 2:
            g_Entities[0].palette = 0;
            break;
        case 3:
            g_Entities[0].palette = 0;
            if (!(g_Player.status & 0xC080)) {
                g_Player.timers[4] = 12;
                g_Player.timers[15] = 12;
                func_060AB44C(1, 12);
            }
            break;
        case 6:
            if (g_Entities[0].step == 3 && g_Player.anim != 0xC3) {
                func_060A5674(0xC3);
                g_Player.unk44 &= ~0x10;
            }
            break;
        case 13:
            func_060AB44C(1, 16);
            break;
        case 15:
            func_060A7DD0();
            break;
        case 11:
            func_060AF124(0);
            break;
        }
    }
}

void func_060AD714(void) {
    u32 s = 0;
    u16 step_s = g_Entities[0].step_s;

    switch (g_Entities[0].step) {
    case 2:
        if (step_s != 2) {
            s = 0x20;
        }
        s |= 0x10000000;
        break;
    case 1:
    case 19:
        s = 0x04000000;
    case 0:
        s |= 0x10000000;
        if (step_s == 4) {
            s |= 0x08100000;
        }
        break;
    case 3:
    case 4:
        s = 0x10002000;
        break;
    case 5:
        if (step_s == 3) {
            func_060AB44C(1, 4);
            g_unkGraphicsStruct.unk24 |= 2;
        }
        s = 0x28100001;
        break;
    case 7:
        func_060AB44C(1, 4);
        s = 0x28100002;
        g_Entities[0].palette = 0xFF;
        break;
    case 14:
        s = 0x28900002;
        g_Entities[0].palette = 0xFF;
        func_060AB44C(1, 4);
        break;
    case 6:
        func_060AB44C(1, 4);
        s = 0x18100030;
        break;
    case 9:
        s = 0x28500001;
        if (step_s == 0) {
            g_Entities[0].animSet = 13;
        }
        func_060AB44C(1, 4);
        break;
    case 8:
        func_060AB44C(1, 4);
        s = 0x38000000;
        break;
    case 48:
    case 49:
        s = 0x38100000;
        func_060AB44C(1, 12);
        break;
    case 10:
        s = 0x38110000;
        func_060AB44C(1, 12);
        break;
    case 11:
        s = 0x38110080;
        break;
    case 12:
        s = 0x38110040;
        func_060AB44C(1, 12);
        break;
    case 13:
    case 16:
        s = 0x18150000;
        if (step_s == 0x80) {
            s |= 0x80000;
        }
        func_060AB44C(1, 12);
        break;
    case 17:
        s = 0x18150000;
        func_060AB44C(1, 12);
        break;
    case 18:
        s = 0x18100000;
        func_060AB44C(1, 12);
        break;
    case 33:
    case 35:
    case 39:
        func_060AB44C(1, 16);
        s = 0x38000220;
        break;
    case 32:
    case 34:
    case 37:
        func_060AB44C(1, 16);
        s = 0x38000200;
        break;
    case 43:
        func_060AB44C(1, 20);
    case 40:
    case 41:
    case 42:
    case 50:
        s = 0x29100000;
        g_Entities[0].unk56 = 100;
        break;
    case 15:
        s = 0x18100000;
        func_060AB44C(4, 12);
        g_Entities[0].palette = 0xFF;
        break;
    case 24:
        if (DAT_060CC774 == 2) {
            g_unkGraphicsStruct.unk24 |= 2;
        }
        if ((g_Entities[0].velocityX < 0 ? -g_Entities[0].velocityX
                                         : g_Entities[0].velocityX) > 0x30000) {
            func_060AB44C(1, 4);
        }
        s = 0x2C100204;
        if (step_s == 0 || step_s == 8) {
            s |= 0x40000000;
        }
        if (step_s == 3) {
            s |= 0x20;
        }
        break;
    case 25:
        s = 0x68100000;
        func_060AB44C(1, 4);
        break;
    }
    if ((u16)g_Player.timers[9]) {
        s |= 0x400;
    }
    if ((u16)g_Player.timers[10]) {
        s |= 0x800;
    }
    if ((u16)g_Player.timers[12]) {
        s |= 0x1000;
    }
    if (g_Player.timers[0]) {
        s |= 0x28104000;
    }
    if (g_Player.timers[1]) {
        s |= 0x28108000;
    }
    if (g_unkGraphicsStruct.D_80097448) {
        s |= 0x08020000;
    }
    if ((u16)g_Player.timers[11]) {
        s |= 0x02000000;
    }
    g_Player.status = s;
    if ((s & 0x08000000) || g_unkGraphicsStruct.D_800973FC) {
        func_060A7D68(1, 1);
    }
    if (s & 0x10000000) {
        g_Entities[0].animSet = 1;
    }
    if (s & 0x20000000) {
        g_Status.D_80097BF8 |= 1;
    }
    if ((u16)g_Player.timers[14] | (u16)g_Player.timers[13]) {
        g_Player.status |= 0x100;
    }
}

s32 func_060ADACC(s8* frameProps, u16** frames) {
    Entity* e = g_CurrentEntity;
    u16* seq = frames[e->ext.weapon.anim];
    u16 entry = seq[g_Player.poseTimer];
    s8* hb;

    if (entry == 0xFFFF) {
        return -1;
    }
    if (frameProps) {
        hb = &frameProps[(entry >> 9) * 4];
        e->hitboxOffX = hb[0];
        e->hitboxOffY = hb[1];
        e->hitboxWidth = hb[2];
        e->hitboxHeight = hb[3];
    }
    e->animCurFrame = entry & 0x1FF;
    g_Player.unk399 = entry & 0x1FF;
    if ((u8)entry) {
        func_060C1618(e);
    }
    return (g_Player.unk39D & 0x40) ? -1 : 0;
}

void func_060ADB80(s8* frameProps, AnimationFrame** frames) {
    Entity* e = g_CurrentEntity;
    ET_Weapon* ext = &e->ext.weapon;
    AnimationFrame* f = &frames[ext->anim][e->pose];
    s8* hb;

    if (e->poseTimer != -1) {
        if (e->poseTimer == 0) {
            e->poseTimer = f->duration;
        } else if (--e->poseTimer == 0) {
            e->pose++;
            f = &frames[ext->anim][e->pose];
            if (f->duration == 0) {
                e->pose = f->pose;
                f = &frames[ext->anim][e->pose];
                e->poseTimer = f->duration;
            } else if (f->duration == 0xFFFF) {
                e->pose--;
                e->poseTimer = -1;
                f = &frames[ext->anim][e->pose];
            } else if (f->duration == 0xFFFE) {
                ext->anim = f->pose & 0xFF;
                e->pose = (u8)(f->pose >> 8);
                f = &frames[ext->anim][e->pose];
                e->poseTimer = f->duration;
            } else {
                e->poseTimer = f->duration;
            }
        }
    }
    if (frameProps) {
        hb = &frameProps[(f->pose >> 9) * 4];
        e->hitboxOffX = hb[0];
        e->hitboxOffY = hb[1];
        e->hitboxWidth = hb[2];
        e->hitboxHeight = hb[3];
    }
    e->animCurFrame = f->pose & 0x1FF;
    func_060C1618(e);
}

void func_060ADD74(void) {
    g_CurrentEntity = &g_Entities[0];
    switch (g_Player.anim - 0xB6) {
    case 0:
    case 1:
    case 8:
    case 9:
    case 11:
        func_060ACB6C();
        break;
    }
}

void func_060ADDDC(void) {
    SaturnSpriteResource* res;
    SpriteObject* obj;
    s32 i;

    res = &AlucardSpriteResources[1];
    for (i = 5; i >= 0; i--) {
        obj = CreateSpriteObject(
            res->allocationIndex, res->flags, AlucardImages, 2);
        DAT_060CEA80[i].unk4 = (s16*)obj;
        DAT_060CEA80[i].unk8 = (AnimationFrame*)AlucardFrames;
        DAT_060CEA80[i].unkC = (void*)g_AlucardAnimationTable;
        ((SpriteObject*)DAT_060CEA80[i].unk4)->zPriority = 0x8F;
    }
    res = &AlucardSpriteResources[2];
    for (i = 0; i < 16; i++) {
        obj = CreateSpriteObject(
            res->allocationIndex, res->flags, AlucardSubImages, 2);
        DAT_060CE980[i].unk4 = (s16*)obj;
        obj->zPriority = 0x90;
    }
    res = &AlucardSpriteResources[0];
    obj =
        CreateSpriteObject(res->allocationIndex, res->flags, AlucardImages, 3);
    DAT_060CE8F0[0].unk4 = (s16*)obj;
    g_Entities[0].unk0 = obj;
    DAT_060CE8F0[0].unk8 = (AnimationFrame*)AlucardFrames;
    g_Entities[0].ext.spriteEntity.frames = AlucardFrames;
    DAT_060CE8F0[0].unkC = (void*)g_AlucardAnimationTable;
    g_Entities[0].zPriority = 0x90;
    obj->zPriority = 0x90;
    DAT_060CE8F0[2].unk8 = (AnimationFrame*)g_AlucardEffectSpriteMetadataTable;
    DAT_060CE8F0[2].unkC = g_AlucardResidualAnimationTable;
    DAT_060CE8F0[3].unk8 = (AnimationFrame*)AlucardSubFrames;
    DAT_060CE8F0[3].unkC = g_AlucardAnimationCommandTable;
    obj =
        CreateSpriteObject(res->allocationIndex, res->flags, AlucardImages, 2);
    DAT_060CE8F0[4].unk4 = (s16*)obj;
    DAT_060CE8F0[4].unk8 = (AnimationFrame*)AlucardFrames;
    DAT_060CE8F0[4].unkC = (void*)g_AlucardAnimationTable;
    obj->zPriority = 0x90;
    DAT_060CE8F0[5].unk4 = NULL;
    DAT_060CE8F0[5].unk8 = (AnimationFrame*)AlucardFrames;
    DAT_060CE8F0[5].unkC = (void*)g_AlucardAnimationTable;
}

void func_060ADF3C(u16 params) {
    s32 i;

    D_060C8500 = 1;
    D_060C84F8 = g_Status.mp == g_Status.mpMax;
    memset(DAT_060CE8F0, 0, sizeof(DAT_060CE8F0));
    memset(DAT_060CEA80, 0, sizeof(EntryS060CE980) * 6);
    memset(DAT_060CE980, 0, sizeof(EntryS060CE980) * 16);
    DestroyEntity(&g_Entities[0]);
    func_060ADDDC();
    g_Entities[0].animSet = 1;
    func_060AF4A0();
    memset(&g_Player, 0, sizeof(g_Player));
    func_060AF124(0);
    for (i = 0; i < 16; i++) {
        DAT_060CE7A0[i].buttonsCorrect = 0;
        DAT_060CE7A0[i].timer = 0;
    }
    g_Player.unk318 = 0;
    func_060AC2F0();
    g_Entities[0].scaleX = g_Entities[0].scaleY = 0x100;
    g_Entities[0].posX.val = 0x00200000;
    g_Entities[0].posY.val = 0x00900000;
}

s32 func_060AE048(void) {
    ButtonComboState* c = &DAT_060CE7A0[0];

    switch (c->buttonsCorrect) {
    case 0:
        if ((g_Player.padTapped & 0x2000) && !g_Player.padHeld) {
            c->timer = 16;
            c->buttonsCorrect++;
        }
        break;
    case 1:
        if (g_Player.padTapped & 0x1000) {
            c->timer = 16;
            c->buttonsCorrect++;
        } else if (--c->timer == 0) {
            c->buttonsCorrect = 0;
        }
        break;
    case 2:
        if (c->timer && --c->timer == 0) {
            c->buttonsCorrect = 0;
            break;
        }
        if (!IsRelicActive(12) || !(g_Player.padTapped & 0x100) ||
            (g_Player.unk46 & 0x8000)) {
            break;
        }
        if (g_Entities[0].step != 2 &&
            !(g_Entities[0].step == 4 && (g_Player.unk44 & 1))) {
            break;
        }
        if (g_Player.unk72) {
            c->buttonsCorrect = 0;
            break;
        }
        if (HandleGravityBootsMP(1) >= 0) {
            func_060A5D50();
            c->buttonsCorrect = 0;
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_060AE184(void) {
    ButtonComboState* c = &DAT_060CE7A0[1];
    u32 dirs = (g_Player.padPressed & 0xF000) << 16;
    u32 forward = DAT_060CE498 ? 0x40000000 : 0x80000000;
    u32 downForward = DAT_060CE498 ? 0x60000000 : 0xA0000000;

    switch (c->buttonsCorrect) {
    case 0:
        DAT_060CE498 = g_Entities[0].facingLeft;
        if (dirs == 0x20000000) {
            c->timer = 20;
            c->buttonsCorrect++;
        } else if (--c->timer == 0) {
            c->buttonsCorrect = 0;
        }
        break;
    case 1:
        if (dirs == downForward) {
            c->timer = 20;
            c->buttonsCorrect++;
        } else if (--c->timer == 0) {
            c->buttonsCorrect = 0;
        }
        break;
    case 2:
        if (dirs == forward) {
            c->timer = 20;
            c->buttonsCorrect = COMBO_COMPLETE;
        } else if (--c->timer == 0) {
            c->buttonsCorrect = 0;
        }
        break;
    default:
        if (c->timer) {
            if (g_Player.unk72) {
                c->buttonsCorrect = 0;
            } else if (--c->timer == 0) {
                c->buttonsCorrect = 0;
                DAT_060CE498 = g_Entities[0].facingLeft;
            }
        }
        break;
    }
    return 0;
}

static s32 combo_step(ButtonComboState* c, s32 ok, s16 timer, s16 next) {
    if (ok) {
        c->timer = timer;
        c->buttonsCorrect = next;
    } else if (--c->timer == 0) {
        c->buttonsCorrect = 0;
    }
    return 0;
}

s32 func_060AE284(void) {
    ButtonComboState* c = &DAT_060CE7A0[2];
    u32 dirs = (g_Player.padPressed & 0xF000) << 16;
    u32 forward = DAT_060CE49A ? 0x40000000 : 0x80000000;

    switch (c->buttonsCorrect) {
    case 0:
        DAT_060CE49A = g_Entities[0].facingLeft;
        return combo_step(
            c, dirs == ((s16)DAT_060CE49A ? 0x80000000 : 0x40000000), 15, 1);
    case 1:
        return combo_step(c, dirs == forward, 15, COMBO_COMPLETE);
    default:
        if (g_Player.unk72) {
            c->buttonsCorrect = 0;
        } else if (c->timer && --c->timer == 0) {
            c->buttonsCorrect = 0;
            DAT_060CE49A = g_Entities[0].facingLeft;
        }
        return 0;
    }
}

s32 func_060AE36C(void) {
    ButtonComboState* c = &DAT_060CE7A0[15];
    u32 all = g_Player.padPressed << 16;
    u32 dirs = (g_Player.padPressed & 0xF000) << 16;
    u32 forwardUp, forward, backUp;

    if (!DAT_060CE49C) {
        forwardUp = 0x90000000, forward = 0x80000000, backUp = 0x50000000;
    } else {
        forwardUp = 0x50000000, forward = 0x40000000, backUp = 0x90000000;
    }
    switch ((u16)c->buttonsCorrect) {
    case 0:
        if (!g_Entities[0].facingLeft) {
            if (g_Player.padTapped & 0x4000) {
                c->timer = 20;
                c->buttonsCorrect++;
                DAT_060CE49C = 0;
            }
        } else if (g_Player.padTapped & 0x8000) {
            c->timer = 20;
            c->buttonsCorrect++;
            DAT_060CE49C = 1;
        }
        return 0;
    case 1:
        return combo_step(
            c, (all & backUp) == backUp, 20, c->buttonsCorrect + 1);
    case 2:
        return combo_step(c, all == 0x10000000, 20, c->buttonsCorrect + 1);
    case 3:
        return combo_step(
            c, (dirs & forwardUp) == forwardUp, 20, c->buttonsCorrect + 1);
    case 4:
        return combo_step(c, dirs == forward, 20, c->buttonsCorrect + 1);
    case 5:
        if (--c->timer == 0) {
            c->buttonsCorrect = 0;
            return 0;
        }
        if (!(g_Player.padTapped & 0x600) || (g_Player.unk46 & 0x8000) ||
            g_Entities[0].step > 1) {
            return 0;
        }
        if (!CastSpell(0)) {
            return 0;
        }
        func_060A5EA8();
        c->buttonsCorrect = 0;
        LearnSpell(0);
        return 1;
    }
    return 0;
}

s32 func_060AE544(void) {
    ButtonComboState* c = &DAT_060CE7A0[14];
    u32 dirs = (g_Player.padPressed & 0xF000) << 16;
    u32 fwd = dirs & (DAT_060CE4A0 ? 0x40000000 : 0x80000000);

    switch ((u16)c->buttonsCorrect) {
    case 0:
        if (!g_Entities[0].facingLeft) {
            if (g_Player.padTapped == 0x4000) {
                c->timer = 20;
                c->buttonsCorrect++;
                DAT_060CE4A0 = 0;
            }
        } else if (g_Player.padTapped == 0x8000) {
            c->timer = 20;
            c->buttonsCorrect++;
            DAT_060CE4A0 = 1;
        }
        return 0;
    case 1:
        return combo_step(c, dirs == fwd, 20, c->buttonsCorrect + 1);
    case 2:
        return combo_step(c, dirs == 0x10000000, 20, c->buttonsCorrect + 1);
    case 3:
        return combo_step(c, dirs == 0x20000000, 20, c->buttonsCorrect + 1);
    case 4:
        if (--c->timer == 0) {
            c->buttonsCorrect = 0;
        }
        if (!(g_Player.padTapped & 0x600) || (g_Player.unk46 & 0x8000) ||
            g_Entities[0].step != 2) {
            return 0;
        }
        if (!CastSpell(1)) {
            return 0;
        }
        func_060A5F9C();
        c->buttonsCorrect = 0;
        LearnSpell(1);
        return 1;
    }
    return 0;
}

s32 func_060AE6F4(void) {
    ButtonComboState* c = &DAT_060CE7A0[3];
    u32 dirs = (g_Player.padPressed & 0xF000) << 16;
    u32 forward = DAT_060CE4A4 ? 0x40000000 : 0x80000000;
    u32 downForward = DAT_060CE4A4 ? 0x60000000 : 0xA0000000;

    switch ((u16)c->buttonsCorrect) {
    case 0:
        if (g_Player.padTapped == 0x1000) {
            c->timer = 20;
            c->buttonsCorrect++;
        }
        return 0;
    case 1:
        if (dirs == 0x20000000) {
            c->timer = 21;
            c->buttonsCorrect++;
            DAT_060CE4A4 = g_Entities[0].facingLeft;
            return 0;
        }
        return combo_step(c, 0, 0, 0);
    case 2:
        return combo_step(
            c, (dirs & downForward) == downForward, 20, c->buttonsCorrect + 1);
    case 3:
        return combo_step(c, dirs == forward, 20, c->buttonsCorrect + 1);
    case 4:
        if (c->timer && --c->timer == 0) {
            c->buttonsCorrect = 0;
            return 0;
        }
        if (!(g_Player.padTapped & 0x600) || (g_Player.unk46 & 0x8000) ||
            g_Entities[0].step > 2) {
            return 0;
        }
        if (g_Player.unk72) {
            c->buttonsCorrect = 0;
            return 0;
        }
        if (!CastSpell(2)) {
            return 0;
        }
        func_060A605C();
        c->buttonsCorrect = 0;
        LearnSpell(2);
        return 1;
    }
    return 0;
}

static s32 cast(
    ButtonComboState* c, s32 spell, void (*start)(void), s32 crouching) {
    if (!(g_Player.padTapped & 0x600) || (g_Player.unk46 & 0x8000)) {
        return 0;
    }
    if (crouching ? g_Entities[0].step != 2 : g_Entities[0].step > 1) {
        return 0;
    }
    if (!CastSpell(spell)) {
        return 0;
    }
    start();
    c->buttonsCorrect = 0;
    LearnSpell(spell);
    return 1;
}

s32 func_060AE8E4(void) {
    ButtonComboState* c = &DAT_060CE7A0[4];
    u32 dirs = (g_Player.padPressed & 0xF000) << 16;
    u32 forward = DAT_060CE4A8 ? 0x40000000 : 0x80000000;
    u32 downForward = DAT_060CE4A8 ? 0x60000000 : 0xA0000000;
    u32 upForward = DAT_060CE4A8 ? 0x50000000 : 0x90000000;

    switch ((u16)c->buttonsCorrect) {
    case 0:
        if (g_Player.padTapped == 0x1000) {
            c->timer = 32;
            c->buttonsCorrect++;
        }
        return 0;
    case 1:
        if (dirs != 0x10000000) {
            c->buttonsCorrect = 0;
        } else if (--c->timer == 0) {
            c->buttonsCorrect++;
            DAT_060CE4A8 = g_Entities[0].facingLeft;
        }
        return 0;
    case 2:
        if (dirs != 0x10000000) {
            c->buttonsCorrect++;
            c->timer = 32;
        }
        if ((dirs & upForward) == upForward) {
            c->timer = 20;
            c->buttonsCorrect = 4;
        }
        return 0;
    case 3:
        if ((dirs & upForward) == upForward) {
            c->timer = 20;
            c->buttonsCorrect = 4;
            return 0;
        }
        return combo_step(c, 0, 0, 0);
    case 4:
        return combo_step(c, dirs == forward, 20, c->buttonsCorrect + 1);
    case 5:
        return combo_step(
            c, (dirs & downForward) == downForward, 20, c->buttonsCorrect + 1);
    case 6:
        return combo_step(c, dirs == 0x20000000, 20, c->buttonsCorrect + 1);
    case 7:
        if (--c->timer == 0) {
            c->buttonsCorrect = 0;
        }
        return cast(c, 3, func_060A60EC, 1);
    }
    return 0;
}

s32 func_060AEAE8(void) {
    ButtonComboState* c = &DAT_060CE7A0[6];
    u32 dirs = (g_Player.padPressed & 0xF000) << 16;
    u32 downForward, forward, back, downBack;

    if (!DAT_060CE4AC) {
        downForward = 0xA0000000, forward = 0x80000000, back = 0x40000000,
        downBack = 0x60000000;
    } else {
        downForward = 0x60000000, forward = 0x40000000, back = 0x80000000,
        downBack = 0xA0000000;
    }
    switch ((u16)c->buttonsCorrect) {
    case 0:
        if (!g_Entities[0].facingLeft) {
            if ((g_Player.padTapped << 16) == 0x40000000) {
                c->timer = 24;
                c->buttonsCorrect++;
                DAT_060CE4AC = 0;
            }
        } else if ((g_Player.padTapped << 16) == 0x80000000) {
            c->timer = 20;
            c->buttonsCorrect++;
            DAT_060CE4AC = 1;
        }
        return 0;
    case 1:
        return combo_step(c, dirs == forward, 24, c->buttonsCorrect + 1);
    case 2:
        return combo_step(
            c, (dirs & downForward) == downForward, 24, c->buttonsCorrect + 1);
    case 3:
        return combo_step(c, dirs == 0x20000000, 24, c->buttonsCorrect + 1);
    case 4:
        return combo_step(
            c, (dirs & downBack) == downBack, 24, c->buttonsCorrect + 1);
    case 5:
        return combo_step(c, dirs == back, 24, c->buttonsCorrect + 1);
    case 6:
        return combo_step(c, dirs == forward, 24, c->buttonsCorrect + 1);
    case 7:
        if (--c->timer == 0) {
            c->buttonsCorrect = 0;
            return 0;
        }
        return cast(c, 5, func_060A61B0, 0);
    }
    return 0;
}

s32 func_060AECC4(void) {
    ButtonComboState* c = &DAT_060CE7A0[9];
    u32 dirs = (g_Player.padPressed & 0xF000) << 16;
    u32 downForward, forward, upForward;

    if (!g_Entities[0].facingLeft) {
        downForward = 0xA0000000, forward = 0x80000000, upForward = 0x90000000;
    } else {
        downForward = 0x60000000, forward = 0x40000000, upForward = 0x50000000;
    }
    if (g_Servant != 5) {
        c->buttonsCorrect = 0;
    }
    switch ((u16)c->buttonsCorrect) {
    case 0:
        if (dirs == 0x20000000) {
            c->timer = 20;
            c->buttonsCorrect++;
        }
        return 0;
    case 1:
        return combo_step(c, dirs == downForward, 20, c->buttonsCorrect + 1);
    case 2:
        return combo_step(c, dirs == forward, 20, c->buttonsCorrect + 1);
    case 3:
        return combo_step(c, dirs == upForward, 20, c->buttonsCorrect + 1);
    case 4:
        return combo_step(c, dirs == 0x10000000, 64, c->buttonsCorrect + 1);
    case 5:
        if (--c->timer == 0) {
            c->buttonsCorrect++;
        } else if (!(dirs & 0x10000000)) {
            c->buttonsCorrect = 0;
        }
        return 0;
    case 6:
        if (!(dirs & 0x10000000)) {
            c->buttonsCorrect = 7;
            c->timer = 20;
        }
        return 0;
    case 7:
        return combo_step(c, dirs == 0x20000000, 20, c->buttonsCorrect + 1);
    case 8:
        if (--c->timer == 0) {
            c->buttonsCorrect = 0;
        }
        if (!(g_Player.padTapped & 0x600) || (g_Player.unk46 & 0x8000) ||
            g_Entities[0].step != 2) {
            return 0;
        }
        if (!CastSpell(7)) {
            return 0;
        }
        func_060A6248();
        c->buttonsCorrect = COMBO_COMPLETE;
        c->timer = 20;
        LearnSpell(7);
        g_Player.unk70 = 1;
        return 1;
    case COMBO_COMPLETE:
        if (--c->timer == 0) {
            c->buttonsCorrect = 0;
            g_Player.unk70 = 1;
        }
        return 0;
    }
    return 0;
}

void func_060AEEE4(void) {
    static s32 (* const checks[16])(void) = {
        func_060AE048, func_060AE184, func_060AE284, func_060AE6F4,
        func_060AE8E4, NULL,          func_060AEAE8, NULL,
        NULL,          func_060AECC4, NULL,          NULL,
        NULL,          NULL,          func_060AE544, func_060AE36C,
    };
    s32 i;

    for (i = 0; i < 16; i++) {
        if (checks[i] && checks[i]()) {
            return;
        }
    }
}

void func_060AF050(u16* palette) {
    static const s32 scale[3] = {0xC000, 0x8000, 0x5556};
    u16 i, j;
    u16 c;

    for (j = 0; j < 3; j++) {
        for (i = 0; i < 16; i++) {
            c = palette[i];
            g_AlucardPaletteVariants[j][i] =
                (c & 0x7C00) +
                ((((c >> 5) & 31) * scale[j]) >> 16 & 0xFF) * 32 +
                (((c & 31) * scale[j]) >> 16 & 0xFF) + 0x8000;
        }
        LookupTblNoToVramAddr(j + AlucardSpriteResources[1].flags,
                              (u8*)g_AlucardPaletteVariants[j]);
    }
}

static u16 rgb(s32 r, s32 g, s32 b) { return (b << 10) + g * 32 + r + 0x8000; }

void func_060AF1BC(s32 changed) {
    s32 i;
    s32 t, r;

    if (!(g_Player.unk39E & 0x20)) {
        for (i = 0; i < 4; i++) {
            s_CapePalette[6 + i] = g_EquippedCapePalette[i];
        }
        switch (g_Status.equipment[5]) {
        case CLOAK_TWILIGHT:
            t = g_GameTimer >> 1;
            r = (t & 0x20) ? 0x3F - (t & 0x3F) : t & 0x1F;
            s_CapePalette[7] = s_CapePalette[6] = 0x8000 + r;
            changed = 1;
            break;
        case CLOAK_RAINBOW:
            t = g_GameTimer;
            DAT_060C85B4 = (rcos(t) + 0x1000) >> 8;
            DAT_060C85B6 = (rcos(t + 0x555) + 0x1000) >> 8;
            DAT_060C85B8 = (rsin(t + 0xAAA) + 0x1000) >> 8;
            DAT_060C85BA = (rsin((t * 11 >> 3) + 0x1E0) + 0x1000) >> 8;
            DAT_060C85BC = (rsin(t + 0xCC) + 0x1000) >> 8;
            DAT_060C85BE = (rcos(t * 2) + 0x1000) >> 8;
            s_CapePalette[7] = rgb(DAT_060C85BA, DAT_060C85BC, DAT_060C85BE);
            DAT_060C85BA = ((u16)DAT_060C85BA * 3) >> 2;
            DAT_060C85BC = ((u16)DAT_060C85BC * 3) >> 2;
            DAT_060C85BE = ((u16)DAT_060C85BE * 3) >> 2;
            s_CapePalette[6] = rgb(DAT_060C85BA, DAT_060C85BC, DAT_060C85BE);
            s_CapePalette[8] = rgb(DAT_060C85B4, DAT_060C85B6, DAT_060C85B8);
            DAT_060C85B4 = ((u16)DAT_060C85B4 * 3) >> 2;
            DAT_060C85B6 = ((u16)DAT_060C85B6 * 3) >> 2;
            DAT_060C85B8 = ((u16)DAT_060C85B8 * 3) >> 2;
            s_CapePalette[9] = rgb(DAT_060C85B4, DAT_060C85B6, DAT_060C85B8);
            changed = 1;
            break;
        case CLOAK_GLARING:
            changed = 1;
            for (i = 0; i < 4; i++) {
                s_CapePalette[6 + i] = DAT_060AF1AC[(g_GameTimer & 1) * 4 + i];
            }
            break;
        }
    }
    if (g_Entities[0].animSet == 13 || g_Entities[0].animSet == 1) {
        if (changed || memcmp(DAT_060C8594, s_CapePalette, 32)) {
            LookupTblNoToVramAddr(
                AlucardSpriteResources[0].flags, (u8*)s_CapePalette);
            func_060AF050(s_CapePalette);
            memcpy(DAT_060C8594, s_CapePalette, 32);
        }
    }
}

void func_060AF4B8(void) {
    s32 limit;

    if (g_Player.status & 0x02000000) {
        limit = (DAT_060CE4B3 & 0x1F) << 8;
        DAT_060CE972 += DAT_060CE4B4;
        if (DAT_060CE972 > limit || DAT_060CE972 < 0) {
            DAT_060CE4B4 = -DAT_060CE4B4;
            DAT_060CE972 += DAT_060CE4B4;
        }
        DAT_060C8588 = (DAT_060CE972 >> 8) + 0x8000;
    } else if (g_Entities[0].animSet == 1) {
        DAT_060C8588 = 0xC210;
    } else {
        DAT_060C8588 = 0xFFE0;
    }
}

void func_060AF654(s32 reset) {
    g_CurrentEntity = &g_Entities[0];
    if (DAT_060D6018() == 0x2D && CheckEquipmentItemCount(25, 2)) {
        if (g_Player.status & 0x01000000) {
            return;
        }
        PlaySfx(0x5C3);
        g_Player.padSim = 0;
        g_Player.demo_timer = 32;
        func_060A7D3C();
        ((void (**)(void))g_Weapon0OvlArea)[0]();
        g_Player.status |= 0x01000000;
        func_060A7D68(1, 10);
        func_060AF550();
        if (reset) {
            func_060ACB6C();
        }
        return;
    }
    if (g_Player.status & 0x01000000) {
        g_Entities[0].palette = 0;
        g_Entities[0].animSet = 0;
        g_Entities[0].unk56 = 0;
        g_Entities[0].rotate = 0;
        g_Entities[0].drawFlags &= 0xF3;
        func_060A7D3C();
        g_Entities[0].unk26 = 0;
        g_Entities[0].unk24 = 0;
        if (g_Player.vram_flag & 1) {
            func_060A580C(0);
        } else {
            func_060A5AF0();
        }
        g_Player.status &= 0xFEFFFFFF;
        func_060AA0FC();
        if (reset) {
            func_060ACB6C();
        }
        return;
    }
    if (!reset || (u16)(g_Entities[0].step_s - 0x41) > 46) {
        return;
    }
    if (g_Entities[0].step == 0) {
        func_060A580C(0);
    } else if (g_Entities[0].step == 2) {
        func_060A56E4(0, 0);
    } else {
        return;
    }
    g_Player.unk46 = 0;
}

static s32 can_transform(u16 step, u16 step_s, s32 bat) {
    if (step <= 1 || step == 0x13 || (u16)(step - 2) <= 1 || step == 4 ||
        step == 6) {
        return 1;
    }
    if (bat) {
        if (step == 8) {
            return 1;
        }
        if (step == 5 && step_s) {
            return 1;
        }
    } else if ((u16)(step - 7) <= 1) {
        return 1;
    }
    return step == 0x18 && step_s && step_s != 8;
}

void func_060AFA20(void) {
    s32 i, n, dx, vramFlag;
    u32 pad;

    g_CurrentEntity = &g_Entities[0];
    g_Player.unk318++;
    if (D_060C8504) {
        D_060C8504--;
    }
    if (g_unkGraphicsStruct.D_800973FC && !D_060C84FC) {
        func_060BAF44(&g_Entities[0], 120, 0);
    }
    D_060C84FC = g_unkGraphicsStruct.D_800973FC;
    g_Player.unk4C = 0;
    D_060C8510 = 0;
    DAT_060CE970 = 0;
    DAT_060CE974 = 0;
    g_Entities[0].drawFlags = 0;
    g_Player.unk18 = 0;
    g_Player.unk70 = 0;
    g_Player.unk72 = func_060B0584();
    if (g_Player.status & 0x40000) {
        goto step;
    }
    if ((n = func_060AF8E0()) != 0) {
        func_060A6688(n);
    }
    if (g_Entities[0].step == 0x12) {
        goto step;
    }
    func_060AF654(0);
    func_060AF7F0();
    func_060AEFBC();
    func_060B0638();
    if ((n = CheckAndDoLevelUp()) != 0) {
        func_060BAF44(g_CurrentEntity, ((n - 1) << 16) + 0x19, 0);
    }
    if (D_80097C98) {
        g_Player.padSim = 0;
        g_Player.demo_timer = 16;
    }
    g_Player.padHeld = g_Player.padPressed;
    if (g_Player.demo_timer) {
        if (--g_Player.demo_timer == 0) {
            D_060C8500 = 1;
        }
        g_Player.padPressed = g_Player.padSim & 0xFFFF;
        switch (g_Player.padSim >> 16) {
        case 1:
            if (g_Entities[0].step != 0x30) {
                func_060AB44C(1, 4);
                SetPlayerStep(0x30);
                g_unkGraphicsStruct.pauseEnemies = 1;
            }
            break;
        case 2:
            func_060AB44C(1, 4);
            SetPlayerStep((g_Player.status & 0x01000000) ? 50 : 49);
            g_unkGraphicsStruct.pauseEnemies = 1;
            break;
        }
    } else {
        pad = g_pads[0].pressed;
        g_Player.padPressed = pad & 0xF800;
        for (i = 0; i < 8; i++) {
            if (pad & g_Settings.buttonMask[i]) {
                g_Player.padPressed |= (u16)g_ButtonMask[i];
            }
        }
        if (D_060C8500) {
            D_060C8500 = 0;
            g_Player.padHeld = g_Player.padPressed;
        }
    }
    g_Player.padTapped = ~g_Player.padHeld & g_Player.padPressed;
    if (g_Player.status & 8) {
        g_Player.padTapped &= 0xFFFFF9FF;
        g_Player.padPressed &= 0xFFFFF9FF;
    }
    if (g_unkGraphicsStruct.D_8009744C && !IsRelicActive(14) &&
        !(g_Entities[0].hitParams & 0x1F)) {
        g_Entities[0].hitParams = 6;
    }
    if ((u16)g_Player.grabState > 1) {
        goto step;
    }
    if ((u16)g_Player.grabState == 1) {
        DAT_060CE970 = g_Entities[0].step;
        DAT_060CE974 = g_Entities[0].step_s;
        SetPlayerStep(12);
        goto step;
    }
    if (!((u16)g_Player.timers[13] | (u16)g_Player.timers[14])) {
        func_060B0310();
    }
    func_060AEEE4();
    if (D_060C8508) {
        D_060C8508--;
    }
    if (D_060C8508) {
        goto step;
    }
    if (!g_unkGraphicsStruct.D_8009744C) {
        if ((g_Player.padTapped & 0x40) && !HandleTransformationMP(1, 0) &&
            can_transform(g_Entities[0].step, g_Entities[0].step_s, 1)) {
            func_060AF550();
            SetPlayerStep(7);
            func_060B7994();
            PlaySfx(0x6A0);
            goto step;
        }
        if ((g_Player.padTapped & 0x20) && !HandleTransformationMP(0, 0) &&
            can_transform(g_Entities[0].step, g_Entities[0].step_s, 0)) {
            if (g_Entities[0].step == 6 || g_Entities[0].step == 2) {
                D_060C850C = 12;
            }
            func_060AF550();
            SetPlayerStep(5);
            func_060B7994();
            PlaySfx(0x6A0);
            goto step;
        }
    }
    if ((g_Player.padTapped & 0x10) && !HandleTransformationMP(2, 0) &&
        (!g_unkGraphicsStruct.D_8009744C || IsRelicActive(14))) {
        u16 st = g_Entities[0].step;
        if (st <= 1 || st == 0x13 || (u16)(st - 2) <= 1 || st == 4 || st == 6 ||
            (u16)(st - 7) <= 1 || (st == 5 && g_Entities[0].step_s)) {
            func_060AF550();
            SetPlayerStep(24);
            PlaySfx(0x668);
        }
    }
step:
    func_060AC574();
    if (g_Player.status & 0x40000) {
        if (g_Player.unk39D & 0x40) {
            g_Entities[0].animCurFrame |= 0x8000;
        }
        g_Entities[0].hitParams = 0;
        g_Entities[0].hitboxState = 0;
    } else {
        g_Entities[0].hitboxState = 1;
        g_Entities[0].hitPoints = 0;
        g_Entities[0].hitParams = 0;
    }
    g_Player.unk14 = 0;
    g_Player.runDisable = 0;
    if (g_Player.status & 0x50) {
        goto end;
    }
    if (CheckEquipmentItemCount(90, 4) && !(g_Player.status & 0x01050017) &&
        !(g_Entities[0].drawFlags & 4)) {
        g_Entities[0].drawFlags |= 2;
        g_Entities[0].scaleY = 0x110;
        g_Entities[0].unk26 = -3;
    } else if (g_Entities[0].unk26 == -3) {
        g_Entities[0].unk26 = 0;
    }
    g_Player.unk20 = g_Entities[0].posX.val;
    g_Player.unk24 = g_Entities[0].posY.val;
    if ((g_unkGraphicsStruct.D_80097448 > 40 ||
         ((g_Player.status & 4) && g_unkGraphicsStruct.D_80097448 > 12)) &&
        !g_CurrentEntity->nFramesInvincibility) {
        g_Entities[0].velocityY = g_Entities[0].velocityY * 3 / 4;
        g_Entities[0].velocityX = g_Entities[0].velocityX * 3 / 4;
    }
    vramFlag = g_Player.vram_flag;
    {
        s32 speed = g_Entities[0].velocityX < 0 ? -g_Entities[0].velocityX
                                                : g_Entities[0].velocityX;
        if (!(g_Player.status & 0x40400005) && speed <= 0x1FFFF &&
            g_Entities[0].step != 8) {
            g_Entities[0].velocityX >>= 2;
            g_Entities[0].velocityY >>= 2;
            func_060ACF00(g_Entities[0].step == 0x0E ? 0 : 1);
            for (i = 0; i <= 2; i++) {
                func_060ACF00(0);
            }
            g_Entities[0].velocityX <<= 2;
            g_Entities[0].velocityY <<= 2;
        } else {
            n = speed > 0x80000 ? 11 : 7;
            g_Entities[0].velocityX = g_Entities[0].velocityX / (n + 1);
            g_Entities[0].velocityY = g_Entities[0].velocityY / (n + 1);
            if (g_Entities[0].posY.i.hi >= 0) {
                func_060ACF00((g_Player.status & 0x40400000) ? 0 : 1);
            }
            for (i = 0; i < n; i++) {
                if (g_Entities[0].posY.i.hi >= 0) {
                    func_060ACF00(0);
                }
            }
            if (g_Entities[0].posY.i.hi < 0) {
                g_Entities[0].posY.val = 0xFFFF0000;
            }
            g_Entities[0].velocityX *= n + 1;
            g_Entities[0].velocityY *= n + 1;
        }
    }
    g_Player.unk04 = vramFlag;
    dx = g_Entities[0].posX.val - g_Player.unk20;
    if (dx > 0xFFFFF) {
        dx = 0x100000;
    } else if (dx < -0x100000) {
        dx = -0x100000;
    }
    g_Entities[0].posX.val = g_Player.unk20 + dx;
    dx = g_Entities[0].posY.val - (s32)g_Player.unk24;
    if (dx > 0xFFFFF) {
        dx = 0x100000;
    } else if (dx < -0x100000) {
        dx = -0x100000;
    }
    g_Entities[0].posY.val = (s32)g_Player.unk24 + dx;
    if ((g_unkGraphicsStruct.D_80097448 > 40 ||
         ((g_Player.status & 4) && g_unkGraphicsStruct.D_80097448 > 12)) &&
        !g_CurrentEntity->nFramesInvincibility) {
        g_Entities[0].velocityY = g_Entities[0].velocityY * 4 / 3;
        g_Entities[0].velocityX = g_Entities[0].velocityX * 4 / 3;
    }
    g_CurrentEntity->nFramesInvincibility = 0;
    func_060AC8F4();
end:
    func_060ACB6C();
    func_060AF4B8();
    func_060AF1BC(0);
    func_060B071C();
}

void func_060B0310(void) {
    DamageParam* damage = &DAT_060CE7E0;
    s32 result;

    if (!g_Entities[0].hitParams) {
        return;
    }
    DAT_060CE970 = g_Entities[0].step;
    DAT_060CE974 = g_Entities[0].step_s;
    result =
        HandleDamage(damage, g_Entities[0].hitParams, g_Entities[0].hitPoints);
    if ((g_Player.status & 0x01000000) &&
        (result == 1 || (u32)(result - 7) <= 1)) {
        result = 3;
        damage->damageKind = 1;
    }
    switch (result) {
    case 0:
        func_060BAF44(g_CurrentEntity, 47, 0);
        func_060BAF44(g_CurrentEntity, 0x0043002C, 0);
        func_060BAF44(g_CurrentEntity, 0x0051002C, 0);
        func_060B9610(0, 0);
        func_060AB44C(1, 12);
        break;
    case 1:
        g_Player.unk18 = damage->effects;
        g_Player.high_jump_timer = 70;
        func_060AB44C(1, 12);
        g_Player.timers[3] = 6;
        PlaySfx(0x701);
        func_060B9610(1, 0);
        break;
    case 2:
        g_Player.unk18 = damage->effects;
        func_060BAF44(g_CurrentEntity, 115, 0);
        func_060BAF44(g_CurrentEntity, 0x0058002C, 0);
        g_Player.high_jump_timer = 70;
        func_060AB44C(1, 12);
        g_Player.timers[3] = 6;
        break;
    case 3:
        g_Player.unk18 = damage->effects;
        SetPlayerStep(10);
        func_060B9610(damage->damageTaken, 0);
        break;
    case 4:
        func_060B9610(damage->damageTaken, 0);
        SetPlayerStep(16);
        break;
    case 5:
        func_060BAF44(g_CurrentEntity, 0x0044002C, 0);
        func_060BAF44(g_CurrentEntity, 0x0048002C, 0);
        func_060B9610(damage->unkC, 1);
        func_060AB44C(1, 12);
        break;
    case 6:
        SetPlayerStep(13);
        break;
    case 7:
        g_Player.unk18 = damage->effects;
        SetPlayerStep(11);
        func_060B9610(damage->damageTaken, 0);
        break;
    case 8:
        g_Player.unk18 = damage->effects;
        func_060B9610(damage->damageTaken, 0);
        D_060C8510 = 1;
        break;
    case 9:
        func_060BAF44(g_CurrentEntity, 0x004E002C, 0);
        if (!D_060C84F4) {
            PlaySfx(0x705);
        }
        if (damage->damageTaken) {
            PlaySfx(0x6A3);
        }
        D_060C84F4 = 32;
        break;
    }
}

typedef struct {
    /* 0x78 */ s16 timer;
    /* 0x7A */ u8 pad7A[2];
    /* 0x7C */ s32 bounce;
} AluFoodExt;
#define ALU_FOOD(e) ((AluFoodExt*)&(e)->ext)

extern SaturnSpriteImage g_SaturnSharedSpriteBank10Images[];
extern SaturnSpriteFrameHeader* g_SaturnSharedSpriteBank10Frames[];
s32 func_060B24E0(Entity* self, s32 landed);
void func_060A5614(s32 amount);
void func_060B2B30(Entity* self);
void func_060C1618(Entity* self);

static void food_got(Entity* self, u16 padSim) {
    s32 id = (self->params >> 8) & 0x7F;

    if (id == 7 || id == 0x29) {
        ALU_FOOD(self)->timer = 0xC;
        self->animCurFrame = 0;
        self->step = 4;
        g_Player.padSim = padSim;
        g_Player.demo_timer = 0x14;
        return;
    }
    if (g_Player.healKind) {
        ALU_FOOD(self)->timer = 8;
        self->animCurFrame = 0;
        self->step = 3;
        return;
    }
    g_Player.healKind = 1;
    g_Player.healAmount = self->attack;
    DestroyEntity(self);
}

void func_060B25F4(Entity* self) {
    AluFoodExt* ext = ALU_FOOD(self);
    SpriteObject* sprite;
    Collider col;
    s32 id = (self->params >> 8) & 0x7F, v, dx;

    switch (self->step) {
    case 0:
        sprite = CreateSpriteObject(
            g_SaturnSharedSpriteBank10Resource.allocationIndex,
            g_SaturnSharedSpriteBank10Resource.flags,
            g_SaturnSharedSpriteBank10Images, 1);
        self->unk0 = sprite;
        if (!sprite) {
            DestroyEntity(self);
            return;
        }
        self->ext.weapon.frames = g_SaturnSharedSpriteBank10Frames;
        sprite->zPriority = PLAYER.zPriority + 2;
        self->animSet = 0x8010;
        self->palette = 0x110;
        self->unk56 = 0x64;
        if (id == 0x2B) {
            self->params = (rand() % 43 + 0x1D) << 8;
            self->step = 0x100;
            return;
        }
        self->facingLeft = PLAYER.facingLeft;
        self->flags = 0x08000000;
        self->animCurFrame = id + 1;
        self->posY.i.hi -= 4;
        v = (MTH_GetRand() & 0x3FFF) + 0xE000;
        self->velocityX = self->facingLeft == 1 ? -v : v;
        self->velocityY = -0x20000;
        if (id == 6) {
            self->posX.i.hi += self->facingLeft ? -8 : 8;
            v = (MTH_GetRand() & 0xFFF) + 0x1000;
            self->velocityX = self->facingLeft == 1 ? -v : v;
            self->velocityY = -0x58000;
            ext->bounce = 0xFFFA8000;
        }
        self->attack = g_EquipDefs[self->ext.factory.argLow].attack;
        if (g_Player.unk48) {
            DestroyEntity(&g_Entities[16]);
            g_Player.unk48 = 0;
        }
        self->facingLeft = 0;
        self->hitboxWidth = 8;
        self->hitboxHeight = 8;
        self->step++;
        break;
    case 1:
        if (func_060B24E0(self, 0)) {
            food_got(self, 0x2000);
            if (!self->entityId) {
                return;
            }
            break;
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityY += 0x2800;
        CheckCollision(self->posX.val, self->posY.val + 0x80000, &col, 0);
        if (col.effects & 1) {
            self->posY.val += col.unk18;
            if (id != 6) {
                ext->timer = 0x80;
                self->step++;
                break;
            }
            ext->bounce /= 2;
            self->velocityY = ext->bounce;
            if (ext->bounce > (s32)0xFFFF0000) {
                DestroyEntity(self);
                return;
            }
            self->posY.val += ext->bounce;
        }
        dx = self->velocityX < 0 ? -0x40000 : 0x40000;
        CheckCollision(self->posX.val + dx, self->posY.val, &col, 0);
        if (col.effects & 2) {
            self->posX.val += dx < 0 ? col.unkC : col.unk4;
            self->velocityX = -(self->velocityX / 2);
            if (id == 6) {
                DestroyEntity(self);
                return;
            }
        }
        CheckCollision(
            self->posX.val,
            self->posY.val + (id == 6 ? (s32)0xFFFC0000 : (s32)0xFFF80000),
            &col, 0);
        if (col.effects & 1) {
            self->posY.val += 1 + col.unk20;
            self->velocityY = 0x10000;
            self->velocityX /= 2;
        }
        break;
    case 2:
        func_060A5614(0x4800);
        self->posX.val += self->velocityX;
        if (func_060B24E0(self, 1)) {
            food_got(self, 0);
            if (!self->entityId) {
                return;
            }
            break;
        }
        if (ext->timer == 0x18) {
            self->drawFlags |= 0x80;
        }
        if (--ext->timer == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    case 3:
        if (--ext->timer == 0) {
            if (!g_Player.healKind) {
                g_Player.healKind = 1;
                g_Player.healAmount = self->attack;
                DestroyEntity(self);
                return;
            }
            ext->timer = 8;
        }
        break;
    case 4:
        if (--ext->timer == 0) {
            PLAYER.hitParams = 0x81;
            PLAYER.hitPoints = 0;
            PLAYER.hitboxState = 0;
            DestroyEntity(self);
            return;
        }
        break;
    case 5:
    case 6:
        if (self->step == 5 || --ext->timer == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    default:
        func_060B2B30(self);
        return;
    }
    func_060C1618(self);
}

void func_060B3024(void) {
    Collider c;
    s32 i = 0, lift = 0, abs_vx, r7, room;
    u32 e, s2, s1, flags;

    if (g_unkGraphicsStruct.unk20) {
        g_Player.vram_flag = 1;
        return;
    }
    if (g_Entities[0].velocityY == 0 && (g_Player.unk04 & 1) &&
        !(g_Player.status & 3)) {
        lift = 0x40000;
    } else {
        i = 1;
    }
    for (; i < 4; i++, lift = 0) {
        e = g_Player.colFloor[i].effects;
        if (e & 0x80) {
            continue;
        }
        abs_vx = g_Entities[0].velocityX < 0 ? -g_Entities[0].velocityX
                                             : g_Entities[0].velocityX;
        if (!(e & 2) && g_Entities[0].velocityY < 0 && !(g_Player.status & 7) &&
            abs_vx <= 0x1FFFF) {
            continue;
        }
        s2 = e & 0x8801;
        if (s2 == 1 || (s2 & 0x800)) {
            if ((g_Player.status & 3) && !(e & 1)) {
                continue;
            }
            CheckCollision(g_Entities[0].posX.val + g_AlucardSensorsFloor[i].x,
                           g_Entities[0].posY.val + g_AlucardSensorsFloor[i].y -
                               0x10000 + g_Player.colFloor[i].unk18,
                           &c, 0);
            if ((g_Player.status & 2) && (c.effects & 0x10)) {
                c.effects &= ~3;
            }
            s1 = c.effects;
            if (!(s1 & 1)) {
                e = g_Player.colFloor[i].effects;
                if ((e != 1 && e != 0x41) || g_Entities[0].velocityY >= 0) {
                    g_Entities[0].posY.val +=
                        ((s2 & 0x800) ? g_Player.colFloor[i].unk8
                                      : g_Player.colFloor[i].unk18) +
                        lift;
                    g_Player.vram_flag |= 1;
                    return;
                }
                continue;
            }
            if ((s1 & 0x8003) == 0x8001) {
                if (i < 2) {
                    g_Player.vram_flag |= (s1 & 0x7000) + 0x8001;
                    g_Entities[0].posY.val +=
                        g_Player.colFloor[i].unk8 + c.unk18 + lift - 0x10000;
                    return;
                }
                if (i == 2 && (s1 & 0xC001) == 0x8001) {
                    g_Player.colFloor[2].effects = s1;
                    g_Player.colFloor[2].unk10 = g_Player.colFloor[2].unk8;
                }
                if (i == 3 && (s1 & 0xC001) == 0xC001) {
                    g_Player.colFloor[3].effects = s1;
                    g_Player.colFloor[3].unk10 = g_Player.colFloor[3].unk8;
                }
            }
        }
        if (s2 != 0x8001 || i > 1) {
            continue;
        }
        g_Player.vram_flag |= g_Player.colFloor[i].effects & 0xF001;
        g_Entities[0].posY.val += g_Player.colFloor[i].unk18 + lift;
        return;
    }
    if (g_Player.colFloor[1].effects & 4) {
        g_Player.vram_flag |= 0x11;
        if (!(g_Timer & 3)) {
            g_Entities[0].posY.val += 0x10000;
        }
        return;
    }
    if (g_Player.colFloor[1].effects & 8) {
        g_Player.vram_flag |= 0x80;
    }
    if (g_Entities[0].velocityY < 0) {
        return;
    }
    CheckCollision(
        g_Entities[0].posX.val + g_AlucardSensorsFloor[0].x,
        g_Entities[0].posY.val + g_AlucardSensorsFloor[0].y + 0xA0000, &c, 0);
    if (c.effects & 0x8001) {
        return;
    }
    for (i = 2; i < 4; i++) {
        if ((g_Player.colFloor[3].effects & 0x8000) &&
            (g_Player.colFloor[2].effects & 0x8000)) {
            return;
        }
        e = g_Player.colFloor[i].effects;
        flags = (e & 0x7000) + 0x8001;
        if (!(e & 0x8000)) {
            continue;
        }
        if (i == 2) {
            s1 = 0x4000;
            r7 = g_Player.colFloor[2].unk4;
            room = r7 + 0xA0000;
        } else {
            s1 = 0;
            r7 = g_Player.colFloor[3].unkC;
            room = 0xA0000 - r7;
        }
        if ((e & 0x4000) == s1) {
            CheckCollision(
                g_Entities[0].posX.val + g_AlucardSensorsFloor[i].x + r7,
                g_Entities[0].posY.val + g_AlucardSensorsFloor[i].y, &c, 0);
            if (c.effects & 1) {
                g_Entities[0].posY.val += c.unk18;
                g_Player.vram_flag |= flags;
                return;
            }
            continue;
        }
        if (room > 0 && (e & 1)) {
            CheckCollision(
                g_Entities[0].posX.val + g_AlucardSensorsFloor[i].x + r7,
                g_Entities[0].posY.val + g_AlucardSensorsFloor[i].y +
                    g_Player.colFloor[i].unk10,
                &c, 0);
            if (c.effects & 1) {
                g_Entities[0].posY.val += c.unk18 + g_Player.colFloor[i].unk10;
                g_Player.vram_flag |= flags;
                return;
            }
        }
    }
}

void func_060B349C(void) {
    Collider c;
    s32 i, r7, room;
    u32 e, s2, s1, flags;

    if (g_unkGraphicsStruct.unk20) {
        return;
    }
    for (i = 1; i < 4; i++) {
        e = g_Player.colCeiling[i].effects;
        if (e & 0x40) {
            continue;
        }
        s2 = e & 0x8801;
        if (s2 == 1 || (s2 & 0x8000)) {
            if ((g_Player.status & 3) && !(e & 1)) {
                continue;
            }
            CheckCollision(
                g_Entities[0].posX.val + g_AlucardSensorsCeiling[i].x,
                g_Entities[0].posY.val + g_AlucardSensorsCeiling[i].y +
                    g_Player.colCeiling[i].unk10 + 0x10000,
                &c, 0);
            if ((g_Player.status & 2) && (c.effects & 0x10)) {
                c.effects &= ~3;
            }
            s1 = c.effects;
            if (!(s1 & 1)) {
                if (g_Player.colCeiling[i].effects == 1 &&
                    g_Entities[0].velocityY > 0) {
                    continue;
                }
                g_Player.vram_flag |= 2;
                if (!(g_Player.vram_flag & 1) &&
                    (g_Player.unk04 & 0x41) != 0x41) {
                    g_Entities[0].posY.val +=
                        (g_Player.colCeiling[i].effects & 0x8000)
                            ? g_Player.colCeiling[i].unk10
                            : g_Player.colCeiling[i].unk20;
                }
                return;
            }
            if ((s1 & 0x803) == 0x801) {
                if (i < 2) {
                    g_Player.vram_flag |= 0x802 | ((s1 >> 4) & 0x700);
                    if (!(g_Player.vram_flag & 1)) {
                        g_Entities[0].posY.val +=
                            0x10000 + g_Player.colCeiling[i].unk10 + c.unk20;
                    }
                    return;
                }
                if (i == 2 && (s1 & 0x4801) == 0x801) {
                    g_Player.colFloor[2].effects = s1;
                    g_Player.colFloor[2].unk8 = g_Player.colFloor[2].unk10;
                }
                if (i == 3 && (s1 & 0x4801) == 0x4801) {
                    g_Player.colFloor[3].effects = s1;
                    g_Player.colFloor[3].unk8 = g_Player.colFloor[3].unk10;
                }
            }
            if (!(s1 & 0x800)) {
                g_Player.vram_flag |= 0x802 | ((s1 >> 4) & 0x700);
                if (!(g_Player.vram_flag & 1)) {
                    g_Entities[0].posY.val +=
                        0x10000 + g_Player.colCeiling[i].unk10 + c.unk20;
                }
                return;
            }
        }
        if (s2 == 0x801 && i < 2) {
            g_Player.vram_flag |=
                0x802 | ((g_Player.colCeiling[i].effects >> 4) & 0x700);
            if (!(g_Player.vram_flag & 1)) {
                g_Entities[0].posY.val += g_Player.colCeiling[i].unk20;
            }
            return;
        }
    }
    if (g_Entities[0].velocityY > 0) {
        return;
    }
    CheckCollision(
        g_Entities[0].posX.val + g_AlucardSensorsCeiling[0].x,
        g_Entities[0].posY.val + g_AlucardSensorsCeiling[0].y - 0xA0000, &c, 0);
    if (c.effects & 1) {
        return;
    }
    for (i = 2; i < 4; i++) {
        if ((g_Player.colCeiling[3].effects & 0x800) &&
            (g_Player.colCeiling[2].effects & 0x800)) {
            return;
        }
        e = g_Player.colCeiling[i].effects;
        flags = ((e >> 4) & 0x700) + 0x802;
        if (!(e & 0x800)) {
            continue;
        }
        if (i == 2) {
            s1 = 0x4000;
            r7 = g_Player.colCeiling[2].unk4;
            room = r7 + 0xA0000;
        } else {
            s1 = 0;
            r7 = g_Player.colCeiling[3].unkC;
            room = 0xA0000 - r7;
        }
        if ((e & 0x4000) == s1) {
            CheckCollision(
                g_Entities[0].posX.val + g_AlucardSensorsCeiling[i].x + r7,
                g_Entities[0].posY.val + g_AlucardSensorsCeiling[i].y, &c, 0);
            if (c.effects & 1) {
                g_Player.vram_flag |= flags;
                if (!(g_Player.vram_flag & 1)) {
                    g_Entities[0].posY.val += c.unk20;
                }
                return;
            }
            continue;
        }
        if (room > 0 && (e & 1)) {
            CheckCollision(
                g_Entities[0].posX.val + g_AlucardSensorsCeiling[i].x + r7,
                g_Entities[0].posY.val + g_AlucardSensorsCeiling[i].y +
                    g_Player.colCeiling[i].unk8,
                &c, 0);
            if (c.effects & 1) {
                if (!(g_Player.vram_flag & 1)) {
                    g_Entities[0].posY.val +=
                        c.unk20 + g_Player.colCeiling[i].unk8;
                }
                g_Player.vram_flag |= flags;
                return;
            }
        }
    }
}

static s32 arena_room(void) {
    u16 room = *(u16*)&g_CurrentRoom;
    return room == 0x18 || room == 0x38 || room == 0x12;
}

static void wall_push(u32 flag, s32 dx) {
    g_Player.vram_flag |= flag;
    g_Entities[0].posX.val += dx;
}

void func_060B38B4(void) {
    Collider c;
    s32 i;
    u32 e, w;

    if (arena_room() && g_Entities[0].posX.i.hi > 0x12F) {
        g_Entities[0].posX.i.hi = 0x130;
        g_Player.vram_flag |= 4;
        return;
    }
    if (g_unkGraphicsStruct.unk20) {
        return;
    }
    e = g_Player.unk04 & 0xCC03;
    if (e == 0x8003 || e == 0x803 || e == 0x8803) {
        g_Player.vram_flag |= 4;
        return;
    }
    for (i = 0; i < 7; i++) {
        e = g_Player.colWall[i].effects & 0xC803;
        if (e == 0xC001 || e == 0xC003 || e == 0x4801 || e == 0x4803 ||
            e == 0x8003 || e == 0x803 || e == 3) {
            CheckCollision(
                g_Entities[0].posX.val + g_AlucardSensorsWall[i].x +
                    g_Player.colWall[i].unk4 - 0x10000,
                g_Entities[0].posY.val + g_AlucardSensorsWall[i].y, &c, 0);
            if (!(c.effects & 1)) {
                wall_push(4, g_Player.colWall[i].unk4);
                return;
            }
        }
        if (!(g_Player.vram_flag & 1)) {
            w = g_Player.colWall[0].effects;
            if ((e & 0xC800) == 0x8000 && i != 0 &&
                ((w & 0x800) || !(w & 0x8802))) {
                wall_push(4, g_Player.colWall[i].unk4);
                return;
            }
            w = g_Player.colWall[6].effects;
            if ((e & 0xC800) == 0x800 && i != 6 &&
                ((w & 0x8000) || !(w & 0x8802))) {
                wall_push(4, g_Player.colWall[i].unk4);
                return;
            }
        }
    }
}

void func_060B3A90(void) {
    Collider c;
    s32 i;
    u32 e, w;

    if (arena_room() && g_Entities[0].posX.i.hi <= 0x10) {
        g_Entities[0].posX.i.hi = 0x10;
        g_Player.vram_flag |= 8;
        return;
    }
    if (g_unkGraphicsStruct.unk20) {
        return;
    }
    e = g_Player.unk04 & 0xCC03;
    if (e == 0xC003 || e == 0xC03 || e == 0xCC03) {
        g_Player.vram_flag |= 8;
        return;
    }
    for (i = 7; i < 14; i++) {
        e = g_Player.colWall[i].effects & 0xC803;
        if (e == 0x8001 || e == 0x8003 || e == 0x801 || e == 0x803 ||
            e == 0xC003 || e == 0x4803 || e == 3) {
            CheckCollision(
                g_Entities[0].posX.val + g_AlucardSensorsWall[i].x +
                    g_Player.colWall[i].unkC + 0x10000,
                g_Entities[0].posY.val + g_AlucardSensorsWall[i].y, &c, 0);
            if (!(c.effects & 1)) {
                wall_push(8, g_Player.colWall[i].unkC);
                return;
            }
        }
        if (!(g_Player.vram_flag & 1)) {
            w = g_Player.colWall[7].effects;
            if ((e & 0xC800) == 0xC000 && i != 7 &&
                ((w & 0x800) || !(w & 0x8802))) {
                wall_push(8, g_Player.colWall[i].unkC);
                return;
            }
            w = g_Player.colWall[13].effects;
            if ((e & 0xC800) == 0x4800 && i != 13 &&
                ((w & 0x8000) || !(w & 0x8802))) {
                wall_push(8, g_Player.colWall[i].unkC);
                return;
            }
        }
    }
}

Entity* func_060B93C4(void) {
    s32 found[128];
    s32* turn = (s32*)g_AlucardMiscFrameProperties;
    Entity* e = &g_Entities[64];
    s32 i, n = 0, k;

    for (i = 0; i < 128; i++, e++) {
        found[i] = 0;
        if (!e->entityId || !e->hitboxState || (e->flags & 0x00200000)) {
            continue;
        }
        if (e->posX.i.hi < -0x10 || e->posX.i.hi > 0x150 ||
            e->posY.i.hi > 0xF0 || e->posY.i.hi < 0 || e->hitPoints > 0x6FFF) {
            continue;
        }
        if (!(e->flags & 0x80000)) {
            e->flags |= 0x80000;
            return e;
        }
        n++;
        found[i] = 1;
    }
    if (n) {
        k = *turn & 0x7F;
        for (i = 0; i < 128; i++) {
            if (found[k]) {
                *turn = (k + 1) % 128;
                return &g_Entities[64 + k];
            }
            k = (k + 1) % 128;
        }
    }
    return NULL;
}

typedef struct {
    /* 0x78 */ u8 digits[4];
    /* 0x7C */ u16 number;
    /* 0x7E */ s16 type;
    /* 0x80 */ s16 nDigits;
    /* 0x82 */ u8 pad82[6];
    /* 0x88 */ s16 w;
    /* 0x8A */ s16 h;
    /* 0x8C */ s16 timer;
    /* 0x8E */ s16 x2;
    /* 0x90 */ s16 angle;
    /* 0x92 */ u8 pad92[2];
    /* 0x94 */ s16 spin;
    /* 0x96 */ u8 pad96[2];
    /* 0x98 */ s32 dist;
} AluHPNumExt;
#define ALU_HPNUM(e) ((AluHPNumExt*)&(e)->ext)

static u16 res_clut(u16 f) {
    return ((f >> 14) & 1) ? LocalLookupTblNoToVram(f & 0xFFF)
                           : SPR_2LookupTblNoToVram(f & 0xFFF);
}

void func_060B9694(Entity* self) {
    AluHPNumExt* ext = ALU_HPNUM(self);
    SaturnSpriteResource* res = DAT_060645EC[4];
    Primitive* p;
    s32 spark = -1, i, w, h, x, xb, yt, yb, r, k, tx, ty;
    u16 n;
    s16 a;

    switch (self->step) {
    case 0:
        n = ext->number;
        self->primIndex = AllocPrimitives(2, 0x14);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = 0x04810000;
        ext->w = 0;
        ext->h = 2;
        ext->timer = 8;
        ext->digits[0] = n % 10;
        if (n /= 10) {
            ext->digits[1] = n % 10;
            ext->nDigits++;
            if (n /= 10) {
                ext->digits[2] = n % 10;
                ext->nDigits++;
                if (n /= 10) {
                    ext->digits[3] = n % 10;
                    ext->nDigits++;
                }
            }
        }
        p = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 4; i++, p = p->next) {
            if (!ext->digits[i]) {
                ext->digits[i] = 10;
            }
            k = 6;
            if (!ext->number) {
                k = 7;
            }
            if (ext->type == 1) {
                k = 8;
            }
            if (ext->type == 2) {
                k = 0;
            }
            p->unk6 = res_clut(k + res->flags);
            p->unk4 &= ~0x38;
            p->unk6 = (p->unk6 & ~0x7000) | 0x4000;
            p->unk8 =
                DAT_0605AEC0[ext->digits[i] + 3 + res->allocationIndex][0];
            p->unkA =
                DAT_0605AEC0[ext->digits[i] + 3 + res->allocationIndex][1];
            if (i > ext->nDigits) {
                p->drawMode = 8;
            }
            p->priority = 0xE2;
        }
        for (i = 0; i < 16; i++, p = p->next) {
            p->type = 0x1004;
            p->unk4 = 0x4C0;
            p->priority = 0x92;
            p->unk6 = 0xA11F;
            if (!ext->number) {
                p->unk6 = 0xFD08;
            }
            if (ext->type == 1) {
                p->unk6 = 0xA3E8;
            }
            if (ext->type == 2) {
                p->unk6 = 0xFD1F;
            }
            p->drawMode = 0xA;
        }
        self->step++;
        break;
    case 1:
    case 3:
        ext->w++;
        ext->h++;
        if (ext->type != 2) {
            self->posY.i.hi--;
        }
        if (--ext->timer == 0) {
            ext->timer = self->step == 1 ? 8 : 3;
            self->step++;
        }
        break;
    case 2:
        ext->w--;
        ext->h--;
        if (ext->w == 4) {
            self->step++;
            ext->timer = 4;
        }
        break;
    case 4:
        ext->w--;
        ext->h--;
        if (ext->w == 5) {
            ext->timer = 0x18;
            self->step++;
        }
        break;
    case 5:
        if (--ext->timer == 0) {
            tx = self->posX.i.hi - 0xD;
            ty = self->posY.i.hi - 0x46;
            ext->angle = ratan2(-ty, tx) & 0xFFF;
            ext->dist = SquareRoot0(tx * tx + ty * ty);
            ext->timer = 0x10;
            ext->spin = 0;
            self->step++;
        }
        break;
    case 6:
        if (ext->w != 2) {
            ext->w--;
            ext->h--;
        }
        spark = --ext->timer;
        a = ext->angle;
        r = (u32)(ext->dist * spark) >> 4;
        self->posX.i.hi = (((rcos(a) >> 4) * r) >> 8) + 0xD;
        self->posY.i.hi = -(((rsin(a) >> 4) * r) >> 8) + 0x46;
        ext->spin += 0x100;
        self->posX.i.hi += rcos(ext->spin) >> 9;
        self->posY.i.hi -= rsin(ext->spin) >> 9;
        if (!ext->timer) {
            if (ext->type == 2) {
                DestroyEntity(self);
                return;
            }
            self->step++;
        }
        break;
    case 7:
    case 9:
        ext->w++;
        ext->h++;
        if (ext->w == 8) {
            self->step++;
            ext->timer = 0x18;
        }
        break;
    case 8:
        if (ext->w != 5) {
            ext->w--;
            ext->h--;
        } else {
            self->step++;
        }
        break;
    case 10:
        if (ext->w != 5) {
            ext->w--;
            ext->h--;
        }
        if (--ext->timer == 0) {
            self->step++;
        }
        break;
    case 11:
        ext->x2 += 2;
        self->posX.i.hi -= 2;
        if (!(--ext->timer & 2)) {
            ext->h--;
        }
        if (!ext->h) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    w = ext->w;
    h = ext->h;
    if (self->step != 0xB) {
        ext->x2 = self->posX.i.hi;
    }
    x = self->posX.i.hi + ext->nDigits * w;
    xb = ext->x2 + ext->nDigits * w;
    yt = self->posY.i.hi - 0x10 - h;
    yb = h + self->posY.i.hi - 0x10;
    p = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 4; i++, p = p->next) {
        p->x0 = x - w;
        p->y0 = yt;
        p->x1 = w + x;
        p->y1 = yt;
        p->x3 = xb - w;
        p->y3 = yb;
        p->x2 = w + xb;
        p->y2 = yb;
        x = x + 3 - w * 2;
        xb = xb + 3 - w * 2;
    }
    for (i = 0; i < 16; i++, p = p->next) {
        if (p->unkA) {
            if (--p->unk8 == 0) {
                p->drawMode = 8;
            }
            p->y0 = p->y1 = p->y3 = p->y2 = p->y0 + 1;
        } else if (spark == i) {
            p->drawMode &= ~8;
            p->x0 = p->x3 = p->x2 = p->x1 = self->posX.i.hi;
            p->y0 = p->y1 = p->y3 = p->y2 = self->posY.i.hi;
            p->unkA++;
            p->unk8 = 0xC;
        }
    }
}

void func_060BAB00(void) {
    s32 paused = g_unkGraphicsStruct.unk28;
    Entity* e;
    s32 i;
    u16 id;

    for (i = 4; i < 64; i++) {
        g_CurrentEntity = e = &g_Entities[i];
        if (i == 16 && e->entityId == 0) {
            g_Player.unk48 = 0;
        }
        id = e->entityId;
        if (!id) {
            continue;
        }
        if (!e->step) {
            e->pfnUpdate = player_entity_function(id);
        }
        if (paused && !(e->flags & 0x10000)) {
            continue;
        }
        e->pfnUpdate(e);
        e = g_CurrentEntity;
        if (!e->entityId) {
            continue;
        }
        if (!(e->flags & 0x04000000) && ((u16)(e->posX.i.hi + 0x18) > 0x170 ||
                                         (u16)(e->posY.i.hi + 0x10) > 0x110)) {
            DestroyEntity(e);
        } else if (e->flags & 0x100000) {
            func_060C175C(NULL, (AnimationFrame**)g_AlucardMiscFrameProperties);
        }
    }
    if ((u8)DAT_060CC9BC) {
        if (--DAT_060CC9BC & 1) {
            func_800EA5AC(
                1, (u8)DAT_060CE51C, (u8)DAT_060CE51D, (u8)DAT_060CE51E);
        }
    }
    DAT_060CE4F0[2] = 0;
    DAT_060CE4F0[1] = 0;
    if (g_Entities[16].enemyId == 1) {
        DAT_060CE4F0[1] = 1;
    } else if (g_Entities[16].enemyId == 2) {
        DAT_060CE4F0[2] = 1;
    }
    for (i = 3; i <= 10; i++) {
        DAT_060CE4F0[i] = 0;
    }
    for (i = 17; i < 48; i++) {
        id = g_Entities[i].entityId;
        if (id > 2) {
            if (id > 10) {
                ++*(s32*)sotn_satz_retail_address(0x060CE4F0 + id * 4);
            } else {
                DAT_060CE4F0[id]++;
            }
        }
    }
    if ((g_Player.status & 0xC0000) ||
        (g_Entities[0].step == 0x12 && g_Entities[0].step_s == 0)) {
        for (i = 4; i < 64; i++) {
            g_Entities[i].hitboxState = 0;
        }
    }
}

void func_060BAE70(void) {
    Entity* e;
    s32 i;

    if (g_Entities[0].unk0 == NULL) {
        return;
    }
    g_CurrentEntity = e = &g_Entities[4];
    for (i = 4; i < 64; i++) {
        if (!(e->flags & 0x00020000)) {
            DestroyEntity(e);
        }
        if ((u16)(e->entityId - 0x37) <= 5 && e->step) {
            e->pfnUpdate(e);
        }
        if ((e->flags & 0x02000000) && e->step) {
            e->flags |= 0x00200000;
            e->pfnUpdate(e);
            e->flags &= ~0x00200000;
        }
        e++;
        g_CurrentEntity = e;
    }
    func_060A7D68(1, 3);
    DAT_060CEB14 = 1;
}

Entity* func_060BAF44(Entity* source, u32 factoryParams, s32 arg2) {
    Entity* entity;
    s16 i;

    for (i = 8; i < 16; i++) {
        if (g_Entities[i].entityId == 0) {
            break;
        }
    }
    if (i >= 16) {
        return NULL;
    }
    entity = &g_Entities[i];
    DestroyEntity(entity);
    entity->entityId = 1;
    entity->ext.factory.parent = source;
    entity->posX.val = source->posX.val;
    entity->posY.val = source->posY.val;
    entity->facingLeft = source->facingLeft;
    entity->params = factoryParams & 0xFFF;
    if (factoryParams & 0x5000) {
        entity->ext.factory.entityIdMod = 0xE0;
    }
    if (factoryParams & 0xA000) {
        entity->ext.factory.entityIdMod = 0xF0;
    }
    entity->ext.factory.paramsBase = (factoryParams & 0xFF0000) >> 8;
    entity->ext.factory.unk8E = arg2;
    if (source->flags & 0x10000) {
        entity->flags |= 0x10000;
    }
    if (factoryParams & 0x1000) {
        entity->entityId = 0xEF;
    }
    if (factoryParams & 0x2000) {
        entity->entityId = 0xFF;
    }
    if (factoryParams & 0x4000) {
        entity->entityId = 0xED;
    }
    if (factoryParams & 0x8000) {
        entity->entityId = 0xFD;
    }
    return entity;
}

static Entity* first_free(s32 start, s32 end) {
    s32 j;

    for (j = start; j <= end; j++) {
        if (!g_Entities[j].entityId) {
            return &g_Entities[j];
        }
    }
    return NULL;
}

void func_060BB070(Entity* self) {
    ET_Factory* ext = (&(self)->ext.factory);
    AlucardFactoryBlueprint* bp;
    Entity* e;
    s32 i, j, n, start, end;

    if (self->step == 0) {
        bp = &g_AlucardFactoryBlueprints[self->params];
        ext->newEntityId = bp->childId;
        ext->amount = bp->amount;
        ext->nPerCycle = bp->packedCount & 0x3F;
        ext->isNonCritical = bp->packedCount >> 7;
        ext->incParamsKind = (bp->packedCount >> 6) & 1;
        ext->tCycle = bp->timerCycle;
        ext->kind = bp->packedOrigin & 0xF;
        ext->origin = bp->packedOrigin >> 4;
        ext->delay = bp->timerDelay;
        self->flags |= 0x04000000;
        self->step++;
        switch (ext->origin) {
        case 0:
        case 6:
            self->flags |= 0x08000000;
            break;
        case 4:
        case 5:
            self->flags |= 0x20000;
        case 2:
        case 7:
            self->posX.val = g_Entities[0].posX.val;
            self->posY.val = g_Entities[0].posY.val;
            break;
        }
    } else {
        switch (ext->origin) {
        case 2:
            self->posX.val = g_Entities[0].posX.val;
            self->posY.val = g_Entities[0].posY.val;
            break;
        case 4:
            self->posX.val = g_Entities[0].posX.val;
            self->posY.val = g_Entities[0].posY.val;
            if (g_Entities[0].step != 1 && g_Entities[0].step != 0x13) {
                self->entityId = 0;
                return;
            }
            break;
        case 5:
            self->posX.val = g_Entities[0].posX.val;
            self->posY.val = g_Entities[0].posY.val;
            if (g_Entities[0].step_s != 0x70) {
                self->entityId = 0;
                return;
            }
            break;
        case 7:
            self->posX.val = g_Entities[0].posX.val;
            self->posY.val = g_Entities[0].posY.val;
            if (g_Entities[0].step != 0xA) {
                self->entityId = 0;
                return;
            }
            break;
        }
    }
    if (ext->delay) {
        if (--ext->delay) {
            return;
        }
        ext->delay = ext->tCycle;
    }
    n = ext->nPerCycle;
    for (i = 0; i < n; i++) {
        if (ext->kind < 10) {
            start = g_AlucardEntityRanges.ranges[ext->kind][0];
            end = g_AlucardEntityRanges.ranges[ext->kind][1];
        } else {
            start = g_AlucardEffectAnim0[ext->kind - 10] >> 8;
            end = g_AlucardEffectAnim0[ext->kind - 10] & 0xFF;
        }
        e = NULL;
        if (ext->kind == 3 || (u16)(ext->kind - 10) <= 1 ||
            (u16)(ext->kind - 12) <= 1) {
            e = &g_Entities[start];
            DestroyEntity(e);
            g_Player.unk48 = 0;
        } else if (ext->kind == 0) {
            for (j = end; j >= start; j--) {
                if (!g_Entities[j].entityId) {
                    e = &g_Entities[j];
                    break;
                }
            }
        } else if (ext->kind == 8) {
            switch (ext->spawnIndex % 3) {
            case 0:
                e = first_free(17, 31);
                break;
            case 1:
                e = first_free(32, 47);
                break;
            case 2:
                e = first_free(48, 63);
                break;
            }
        } else {
            e = first_free(start, end);
        }
        if (!e) {
            if (ext->isNonCritical == 1) {
                self->entityId = 0;
                return;
            }
            break;
        }
        DestroyEntity(e);
        e->entityId = ext->newEntityId + ext->entityIdMod;
        e->params = ext->paramsBase;
        (&(e)->ext.factory)->parent = ext->parent;
        e->posX.val = self->posX.val;
        e->posY.val = self->posY.val;
        e->facingLeft = self->facingLeft;
        (&(e)->ext.factory)->argLow = ext->unk8E & 0x1FF;
        (&(e)->ext.factory)->argHigh = ext->unk8E >> 9;
        if (self->flags & 0x10000) {
            e->flags |= 0x10000;
        }
        e->params += ext->incParamsKind ? ext->spawnIndex : i;
        if (++ext->spawnIndex == ext->amount) {
            self->entityId = 0;
            return;
        }
    }
    ext->delay = ext->tCycle;
}

static u16 subweapon_def_a(SubweaponDef* d) {
    return (d->anim << 8) | d->blueprintNum;
}

extern s16 g_AlucardEffectPositionOffsets[6];
extern s32 g_AlucardEffectVelocities[6];
extern u16 g_AlucardEffectSizes[6];
extern u8 g_AlucardSubweaponFramePairs0[8][2];
extern u8 g_AlucardSubweaponFramePairs1[5][2];
extern AnimationFrame g_AlucardSubweaponAnim0[];
extern SaturnSpriteFrameHeader* g_SaturnSharedSpriteBank5Frames[];

void func_060BB968(Entity* self) {
    s32 lo, hi, i, x;
    SpriteObject* sprite;
    u8* pairs;

    switch (self->step) {
    case 0:
        lo = (u8)self->params;
        hi = self->params >> 8;
        if ((g_Player.status & 0x20000) && hi != 9) {
            DestroyEntity(self);
            return;
        }
        self->animSet = 5;
        self->anim = g_AlucardSubweaponAnim0;
        self->flags = 0x08110000;
        self->palette = 0x8195;
        self->unk1C = 0x10;
        self->drawFlags = 3;
        x = g_AlucardEffectPositionOffsets[lo];
        if (hi == 0) {
            x += 6;
        }
        if (hi == 1) {
            x -= 8;
        }
        if (hi == 2 || hi == 0xA) {
            x -= 2;
        }
        if (hi == 5) {
            x = -6;
        }
        if (hi == 6) {
            x = -0x18;
        }
        if (hi == 3) {
            x = MTH_GetRand() % 30 - 0xE;
            lo = (u8)((MTH_GetRand() & 3) + 2);
            self->posY.i.hi -= MTH_GetRand() & 3;
        }
        if (hi == 7) {
            x = MTH_GetRand() % 60 - 0x1E;
            lo = (u8)((MTH_GetRand() & 3) + 2);
            self->posY.i.hi -= MTH_GetRand() & 3;
        }
        if (hi == 9) {
            x = (MTH_GetRand() & 0xF) - 8;
            lo = (u8)((MTH_GetRand() & 3) + 2);
            self->posY.i.hi -= (MTH_GetRand() & 3) + 0x14;
        }
        if (hi == 4 || hi == 8) {
            s32 end = hi == 4 ? 14 : 10;
            pairs = hi == 4 ? &g_AlucardSubweaponFramePairs0[0][0]
                            : &g_AlucardSubweaponFramePairs1[0][0];
            for (i = lo * 2; i < end; i++) {
                if (g_Player.colWall[pairs[i]].effects & 3) {
                    break;
                }
            }
            if (i == end) {
                DestroyEntity(self);
                return;
            }
            self->posX.val = PLAYER.posX.val + g_AlucardSensorsWall[pairs[i]].x;
            self->posY.val = PLAYER.posY.val + g_AlucardSensorsWall[pairs[i]].y;
            if (hi == 4) {
                self->velocityY = -0x4000;
                self->scaleX = self->scaleY = g_AlucardEffectSizes[1] + 0x40;
            } else {
                self->velocityY = g_AlucardEffectVelocities[lo];
                self->scaleX = self->scaleY = g_AlucardEffectSizes[lo] + 0x20;
            }
            self->step++;
            return;
        }
        if (hi == 1 && (g_Player.vram_flag & 0x8000)) {
            x /= 2;
        }
        if (hi == 6) {
            if (PLAYER.velocityX > 0) {
                x = -x;
            }
        } else if (self->facingLeft) {
            x = -x;
        }
        self->posX.i.hi += x;
        self->posY.i.hi += 0x18;
        self->scaleX = g_AlucardEffectSizes[lo] + 0x40;
        self->velocityY = g_AlucardEffectVelocities[lo];
        if (hi == 1) {
            self->velocityY = -0x4000;
            self->velocityX = self->facingLeft == 1 ? 0x3000 : -0x3000;
            self->scaleX = g_AlucardEffectSizes[1] + 0x40;
        }
        if (hi == 5) {
            self->velocityY = g_AlucardEffectVelocities[4 - lo * 2];
        }
        self->scaleY = self->scaleX;
        if (hi == 0xA) {
            self->posY.i.hi -= 6;
        }
        sprite = CreateSpriteObject(
            g_SaturnSharedSpriteBank5Resource.allocationIndex,
            g_SaturnSharedSpriteBank5Resource.flags,
            g_SaturnSharedSpriteBank5Resource.images, 1);
        self->unk0 = sprite;
        if (!sprite) {
            DestroyEntity(self);
            return;
        }
        sprite->zPriority = PLAYER.zPriority + 2;
        self->ext.weapon.frames = g_SaturnSharedSpriteBank5Frames;
        self->step++;
        break;
    case 1:
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_060BBF5C(Primitive* prim) {
    u16 clut;

    if (g_Entities[0].animSet == 0xF) {
        return;
    }
    prim->unkA = ((DAT_060CE568->storedWidth >> 2) << 8) |
                 (u8)(DAT_060CE568->storedHeight * 2);
    clut = g_Entities[0].animSet == 0xD ? AlucardSpriteResources[3].flags
                                        : AlucardSpriteResources[0].flags;
    prim->unk6 = ((clut >> 14) & 1) ? LocalLookupTblNoToVram(clut & 0xFFF)
                                    : SPR_2LookupTblNoToVram(clut & 0xFFF);
}

static s32 colour_channel(s32 strength, s32 diff, s32 div) {
    u32 c = (u8)((sh2_div(strength * diff * 16, div) >> 12) + 0x10);
    return c > 0x1F ? 0x1F : c;
}

void func_060BC01C(Entity* self) {
    AluBlinkExt* ext = ALU_BLINK(self);
    s32 kind = (self->params >> 8) & 0x7F;
    s32 k = kind & 0x3F;
    SubweaponDef* def;
    Primitive* prim = NULL;
    SprGourTbl* gour;
    u16* g;
    SaturnSpriteImage* img;
    s32 i, x, y, dx = 0, dy = 0, w2 = 0x40, h2 = 0x40, wob, shaky, frame = 0;
    s32 divR, divG, divB, r, gg, b, d;
    s16 corner[4][2];
    u16 c;
    u16 st;
    Entity* e;

    if (g_Entities[0].animSet == 0xF) {
        DestroyEntity(self);
        return;
    }
    if ((k != 0x1D && (g_Player.status & 2)) ||
        (g_Player.status & 0x01000000)) {
        goto clear;
    }
    if (g_Player.unk6C && (u16)(kind - 0x20) > 1 && k != 0x1D) {
        g_Player.unk6E = 0;
        goto destroy;
    }
    if (g_Player.unk6E && (u16)(kind - 0x23) > 1 && k != 0x1D) {
        g_Player.unk6C = 0;
        goto destroy;
    }
    if ((g_Entities[0].step == 0x22 && g_Entities[0].palette == 0xFF) ||
        !g_Entities[0].animSet || !(g_Entities[0].animCurFrame & 0x7FFF)) {
        goto clear;
    }
    y = self->posY.i.hi = g_Entities[0].unk0->posY >> 16;
    x = self->posX.i.hi = g_Entities[0].unk0->posX >> 16;
    self->facingLeft = g_Entities[0].facingLeft;
    if (g_Entities[0].animSet == 1) {
        frame = g_Entities[0].animCurFrame & 0x7FFF;
        DAT_060CE560 = ((SaturnSpriteFrameHeader**)AlucardFrames)[frame];
        DAT_060CE564 = ((u16*)DAT_060CE560)[5];
        DAT_060CE568 = &AlucardImages[DAT_060CE564];
    }
    if (g_Entities[0].animSet == 0xD) {
        frame = g_Entities[0].animCurFrame & 0x7FFF;
        DAT_060CE560 =
            (SaturnSpriteFrameHeader*)g_AlucardEffectSpriteMetadataTable[frame];
        DAT_060CE564 = ((u16*)DAT_060CE560)[5];
        DAT_060CE568 = &AlucardFxImages[DAT_060CE564];
    }
    h2 = (u8)(DAT_060CE568->storedHeight * 2);
    w2 = (u8)(DAT_060CE568->storedWidth * 2);
    dy = ((s16*)DAT_060CE560)[4];
    dx = ((s16*)DAT_060CE560)[3];
    self->rotate = g_Entities[0].rotate;
    self->drawFlags = g_Entities[0].drawFlags;
    self->scaleX = g_Entities[0].scaleX;
    self->scaleY = g_Entities[0].scaleY;
    self->unk26 = g_Entities[0].unk26;
    self->unk24 = g_Entities[0].unk24;
    def = &g_AlucardSubweaponDefs[k];
    gour = &SpGourTbl[(u16)(self->primIndex + 0x100)];

    switch (self->step) {
    case 0:
        for (i = 16; i < 64; i++) {
            e = &g_Entities[i];
            if (e->entityId == self->entityId && e->params == self->params &&
                e != self) {
                goto destroy;
            }
        }
        self->primIndex = AllocPrimitives(0x8000, 1);
        if (self->primIndex == -1) {
            return;
        }
        self->flags = 0x04870000;
        prim = &g_PrimBuf[self->primIndex];
        func_060BBF5C(prim);
        prim->priority =
            ((u16)(kind - 0x20) <= 1 || (u16)(kind - 0x23) <= 1) ? 0x94 : 0x92;
        prim->drawMode = 0x304;
        ext->angleSpeed = def->entityRoomIndex;
        ext->strength = 0;
        ext->wobble = 0;
        ext->unk96 = 0x100;
        self->step++;
        switch (kind - 0x20) {
        case 0:
            self->step = 8;
            break;
        case 1:
            self->step = 0xA;
            break;
        case 3:
            self->step = 0xC;
            break;
        case 4:
            self->step = 0xE;
            break;
        case 6:
            self->step = 0x10;
            break;
        case 9:
            ext->strength = 0xFF;
            self->step = 0x13;
            break;
        }
        gour = &SpGourTbl[(u16)(self->primIndex + 0x100)];
        break;
    case 1:
        ext->strength += def->hitEffect == 0x7008 ? 0x50 : 0xA;
        if (ext->strength > 0x100) {
            ext->strength = 0x100;
            ext->timer = def->hitEffect;
            self->step++;
        }
        break;
    case 2:
        if (def->hitEffect > 0x6FFF) {
            ext->timer = 8;
            switch (def->hitEffect - 0x7000) {
            case 0:
                if (!g_Player.timers[1]) {
                    self->step++;
                }
                break;
            case 1:
            case 7:
                if (g_Entities[0].step != 0xA) {
                    self->step++;
                }
                break;
            case 2:
                if (!g_Player.timers[0]) {
                    self->step++;
                }
                ext->strength = g_Player.timers[0] * 0xC0 / 0x555 + 0x10;
                break;
            case 3:
                for (d = 0, i = 33; i < 49; i++) {
                    if (g_Entities[i].entityId == 0x11) {
                        d++;
                    }
                }
                if (!d) {
                    ext->timer = 0x14;
                    self->step++;
                }
                break;
            case 4:
                if (!g_unkGraphicsStruct.D_8009744C || IsRelicActive(0xE)) {
                    self->step++;
                }
                break;
            case 5:
            case 6:
                if (g_Player.anim != 0x33) {
                    self->step++;
                }
                break;
            case 8:
                if (!(g_Player.status & 0x400000)) {
                    self->step++;
                }
                break;
            case 9:
                if (g_Entities[0].step != 5 || g_Entities[0].step_s != 3) {
                    self->step++;
                }
            case 11:
                if (!(g_Player.status & 0x40000000)) {
                    self->step++;
                }
                break;
            }
        }
        if (--ext->timer == 0) {
            self->step++;
        }
        break;
    case 3:
        ext->strength -= 0xA;
        if (ext->strength < 0) {
            goto destroy;
        }
        break;
    case 8:
        g_Player.unk6C = 1;
        ext->wobbleAngle += 0x100;
        if (g_Entities[0].animSet != 0xF) {
            ext->wobble += 8;
            if (ext->wobble > 0x80) {
                ext->wobble = 0x80;
                g_Player.unk452 = 2;
                self->step++;
            }
        } else {
            ext->wobble += 0x10;
            if (ext->wobble > 0x100) {
                ext->wobble = 0x100;
                g_Player.unk452 = 2;
                self->step++;
            }
        }
        break;
    case 9:
    case 11:
        ext->wobble -= 8;
        ext->wobbleAngle += 0x100;
        if (ext->wobble < 0) {
            g_Player.unk452 = 3;
            self->params = 0x1B00;
            self->step = 1;
            g_Player.unk6C = 0;
            return;
        }
        break;
    case 10:
        g_Player.unk6C = 1;
        ext->wobble += 8;
        ext->wobbleAngle += 0x100;
        if (ext->wobble > 0x80) {
            ext->wobble = 0x80;
        }
        if ((u16)g_Player.unk452 == 1) {
            self->step++;
        }
        break;
    case 12:
        g_Player.unk6E = 1;
        ext->wobbleAngle += 0x100;
        ext->wobble += 0x10;
        if (ext->wobble > 0x100) {
            ext->wobble = 0x100;
            g_Player.unk452 = 2;
            self->step++;
        }
        break;
    case 13:
        ext->wobble -= 8;
        ext->wobbleAngle += 0x100;
        if (ext->wobble < 0) {
            g_Player.unk452 = 3;
            self->params = 0x2500;
            self->step = 1;
            g_Player.unk6E = 0;
            return;
        }
        break;
    case 14:
        g_Player.unk6E = 1;
        ext->wobble += 0x10;
        ext->wobbleAngle += 0x100;
        if (ext->wobble > 0x100) {
            ext->wobble = 0x100;
        }
        if ((u16)g_Player.unk452 == 1) {
            self->step++;
        }
        break;
    case 15:
        ext->wobble -= 8;
        ext->wobbleAngle += 0x100;
        if (ext->wobble < 0) {
            g_Player.unk452 = 3;
            self->params = 0x1B00;
            self->step = 1;
            g_Player.unk6E = 0;
            return;
        }
        break;
    case 17:
        ext->wobble += 4;
        ext->wobbleAngle += 0x100;
        if (ext->wobble > 0x60) {
            self->step++;
        }
        break;
    case 19:
        ext->strength -= 2;
        if (ext->strength < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        goto destroy;
    }

    shaky = (u16)(kind - 0x20) <= 1 || (u16)(kind - 0x23) <= 1 || kind == 0x26;
    wob = ext->wobble;
    ext->angle += ext->angleSpeed;
    x = self->facingLeft ? (s16)(x - dx) : (s16)(dx + x);
    y = (s16)(dy + y);
    prim = &g_PrimBuf[self->primIndex];
    prim->unkA = ((w2 >> 3) << 8) | h2;
    if (self->facingLeft) {
        prim->type |= 0x10;
    } else {
        prim->type &= ~0x10;
    }
    img = DAT_060CE568;
    prim->x2 = prim->x1 = img->storedWidth + x + w2;
    prim->x3 = prim->x0 = x - img->storedWidth;
    prim->y1 = prim->y0 = y - img->storedHeight;
    y += img->storedHeight;
    prim->y3 = prim->y2 = y + h2;
    if (!(kind & 0x40) && shaky) {
        s16 a = ext->wobbleAngle;
        s32 o = ((rsin(a) >> 7) * wob) / 256;
        prim->x0 += o;
        prim->x1 += o;
        o = ((rsin((s16)(a + 0x600)) >> 7) * wob) / 256;
        prim->x3 += o;
        prim->x2 += o;
    }
    g = (u16*)gour;
    if (!shaky) {
        if (kind == 0x29) {
            c = ext->strength * 0x421 + 0x8000;
            g[0] = g[1] = g[2] = g[3] = c;
        } else {
            divR = def->stunFrames;
            divB = (s16)subweapon_def_a(def);
            divG = (s16)def->hitboxState;
            SquareRoot0(img->storedWidth * img->storedWidth +
                        img->storedHeight * img->storedHeight);
            if (!(kind & 0x40)) {
                s32 s = (rsin(ext->angle) + 0x1000) >> 6;
                r = (u8)(sh2_div(s * ext->strength, divR) >> 3);
                gg = (u8)(sh2_div(s * ext->strength, divG) >> 3);
                b = (u8)(sh2_div(s * ext->strength, divB) >> 3);
                g[0] = g[1] = (b << 10) + (gg << 5) + r + 0x8000;
                g[2] = g[3] = 0xC210;
            } else {
                corner[0][0] = -img->storedWidth,
                corner[0][1] = -img->storedHeight;
                corner[1][0] = img->storedWidth,
                corner[1][1] = -img->storedHeight;
                corner[2][0] = img->storedWidth,
                corner[2][1] = img->storedHeight;
                corner[3][0] = -img->storedWidth,
                corner[3][1] = img->storedHeight;
                for (i = 0; i < 4; i++) {
                    d = (ext->angle - ratan2(corner[i][1], corner[i][0])) &
                        0xFFF;
                    if (d > 0x800) {
                        d = 0x1000 - d;
                    }
                    r = colour_channel(ext->strength, d, divR);
                    gg = colour_channel(ext->strength, d, divG);
                    b = colour_channel(ext->strength, d, divB);
                    g[i] = (b << 10) + (gg << 5) + r + 0x8000;
                }
            }
        }
    }
    func_060A7D68(1, 1);
    if (k == 0 || k == 7) {
        func_060AB44C(1, 10);
    }
    if (kind != 0x26 && kind != 0x29) {
        prim->type |= 0x5000;
        g_Entities[0].unk0->slotAndStreamId |= 0x80;
        st = 0;
        {
            u16* dst = (u16*)GetSpriteObjectGourTbl(g_Entities[0].unk0);
            for (i = 0; i < 4; i++) {
                dst[i] = g[i];
            }
        }
        (void)st;
    }
    return;
clear:
    g_Player.unk6E = 0;
    g_Player.unk6C = 0;
destroy:
    DestroyEntity(self);
    g_Entities[0].unk0->slotAndStreamId &= ~0x80;
}

static void glow_scale(Entity* self, s16 alpha, s16 grow) {
    ALU_GLOW(self)->alpha = alpha;
    self->scaleX = g_Entities[0].scaleX + grow;
    self->scaleY = g_Entities[0].scaleY + grow;
    self->unk26 = g_Entities[0].unk26;
    self->unk24 = g_Entities[0].unk24;
    ALU_GLOW(self)->timer = 8;
}

void func_060BCD98(Entity* self) {
    AluGlowExt* ext = ALU_GLOW(self);
    s32 kind;
    AluColorBlend* cfg;
    SpriteObject* obj;
    u16* g;
    s32 i;

    if ((g_Player.status & 0x01040087) ||
        !(g_Entities[0].animCurFrame & 0x7FFF) || !g_Entities[0].animSet ||
        g_Entities[0].step == 0x22) {
        DestroyEntity(self);
        return;
    }
    self->posX.i.hi = g_Entities[0].posX.i.hi;
    self->posY.i.hi = g_Entities[0].posY.i.hi;
    self->facingLeft = g_Entities[0].facingLeft;
    self->rotate = g_Entities[0].rotate;
    kind = (self->params >> 8) & 0x7F;
    self->drawFlags |= 3;
    cfg = &g_AlucardColorBlendConfigs[kind];
    switch (self->step) {
    case 0:
        self->unk0 = CreateSpriteObject(
            AlucardSpriteResources[0].allocationIndex,
            AlucardSpriteResources[0].flags + 2, AlucardImages, 2);
        if (!self->unk0) {
            DestroyEntity(self);
            return;
        }
        self->flags = 0x04070000;
        switch (kind) {
        case 0:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 17:
        case 18:
        case 20:
        case 22:
        case 23:
            glow_scale(self, 0x80, 0);
            break;
        case 2:
            glow_scale(self, 0xC0, 0);
            break;
        case 1:
            glow_scale(self, 0x100, 0);
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 14:
        case 15:
        case 16:
        case 19:
        case 21:
            glow_scale(self, 0x80, 0x60);
            break;
        }
        self->step++;
        break;
    case 1:
        switch (kind) {
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 14:
        case 15:
        case 16:
        case 18:
        case 21:
            ext->alpha += 0x10;
        case 0:
        case 1:
        case 2:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 17:
        case 19:
        case 20:
        case 22:
        case 23:
            if (--ext->timer == 0) {
                self->step++;
            }
            break;
        }
        break;
    case 2:
        switch (kind) {
        case 0:
        case 2:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 15:
        case 16:
        case 17:
        case 18:
        case 20:
        case 22:
        case 23:
            self->scaleX += 8;
            self->scaleY += 8;
            ext->alpha -= 5;
            if (ext->alpha < 0) {
                DestroyEntity(self);
                return;
            }
            break;
        case 1:
            self->scaleX += 2;
            self->scaleY += 2;
            ext->alpha -= 0x10;
            if (ext->alpha < 0) {
                DestroyEntity(self);
                return;
            }
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 14:
        case 19:
        case 21:
            self->scaleX -= 8;
            self->scaleY -= 8;
            if (self->scaleX <= 0x100) {
                self->scaleX = 0x100;
                self->scaleY = 0x100;
                ext->timer = 8;
                self->step++;
            }
            break;
        default:
            return;
        }
        break;
    case 3:
        if (--ext->timer == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    obj = self->unk0;
    func_0600B12C(obj, BODY);
    obj->flags &= ~8;
    obj->slotAndStreamId = (obj->slotAndStreamId & ~0x7F) | 5;
    obj->clutBase += 2;
    obj->zPriority = g_Entities[0].zPriority - 1;
    obj->flags |= 0x40;
    obj->rotate = 0;
    obj->scaleX = (u32)self->scaleX >> 2;
    obj->scaleY = (u32)self->scaleY >> 2;
    obj->slotAndStreamId |= 0x80;
    g = (u16*)GetSpriteObjectGourTbl(obj);
    for (i = 0; i < 4; i++) {
        g[i] = (cfg->b << 10) + (cfg->g << 5) + cfg->r + 0x8000;
    }
    func_060A7D68(1, 1);
}

void func_060BFB2C(Entity* self) {
    AluRingExt* ext = ALU_RING(self);
    s32 params = (u8)self->params;
    Primitive* p;
    s32 i, a0, a1, cx, cy, xa, ya, xb, yb, u0, u1, um;
    u16 idx, clut;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(2, 14);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        PlaySfx(0x687);
        self->flags = 0x04830000;
        func_060BAF44(self, 0x4A002C, 0);
        self->posX.i.hi = g_Entities[0].posX.i.hi;
        self->posY.i.hi = g_Entities[0].posY.i.hi - 0x30;
        p = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 14; i++) {
            idx = g_SaturnSharedSpriteBank4Resource.allocationIndex +
                  pad_060BFAF4[params * 14 + i];
            p->unk8 = DAT_0605AEC0[idx][0];
            p->unkA = DAT_0605AEC0[idx][1];
            clut = g_SaturnSharedSpriteBank4Resource.flags;
            p->unk6 = ((clut >> 14) & 1) ? LocalLookupTblNoToVram(clut & 0xFFF)
                                         : SPR_2LookupTblNoToVram(clut & 0xFFF);
            p->unk4 &= ~0x38;
            p->unk6 = (p->unk6 & ~0x7000) | 0x4000;
            p->priority = 0x1BE;
            p->drawMode = 4;
            p = p->next;
        }
        ext->timer = 0;
        ext->scaleX = 0x100;
        ext->scaleY = 0x100;
        ext->alpha = 0;
        ext->spin = 0x40;
        self->step++;
        DAT_060CE5B4 = 0;
        break;
    case 1:
        if (++DAT_060CE5B4 == 2) {
            g_unkGraphicsStruct.unk28 = 3;
        }
        ext->scaleX -= 8;
        ext->scaleY -= 8;
        ext->alpha += 6;
        if (ext->alpha > 0xFF) {
            ext->alpha = 0xFF;
        }
        if (ext->scaleY < 0) {
            ext->scaleY = 0;
        }
        if (ext->scaleX < 0) {
            ext->scaleX = 0;
            ext->timer = 0x20;
            for (i = 0, p = &g_PrimBuf[self->primIndex]; i < 14; i++,
                p = p->next) {
                p->drawMode = 0;
            }
            self->step++;
        }
        break;
    case 2:
        ext->scaleX = 8;
        ext->scaleY = 4;
        if (--ext->timer == 0) {
            func_060BAF44(self, 0xA0028, 0);
            for (i = 0, p = &g_PrimBuf[self->primIndex]; i < 14; i++,
                p = p->next) {
                p->drawMode = 4;
            }
            self->step++;
        }
        break;
    case 3:
        ext->scaleX += 0x10;
        ext->scaleY += 2;
        ext->alpha -= 6;
        if (ext->alpha < 0) {
            ext->alpha = 0;
        }
        if (ext->scaleX > 0x200) {
            g_unkGraphicsStruct.unk28 = 0;
            DestroyEntity(self);
            return;
        }
        break;
    }
    cx = (s16)(self->posX.i.hi - 0xB0);
    cy = self->posY.i.hi;
    p = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 14; i++) {
        a0 = g_AlucardEffectAngles[i];
        xa = (s16)((-(rsin(a0) >> 5) * ext->scaleX) / 256);
        ya = (s16)(((rcos(a0) >> 5) * ext->scaleY) / 256);
        a1 = g_AlucardEffectAngles[i + 1];
        xb = (s16)((-(rsin(a1) >> 5) * ext->scaleX) / 256);
        yb = (s16)(((rcos(a1) >> 5) * ext->scaleY) / 256);
        u0 = (s16)(i * 8 + 0x80);
        u1 = (s16)((i + 1) * 8 + 0x80);
        um = i == 0 ? 0x80 : (s16)((i - 1) * 8 + 0x80);
        if (i == 13) {
            u1 = u0;
        }
        p->x0 = ya + u0 + cx;
        p->x1 = u1 + cx + yb;
        p->x2 = yb + u0 + cx;
        p->x3 = ya + um + cx;
        p->y0 = cy + xa;
        p->y1 = cy + xb;
        p->y2 = cy + xb + 0x18;
        p->y3 = cy + xa + 0x18;
        g_AlucardEffectAngles[i] += ext->spin;
        p = p->next;
    }
}

static PfnEntityUpdate player_entity_function(u16 id) {
    if (id <= 0xCF) {
        return g_AlucardEntityFunctions[id];
    }
    if (id <= 0xDF) {
        if (id == 0xD0) {
            satz_die("familiar entity 0xD0");
        }
        return ((PfnEntityUpdate*)&g_BatServantDesc)[id - 0xD0];
    }
    switch (id) {
    case 0xEF:
    case 0xFF:
    case 0xED:
    case 0xFD:
        return g_AlucardEntityFunctions[1];
    case 0xEE:
    case 0xFE:
        return g_AlucardEntityFunctions[15];
    }
    if (id > 0xEF) {
        return (PfnEntityUpdate)((void**)g_Weapon1OvlArea)[id - 0xF0];
    }
    return (PfnEntityUpdate)((void**)g_Weapon0OvlArea)[id - 0xE0];
}

void func_060C1618(Entity* self) {
    SaturnSpriteFrameHeader** frames = self->ext.weapon.frames;
    SpriteObject* sprite = self->unk0;
    SaturnSpriteFrameHeader* frame;
    s32 n;

    if (!frames || !sprite) {
        return;
    }
    frame = frames[self->animCurFrame];
    sprite->flags = (sprite->flags & ~0x3F08) | (frame->header & 0x3F08);
    sprite->slotAndStreamId =
        (sprite->slotAndStreamId & ~0x7F) | (frame->commandFlags & 0x7F);
    func_0600B0B8(sprite->parts, frame + 1, (sprite->flags >> 8) & 0x3F);
    sprite->posX = self->posX.val;
    sprite->posY = self->posY.val;
    if (self->unk24) {
        sprite->posX += self->unk24 << 16;
    }
    if (self->unk26) {
        sprite->posY += self->unk26 << 16;
    }
    if (self->facingLeft) {
        sprite->flags |= 0x10;
    } else {
        sprite->flags &= ~0x10;
    }
    if (self->drawFlags & 0x80) {
        sprite->unk0C |= 0x80;
    }
    n = 0;
    if (self->drawFlags & 4) {
        sprite->rotate = self->rotate & 0xFFF;
        n = 1;
    }
    if (self->drawFlags & 1) {
        n++;
        sprite->scaleX = (u32)self->scaleX >> 2;
    }
    if (self->drawFlags & 2) {
        n++;
        sprite->scaleY = (u32)self->scaleY >> 2;
    }
    if (n) {
        sprite->flags |= 0x40;
    } else {
        sprite->flags &= ~0x40;
    }
}

s32 func_060C175C(s8* frameProps, AnimationFrame** anims) {
    Entity* e = g_CurrentEntity;
    AnimationFrame* f;
    s32 ret = 0;
    s8* hb;

    if (e->poseTimer == -1) {
        ret = -1;
    } else if (e->poseTimer == 0) {
        e->poseTimer = e->anim[e->pose].duration;
    } else if (--e->poseTimer == 0) {
        e->pose++;
        f = &e->anim[e->pose];
        if (f->duration == 0) {
            e->pose = f->pose;
            e->poseTimer = e->anim[e->pose].duration;
        } else if (f->duration == 0xFFFF) {
            e->pose--;
            e->poseTimer = -1;
            ret = -1;
        } else if (f->duration == 0xFFFE) {
            e->anim = anims[f->pose];
            e->pose = 0;
            ret = -2;
            e->poseTimer = e->anim->duration;
        } else {
            e->poseTimer = f->duration;
        }
    }
    if (frameProps) {
        e = g_CurrentEntity;
        hb = &frameProps[(e->anim[e->pose].pose >> 9) * 4];
        e->hitboxOffX = hb[0];
        e->hitboxOffY = hb[1];
        e->hitboxWidth = hb[2];
        e->hitboxHeight = hb[3];
    }
    e = g_CurrentEntity;
    e->animCurFrame = e->anim[e->pose].pose & 0x1FF;
    if (e->unk0) {
        func_060C1618(e);
    }
    return ret;
}
