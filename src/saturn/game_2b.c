// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "game.h"
#include "lib/scl.h"
#define _SPR2_
#include "lib/spr/spr.h"

void PlaySfx(s32 sfxId);

extern s32 DAT_00292000;

s32* func_060784A8(void) { return &DAT_00292000; }

INCLUDE_ASM("asm/saturn/game/f_nonmat", f60784B8, func_060784B8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078550, func_06078550);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078604, func_06078604);

// _disp_num_string
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078684, func_06078684);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607872C, func_0607872C);

extern s32 DAT_06086390;

char* func_06078748(s32 id) {
    char* ret = NULL;
    switch (DAT_06086390) {
    case 1:
        if (id < 0xB0) {
            Equipment* equip = &g_EquipDefs[id];
            ret = equip->name;
        } else {
            Accessory* acc;
            id -= 0xB0;
            acc = &g_AccessoryDefs[id];
            ret = acc->name;
        }
        break;
    case 3: {
        RelicDesc* relic = &g_RelicDefs[id];
        ret = relic->name;
    } break;
    case 2: {
        SpellDef* spell = &g_SpellDefs[id];
        ret = spell->name;
    } break;
    }
    return ret;
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f60787C8, func_060787C8);

// _SubDispSpecial
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078920, func_06078920);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60789C4, func_060789C4);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078D58, func_06078D58);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078E80, func_06078E80);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078F58, func_06078F58);

// _SubDispSortKind
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079008, func_06079008);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60790B4, func_060790B4);

// _SubDispFace
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079208, func_06079208);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60792B8, func_060792B8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079424, func_06079424);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079580, func_06079580);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079670, func_06079670);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607973C, func_0607973C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60797FC, func_060797FC);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079958, func_06079958);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079A2C, func_06079A2C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079AF0, func_06079AF0);

// original name: normal_move
inline void NormalMove(Entity* entity) {
    Unk0600B344* temp = entity->unk0;

    if (temp != NULL) {
        temp->unk14 += entity->velocityX;
        temp->unk18 += entity->velocityY;
        entity->posX.val = temp->unk14;
        entity->posY.val = temp->unk18;
    }
}

inline void MoveEntity(Entity* entity) {
    entity->posX.val += entity->velocityX;
    entity->posY.val += entity->velocityY;
}

inline void func_06079BB4(Entity* entity) {
    Unk0600B344* temp = entity->unk0;

    if (temp != NULL) {
        temp->unk14 = entity->posX.val;
        temp->unk18 = entity->posY.val;
    }
}

inline void func_06079BCC(Entity* entity) {
    Unk0600B344* temp = entity->unk0;

    if (temp != NULL) {
        entity->posX.val = temp->unk14;
        entity->posY.val = temp->unk18;
    }
}

inline void FallEntity(Entity* entity) {
#define TERMINAL_VELOCITY FIX(6)
#define GRAVITY FIX(0.25f)

    if (entity->velocityY < TERMINAL_VELOCITY) {
        entity->velocityY += GRAVITY;
    }
}

s32 UnkCollisionFunc3(Entity* entity, s16* sensors) {
    Collider col;
    Collider colBack;
    s16 x, y;
    s16 i;

    NormalMove(entity);
    FallEntity(entity);
    func_06079BCC(entity);

    if (entity->velocityY >= 0) {
        x = entity->posX.i.hi;
        y = entity->posY.i.hi;
        for (i = 0; i < 4; i++) {
            x += *sensors++;
            y += *sensors++;
            CheckCollision(x * 0x10000, y * 0x10000, &col, 0);
            if ((col.effects & EFFECT_UNK_8000) && i == 1) {
                if (col.effects & EFFECT_SOLID) {
                    CheckCollision(x * 0x10000, (y - 8) * 0x10000, &colBack, 0);
                    if (colBack.effects & EFFECT_SOLID) {
                        continue;
                    }
                    entity->posY.i.hi += col.unk18 / 0x10000 + 4;
                    entity->velocityX = 0;
                    entity->velocityY = 0;
                    entity->flags &= ~FLAG_UNK_10000000;
                    func_06079BB4(entity);
                    return 1;
                }
            } else if ((col.effects & EFFECT_NOTHROUGH) && i != 1) {
                if (col.effects & EFFECT_QUICKSAND) {
                    entity->flags &= ~FLAG_UNK_10000000;
                    return 4;
                }
                CheckCollision(x * 0x10000, (y - 8) * 0x10000, &colBack, 0);
                if (colBack.effects & EFFECT_SOLID) {
                    continue;
                }
                entity->posY.i.hi += col.unk18 / 0x10000;
                entity->velocityX = 0;
                entity->velocityY = 0;
                entity->flags &= ~FLAG_UNK_10000000;
                func_06079BB4(entity);
                return 1;
            }
        }
    }
    entity->flags |= FLAG_UNK_10000000;
    func_06079BB4(entity);
    return 0;
}

