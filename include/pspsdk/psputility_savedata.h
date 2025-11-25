/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  psputility_savedata.h - Definitions and Functions for savedata part of
 *                     pspUtility library
 *
 * Copyright (c) 2005    Shine
 *                       weltall <weltall@consoleworld.org>
 *                       Marcus R. Brown <mrbrown@ocgnet.org>
 *						 InsertWittyName <tias_dp@hotmail.com>
 *
 */

#ifndef __PSPUTILITY_SAVEDATA_H__
#define __PSPUTILITY_SAVEDATA_H__

#include <psptypes.h>
#include <pspkerneltypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Save data utility modes */
typedef enum
{
	PSP_UTILITY_SAVEDATA_AUTOLOAD = 0,
	PSP_UTILITY_SAVEDATA_AUTOSAVE,
	PSP_UTILITY_SAVEDATA_LOAD,
	PSP_UTILITY_SAVEDATA_SAVE,
	PSP_UTILITY_SAVEDATA_LISTLOAD,
	PSP_UTILITY_SAVEDATA_LISTSAVE,
	PSP_UTILITY_SAVEDATA_LISTDELETE,
	PSP_UTILITY_SAVEDATA_LISTALLDELETE,
	PSP_UTILITY_SAVEDATA_SIZES,
	PSP_UTILITY_SAVEDATA_AUTODELETE,
	PSP_UTILITY_SAVEDATA_DELETE,
	PSP_UTILITY_SAVEDATA_LIST,
	PSP_UTILITY_SAVEDATA_FILES,
	PSP_UTILITY_SAVEDATA_MAKEDATASECURE,
	PSP_UTILITY_SAVEDATA_MAKEDATA,
	PSP_UTILITY_SAVEDATA_READDATASECURE,
	PSP_UTILITY_SAVEDATA_READDATA,
	PSP_UTILITY_SAVEDATA_WRITEDATASECURE,
	PSP_UTILITY_SAVEDATA_WRITEDATA,
	PSP_UTILITY_SAVEDATA_ERASESECURE,
	PSP_UTILITY_SAVEDATA_ERASE,
	PSP_UTILITY_SAVEDATA_DELETEDATA,
	PSP_UTILITY_SAVEDATA_GETSIZE,
} PspUtilitySavedataMode;

/** Initial focus position for list selection types */
typedef enum
{
	PSP_UTILITY_SAVEDATA_FOCUS_UNKNOWN = 0,
	PSP_UTILITY_SAVEDATA_FOCUS_FIRSTLIST,	/* First in list */
	PSP_UTILITY_SAVEDATA_FOCUS_LASTLIST,	/* Last in list */
	PSP_UTILITY_SAVEDATA_FOCUS_LATEST,	/* Most recent date */
	PSP_UTILITY_SAVEDATA_FOCUS_OLDEST,	/* Oldest date */
	PSP_UTILITY_SAVEDATA_FOCUS_FIRSTDATA,	/* first non-empty (first if none) */
	PSP_UTILITY_SAVEDATA_FOCUS_LASTDATA,	/* last non-empty (first if none) */
	PSP_UTILITY_SAVEDATA_FOCUS_FIRSTEMPTY,	/* First empty slot */
	PSP_UTILITY_SAVEDATA_FOCUS_LASTEMPTY,	/*Last empty slot */
	
} PspUtilitySavedataFocus;

/*Save data utility return values  */
#define PSP_UTILITY_SAVEDATA_ERROR_TYPE					(0x80110300)	/*Type error */

/*Single call type error  */
/*Error when loading */
#define PSP_UTILITY_SAVEDATA_ERROR_LOAD_NO_MS			(0x80110301)	/*No Memory Stick(TM) was inserted */
#define PSP_UTILITY_SAVEDATA_ERROR_LOAD_EJECT_MS		(0x80110302)	/*Memory Stick(TM) was removed while save data was being accessed */
#define PSP_UTILITY_SAVEDATA_ERROR_LOAD_ACCESS_ERROR	(0x80110305)	/*Memory Stick(TM) access error occurred */
#define PSP_UTILITY_SAVEDATA_ERROR_LOAD_DATA_BROKEN		(0x80110306)	/*Specified save data was corrupted */
#define PSP_UTILITY_SAVEDATA_ERROR_LOAD_NO_DATA			(0x80110307)	/*Specified save data was not found */
#define PSP_UTILITY_SAVEDATA_ERROR_LOAD_PARAM			(0x80110308)	/*Utility could not run because parameter that was passed was illegal */
#define PSP_UTILITY_SAVEDATA_ERROR_LOAD_NO_FILE			(0x80110309)	/*Specified file could not be found */
#define PSP_UTILITY_SAVEDATA_ERROR_LOAD_INTERNAL		(0x8011030B)	/*Internal error */

