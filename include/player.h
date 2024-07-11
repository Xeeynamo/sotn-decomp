#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

#include "collider.h"
#include "entity.h"
#include "familiar.h"
#include "spell.h"

#include <psxsdk/libgpu.h>

typedef enum {
    TELEPORT_CHECK_NONE = 0,
    TELEPORT_CHECK_TO_RTOP = 2,
    TELEPORT_CHECK_TO_TOP = 4
} TeleportCheck;

typedef struct {
    /* 80097964 */ u8 relics[30];
    /* 80097982 */ u8 spells[NUM_SPELLS];
    /* 8009798A */ u8 equipHandCount[169];
    /* 80097A33 */ u8 equipBodyCount[90];
    /* 80097A8D */ u8 equipHandOrder[169];
    /* 80097B36 */ u8 equipBodyOrder[90];
    /* 80097B90 */ u8 saveName[12];
    /* 80097B9C */ u32 spellsLearnt;
    /* 80097BA0 */ s32 hp;
    /* 80097BA4 */ s32 hpMax;
    /* 80097BA8 */ s32 hearts;
    /* 80097BAC */ s32 heartsMax;
    /* 80097BB0 */ s32 mp;
    /* 80097BB4 */ s32 mpMax;
    /* 80097BB8 */ s32 statsBase[4];
    /* 80097BC8 */ s32 statsEquip[4];
    /* 80097BD8 */ s32 statsTotal[4];
    /* 80097BE8 */ u32 level;
    /* 80097BEC */ u32 exp;
    /* 80097BF0 */ s32 gold;
    /* 80097BF4 */ s32 killCount;
    /* 80097BF8 */ u32 D_80097BF8;
    /* 80097BFC */ u32 subWeapon;
    /* 80097C00 */ u32 equipment[7];
    /* 80097C1C */ u32 attackHands[2]; // right hand, left hand
    /* 80097C24 */ s32 defenseEquip;
    /* 80097C28 */ u16 defenseElement;
    /* 80097C2A */ u16 D_80097C2A;
    /* 80097C2C */ u16 D_80097C2C;
    /* 80097C2E */ u16 D_80097C2E;
    /* 80097C30 */ s32 timerHours;
    /* 80097C34 */ s32 timerMinutes;
    /* 80097C38 */ s32 timerSeconds;
    /* 80097C3C */ s32 timerFrames;
    /* 80097C40 */ u32 D_80097C40;
    /* 80097C44 */ FamiliarStats statsFamiliars[NUM_FAMILIARS];
} PlayerStatus; /* size=0x334 */

extern PlayerStatus g_Status;
extern s32 g_DebugPlayer;

// Primitive used ad-hoc for the Player entity and the after-image effect
typedef struct {
    /* 0x00 */ RECT rect0;
    /* 0x08 */ RECT rect1;
    /* 0x10 */ RECT rect2;
    /* 0x18 */ u8 r0;
    /* 0x19 */ u8 g0;
    /* 0x1A */ u8 b0;
    /* 0x1B */ u8 enableColorBlend;
    /* 0x1C */ u8 r1;
    /* 0x1D */ u8 g1;
    /* 0x1E */ u8 b1;
    /* 0x1F */ u8 tpage;
    /* 0x20 */ u8 r2;
    /* 0x21 */ u8 g2;
    /* 0x22 */ u8 b2;
    /* 0x23 */ u8 flipX;
    /* 0x24 */ u8 r3;
    /* 0x25 */ u8 g3;
    /* 0x26 */ u8 b3;
    /* 0x27 */ u8 unk27;
} PlayerDraw; /* size = 0x28 */

extern PlayerDraw g_PlayerDraw[0x10];

#define PLAYER g_Entities[PLAYER_CHARACTER]

