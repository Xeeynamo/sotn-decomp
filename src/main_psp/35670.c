// SPDX-License-Identifier: AGPL-3.0-or-later
//! PSPO=4,p
#include <game_psp.h>

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h
#include <psptypes.h>
#include <pspctrl.h>

float sceVfpuVector4InnerProductXYZ(
    const ScePspFVector4* pv0, const ScePspFVector4* pv1);
ScePspFVector4* sceVfpuVector4NormalizeXYZ(
    ScePspFVector4* pv0, const ScePspFVector4* pv1);

s32 MapJoystickToButtons(u8 x, u8 y) {
    ScePspFVector4 dir;

    float fx = (x - 0x80) / 128.0f;
    float fy = -1.0f * ((y - 0x80) / 128.0f);
    s32 pad = 0;

    if (-0.5f < fx && fx < 0.5f) {
        fx = 0.0f;
    } else {
        sceKernelPowerTick(6);
    }
    if (-0.5f < fy && fy < 0.5f) {
        fy = 0.0f;
    } else {
        sceKernelPowerTick(6);
    }
    dir.w = 1.0f;
    dir.x = fx;
    dir.y = fy;
    dir.z = 0.0f;
    if (sceVfpuVector4InnerProductXYZ(&dir, &dir) >= 0.48999998f) {
        ScePspFVector4 padDir;
        padDir.w = 1.0f;
        padDir.z = 0.0f;
        sceVfpuVector4NormalizeXYZ(&dir, &dir);
        if (fx >= 0.5f) {
            padDir.x = 1.0f;
            padDir.y = 0.0f;
            if (sceVfpuVector4InnerProductXYZ(&dir, &padDir) >= 0.9612617f) {
                pad |= PSP_CTRL_RIGHT;
            }
            padDir.x = 0.70710677f;
            padDir.y = 0.70710677f;
            if (sceVfpuVector4InnerProductXYZ(&dir, &padDir) >= 0.9612617f) {
                pad |= PSP_CTRL_RIGHT | PSP_CTRL_UP;
            }
            padDir.x = 0.70710677f;
            padDir.y = -0.70710677f;
            if (sceVfpuVector4InnerProductXYZ(&dir, &padDir) >= 0.9612617f) {
                pad |= PSP_CTRL_RIGHT | PSP_CTRL_DOWN;
            }
        } else if (fx <= -0.5f) {
            padDir.x = -1.0f;
            padDir.y = 0.0f;
            if (sceVfpuVector4InnerProductXYZ(&dir, &padDir) >= 0.9612617f) {
                pad |= PSP_CTRL_LEFT;
            }
            padDir.x = -0.70710677f;
            padDir.y = 0.70710677f;
            if (sceVfpuVector4InnerProductXYZ(&dir, &padDir) >= 0.9612617f) {
                pad |= PSP_CTRL_LEFT | PSP_CTRL_UP;
            }
            padDir.x = -0.70710677f;
            padDir.y = -0.70710677f;
            if (sceVfpuVector4InnerProductXYZ(&dir, &padDir) >= 0.9612617f) {
                pad |= PSP_CTRL_LEFT | PSP_CTRL_DOWN;
            }
        }
        if (fy >= 0.5f) {
            padDir.y = 1.0f;
            padDir.x = 0.0f;
            if (sceVfpuVector4InnerProductXYZ(&dir, &padDir) >= 0.9612617f) {
                pad |= PSP_CTRL_UP;
            }
        } else if (fy <= -0.5f) {
            padDir.y = -1.0f;
            padDir.x = 0.0f;
            if (sceVfpuVector4InnerProductXYZ(&dir, &padDir) >= 0.9612617f) {
                pad |= PSP_CTRL_DOWN;
            }
        }
    }
    return pad;
}