/*Error code when saving */
#define PSP_UTILITY_SAVEDATA_ERROR_SAVE_NO_MS			(0x80110381)	/*No Memory Stick(TM) was inserted */
#define PSP_UTILITY_SAVEDATA_ERROR_SAVE_EJECT_MS		(0x80110382)	/*Memory Stick(TM) was removed while save data was being accessed */
#define PSP_UTILITY_SAVEDATA_ERROR_SAVE_MS_NOSPACE		(0x80110383)	/*Memory Stick(TM) did not contain the amount of free space required for saving */
#define PSP_UTILITY_SAVEDATA_ERROR_SAVE_MS_PROTECTED	(0x80110384)	/*Save data could not be accessed because Memory Stick(TM) was write-protected */
#define PSP_UTILITY_SAVEDATA_ERROR_SAVE_ACCESS_ERROR	(0x80110385)	/*Memory Stick(TM) access error occurred */
#define PSP_UTILITY_SAVEDATA_ERROR_SAVE_DATA_BROKEN		(0x80110386)	/*Specified save data was corrupted */
#define PSP_UTILITY_SAVEDATA_ERROR_SAVE_PARAM			(0x80110388)	/*Utility could not run because parameter that was passed was illegal */
#define PSP_UTILITY_SAVEDATA_ERROR_SAVE_INTERNAL		(0x8011038B)	/*Internal error */

/*Error code when deleting */
#define PSP_UTILITY_SAVEDATA_ERROR_DELETE_NO_MS			(0x80110341)	/*No Memory Stick(TM) was inserted */
#define PSP_UTILITY_SAVEDATA_ERROR_DELETE_EJECT_MS		(0x80110342)	/*Memory Stick(TM) was removed while save data was being accessed */
#define PSP_UTILITY_SAVEDATA_ERROR_DELETE_MS_PROTECTED	(0x80110344)	/*Save data could not be accessed because Memory Stick(TM) was write-protected */
#define PSP_UTILITY_SAVEDATA_ERROR_DELETE_ACCESS_ERROR	(0x80110345)	/*Memory Stick(TM) access error occurred */
#define PSP_UTILITY_SAVEDATA_ERROR_DELETE_NO_DATA		(0x80110347)	/*Specified save data was not found */
#define PSP_UTILITY_SAVEDATA_ERROR_DELETE_PARAM			(0x80110348)	/*Utility could not run because parameter that was passed was illegal */
#define PSP_UTILITY_SAVEDATA_ERROR_DELETE_INTERNAL		(0x8011034B)	/*Internal error */

/*Error code when getting size */
#define PSP_UTILITY_SAVEDATA_ERROR_SIZES_NO_MS			(0x801103C1)	/*No Memory Stick(TM) was inserted */
#define PSP_UTILITY_SAVEDATA_ERROR_SIZES_EJECT_MS		(0x801103C2)	/*Memory Stick(TM) was removed while save data was being accessed */
#define PSP_UTILITY_SAVEDATA_ERROR_SIZES_ACCESS_ERROR	(0x801103C5)	/*Memory Stick(TM) access error occurred */
#define PSP_UTILITY_SAVEDATA_ERROR_SIZES_DATA_BROKEN	(0x801103C6)	/*Specified save data was corrupted */
#define PSP_UTILITY_SAVEDATA_ERROR_SIZES_NO_DATA		(0x801103C7)	/*Specified save data was not found */
#define PSP_UTILITY_SAVEDATA_ERROR_SIZES_PARAM			(0x801103C8)	/*Utility could not run because parameter that was passed was illegal */
#define PSP_UTILITY_SAVEDATA_ERROR_SIZES_INTERNAL		(0x801103CB)	/*Internal error */

