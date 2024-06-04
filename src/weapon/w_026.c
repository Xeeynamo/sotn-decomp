// Weapon ID #26. Used by weapons:
// Shaman shield, Unknown#210
#include "weapon_private.h"
#include "shared.h"

INCLUDE_ASM("weapon/nonmatchings/w_026", EntityWeaponAttack);

void func_ptr_80170004(Entity* self) {}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 26; }

extern s16 D_BA000_8017AA98;
extern s16 D_BA000_8017AA9A;

void func_BA000_8017B37C(void) {
    RECT rect;
    s16 temp;

    if (D_BA000_8017AA9A & 1) {
        if (++D_BA000_8017AA98 >= 0x20) {
            D_BA000_8017AA9A++;
            D_BA000_8017AA98 = 0x1F;
        }
    } else {
        if (--D_BA000_8017AA98 < 0) {
            D_BA000_8017AA9A++;
            D_BA000_8017AA98 = 0;
        }
    }

    temp = g_Clut[0x112D + g_HandId * 0x180];
    temp &= 0xFC1F;
    temp += D_BA000_8017AA98 << 5;
    g_Clut[0x112D + g_HandId * 0x180] = temp;

    rect.x = 0;
    rect.y = 0xF1;
    rect.w = 0x100;
    rect.h = 3;
    LoadImage(&rect, &g_Clut[0x1100]);
}

INCLUDE_ASM("weapon/nonmatchings/w_026", EntityWeaponShieldSpell);

extern u8 D_BA000_8017AADC[];

const SVECTOR D_BA000_8017AB7C = {8, -28, 0};
const SVECTOR D_BA000_8017AB84 = {56, -28, 0};
const SVECTOR D_BA000_8017AB8C = {8, 28, 0};
const SVECTOR D_BA000_8017AB94 = {56, 28, 0};