s32 UnkCollisionFunc2(Entity* entity, s16* posX) {
    Collider collider;
    s16 x, y;

    func_06079BCC(entity);
    entity->posX.val += entity->velocityX;
    entity->posY.i.hi += 3;
    x = entity->posX.i.hi + *posX++;
    y = entity->posY.i.hi + *posX++;
    CheckCollision(x * 0x10000, y * 0x10000, &collider, 0);
    if (collider.effects & EFFECT_SOLID) {
        entity->posY.i.hi += collider.unk18 / 0x10000;
    } else {
        func_06079BB4(entity);
        return 0;
    }
    if (entity->velocityX != 0) {
        if (entity->velocityX < 0) {
            x -= *posX++;
        } else {
            x += *posX++;
        }
        y += *posX++;
        y -= 7;
        CheckCollision(x * 0x10000, y * 0x10000, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if ((collider.effects & (EFFECT_UNK_8000 | EFFECT_UNK_0002)) ==
                EFFECT_UNK_0002) {
                entity->posX.val -= entity->velocityX;
                entity->velocityX = 0;
                func_06079BB4(entity);
                return 0xFF;
            } else {
                func_06079BB4(entity);
                return 0x61;
            }
        }
        y += 0xF;
        CheckCollision(x * 0x10000, y * 0x10000, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if (collider.effects & EFFECT_UNK_8000) {
                func_06079BB4(entity);
                return 0x61;
            } else {
                func_06079BB4(entity);
                return 1;
            }
        } else {
            entity->posX.val -= entity->velocityX;
            entity->velocityX = 0;
            func_06079BB4(entity);
            return 0x80;
        }
    } else {
        func_06079BB4(entity);
        return 1;
    }
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079F60, func_06079F60);

// _v_side_hosei
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607A030, func_0607A030);

u8 CheckColliderOffsets(Entity* entity, s16* arg0, u8 facing) {
    Collider collider;
    s16 posX, posY;
    u8 ret;

    if (g_CurrentEntity->unk0 != NULL) {
        func_06079BCC(entity);
    }
    ret = 0;
    while (*arg0 != 0xFF) {
        ret <<= 1;
        if (facing) {
            posX = entity->posX.i.hi + *arg0++;
        } else {
            posX = entity->posX.i.hi - *arg0++;
        }
        posY = entity->posY.i.hi + *arg0++;
        CheckCollision(posX * 0x10000, posY * 0x10000, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            ret |= 1;
        }
    }
    return ret;
}

bool UnkCollisionFunc5(Entity* entity, s16* pointXY) {
    Collider collider;

    FallEntity(entity);
    func_06079BCC(entity);
    MoveEntity(entity);

    if (entity->velocityY >= 0) {
        s16 posX = entity->posX.i.hi + pointXY[0];
        s16 posY = entity->posY.i.hi + pointXY[1];
        CheckCollision(posX * 0x10000, posY * 0x10000, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            entity->posY.i.hi += collider.unk18 / 0x10000;
            entity->velocityY = -entity->velocityY / 2;
            func_06079BB4(entity);
            if (entity->velocityY > FIX(-1.0)) {
                return true;
            }
        }
    }
    return false;
}

