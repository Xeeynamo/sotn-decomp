/*
    libpspirkeyb: PSP IR Keyboard Library (http://pspirkeyb.podzone.net)
    Copyright (C) 2007 Harald Fielker <harald.fielker@web.de>

    This program can be distributed under the terms of the GNU LGPL.
    See the file LICENSE.
*/

#ifndef __PSPIRKEYB_RAWKEYS_H
#define __PSPIRKEYB_RAWKEYS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Keys and buttons */

#define KEY_RESERVED		0
#define KEY_ESC			1
#define KEY_1			2
#define KEY_2			3
#define KEY_3			4
#define KEY_4			5
#define KEY_5			6
#define KEY_6			7
#define KEY_7			8
#define KEY_8			9
#define KEY_9			10
#define KEY_0			11
#define KEY_MINUS		12
#define KEY_EQUAL		13
#define KEY_BACKSPACE		14
#define KEY_TAB			15
#define KEY_Q			16
#define KEY_W			17
#define KEY_E			18
#define KEY_R			19
#define KEY_T			20
#define KEY_Y			21
#define KEY_U			22
#define KEY_I			23
#define KEY_O			24
#define KEY_P			25
#define KEY_LEFTBRACE		26
#define KEY_RIGHTBRACE		27
#define KEY_ENTER		28
#define KEY_LEFTCTRL		29
#define KEY_A			30
#define KEY_S			31
#define KEY_D			32
#define KEY_F			33
#define KEY_G			34
#define KEY_H			35
#define KEY_J			36
#define KEY_K			37
#define KEY_L			38
#define KEY_SEMICOLON		39
#define KEY_APOSTROPHE		40
#define KEY_GRAVE		41
#define KEY_LEFTSHIFT		42
#define KEY_BACKSLASH		43
#define KEY_Z			44
#define KEY_X			45
#define KEY_C			46
#define KEY_V			47
#define KEY_B			48
#define KEY_N			49
#define KEY_M			50
#define KEY_COMMA		51
#define KEY_DOT			52
#define KEY_SLASH		53
#define KEY_RIGHTSHIFT		54
#define KEY_KPASTERISK		55
#define KEY_LEFTALT		56
#define KEY_SPACE		57
#define KEY_CAPSLOCK		58
#define KEY_F1			59
#define KEY_F2			60
#define KEY_F3			61
#define KEY_F4			62
#define KEY_F5			63
#define KEY_F6			64
#define KEY_F7			65
#define KEY_F8			66
#define KEY_F9			67
#define KEY_F10			68
#define KEY_NUMLOCK		69
#define KEY_SCROLLLOCK		70
#define KEY_KP7			71
#define KEY_KP8			72
#define KEY_KP9			73
#define KEY_KPMINUS		74
#define KEY_KP4			75
#define KEY_KP5			76
#define KEY_KP6			77
#define KEY_KPPLUS		78
#define KEY_KP1			79
#define KEY_KP2			80
#define KEY_KP3			81
#define KEY_KP0			82
#define KEY_KPDOT		83
#define KEY_103RD		84
#define KEY_F13			85
#define KEY_102ND		86
#define KEY_F11			87
#define KEY_F12			88
#define KEY_F14			89
#define KEY_F15			90
#define KEY_F16			91
#define KEY_F17			92
#define KEY_F18			93
#define KEY_F19			94
#define KEY_F20			95
#define KEY_KPENTER		96
#define KEY_RIGHTCTRL		97
#define KEY_KPSLASH		98
#define KEY_SYSRQ		99
#define KEY_RIGHTALT		100
#define KEY_LINEFEED		101
#define KEY_HOME		102
#define KEY_UP			103
#define KEY_PAGEUP		104
#define KEY_LEFT		105
#define KEY_RIGHT		106
#define KEY_END			107
#define KEY_DOWN		108
#define KEY_PAGEDOWN		109
#define KEY_INSERT		110
#define KEY_DELETE		111
#define KEY_MACRO		112
#define KEY_MUTE		113
#define KEY_VOLUMEDOWN		114
#define KEY_VOLUMEUP		115
#define KEY_POWER		116
#define KEY_KPEQUAL		117
#define KEY_KPPLUSMINUS		118
#define KEY_PAUSE		119
#define KEY_F21			120
#define KEY_F22			121
#define KEY_F23			122
#define KEY_F24			123
#define KEY_KPCOMMA		124
#define KEY_LEFTMETA		125
#define KEY_RIGHTMETA		126
#define KEY_COMPOSE		127

