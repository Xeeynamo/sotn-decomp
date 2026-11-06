// SPDX-License-Identifier: AGPL-3.0-or-later
void SaveDeviceProbe(Entity* self) {
    BupStat sttb;
    s32* statusp;
    s32 state;
    s32 index;
    s32 status;
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
        value = g_WorkBuffer.save.unk4;
        index = 1;
        do {
            status = func_0600D028(value, index);
            if (status != 0 && status != BUP_BROKEN) {
                g_WorkBuffer.save.unk5 = index;
                g_WorkBuffer.save.unk4 = value;
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
    value = g_WorkBuffer.save.unk4;
    index = g_WorkBuffer.save.unk5;
    status = BUP_Stat(value, 70, &sttb);
    if (status == BUP_UNFORMAT) {
        *statusp = 43;
    } else {
        status = func_0600D028(value, index);
        if (status == BUP_NOT_FOUND && sttb.freeblock <= 0x4D) {
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
