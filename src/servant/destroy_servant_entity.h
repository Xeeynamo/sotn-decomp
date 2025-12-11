// SPDX-License-Identifier: AGPL-3.0-or-later
void OVL_EXPORT(DestroyServantEntity)(Entity* self) {
    switch (self->params) {
    case 15:
        s_IsServantDestroyed = true;
        break;
    }
    DestroyEntity(self);
}