// When casting the Shaman Shield spell with the Shield Rod, an animation plays
// where several stars rotate in 3D around Alucard. This handles that rotation.
void func_ptr_80170024(Entity* self) {
    SVECTOR rotation_axis;
    VECTOR transfer_vector;
    MATRIX m;
    SVECTOR vectors[4] = {D_BA000_8017AB7C, D_BA000_8017AB84, D_BA000_8017AB8C,
                          D_BA000_8017AB94};
    SVECTOR* vecs[2][4];
    s32 spA0;
    s32 spA4;
    Primitive* prim;
    Primitive* nextPrim;
    Primitive* primSrc;
    Primitive* primDest;
    Primitive* parentPrim;

    u16 uvOffset;
    s32 i;
    u16 clut;
    s32 rotTransResult;

    // This whole block might be fake.
    vecs[1][0] = &vectors[0];
    vecs[1][1] = &vectors[1];
    vecs[1][2] = &vectors[3];
    vecs[1][3] = &vectors[2];
    __builtin_memcpy(vecs[0], vecs[1], 4 * sizeof(SVECTOR*));

    if (g_HandId != 0) {
        clut = 0x12A;
        uvOffset = 0x80;
    } else {
        clut = 0x112;
        uvOffset = 0;
    }
    if ((self->params & 0x7F00) &&
        (self->ext.shamanshieldstar.parent->entityId == 0)) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        if (self->params & 0x7F00) {
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
            if (self->primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            self->flags |= FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
            for (prim = &g_PrimBuf[self->primIndex]; prim != NULL;
                 prim = prim->next) {
                prim->drawMode = DRAW_HIDE;
            }
            self->step++;
            return;
        }
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
        self->ext.shamanshieldstar.unk9C = 0xA0;
        self->ext.shamanshieldstar.unk9E = 0x60;
        self->ext.shamanshieldstar.unk80 = rand() % 15;
        self->ext.shamanshieldstar.unk82 = 0;
        self->ext.shamanshieldstar.unk7C = -0x100;
        self->ext.shamanshieldstar.unk7E = (self->params & 0xFF) << 9;
        self->ext.shamanshieldstar.unk96 = 0x28;
        self->ext.shamanshieldstar.unk9A = 0x180;
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x19;
        prim->clut = clut;
        // Careful here - uvOffset is either 0 or 0x80. But since the V values
        // in the array are all 0 or 0x80, this just ends up flipping the
        // image vertically. Doesn't matter since it's symmetric though.
        prim->u0 = D_BA000_8017AADC[0];
        prim->v0 = D_BA000_8017AADC[1] + uvOffset;
        prim->u1 = D_BA000_8017AADC[2];
        prim->v1 = D_BA000_8017AADC[3] + uvOffset;
        prim->u2 = D_BA000_8017AADC[4];
        prim->v2 = D_BA000_8017AADC[5] + uvOffset;
        prim->u3 = D_BA000_8017AADC[6];
        prim->v3 = D_BA000_8017AADC[7] + uvOffset;

        prim->priority = 0;
        prim->drawMode = 0x71;
        // Factory 90 has child 9 which, for weapons, is func_ptr_80170024, so
        // I think this spawns another copy of the star? Not totally clear.
        g_api.CreateEntFactoryFromEntity(
            self, ((g_HandId + 1) << 0xE) + FACTORY(0x100, 90), 0);
        self->step++;
        break;
    case 1:
        if (self->params & 0x7F00) {
            self->ext.shamanshieldstar.unk80++;
            parentPrim =
                &g_PrimBuf[self->ext.shamanshieldstar.parent->primIndex];
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 4; i++) {
                if (i == ((self->ext.shamanshieldstar.unk80 >> 1) % 4)) {
                    primDest = prim;
                    if (self->ext.shamanshieldstar.parent->ext.shamanshieldstar
                            .unk9C > 0) {
                        nextPrim = prim->next;
                        primSrc = parentPrim;
                        *primDest = *primSrc;
                        prim->next = nextPrim;
                        prim = prim->next;
                        // Note: In this case, we do i++ but not prim =
                        // prim->next
                    } else {
                        prim->drawMode |= DRAW_HIDE;
                        prim = prim->next;
                    }
                } else {
                    prim = prim->next;
                }
            }
            return;
        } else {
            self->ext.shamanshieldstar.unk7E +=
                self->ext.shamanshieldstar.unk96;
            if (self->ext.shamanshieldstar.unk80 == 0) {
                self->ext.shamanshieldstar.unk9C -= 6;
                if (self->ext.shamanshieldstar.unk9C <= 0) {
                    self->ext.shamanshieldstar.unk9C = 0;
                }
                self->ext.shamanshieldstar.unk9E -= 6;
                if (self->ext.shamanshieldstar.unk9E <= 0) {
                    self->ext.shamanshieldstar.unk9E = 0;
                }
            } else {
                self->ext.shamanshieldstar.unk80--;
            }
            if (self->ext.shamanshieldstar.parent->step == 8) {
                self->step++;
                self->ext.shamanshieldstar.unk80 = rand() & 0xF;
            }
        }
        break;
    case 2:
        self->ext.shamanshieldstar.unk7E += self->ext.shamanshieldstar.unk96;
        if (self->ext.shamanshieldstar.unk80 == 0) {
            self->ext.shamanshieldstar.unk9C += 6;
            self->ext.shamanshieldstar.unk9E -= 6;
            if (self->ext.shamanshieldstar.unk9E < -0x80) {
                DestroyEntity(self);
                return;
            }
            break;
        }
        self->ext.shamanshieldstar.unk80--;
    }

    vectors[0].vx += self->ext.shamanshieldstar.unk9C;
    vectors[1].vx += self->ext.shamanshieldstar.unk9C;
    vectors[2].vx += self->ext.shamanshieldstar.unk9C;
    vectors[3].vx += self->ext.shamanshieldstar.unk9C;

    vectors[0].vy += self->ext.shamanshieldstar.unk9E;
    vectors[1].vy += self->ext.shamanshieldstar.unk9E;
    vectors[2].vy += self->ext.shamanshieldstar.unk9E;
    vectors[3].vy += self->ext.shamanshieldstar.unk9E;

    rotation_axis.vx = self->ext.shamanshieldstar.unk7C;
    rotation_axis.vy = self->ext.shamanshieldstar.unk7E;
    rotation_axis.vz = self->ext.shamanshieldstar.unk82;

    transfer_vector.vz = self->ext.shamanshieldstar.unk9A;
    transfer_vector.vx = 0;
    transfer_vector.vy = 0x10;

    SetGeomScreen(0x280);
    SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
    RotMatrix(&rotation_axis, &m);
    TransMatrix(&m, &transfer_vector);
    SetRotMatrix(&m);
    SetTransMatrix(&m);
    prim = &g_PrimBuf[self->primIndex];

    rotTransResult = RotTransPers4(
        vecs[0][0], vecs[0][1], vecs[0][2], vecs[0][3], (long*)&prim->x0,
        (long*)&prim->x1, (long*)&prim->x3, (long*)&prim->x2, &spA0, &spA4);
    prim->drawMode |= DRAW_HIDE;
    if (0 < rotTransResult && rotTransResult <= 0x1BE) {
        prim->priority = 0x1B4;
        if (0x900 < (self->ext.shamanshieldstar.unk7E & 0xFFF) &&
            (self->ext.shamanshieldstar.unk7E & 0xFFF) < 0xF00) {
            prim->priority = 0x1BE;
        }
        prim->drawMode &= ~DRAW_HIDE;
        prim->type = PRIM_GT4;
    }
}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