#define KEY_STOP		128
#define KEY_AGAIN		129
#define KEY_PROPS		130
#define KEY_UNDO		131
#define KEY_FRONT		132
#define KEY_COPY		133
#define KEY_OPEN		134
#define KEY_PASTE		135
#define KEY_FIND		136
#define KEY_CUT			137
#define KEY_HELP		138
#define KEY_MENU		139
#define KEY_CALC		140
#define KEY_SETUP		141
#define KEY_SLEEP		142
#define KEY_WAKEUP		143
#define KEY_FILE		144
#define KEY_SENDFILE		145
#define KEY_DELETEFILE		146
#define KEY_XFER		147
#define KEY_PROG1		148
#define KEY_PROG2		149
#define KEY_WWW			150
#define KEY_MSDOS		151
#define KEY_COFFEE		152
#define KEY_DIRECTION		153
#define KEY_CYCLEWINDOWS	154
#define KEY_MAIL		155
#define KEY_BOOKMARKS		156
#define KEY_COMPUTER		157
#define KEY_BACK		158
#define KEY_FORWARD		159
#define KEY_CLOSECD		160
#define KEY_EJECTCD		161
#define KEY_EJECTCLOSECD	162
#define KEY_NEXTSONG		163
#define KEY_PLAYPAUSE		164
#define KEY_PREVIOUSSONG	165
#define KEY_STOPCD		166
#define KEY_RECORD		167
#define KEY_REWIND		168
#define KEY_PHONE		169
#define KEY_ISO			170
#define KEY_CONFIG		171
#define KEY_HOMEPAGE		172
#define KEY_REFRESH		173
#define KEY_EXIT		174
#define KEY_MOVE		175
#define KEY_EDIT		176
#define KEY_SCROLLUP		177
#define KEY_SCROLLDOWN		178
#define KEY_KPLEFTPAREN		179
#define KEY_KPRIGHTPAREN	180

#define KEY_INTL1		181
#define KEY_INTL2		182
#define KEY_INTL3		183
#define KEY_INTL4		184
#define KEY_INTL5		185
#define KEY_INTL6		186
#define KEY_INTL7		187
#define KEY_INTL8		188
#define KEY_INTL9		189
#define KEY_LANG1		190
#define KEY_LANG2		191
#define KEY_LANG3		192
#define KEY_LANG4		193
#define KEY_LANG5		194
#define KEY_LANG6		195
#define KEY_LANG7		196
#define KEY_LANG8		197
#define KEY_LANG9		198

#define KEY_PLAYCD		200
#define KEY_PAUSECD		201
#define KEY_PROG3		202
#define KEY_PROG4		203
#define KEY_SUSPEND		205
#define KEY_CLOSE		206

#define KEY_UNKNOWN		220

#define KEY_BRIGHTNESSDOWN	224
#define KEY_BRIGHTNESSUP	225

#define BTN_MISC		0x100
#define BTN_0			0x100
#define BTN_1			0x101
#define BTN_2			0x102
#define BTN_3			0x103
#define BTN_4			0x104
#define BTN_5			0x105
#define BTN_6			0x106
#define BTN_7			0x107
#define BTN_8			0x108
#define BTN_9			0x109

#define BTN_MOUSE		0x110
#define BTN_LEFT		0x110
#define BTN_RIGHT		0x111
#define BTN_MIDDLE		0x112
#define BTN_SIDE		0x113
#define BTN_EXTRA		0x114
#define BTN_FORWARD		0x115
#define BTN_BACK		0x116

#define BTN_JOYSTICK		0x120
#define BTN_TRIGGER		0x120
#define BTN_THUMB		0x121
#define BTN_THUMB2		0x122
#define BTN_TOP			0x123
#define BTN_TOP2		0x124
#define BTN_PINKIE		0x125
#define BTN_BASE		0x126
#define BTN_BASE2		0x127
#define BTN_BASE3		0x128
#define BTN_BASE4		0x129
#define BTN_BASE5		0x12a
#define BTN_BASE6		0x12b
#define BTN_DEAD		0x12f

#define BTN_GAMEPAD		0x130
#define BTN_A			0x130
#define BTN_B			0x131
#define BTN_C			0x132
#define BTN_X			0x133
#define BTN_Y			0x134
#define BTN_Z			0x135
#define BTN_TL			0x136
#define BTN_TR			0x137
#define BTN_TL2			0x138
#define BTN_TR2			0x139
#define BTN_SELECT		0x13a
#define BTN_START		0x13b
#define BTN_MODE		0x13c
#define BTN_THUMBL		0x13d
#define BTN_THUMBR		0x13e

#define BTN_DIGI		0x140
#define BTN_TOOL_PEN		0x140
#define BTN_TOOL_RUBBER		0x141
#define BTN_TOOL_BRUSH		0x142
#define BTN_TOOL_PENCIL		0x143
#define BTN_TOOL_AIRBRUSH	0x144
#define BTN_TOOL_FINGER		0x145
#define BTN_TOOL_MOUSE		0x146
#define BTN_TOOL_LENS		0x147
#define BTN_TOUCH		0x14a
#define BTN_STYLUS		0x14b
#define BTN_STYLUS2		0x14c

#define KEY_MAX			0x1ff

struct KeyName
{
    unsigned int raw;
    const char * name;
};

extern int g_maxKeys;
extern struct KeyName keys[];

const char* pspIrKeybRawkeyName(unsigned int raw);

#ifdef __cplusplus
}
#endif

#endif /* __RAWKEYS_H */
