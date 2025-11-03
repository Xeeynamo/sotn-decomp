/*
    libpspirkeyb: PSP IR Keyboard Library (http://pspirkeyb.podzone.net)
    Copyright (C) 2007 Harald Fielker <harald.fielker@web.de>

    This program can be distributed under the terms of the GNU LGPL.
    See the file LICENSE.
*/

#ifndef __PSPIRKEYB_H
#define __PSPIRKEYB_H

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup PSPIrKeyb PSP IR Keyboard Library */

/** @addtogroup PSPIrKeyb */
/*@{*/

/**
 * Enumeration for the supported keyboards.
 *
 * @note PSP_IRKBD_TYPE_COMPAQ_MICROKBD, PSP_IRKBD_TYPE_FOLDABLE, PSP_IRKBD_TYPE_BENQ_GAMEPAD, PSP_IRKBD_TYPE_HPSLIM, PSP_IRKBD_TYPE_SNAPNTYPE can only be set in kernel mode because this requires baudrate change to irda
 */
enum PspIrKeyboards
{
	/** no keyboards. */
	PSP_IRKBD_TYPE_NONE             =  0,
    /** Compaq/HP foldable keyboard */
    PSP_IRKBD_TYPE_FOLDABLE         =  1,
    /** Snap'n'Type */
    PSP_IRKBD_TYPE_SNAPNTYPE        =  2,
    /** HP Slim keyboard */
    PSP_IRKBD_TYPE_BELKINIRF8U1500  =  3,
    /** BELKIN IR F8U1500 IRDA */
	PSP_IRKBD_TYPE_HPSLIM           =  5,
    /** Belkin IR (not IrDA) */
    PSP_IRKBD_TYPE_BELKINIR         =  8,
    /** Flexis FX-100 keyboard */
    PSP_IRKBD_TYPE_FLEXIS           =  9,
    /** Benq G250 gamepad */
    PSP_IRKBD_TYPE_BENQ_GAMEPAD     = 10,
    /** Micro Innovations Pocketop keyboard */
    PSP_IRKBD_TYPE_MICRO_INNOVATIONS= 11,
    /** Micro Innovations Foldaway keyboard */
    PSP_IRKBD_TYPE_MICRO_FOLDAWAY   = 12,
    /** Micro Innovations Datapad */
    PSP_IRKBD_TYPE_MICRO_DATAPAD    = 13,
    /** Compaq MicroKeyboard */
    PSP_IRKBD_TYPE_COMPAQ_MICROKBD  = 14,
    /** Targus Universal Wireless keyboard */
    PSP_IRKBD_TYPE_TARGUSIR         = 15,
    /** Freedom keyboard */
    PSP_IRKBD_TYPE_FREEDOM          = 18,
    /** NOVAETS - KIS2 - IR Keyboard */
    PSP_IRKBD_TYPE_NOVAETS_KIS2     = 19,
    /** Palm Universal Wireless Keyboard */
    PSP_IRKBD_TYPE_PALM_UW          = 20,
    /** hama palm keyboard*/
    PSP_IRKBD_TYPE_HAMA             = 21,
    /** Sprint PCS keyboard */
    PSP_IRKBD_TYPE_SPRINT           = 22,
    /** Palm One Wireless Keyboard */
    PSP_IRKBD_TYPE_PALM_ONE         = 23
};

/**
 * Enumeration for function results.
 *
 * @note this are all return codes from the PSP IR Keyb library
 */
enum PspIrKeyResults
{
    /** result ok */
    PSP_IRKBD_RESULT_OK                         =    0,
    /** failed */
    PSP_IRKBD_RESULT_FAILED                     =   -1,
    /** can't open irda device */
    PSP_IRKBD_RESULT_CANT_OPEN_DEVICE           =   -2,
    /** can't open map file or file doesn't exist */
    PSP_IRKBD_RESULT_CANT_OPEN_MAPFILE          =   -3,
    /** can't open the map file */
    PSP_IRKBD_RESULT_MAPFILE_MAXDEPTHLEVEL      =   -4,
    /** mapfile's include max nestlevel reached */
    PSP_IRKBD_RESULT_CANT_OPEN_MAPFILE_INCLUDE  =   -5,
    /** can't set baudrate - you might need to be in kernel mode for some keyboards */
    PSP_IRKBD_RESULT_CANT_SET_BAUDTATE          =   -6,
    /** config file not found */
    PSP_IRKBD_RESULT_CONFIG_FILE_NOT_FOUND      =   -7,
    /** unknown keyboard in ini file */
    PSP_IRKBD_RESULT_UNKNOW_KEYBOARD            =   -8,
};