u8 UnkCollisionFunc4(Entity* entity, u8 arg1) {
    Collider collider;
    u8 bits_01;
    u8 bits_23;
    u8 bits_45;
    u8 bits_67;
    u16 collEff;
    s16 posX, posY;

    NormalMove(entity);
    func_06079BCC(entity);

    bits_67 = 0;
    bits_23 = 0;
    bits_45 = 0;
    collEff = 0;
    bits_01 = arg1 & 3;
    switch (bits_01) {
    case 0:
        entity->posY.i.hi += 3;
        posX = entity->posX.i.hi;
        posY = entity->posY.i.hi;
        CheckCollision(posX * 0x10000, posY * 0x10000, &collider, 0);
        if (collider.effects) {
            collEff = collider.effects;
            entity->posY.i.hi += collider.unk18 / 0x10000;
            posX = entity->posX.i.hi;
            posY = entity->posY.i.hi - 4;
            CheckCollision(posX * 0x10000, posY * 0x10000, &collider, 0);
            if (collider.effects & EFFECT_UNK_0002) {
                bits_67 = 0x40;
                if (entity->velocityX > 0) {
                    bits_01 = 2;
                } else {
                    bits_01 = 3;
                    entity->velocityX = -entity->velocityX;
                }
                entity->velocityY = -entity->velocityX;
                entity->velocityX = 0;
            }
        } else {
            bits_67 = 0x80;
            entity->posX.val -= entity->velocityX;
            if (entity->velocityX > 0) {
                bits_01 = 3;
            } else {
                bits_01 = 2;
                entity->velocityX = -entity->velocityX;
            }
            entity->velocityY = entity->velocityX;
            entity->velocityX = 0;
        }
        break;
    case 1:
        entity->posY.i.hi -= 3;
        posX = entity->posX.i.hi;
        posY = entity->posY.i.hi;
        CheckCollision(posX * 0x10000, posY * 0x10000, &collider, 0);
        if (collider.effects) {
            collEff = collider.effects;
            entity->posY.i.hi += collider.unk20 / 0x10000;
            posX = entity->posX.i.hi;
            posY = entity->posY.i.hi + 4;
            CheckCollision(posX * 0x10000, posY * 0x10000, &collider, 0);
            if (collider.effects & EFFECT_UNK_0002) {
                bits_67 = 0x40;
                if (entity->velocityX > 0) {
                    bits_01 = 2;
                } else {
                    bits_01 = 3;
                    entity->velocityX = -entity->velocityX;
                }
                entity->velocityY = entity->velocityX;
                entity->velocityX = 0;
            }
        } else {
            bits_67 = -0x80;
            entity->posX.val -= entity->velocityX;
            if (entity->velocityX > 0) {
                bits_01 = 3;
            } else {
                bits_01 = 2;
                entity->velocityX = -entity->velocityX;
            }
            entity->velocityY = -entity->velocityX;
            entity->velocityX = 0;
        }
        break;
    case 2:
        entity->posX.i.hi += 3;
        posX = entity->posX.i.hi;
        posY = entity->posY.i.hi;
        CheckCollision(posX * 0x10000, posY * 0x10000, &collider, 0);
        if (collider.effects) {
            collEff = collider.effects;
            entity->posX.i.hi += collider.unk14 / 0x10000;
            posX = entity->posX.i.hi - 4;
            posY = entity->posY.i.hi;
            CheckCollision(posX * 0x10000, posY * 0x10000, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                bits_67 = 0x40;
                if (entity->velocityY > 0) {
                    bits_01 = 0;
                } else {
                    bits_01 = 1;
                    entity->velocityY = -entity->velocityY;
                }
                entity->velocityX = -entity->velocityY;
                entity->velocityY = 0;
            }
        } else {
            bits_67 = 0x80;
            entity->posY.val -= entity->velocityY;
            if (entity->velocityY > 0) {
                bits_01 = 1;
            } else {
                bits_01 = 0;
                entity->velocityY = -entity->velocityY;
            }
            entity->velocityX = entity->velocityY;
            entity->velocityY = 0;
        }
        break;
    case 3:
        entity->posX.i.hi -= 3;
        posX = entity->posX.i.hi;
        posY = entity->posY.i.hi;
        CheckCollision(posX * 0x10000, posY * 0x10000, &collider, 0);
        if (collider.effects) {
            collEff = collider.effects;
            entity->posX.i.hi += collider.unk1C / 0x10000;
            posX = entity->posX.i.hi + 4;
            posY = entity->posY.i.hi;
            CheckCollision(posX * 0x10000, posY * 0x10000, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                bits_67 = 0x40;
                if (entity->velocityY > 0) {
                    bits_01 = 0;
                } else {
                    bits_01 = 1;
                    entity->velocityY = -entity->velocityY;
                }
                entity->velocityX = entity->velocityY;
                entity->velocityY = 0;
            }
        } else {
            bits_67 = 0x80;
            entity->posY.val -= entity->velocityY;
            if (entity->velocityY > 0) {
                bits_01 = 1;
            } else {
                bits_01 = 0;
                entity->velocityY = -entity->velocityY;
            }
            entity->velocityX = -entity->velocityY;
            entity->velocityY = 0;
        }
        break;
    }

    func_06079BB4(entity);

    if (collEff & 0x8000) {
        bits_23 = 4;
    }
    if (collEff & 0x1000) {
        bits_23 = 8;
    }
    if (collEff & 0x2000) {
        bits_23 = 0xC;
    }
    if (collEff & 0x0800) {
        bits_45 = 0x20;
    }
    if (collEff & 0x4000) {
        bits_45 = 0x10;
    }
    bits_01 = bits_01 + bits_67 + bits_23 + bits_45;
    return bits_01;
}

u8 GetPlayerCollisionWith(Entity* self, u16 w, u16 h, u16 flags) {
    Entity* player;
    s16 x, y;
    u16 checks;
    Collider col;
    s32 plStatus;

    plStatus = g_Player.status;
    player = &PLAYER;

    x = g_CurrentEntity->posX.i.hi;
    y = g_CurrentEntity->posY.i.hi;
    if (x > 0x160 || x < -0x20 || y < -0x180 || y > 0x180) {
        return 0;
    }

    x = player->posX.i.hi - x;
    y = player->posY.i.hi - y;

    if (g_CurrentEntity->facingLeft) {
        x += g_CurrentEntity->hitboxOffX;
    } else {
        x -= g_CurrentEntity->hitboxOffX;
    }
    y -= g_CurrentEntity->hitboxOffY;

    GetPlayerSensor(&col);
    w += col.unk14 >> 0x10;
    h += col.unk18 >> 0x10;

    if (x > 0) {
        checks = 1;
    } else {
        checks = 0;
    }
    if (y > 0) {
        checks |= 2;
    }
    x += w;
    y += h;
    w += w;
    h += h;

    if ((u16)x <= w && (u16)y <= h) {
        if (x != 0 && x != w) {
            if ((flags & 4) && checks ^ 2 && player->velocityY >= 0) {
                if (y < 8) {
                    player->posY.i.hi -= y;
                    g_unkGraphicsStruct.shoveY.i.hi -= y;
                    g_Player.vram_flag |= VRAM_FLAG_UNK40 | TOUCHING_GROUND;
                    if (plStatus & 3) {
                        return 0;
                    }
                    return 4;
                }
            }
            if ((flags & 2) && (checks & 2) &&
                (player->velocityY <= 0 || (flags & 0x10))) {
                y = h - y;
                if (y < 0x10) {
                    player->posY.i.hi += y;
                    g_unkGraphicsStruct.shoveY.i.hi += y;
                    g_Player.vram_flag |= VRAM_FLAG_UNK40 | TOUCHING_CEILING;
                    if (plStatus & 3) {
                        return 0;
                    }
                    return 2;
                }
            }
        }
        if (y != 0 && y != h) {
            if (flags & 1) {
                if (checks & 1) {
                    x = w - x;
                    if (flags & 8 && x > 2) {
                        x = 2;
                    }
                    player->posX.i.hi += x;
                    g_unkGraphicsStruct.shoveX.i.hi += x;
                    g_Player.vram_flag |= VRAM_FLAG_UNK40 | TOUCHING_L_WALL;
                    return 1;
                } else {
                    if (flags & 8 && x > 2) {
                        x = 2;
                    }
                    player->posX.i.hi -= x;
                    g_unkGraphicsStruct.shoveX.i.hi -= x;
                    g_Player.vram_flag |= VRAM_FLAG_UNK40 | TOUCHING_R_WALL;
                    return 1;
                }
            }
        }
    }
    return 0;
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607A88C, func_0607A88C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607A994, func_0607A994);

