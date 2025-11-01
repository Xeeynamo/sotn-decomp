/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  psputility.h - Master include for the pspUtility library
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#ifndef __PSPUTILITY_H__
#define __PSPUTILITY_H__

typedef struct
{
	/** Size of the structure */
	unsigned int size;
	/** Language */
	int language;
	/** Set to 1 for X/O button swap */	
	int buttonSwap;
	/** Graphics thread priority */
	int graphicsThread;
	/** Access/fileio thread priority (SceJobThread) */
	int accessThread;
	/** Font thread priority (ScePafThread) */
	int fontThread;
	/** Sound thread priority */
	int soundThread;
	/** Result */	
	int result;
	/** Set to 0 */		
	int reserved[4];

} pspUtilityDialogCommon;

#include <psputility_msgdialog.h>
#include <psputility_netconf.h>
#include <psputility_netparam.h>
#include <psputility_savedata.h>
#include <psputility_gamesharing.h>
#include <psputility_htmlviewer.h>
#include <psputility_sysparam.h>
#include <psputility_osk.h>
#include <psputility_netmodules.h>
#include <psputility_avmodules.h>
#include <psputility_usbmodules.h>
#include <psputility_modules.h>

#define PSP_UTILITY_ACCEPT_CIRCLE 0
#define PSP_UTILITY_ACCEPT_CROSS  1

/**
 * Return-values for the various sceUtility***GetStatus() functions
**/
typedef enum
{
	PSP_UTILITY_DIALOG_NONE = 0,	/**< No dialog is currently active */
	PSP_UTILITY_DIALOG_INIT,		/**< The dialog is currently being initialized */
	PSP_UTILITY_DIALOG_VISIBLE,		/**< The dialog is visible and ready for use */
	PSP_UTILITY_DIALOG_QUIT,		/**< The dialog has been canceled and should be shut down */
	PSP_UTILITY_DIALOG_FINISHED		/**< The dialog has successfully shut down */
	
} pspUtilityDialogState;

#endif
