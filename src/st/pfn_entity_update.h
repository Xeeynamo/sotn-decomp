// SPDX-License-Identifier: AGPL-3.0-or-later

// NOTE: include this AFTER the stage entity is included
// this is to ensure OVL_EXPORT is defined

#if defined(VERSION_PSP) || defined(VERSION_PC)
extern PfnEntityUpdate* PfnEntityUpdates;
#else
extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[];
#define PfnEntityUpdates OVL_EXPORT(EntityUpdates)
#endif