// SAT func_0607A9F8
// Original name: _hkyori_search
// Absolute distance from the specified entity to the player in the X Axis
s32 GetDistanceToPlayerX(Entity* self) {
    s16 xDistance = self->posX.i.hi - PLAYER.posX.i.hi;

    if (xDistance < 0) {
        xDistance = -xDistance;
    }
    return xDistance;
}

// SAT func_0607AA1C
// Absolute distance from the specified entity to the player in the Y Axis
s32 GetDistanceToPlayerY(Entity* self) {
    s16 yDistance = self->posY.i.hi - PLAYER.posY.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AA40, func_0607AA40);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AA74, func_0607AA74);

void func_0607AAA4(Entity* entity) {
    Entity* player = &PLAYER;
    Unk0600B344* temp = entity->unk0;

    if (temp->unk14 >= player->posX.val) {
        entity->facingLeft = 0;
    } else {
        entity->facingLeft = 1;
    }
}

void func_0607AACC(Entity* entity) {
    Entity* player = &PLAYER;
    Unk0600B344* temp = entity->unk0;

    if (temp->unk14 >= player->posX.val) {
        entity->facingLeft = 1;
    } else {
        entity->facingLeft = 0;
    }
}

// SAT func_0607AAF4
/*
 * Returns the player's side position relative to g_CurrentEntity
 * 0 = Player is on the right side
 * 1 = Player is on the left side
 * 2 = Player is above
 */
s32 GetSideToPlayer(Entity* self) {
    Entity* player = &PLAYER;
    s16 side = 0;

    if (self->posX.val > player->posX.val) {
        side = 1;
    }

    if (self->posY.val > player->posY.val) {
        side |= 2;
    }
    return side;
}

// func_0607AB1C
// saturn unique?
s32 GetSideToPlayer2(Entity* self) {
    s16 side = 0;

    if (g_CurrentEntity->posX.val > PLAYER.posX.val) {
        side = 1;
    }
    if (g_CurrentEntity->posY.val > PLAYER.posY.val) {
        side |= 2;
    }

    return side;
}

// original name: bicyousei_dir_0
void BicyouseiDir0(Entity* entity) {
    Unk0600B344* temp = entity->unk0;

    if (temp->unk14 >= PLAYER.posX.val) {
        temp->unk0 &= ~0x10;
        entity->facingLeft = 0;
    } else {
        temp->unk0 |= 0x10;
        entity->facingLeft = 1;
    }
}

void BicyouseiDir1(Entity* entity) {
    Unk0600B344* temp = entity->unk0;

    if (temp->unk14 >= PLAYER.posX.val) {
        temp->unk0 |= 0x10;
        entity->facingLeft = 0;
    } else {
        temp->unk0 &= ~0x10;
        entity->facingLeft = 1;
    }
}

// original name: hanten_dir_0
bool HantenDir0(Entity* entity) {
    Unk0600B344* temp = entity->unk0;
    bool ret = false;
    Entity* player = &PLAYER;

    if (entity->facingLeft == 0) {
        if (temp->unk14 < player->posX.val) {
            ret = true;
        }
    } else {
        if (temp->unk14 > player->posX.val) {
            ret = true;
        }
    }
    return ret;
}

bool HantenDir1(Entity* entity) {
    Unk0600B344* temp = entity->unk0;
    bool ret = false;
    Entity* player = &PLAYER;

    if (entity->facingLeft == 0) {
        if (temp->unk14 > player->posX.val) {
            ret = true;
        }
    } else {
        if (temp->unk14 < player->posX.val) {
            ret = true;
        }
    }
    return ret;
}

u8 func_0607AC2C(void) { return PLAYER.facingLeft; }

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AC40, func_0607AC40);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AE48, func_0607AE48);

Entity* FindFirstFreeEntity(s16 start, s16 end) {
    Entity* current = &g_Entities[start];

    while (start < end) {
        if (current->entityId == 0) {
            return current;
        }
        start++;
        current++;
    }
    return NULL;
}

extern s16 g_SineTable[];

inline s32 GetSineScaled(u8 arg0, s16 arg1) {
    s32 sine = g_SineTable[arg0];
    return sine * arg1;
}

s16 GetSine(u8 arg0) { return g_SineTable[arg0]; }

void SetEntityVelocityFromAngle(Entity* entity, u8 arg0, s16 arg1) {
    entity->velocityX = GetSineScaled(arg0, arg1);
    entity->velocityY = GetSineScaled(arg0 - 0x40, arg1);
}

