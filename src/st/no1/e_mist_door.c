// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

extern char D_psp_09265A88[];
extern char D_psp_09265AA0[];
extern char D_psp_09265AB8[];
extern char D_psp_09265AD8[];
extern char D_psp_09265AF0[];
extern char D_psp_09265B08[];
extern char D_psp_09265B20[];
extern char D_psp_09265B38[];
extern char D_psp_09265B58[];
extern char D_psp_09265B70[];
extern char D_psp_09265B88[];
extern char D_psp_09265BA0[];
extern char D_psp_09265BB8[];
extern char D_psp_09265BD0[];
extern char D_psp_09265BF0[];
extern char D_psp_092753D8[];
extern char* D_psp_0929A510;
extern char* D_psp_0929A518;
extern char* D_psp_0929A520;
static char D_us_80183448[] = {
    0x7C, 0x0E, 'M', 'i', 's', 't', ' ', 'c',  'o',  'u',
    'l',  'd',  ' ', 'p', 'a', 's', 's', 0x81, 0x44, 0x00};
static char D_us_8018345C[] = {
    0x94, 0x1E, 'I', ' ', 'h',  'a',  'v',  'e',  ' ',  'n',  'o',
    't',  'h',  'i', 'n', 'g',  ' ',  't',  'o',  ' ',  'd',  'o',
    0x01, 'w',  'i', 't', 'h',  ' ',  't',  'h',  'i',  's',  ' ',
    'w',  'a',  'l', 'l', 0x81, 0x44, 0x81, 0x44, 0x81, 0x44, 0x00};

void EntityMistDoor(Entity* self) {
    Entity* messageBox;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->hitboxState = 1;
        self->hitPoints = 0x7FFF;
        self->attack = 0;
        self->hitboxWidth = 0xC;
        self->hitboxHeight = 0x18;
    }
    if (self->hitFlags) {
        messageBox = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (messageBox != NULL) {
            CreateEntityFromCurrentEntity(E_MESSAGE_BOX, messageBox);
            messageBox->posX.i.hi = 0x80;
            messageBox->posY.i.hi = 0xB0;
#ifdef VERSION_PSP
            D_psp_0929A520 = func_psp_092490A8(
                D_psp_09265A88, D_psp_09265AD8, D_psp_09265AA0, D_psp_09265AF0,
                D_psp_09265AB8);
            D_psp_0929A518 = func_psp_092490A8(
                D_psp_09265B88, D_psp_09265BD0, D_psp_09265BA0, D_psp_09265BF0,
                D_psp_09265BB8);
            D_psp_0929A510 = func_psp_092490A8(
                D_psp_09265B08, D_psp_09265B58, D_psp_09265B20, D_psp_09265B70,
                D_psp_09265B38);
            if (g_PlayableCharacter == PLAYER_MARIA) {
                messageBox->ext.messageBox.label = D_psp_0929A518;
            } else if (g_PlayableCharacter == PLAYER_RICHTER) {
                messageBox->ext.messageBox.label = D_psp_0929A510;
            } else {
                messageBox->ext.messageBox.label = D_psp_0929A520;
            }
#else
            if (g_PlayableCharacter != PLAYER_ALUCARD) {
                messageBox->ext.messageBox.label = D_us_8018345C;
            } else {
                messageBox->ext.messageBox.label = D_us_80183448;
            }
#endif
            messageBox->params = 0x100;
            self->hitboxState = 0;
        }
    }
}
