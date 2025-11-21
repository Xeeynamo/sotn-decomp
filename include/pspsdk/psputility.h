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

/* Utility execution result macro */
#define PSP_UTILITY_COMMON_RESULT_OK			(0)	/* Utility processing was successful */
#define PSP_UTILITY_COMMON_RESULT_CANCELED		(1)	/* Utility processing was canceled by the user */
#define PSP_UTILITY_COMMON_RESULT_ABORTED		(2)	/* Utility processing was forcibly terminated */

/**
 * Return-values for the various sceUtility***GetStatus() functions
**/
typedef enum
{
	PSP_UTILITY_COMMON_STATUS_NONE = 0,	/* Utility is uninitialized */
	PSP_UTILITY_COMMON_STATUS_INIT,		/* Utility is currently being initialized */
	PSP_UTILITY_COMMON_STATUS_RUNNING,	/* Utility is running */
	PSP_UTILITY_COMMON_STATUS_FINISHED,	/* Utility operation finished */
	PSP_UTILITY_COMMON_STATUS_SHUTDOWN,	/* Utility is shutting down */
	PSP_UTILITY_COMMON_STATUS_WAITING,	/* Utility is waiting for next call */
} pspUtilityCommonStatus;

#endif