inline u8 Ratan2Shifted(s16 x, s16 y) {
    u8 angle = ratan2(y, x) >> 4;
    return angle + 0x40;
}

u8 GetAngleBetweenEntitiesShifted(Entity* a, Entity* b) {
    s16 dx = b->posX.i.hi - a->posX.i.hi;
    s16 dy = b->posY.i.hi - a->posY.i.hi;
    return Ratan2Shifted(dx, dy);
}

// original name: search_point
u8 GetAnglePointToEntityShifted(Entity* entity, s16 x, s16 y) {
    s16 dx = x - entity->posX.i.hi;
    s16 dy = y - entity->posY.i.hi;

    return Ratan2Shifted(dx, dy);
}

u8 AdjustValueWithinThreshold(u8 threshold, u8 currentValue, u8 targetValue) {
    u8 absoluteDifference;
    s8 relativeDifference = targetValue - currentValue;

    if (relativeDifference < 0) {
        absoluteDifference = -relativeDifference;
    } else {
        absoluteDifference = relativeDifference;
    }

    if (absoluteDifference > threshold) {
        if (relativeDifference < 0) {
            absoluteDifference = currentValue - threshold;
        } else {
            absoluteDifference = currentValue + threshold;
        }

        return absoluteDifference;
    }

    return targetValue;
}

void UnkEntityFunc0(Entity* entity, u16 slope, s16 speed) {
    entity->velocityX = rcos(slope) * speed / 16;
    entity->velocityY = rsin(slope) * speed / 16;
}

u16 Ratan2(s16 x, s16 y) { return ratan2(y, x); }

u16 GetAngleBetweenEntities(Entity* a, Entity* b) {
    s32 dx = b->posX.i.hi - a->posX.i.hi;
    s32 dy = b->posY.i.hi - a->posY.i.hi;
    return ratan2(dy, dx);
}

u16 GetAnglePointToEntity(Entity* entity, s16 x, s16 y) {
    s16 dx = x - entity->posX.i.hi;
    s16 dy = y - entity->posY.i.hi;
    return ratan2(dy, dx);
}

u16 LimitAngleChange(u16 delta, u16 base, u16 target) {
    u16 temp_a2 = (s16)(target - base);
    u16 ret;

    if (temp_a2 & 0x800) {
        ret = (0x800 - temp_a2) & 0x7FF;
    } else {
        ret = temp_a2;
    }

    if (ret > delta) {
        if (temp_a2 & 0x800) {
            ret = base - delta;
        } else {
            ret = base + delta;
        }
        return ret;
    }
    return target;
}

// SAT: func_0607B184
Entity* AllocEntity(Entity* start, Entity* end) {
    Entity* current = start;

    while (current < end) {
        if (current->entityId == 0) {
            DestroyEntity(current);
            return current;
        }
        current++;
    }
    return NULL;
}

// SAT: func_0607B1C8
void PreventEntityFromRespawning(Entity* entity) {
    if (entity->entityRoomIndex) {
        u16 index = entity->entityRoomIndex - 1 >> 5;
        g_unkGraphicsStruct.D_80097428[index] |=
            1 << ((entity->entityRoomIndex - 1) & 0x1F);
    }
}

// SAT: func_0607B218
void SetStep(s32 step) {
    g_CurrentEntity->step = step;
    g_CurrentEntity->step_s = 0;
    g_CurrentEntity->pose = 0;
    g_CurrentEntity->poseTimer = 0;
}

// SAT: func_0607B240
void SetSubStep(s32 step_s) {
    g_CurrentEntity->step_s = step_s;
    g_CurrentEntity->pose = 0;
    g_CurrentEntity->poseTimer = 0;
}

// original name: teki_init
void TekiInit(Entity* entity, u16 enemyId) {
    EnemyDef* enemy;

    g_CurrentEntity->enemyId = enemyId;

    enemy = &g_EnemyDefs[enemyId];
    entity->hitPoints = enemy->hitPoints;
    entity->attack = enemy->attack;
    entity->attackElement = enemy->attackElement;
    entity->hitboxState = enemy->hitboxState;
    entity->hitboxWidth = enemy->hitboxWidth * 5 / 4;
    entity->hitboxHeight = enemy->hitboxHeight;
    entity->flags = enemy->flags;
    entity->hitboxOffX = 0;
    entity->hitboxOffY = 0;
    entity->step_s = 0;
}

extern u32 g_randomNext;

// SAT: func_0607B2F4
s32 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}

void CreateEntityFromCurrentEntity(u16 entityId, Entity* entity) {
    DestroyEntity(entity);
    entity->entityId = entityId;
    entity->pfnUpdate = (*PfnEntityUpdates)[entityId - 1]->func;
    entity->posX.i.hi = g_CurrentEntity->posX.i.hi;
    entity->posY.i.hi = g_CurrentEntity->posY.i.hi;
}

void CreateEntityFromEntity(u16 entityId, Entity* source, Entity* entity) {
    DestroyEntity(entity);
    entity->entityId = entityId;
    entity->pfnUpdate = (*PfnEntityUpdates)[entityId - 1]->func;
    entity->posX.i.hi = source->posX.i.hi;
    entity->posY.i.hi = source->posY.i.hi;
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B3D0, func_0607B3D0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B448, func_0607B448);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B4B8, func_0607B4B8);