/*Error code for types supporting multiple calls */
#define PSP_UTILITY_SAVEDATA_ERROR_MC_NO_MS				(0x80110321)	/*No Memory Stick(TM) was inserted */
#define PSP_UTILITY_SAVEDATA_ERROR_MC_EJECT_MS			(0x80110322)	/*Memory Stick(TM) was removed while save data was being accessed */
#define PSP_UTILITY_SAVEDATA_ERROR_MC_MS_NOSPACE		(0x80110323)	/*Memory Stick(TM) did not contain the amount of free space required for saving */
#define PSP_UTILITY_SAVEDATA_ERROR_MC_MS_PROTECTED		(0x80110324)	/*Save data could not be accessed because Memory Stick(TM) was write-protected */
#define PSP_UTILITY_SAVEDATA_ERROR_MC_ACCESS_ERROR		(0x80110325)	/*Memory Stick(TM) access error occurred */
#define PSP_UTILITY_SAVEDATA_ERROR_MC_DATA_BROKEN		(0x80110326)	/*Specified save data was corrupted */
#define PSP_UTILITY_SAVEDATA_ERROR_MC_NO_DATA			(0x80110327)	/*Specified save data was not found */
#define PSP_UTILITY_SAVEDATA_ERROR_MC_PARAM				(0x80110328)	/*Utility could not run because parameter that was passed was illegal */
#define PSP_UTILITY_SAVEDATA_ERROR_MC_NO_FILE			(0x80110329)	/*Specified file could not be found  */
#define PSP_UTILITY_SAVEDATA_ERROR_MC_SUSPEND_ERROR		(0x8011032A)	/*Processing stopped because the utility was suspended during multiple calls */
#define PSP_UTILITY_SAVEDATA_ERROR_MC_INTERNAL			(0x8011032B)	/*Internal error */
#define PSP_UTILITY_SAVEDATA_ERROR_MC_STATUS_ERROR		(0x8011032C)	/*Multiple call status error */
#define PSP_UTILITY_SAVEDATA_ERROR_MC_SECUREFILE_FULL	(0x8011032D)	/*No more protected files can be added */


/** title, savedataTitle, detail: parts of the unencrypted SFO
    data, it contains what the VSH and standard load screen shows */
typedef struct PspUtilitySavedataSFOParam
{
	char title[0x80];
	char savedataTitle[0x80];
	char detail[0x400];
	unsigned char parentalLevel;
	unsigned char unknown[3];
	
} PspUtilitySavedataSFOParam;

typedef struct PspUtilitySavedataFileData {
	void *buf;
	SceSize bufSize;
	SceSize size;	/* ??? - why are there two sizes? */
	int unknown;
	
} PspUtilitySavedataFileData;

typedef struct PspUtilitySavedataSizeEntry {
	uint64_t size;
	char name[16];

} PspUtilitySavedataSizeEntry;

typedef struct PspUtilitySavedataSizeInfo {
	int numSecureEntries;
	int numNormalEntries;
	PspUtilitySavedataSizeEntry *secureEntries;
	PspUtilitySavedataSizeEntry *normalEntries;
	int sectorSize;
	int freeSectors;
	int freeKB;
	char freeString[8];
	int neededKB;
	char neededString[8];
	int overwriteKB;
	char overwriteString[8];

} PspUtilitySavedataSizeInfo;

typedef struct PspUtilitySavedataIdListEntry
{
	int st_mode;
	ScePspDateTime sce_st_ctime;
	ScePspDateTime sce_st_atime;
	ScePspDateTime sce_st_mtime;
	char name[20];

} PspUtilitySavedataIdListEntry;

typedef struct PspUtilitySavedataIdListInfo
{
	int maxCount;
	int resultCount;
	PspUtilitySavedataIdListEntry *entries;

} PspUtilitySavedataIdListInfo;

typedef struct PspUtilitySavedataFileListEntry
{
	int st_mode;
	uint32_t st_unk0;
	uint64_t st_size;
	ScePspDateTime sce_st_ctime;
	ScePspDateTime sce_st_atime;
	ScePspDateTime sce_st_mtime;
	char name[16];

} PspUtilitySavedataFileListEntry;

typedef struct PspUtilitySavedataFileListInfo
{
	uint32_t maxSecureEntries;
	uint32_t maxNormalEntries;
	uint32_t maxSystemEntries;
	uint32_t resultNumSecureEntries;
	uint32_t resultNumNormalEntries;
	uint32_t resultNumSystemEntries;
	PspUtilitySavedataFileListEntry *secureEntries;
	PspUtilitySavedataFileListEntry *normalEntries;
	PspUtilitySavedataFileListEntry *systemEntries;

} PspUtilitySavedataFileListInfo;