/**
 * Enumeration for library output modes.
 *
 * @note this are possible output modes
 */
enum PspIrKeyOutputModes
{
    /**  ascii without control sequences e.g. UP/DOWN keys  */
    PSP_IRKBD_OUTPUT_MODE_ASCII                 = 0,
    /** raw codes - basically use this for creating new drivers - result is a SIrKeybRawCodeData pointer */
    PSP_IRKBD_OUTPUT_MODE_RAW                   = 1,
    /** scan codes - use this to write games - result is a SIrKeybScanCodeData pointer */
    PSP_IRKBD_OUTPUT_MODE_SCANCODE              = 2,
    /** vt100 mode - special chars will be mapped to vt100 (escape)sequences or codes */
    PSP_IRKBD_OUTPUT_MODE_VT100                 = 3,
};

/** Returning data in raw code mode */
typedef struct SIrKeybRawCodeData
{
    /** 0 = not pressed, else = pressed */
    unsigned char pressed;
    /** raw key */
    unsigned char raw;
} SIrKeybRawCodeData;

/** Returning data in scan code mode */
typedef struct SIrKeybScanCodeData
{
    /** shift key: 0 = not pressed, else = pressed */
    unsigned char shift;
    /** control key: 0 = not pressed, else = pressed */
    unsigned char ctrl;
    /** alt key: 0 = not pressed, else = pressed */
    unsigned char alt;
    /** 0 = not pressed, else = pressed */
    unsigned char pressed;
    /** effective raw key - this includes modifiers from map */
    unsigned char raw;
} SIrKeybScanCodeData;

/* we hide this functions when we use the prx mode */
#ifndef __PSPIRKEYB_HIDE_LIB_FUNCTIONS

/**
 * Initalizes the keyboard from a ini file.
 *
 * @param inifile - Inifile. If this is NULL the default file 'ms0:/seplugins/pspirkeyb.ini' is used.
 * @param kernelmode - Initalize in kernel mode. 0 = no kernel - 1 = kernelmode. Kernel mode is needed for some keyboards to set the baudrate.
 *
 * @note the keyboard will be opened in ascii mode. If you set "kernelmode" to -1 and are not in kernel mode your application crashes.
 *
 * @returns PspIrKeyResults constant.
 */
int pspIrKeybInit(const char* inifile, int kernelmode);

/**
 * Set the output mode of the skeyboard.
 *
 * @param outputmode - a PspIrKeyOutputModes constant.
 *
 * @returns PspIrKeyResults constant.
 */
int pspIrKeybOutputMode( int outputmode );

/**
 * Returns the current output mode of the keyboard.
 *
 * @returns PspIrKeyOutputModes constant.
 */
int pspIrKeybGetOutputMode();

/**
 * Nonblocking read data from the keyboard.
 *
 * The Keyboard input data goes to "buff". The result depends on the selected
 * of pspIrKeybOutputMode().
 *
 * PSP_IRKBD_OUTPUT_MODE_ASCII
 *     returns unsigned char
 * PSP_IRKBD_OUTPUT_MODE_VT100
 *     returns unsigned char
 * PSP_IRKBD_OUTPUT_MODE_SCANCODE
 *     returns SIrKeybScanCodeData pointers
 * PSP_IRKBD_OUTPUT_MODE_RAW
 *     returns SIrKeybRawCodeData pointers
 *
 * @param buffer - Receive buffer.
 * @param length - Length of the received data.
 *
 * @par Example:
 * @code
 * unsigned char buffer[255];
 * int length;
 *
 * while( 1 ) {
 *      if( pspIrKeybReadinput( buffer, &length ) ==  PSP_IRKBD_RESULT_OK && length > 0)
 *          // Do something with the read keyboard data
 *          processKeyboardData( buffer, length );
 *      tick(); // this is a non blocking read
 * }
 * @endcode
 *
 * @returns PspIrKeyResults constant.
 */
int pspIrKeybReadinput(void* buffer, int *length);

/**
 * Finishes the keyboard driver.
 *
 * @returns PspIrKeyResults constant.
 */
int pspIrKeybFinish(void);

/*@}*/

#endif /*__PSPIRKEYB_HIDE_LIB_FUNCTIONS */

#ifdef __cplusplus
}
#endif

#endif