typedef struct {
    /* 80072BD0 */ Collider colliders[4];
    /* 80072C60 */ Collider colliders2[4];
    /* 80072CF0 */ Collider colliders3[14];
    /* 80072EE8 */ s32 padPressed;
    /* 80072EEC */ s32 padTapped;
    /* 80072EF0 */ s32 padHeld;
    /* 80072EF4 */ u32 padSim; // simulate input to force player actions
    /* 80072EF8 */ s32 D_80072EF8;
    /* 80072EFC */ s32 D_80072EFC; // stun timer
    // Known timers: 0 = poison, 1 = curse, 2 = visual from stoned/hit,
    //  13 = invincibility, 14 = invincibility from consumables
    /* 80072F00 */ s16 D_80072F00[16]; // poison timer

    // 0x01: touching the ground
    // 0x02: touching the ceiling
    // 0x04: touching the right wall
    // 0x08: touching the left wall
    // 0x20: in-air or near the edge
    // 0x0800: touching the ceiling slope
    // 0x1000: standing on a slightly ascending or descending slope
    // 0x4000: standing on a raising slope
    // 0x8000: standing on any slope
    /* 80072F20 */ s32 pl_vram_flag;

    /* 80072F24 */ s32 unk04; // copy of the previous field
    /* 80072F28 */ s32 unk08;
    /* 80072F2C */ u32 unk0C;
    /* 80072F30 */ s32 unk10;
    /* 80072F34 */ u32 unk14;
    /* 80072F38 */ s32 unk18;
    /* 80072F3C */ s32 unk1C;
    /* 80072F40 */ s32 unk20;
    /* 80072F44 */ s32 unk24;
    /* 80072F48 */ s32 unk28;
    /* 80072F4C */ s32 unk2C;
    /* 80072F50 */ s32 unk30;
    /* 80072F54 */ s32 unk34;
    /* 80072F58 */ s32 unk38;
    /* 80072F5C */ s32 unk3C;
    /* 80072F60 */ u16 unk40;
    /* 80072F62 */ u16 pl_high_jump_timer;
    /* 80072F64 */ u16 unk44;
    /* 80072F66 */ u16 unk46;
    /* 80072F68 */ u16 unk48;
    /* 80072F6A */ s16 unk4A;
    /* 80072F6C */ u16 unk4C;
    /* 80072F6E */ u16 unk4E;
    /* 80072F70 */ u16 unk50;
    /* 80072F72 */ u16 unk52;
    /* 80072F74 */ u16 unk54;
    /* 80072F76 */ u16 unk56;
    /* 80072F78 */ u16 unk58;
    /* 80072F7A */ u16 damageTaken;
    /* 80072F7C */ u16 unk5C;
    /* 80072F7E */ u16 unk5E; // status ailment timer
    /* 80072F80 */ u16 unk60;
    /* 80072F82 */ u16 unk62;
    /* 80072F84 */ u16 unk64;
    /* 80072F86 */ u16 unk66;
    /* 80072F88 */ u16 unk68;
    /* 80072F8A */ u16 unk6A;
    /* 80072F8C */ u16 unk6C;
    /* 80072F8E */ u16 unk6E;
    /* 80072F90 */ u16 unk70;
    /* 80072F92 */ u16 unk72;
    /* 80072F94 */ u32 unk74;
    /* 80072F98 */ u16 unk78;
    /* 80072F9A */ u16 unk7A;
    /* 80072F9C */ u16 unk7C;
    /* 80072F9E */ u16 unk7E;
} PlayerState;

extern PlayerState g_Player;

// the following are most likely part of g_Player
extern Entity* D_psp_091CF3A0;
extern s32 D_psp_091CF3A4; // maybe not s32 but a pointer?
extern void (*D_psp_091CF3A8)(Entity*);
extern s32 D_psp_091CF3AC; // maybe not s32 but a pointer?
extern u16 D_psp_091CF3DC;

extern s32 g_PlayerX;
extern s32 g_PlayerY;

/* 0x8003C9A0 */ extern s32 g_PlayableCharacter;
/* 0x8003C9A4 */ extern u32 D_8003C9A4; // when player change stages?
                                           // overlap, hard to remove
typedef enum {
    Player_Stand,
    Player_Walk,
    Player_Crouch,
    Player_Fall,
    Player_Jump,
    Player_MorphBat,
    Player_AlucardStuck,
    Player_MorphMist,
    Player_HighJump,
    Player_UnmorphBat,
    Player_Hit,
    Player_StatusStone,
    Player_BossGrab, // Darkwing Bat and Akmodan II
    Player_KillWater,
    Player_UnmorphMist,
    Player_SwordWarp, // Alucard Sword and Osafune Katana
    Player_Kill,
    Player_Unk17,
    Player_Teleport, // also Grand Cross and Spiral Axe
    Player_FlameWhip,
    Player_Hydrostorm,
    Player_ThousandBlades,
    Player_RichterFourHolyBeasts,
    Player_Slide,
    Player_MorphWolf,
    Player_UnmorphWolf,
    Player_SlideKick,
    Player_Unk27, // other item crashes
    Player_SpellDarkMetamorphosis = 32,
    Player_SpellSummonSpirit,
    Player_SpellHellfire,
    Player_SpellTetraSpirit,
    Player_Spell36,
    Player_SpellSoulSteal,
    Player_Unk38,
    Player_SpellSwordBrothers,
    Player_AxearmorStand,
    Player_AxearmorWalk,
    Player_AxearmorJump,
    Player_AxearmorHit,
    Player_Unk48 = 48,
    Player_Unk49,
    Player_Unk50
} PlayerSteps;

#define PLAYER_ALUCARD 0
#define PLAYER_RICHTER 1
#define PLAYER_MARIA 2

#define MAX_GOLD 999999

#define PLAYER_STATUS_BAT_FORM 0x00000001
#define PLAYER_STATUS_MIST_FORM 0x00000002
#define PLAYER_STATUS_WOLF_FORM 0x00000004
#define PLAYER_STATUS_UNK_20 0x00000020
#define PLAYER_STATUS_TRANSFORM                                                \
    (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM | PLAYER_STATUS_WOLF_FORM)
#define PLAYER_STATUS_STONE 0x00000080
#define PLAYER_STATUS_POISON 0x00004000
#define PLAYER_STATUS_CURSE 0x00008000
#define PLAYER_STATUS_UNK10000 0x10000 // possibly freezing?
#define PLAYER_STATUS_UNK400000 0x400000
#define PLAYER_STATUS_AXEARMOR 0x01000000
#define PLAYER_STATUS_ABSORB_BLOOD 0x02000000
#define PLAYER_STATUS_UNK40000000 0x40000000

#define HEART_VESSEL_INCREASE 5
#define HEART_VESSEL_RICHTER 30
#define LIFE_VESSEL_INCREASE 5
#define FALL_GRAVITY 0x4000
#define FALL_TERMINAL_VELOCITY 0x60000

#endif