void func_0607B604(Entity* entity) {
    Unk0600B344* temp = entity->unk0;

    temp->unk14 = entity->posX.val;
    temp->unk18 = entity->posY.val;
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B618, func_0607B618);

u32 AnimateEntity(u8 frames[], Entity* entity) {
    u8* currentFrame;
    u16 flag;

    flag = 0;
    currentFrame = frames + entity->pose * 2;
    if (!entity->poseTimer) {
        if (*currentFrame) {
            if (*currentFrame == 0xFF) {
                return 0;
            }

            entity->poseTimer = currentFrame[0];
            entity->animCurFrame = currentFrame[1];
            currentFrame += 2;
            entity->pose++;
            flag |= 0x80;
        } else {
            entity->pose = 0;
            currentFrame = frames;
            entity->poseTimer = currentFrame[0];
            entity->animCurFrame = currentFrame[1];
            entity->pose++;
            return 0;
        }
    }
    entity->poseTimer--;
    entity->animCurFrame = currentFrame[-1];
    flag |= 1;

    return flag;
}

void PlaySfxVolPan();

void PlaySfxPositional(s32 sfxId) {
    Entity* entity = g_CurrentEntity;
    s16 sfxVol;
    int dx;
    s32 dy;
    s16 sfxPan;

    dx = entity->posX.i.hi - 0xA0;
    sfxPan = (ABS(dx) - 0x28) >> 5;
    if (sfxPan > 8) {
        sfxPan = 8;
    } else if (sfxPan < 0) {
        sfxPan = 0;
    }
    if (dx < 0) {
        sfxPan = -sfxPan;
    }
    sfxVol = ABS(dx) - 0x60;

    dy = ABS(entity->posY.i.hi - 0x80) - 0x70;
    if (dy > 0) {
        sfxVol += dy;
    }
    if (sfxVol < 0) {
        sfxVol = 0;
    }
    sfxVol = 0x7F - (sfxVol >> 1);
    if (sfxVol > 0) {
        PlaySfxVolPan(sfxId, sfxVol, sfxPan);
    }
}

extern u16 DAT_0605cdb8;
extern u8 DAT_0608FFF8[];

