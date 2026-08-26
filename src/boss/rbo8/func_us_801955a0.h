// SPDX-License-Identifier: AGPL-3.0-or-later
void func_us_801955A0(Entity* self, Collider* collider) {
    s16 result;
    u16 hitFloor = false;

    result = HIH(g_Tilemap.scrollY) + HIH(self->posY) + collider->unk18;
    if (result >= 0x1C0) {
        result = 0x1C0 - result;
        hitFloor = true;
    } else {
        result = 0;
        hitFloor = false;
    }

    collider->unk18 = result;
    self->ext.et_8019921C.hitFloor = hitFloor;
}
