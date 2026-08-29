// SPDX-License-Identifier: AGPL-3.0-or-later
void SaveDeviceProbe(Entity* self) {
    u32 scratch[6];
    s32* statusp;
    s32 state;
    s32 index;
    s32 result;
    s8 value;

    statusp = &self->ext.save.unk4;
    state = *statusp;
    if (state != 10) {
        if (state <= 10) {
            return;
        }
        if (state == 30) {
            goto state30;
        }
        return;
    } else {
        value = DAT_060485C4;
        index = 1;
        do {
            result = func_0600D028(value, index);
            if (result != 0 && result != 8) {
                DAT_060485C0.unk5 = index;
                DAT_060485C0.unk4 = value;
                self->ext.save.unk4 = 30;
                break;
            }
            index++;
        } while (index <= 5);

        if (index == 6) {
            self->step = 1;
            self->ext.save.unk4 = 41;
        }
        return;
    }

state30:
    value = DAT_060485C0.unk4;
    index = DAT_060485C0.unk5;
    result = func_06030690(value, 70, scratch);
    if (result == 2) {
        *statusp = 43;
    } else {
        result = func_0600D028(value, index);
        if (result == 5 && scratch[4] <= 0x4D) {
            *statusp = 44;
        } else if (func_0600D264(value, index) == 0 &&
                   func_0600D264(value, index) == 0 &&
                   func_0600D47C(value, index) == 0) {
            self->ext.save.unk4 = 40;
        } else {
            self->ext.save.unk4 = 45;
        }
    }
}