void CheckCollision(s32 x, s32 y, Collider* res, u16 unk) {
    Collider col0;
    Collider col1;
    s32 posX, posY;
    s32 maxX, maxY;
    s32 offset;
    u8 colType;

    posX = x + g_Tilemap.scrollX.val;
    posY = y + g_Tilemap.scrollY.val;
    maxX = g_Tilemap.width << 0x10;
    maxY = g_Tilemap.height << 0x10;
    if (posX < 1 || posX >= maxX || posY < 1 || posY >= maxY) {
        colType = 0;
        res->effects = EFFECT_NONE;
        return;
    } else {
        u32 A;
        u16 B;
        u16 C;
        u16 D;
        u16 E;
        posX = posX * 4 / 5;
        A = DAT_0605cdb8 * 4 / 5;
        B = A / 2;
        C = posX >> 20;
        D = posY >> 20;
        E = C + D * B;
        colType = DAT_0608FFF8[E];
        res->effects = EFFECT_NONE;
    }
    res->unk4 = res->unk14 = -(posX & 0xF0000);
    res->unkC = res->unk1C = res->unk14 + 0xF0000;
    res->unk8 = res->unk18 = -(posY & 0xF0000);
    res->unk10 = res->unk20 = res->unk18 + 0xF0000;
    if ((colType & 0x80) == 0) {
        res->effects = colType & 3;
    } else {
        offset = 0;
        switch (colType - 0x80) {
        case 0x01:
        case 0x02:
        case 0x0A:
        case 0x0B:
        case 0x18:
        case 0x19:
            if (unk == 0) {
                CheckCollision(x, y + res->unk18 - 0x10000, &col0, true);
                if (col0.effects & EFFECT_UNK_8000) {
                    if (col0.effects & EFFECT_SOLID) {
                        res->unk18 += col0.unk18 - 0x10000;
                    }
                    res->effects = col0.effects |=
                        EFFECT_UNK_0002 | EFFECT_SOLID;
                } else {
                    res->effects =
                        EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID;
                }
            } else {
                res->effects = EFFECT_SOLID;
            }
            break;

        case 0x00:
            if (res->unk1C + res->unk20 < 0x100000) {
                res->unk14 = res->unk18 = res->unk1C + res->unk20 - 0xF0000;
                res->effects = EFFECT_UNK_8000 | EFFECT_SOLID;
            } else {
                res->effects = EFFECT_UNK_8000;
            }
            break;

        case 0x08:
            offset = 0x100000;
        case 0x09:
            if (res->unk1C + offset + res->unk20 * 2 < 0x200000) {
                res->unk14 = res->unk1C + offset + res->unk20 * 2 - 0x1F0000;
                res->unk18 = (res->unk1C + offset) / 2 + res->unk20 - 0xF0000;
                res->effects = EFFECT_UNK_8000 | EFFECT_UNK_1000 | EFFECT_SOLID;
            } else {
                res->effects = EFFECT_UNK_8000 | EFFECT_UNK_1000;
            }
            break;

        case 0x14:
            offset = 0x100000;
        case 0x15:
            offset += 0x100000;
        case 0x16:
            offset += 0x100000;
        case 0x17:
            if (res->unk1C + offset + res->unk20 * 4 < 0x400000) {
                res->unk14 = res->unk1C + offset + res->unk20 * 4 - 0x3F0000;
                res->unk18 = (res->unk1C + offset) / 4 + res->unk20 - 0xF0000;
                res->effects = EFFECT_UNK_8000 | EFFECT_UNK_2000 | EFFECT_SOLID;
            } else {
                res->effects = EFFECT_UNK_8000 | EFFECT_UNK_2000;
            }
            break;

        case 0x03:
            if (res->unk1C >= res->unk20) {
                res->unk18 = res->unk20 - res->unk1C;
                res->unk1C = -res->unk18;
                res->effects = EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID;
            } else {
                res->effects = EFFECT_UNK_8000 | EFFECT_UNK_4000;
            }
            break;

        case 0x0C:
            offset = 0x100000;
        case 0x0D:
            if (res->unk1C + offset >= res->unk20 * 2) {
                res->unk18 = res->unk20 - (res->unk1C + offset) / 2;
                res->effects = EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                               EFFECT_UNK_1000 | EFFECT_SOLID;
            } else {
                res->effects =
                    EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_1000;
            }
            break;

        case 0x1A:
            offset = 0x100000;
        case 0x1B:
            offset += 0x100000;
        case 0x1C:
            offset += 0x100000;
        case 0x1D:
            if (res->unk1C + offset >= res->unk20 * 4) {
                res->unk18 = res->unk20 - (res->unk1C + offset) / 4;
                res->effects = EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                               EFFECT_UNK_2000 | EFFECT_SOLID;
            } else {
                res->effects =
                    EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000;
            }
            break;

        case 0x05:
        case 0x06:
        case 0x10:
        case 0x11:
        case 0x22:
        case 0x23:
            if (unk == 0) {
                CheckCollision(x, y + res->unk20 + 0x10000, &col1, true);
                if (col1.effects & EFFECT_UNK_0800) {
                    if (col1.effects & EFFECT_SOLID) {
                        res->unk20 += col1.unk20 + 0x10000;
                    }
                    res->effects = col1.effects |=
                        EFFECT_UNK_0002 | EFFECT_SOLID;
                } else {
                    res->effects =
                        EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID;
                }
            } else {
                res->effects = EFFECT_SOLID;
            }
            break;

        case 0x04:
            if (res->unk1C <= res->unk20) {
                res->unk14 = res->unk1C - res->unk20;
                res->unk20 = -res->unk14;
                res->effects = EFFECT_UNK_0800 | EFFECT_SOLID;
            } else {
                res->effects = EFFECT_UNK_0800;
            }
            break;

        case 0x0E:
            offset = 0x100000;
        case 0x0F:
            if (res->unk1C + offset <= res->unk20 * 2) {
                res->unk14 = res->unk1C + offset - res->unk20 * 2;
                res->unk20 = -res->unk14 / 2;
                res->effects = EFFECT_UNK_1000 | EFFECT_UNK_0800 | EFFECT_SOLID;
            } else {
                res->effects = EFFECT_UNK_1000 | EFFECT_UNK_0800;
            }
            break;

        case 0x1E:
            offset = 0x100000;
        case 0x1F:
            offset += 0x100000;
        case 0x20:
            offset += 0x100000;
        case 0x21:
            if (res->unk1C + offset <= res->unk20 * 4) {
                res->unk14 = res->unk1C + offset - res->unk20 * 4;
                res->unk20 = -res->unk14 / 4;
                res->effects = EFFECT_UNK_2000 | EFFECT_UNK_0800 | EFFECT_SOLID;
            } else {
                res->effects = EFFECT_UNK_2000 | EFFECT_UNK_0800;
            }
            break;

        case 0x07:
            if (res->unk1C + res->unk20 > 0xE0000) {
                res->unk1C = res->unk20 = res->unk14 + 0xF0000 + res->unk18;
                res->effects = EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID;
            } else {
                res->effects = EFFECT_UNK_4000 | EFFECT_UNK_0800;
            }
            break;

        case 0x12:
            offset = 0x100000;
        case 0x13:
            if (res->unk1C + offset + res->unk20 * 2 > 0x1D0000) {
                res->unk20 = ((res->unk14 + offset - 0xF0000) / 2) + 0xF0000 +
                             res->unk18;
                res->effects = EFFECT_UNK_4000 | EFFECT_UNK_1000 |
                               EFFECT_UNK_0800 | EFFECT_SOLID;
            } else {
                res->effects =
                    EFFECT_UNK_4000 | EFFECT_UNK_1000 | EFFECT_UNK_0800;
            }
            break;

        case 0x24:
            offset = 0x100000;
        case 0x25:
            offset += 0x100000;
        case 0x26:
            offset += 0x100000;
        case 0x27:
            if (res->unk1C + offset + res->unk20 * 4 > 0x3B0000) {
                res->unk20 = ((res->unk14 + offset - 0x2D0000) / 4) + 0xF0000 +
                             res->unk18;
                res->effects = EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                               EFFECT_UNK_0800 | EFFECT_SOLID;
            } else {
                res->effects =
                    EFFECT_UNK_4000 | EFFECT_UNK_2000 | EFFECT_UNK_0800;
            }
            break;

        case 0x7F:
            if (res->unk20 < 0x80000) {
                res->effects = EFFECT_UNK_0002 | EFFECT_SOLID;
                res->unk18 += 0x80000;
            }
            break;

        case 0x7E:
            if (res->unk20 >= 0x80000) {
                res->effects = EFFECT_UNK_0002 | EFFECT_SOLID;
                res->unk20 -= 0x80000;
            }
            break;

        case 0x7D:
            if (res->unk20 < 0x80000) {
                res->effects = EFFECT_SOLID;
                res->unk18 += 0x80000;
            }
            break;

        case 0x7C:
            if (res->unk20 >= 0x80000) {
                res->effects = EFFECT_SOLID;
                res->unk20 -= 0x80000;
            }
            break;

        case 0x79:
            if (res->unk20 < 0x80000) {
                res->effects = EFFECT_WATER;
                res->unk18 += 0x80000;
            }
            break;

        case 0x78:
            res->effects = EFFECT_MIST_ONLY | EFFECT_UNK_0002 | EFFECT_SOLID;
            break;

        case 0x74:
        case 0x75:
        case 0x76:
        case 0x77:
            res->effects = EFFECT_UNK_0020;
            break;

        case 0x6E:
        case 0x6F:
        case 0x70:
        case 0x71:
        case 0x72:
        case 0x73:
            res->effects = EFFECT_UNK_0002 | EFFECT_SOLID;
            break;

        case 0x6D:
            res->effects = EFFECT_WATER;
            break;

        case 0x6A:
            if (res->unk20 >= 0x80000) {
                res->effects = EFFECT_WATER;
                res->unk20 -= 0x80000;
            }
            break;

        case 0x68:
            if (res->unk20 < 0x80000) {
                res->effects = EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID;
                res->unk18 += 0x80000;
            }
            break;

        case 0x67:
            if (res->unk20 >= 0x80000) {
                res->effects = EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID;
                res->unk20 -= 0x80000;
            }
            break;

        case 0x66:
            if (res->unk20 < 0x80000) {
                res->effects = EFFECT_SOLID_FROM_BELOW | EFFECT_SOLID;
                res->unk18 += 0x80000;
            }
            break;

        case 0x65:
            if (res->unk20 >= 0x80000) {
                res->effects = EFFECT_SOLID_FROM_BELOW | EFFECT_SOLID;
                res->unk20 -= 0x80000;
            }
            break;
        }
    }

    res->unk14 = res->unk14 * 5 / 4;
    res->unk4 = res->unk4 * 5 / 4;
    res->unk1C = res->unk1C * 5 / 4;
    res->unkC = res->unkC * 5 / 4;
}

