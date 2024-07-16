#include <game.h>
#ifdef _MSC_VER
#define SDL_MAIN_HANDLED
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include "macros.h"

int press_pos = 0;
int press_spell = 0;
int next_time = 0;
int spell_num = 0;
int spell_dir = 0;

#define STOP -1

struct SpellInput {
    int pad;
    int frames;
};

struct SpellInput tetra_spirit[] = {
    {PAD_UP, 33},   {PAD_UP + PAD_RIGHT, 1},
    {PAD_RIGHT, 1}, {PAD_DOWN + PAD_RIGHT, 1},
    {PAD_DOWN, 1},  {PAD_SQUARE, 1},
    {STOP, 0}};

struct SpellInput dark_metamorphosis[] = {
    {PAD_LEFT, 1},  {PAD_UP + PAD_LEFT, 1},
    {PAD_UP, 1},    {PAD_UP + PAD_RIGHT, 1},
    {PAD_RIGHT, 1}, {PAD_SQUARE, 1},
    {STOP, 0}};

struct SpellInput* spells_right[] = {&tetra_spirit, &dark_metamorphosis};

struct SpellInput tetra_spirit_left[] = {
    {PAD_UP, 33},  {PAD_UP + PAD_LEFT, 1},
    {PAD_LEFT, 1}, {PAD_DOWN + PAD_LEFT, 1},
    {PAD_DOWN, 1}, {PAD_SQUARE, 1},
    {STOP, 0}};

struct SpellInput dark_metamorphosis_left[] = {
    {PAD_RIGHT, 1}, {PAD_UP + PAD_RIGHT, 1},
    {PAD_UP, 1},    {PAD_UP + PAD_LEFT, 1},
    {PAD_LEFT, 1},  {PAD_SQUARE, 1},
    {STOP, 0}};

struct SpellInput* spells_left[] = {
    &tetra_spirit_left, &dark_metamorphosis_left};

struct SpellInput** spell[] = {&spells_right, &spells_left};

enum Spells { TETRA_SPIRIT, DARK_METAMORPHOSIS };

u8 previousKeyStates[SDL_NUM_SCANCODES] = {0};

void check_macro(int scanCode, enum Spells which, const u8* keyb) {
    if (keyb[scanCode] && !previousKeyStates[scanCode]) {
        press_spell = 1;
        press_pos = 0;
        next_time = 0;
        spell_num = which;
        spell_dir = PLAYER.facingLeft;
    }
}

void handle_macros(const u8* keyb, u_long* pressed) {
    check_macro(SDL_SCANCODE_Y, TETRA_SPIRIT, keyb);
    check_macro(SDL_SCANCODE_U, DARK_METAMORPHOSIS, keyb);

    memcpy(previousKeyStates, keyb, SDL_NUM_SCANCODES * sizeof(Uint8));

    if (press_spell == 1) {
        if (spell[spell_dir][spell_num][press_pos].pad == STOP) {
            press_spell = 0;
            press_pos = 0;
            next_time = 0;
        } else if (next_time == 0) {
            *pressed |= spell[spell_dir][spell_num][press_pos].pad;
            next_time = spell[spell_dir][spell_num][press_pos].frames + g_Timer;
        } else if (g_Timer >= next_time) {
            press_pos++;

            if (spell[spell_dir][spell_num][press_pos].pad == STOP) {
                press_spell = 0;
                press_pos = 0;
                next_time = 0;
            } else {
                *pressed |= spell[spell_dir][spell_num][press_pos].pad;
                next_time =
                    spell[spell_dir][spell_num][press_pos].frames + g_Timer;
            }
        } else {
            *pressed |= spell[spell_dir][spell_num][press_pos].pad;
        }
    }
}