typedef struct PspUtilitySavedataMsFreeSize
{
	int clusterSize;
	int freeClusters;
	int freeSpaceKB;
	char freeSpaceStr[8];

} PspUtilitySavedataMsFreeSize;

typedef struct PspUtilitySavedataUtilityDataSize
{
	int usedClusters;
	int usedSpaceKB;
	char usedSpaceStr[8];
	int usedSpace32KB;
	char usedSpace32Str[8];

} PspUtilitySavedataUtilityDataSize;

typedef struct PspUtilitySavedataMsDataSize
{
	char gameName[13];
	char pad[3];
	char saveName[20];
	PspUtilitySavedataUtilityDataSize info;

} PspUtilitySavedataMsDataSize;

typedef struct PspUtilitySavedataListSaveNewData
{
	PspUtilitySavedataFileData icon0;
	char *title;
	
} PspUtilitySavedataListSaveNewData;

/** Structure to hold the parameters for the ::sceUtilitySavedataInitStart function. */
typedef struct PspUtilitySavedataParam
{
	pspUtilityDialogCommon base;

	PspUtilitySavedataMode mode;
	
	int bind;
	
	int overwrite;

	/** gameName: name used from the game for saves, equal for all saves */
	char gameName[13];
	char reserved[3];
	/** saveName: name of the particular save, normally a number */
	char saveName[20];

	/** saveNameList: used by multiple modes */
	char (*saveNameList)[20];

	/** fileName: name of the data file of the game for example DATA.BIN */
	char fileName[13];
	char reserved1[3];

	/** pointer to a buffer that will contain data file unencrypted data */
	void *dataBuf;
	/** size of allocated space to dataBuf */
	SceSize dataBufSize;
	SceSize dataSize;

	PspUtilitySavedataSFOParam sfoParam;

	PspUtilitySavedataFileData icon0FileData;
	PspUtilitySavedataFileData icon1FileData;
	PspUtilitySavedataFileData pic1FileData;
	PspUtilitySavedataFileData snd0FileData;

	/** Pointer to an PspUtilitySavedataListSaveNewData structure */
	PspUtilitySavedataListSaveNewData *newData;

	/** Initial focus for lists */
	PspUtilitySavedataFocus focus;

	int abortStatus;

	/* Function PSP_UTILITY_SAVEDATA_TYPE_SIZES */
	PspUtilitySavedataMsFreeSize *msFree;
	PspUtilitySavedataMsDataSize *msData;
	PspUtilitySavedataUtilityDataSize *utilityData;

#if defined(_PSP_FW_VERSION) && _PSP_FW_VERSION >= 200

	/** key: encrypt/decrypt key for save with firmware >= 2.00 */
	char key[16];

	uint32_t secureVersion;
	int multiStatus;

	/* Function 11 LIST */
	PspUtilitySavedataIdListInfo *idList;

	/* Function 12 FILES */
	PspUtilitySavedataFileListInfo *fileList;

	/* Function 22 GETSIZES */
	PspUtilitySavedataSizeInfo *sizeInfo;

#endif

} PspUtilitySavedataParam;


/**
 * Saves or Load savedata to/from the passed structure
 * After having called this continue calling sceUtilitySavedataGetStatus to
 * check if the operation is completed
 *
 * @param params - savedata parameters
 * @return 0 on success
 */
int sceUtilitySavedataInitStart(PspUtilitySavedataParam * params);

/**
 * Check the current status of the saving/loading/shutdown process
 * Continue calling this to check current status of the process
 * before calling this call also sceUtilitySavedataUpdate
 * @return 2 if the process is still being processed.
 * 3 on save/load success, then you can call sceUtilitySavedataShutdownStart.
 * 4 on complete shutdown.
 */
int sceUtilitySavedataGetStatus(void);


/**
 * Shutdown the savedata utility. after calling this continue calling
 * ::sceUtilitySavedataGetStatus to check when it has shutdown
 *
 * @return 0 on success
 *
 */
int sceUtilitySavedataShutdownStart(void);

/**
 * Refresh status of the savedata function
 *
 * @param unknown - unknown, pass 1
 */
int sceUtilitySavedataUpdate(int unknown);

#ifdef __cplusplus
}
#endif

#endif