extern s32 DAT_06086128;
extern s32 DAT_0608612c;
extern s32 DAT_06086130;
extern s32 DAT_06086134;

void func_06008048();
void func_0600C818();

void func_0607BE38(void) {
    func_0600C818();
    DAT_06086128 = 0x50000;
    DAT_0608612c = 0xF0000;
    DAT_06086130 = 0x0;
    func_06008048();
    SCL_SET_CCMD(0);
    SCL_SetColMixMode(0x7, 0x1);
    DAT_06086134 = 0x1F;
    SCL_SET_S0CCRT(DAT_06086134);
}

extern s32 d_0605AEAC;
extern s16 DAT_0605aec4;
extern u32 g_Timer;
extern s32 SpMstCmdPos;

void func_0607BED0(void) {
    SprSpCmd cmd;
    SprSpCmd* spCmd;
    s32 i;
    s32 angle;

    spCmd = &cmd;
    spCmd->control = JUMP_ASSIGN;
    spCmd->drawMode = UCLPIN_ENABLE | ECD_DISABLE;
    spCmd->color = 0x6400;
    spCmd->charAddr = DAT_0605aec4;
    spCmd->charSize = 0x2801;
    angle = DAT_06086130;
    for (i = 0; i < 0x20; i++, angle += 0x80) {
        spCmd->ax = func_0607C054(DAT_0608612c, DAT_06086128, angle);
        spCmd->ay = i + 0x68;
        if (SpMstCmdPos < 0x278) {
            SPR_2Cmd(0x1C0, spCmd);
            d_0605AEAC += 0x20;
        }
        spCmd->charAddr += 20;
    }
    DAT_06086130 += 0x80;
    DAT_0608612c -= 0x2000;
    if (DAT_0608612c < 0) {
        DAT_0608612c = 0;
    }
    DAT_06086128 -= 0x800;
    if (DAT_06086128 < 0) {
        DAT_06086128 = 0;
    }
    if (g_Timer & 1) {
        DAT_06086134--;
        if (DAT_06086134 > 0) {
            SCL_SET_S0CCRT(DAT_06086134);
        } else {
            if (DAT_06086134 == 0) {
                SCL_SET_CCMD(1);
                SCL_SetColMixMode(6, 1);
                SCL_SET_S0CCRT(0);
            }
        }
    }
}

s16 func_0607C054(s32 arg0, s32 arg1, s32 angle) {
    angle &= 0xFFF;
    return ((rsin((angle * (arg1 >> 8)) >> 8) >> 4) * (arg0 >> 8)) >> 0x10;
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607C0A0, func_0607C0A0);

// _MTH_GetRand
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607C0BC, func_0607C0BC);
