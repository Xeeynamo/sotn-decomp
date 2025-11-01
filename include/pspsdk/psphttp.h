/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * psphttp.h - Interface to the http library.
 *
 * Copyright (c) 2008 David Perry (InsertWittyName)
 * Copyright (c) 2008 moonlight
 *
 */
 
#ifndef __PSPHTTP_H__
#define __PSPHTTP_H__

#include <pspkerneltypes.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef enum
{
	PSP_HTTP_VERSION_1_0,
	PSP_HTTP_VERSION_1_1
} PspHttpHttpVersion;

typedef enum
{
	PSP_HTTP_METHOD_GET,
	PSP_HTTP_METHOD_POST,
	PSP_HTTP_METHOD_HEAD
	
} PspHttpMethod;

typedef enum
{
	PSP_HTTP_AUTH_BASIC,
	PSP_HTTP_AUTH_DIGEST
} PspHttpAuthType;


typedef enum
{
	PSP_HTTP_PROXY_AUTO,
	PSP_HTTP_PROXY_MANUAL
} PspHttpProxyMode;

typedef enum
{
	PSP_HTTP_HEADER_OVERWRITE,
	PSP_HTTP_HEADER_ADD
} PspHttpAddHeaderMode;

/* Memory function types */
typedef void *(*PspHttpMallocFunction)(SceSize size);
typedef void *(*PspHttpReallocFunction)(void *p, SceSize size);
typedef void (*PspHttpFreeFunction)(void *p);

typedef int (*PspHttpPasswordCB)(
	int request,
	PspHttpAuthType auth_type,
	const unsigned char *realm,
	unsigned char *username,
	unsigned char *password,
	SceBool need_entity,
	unsigned char **entity_body,
	SceSize *entity_size,
	SceBool *save);

/**
 * Init the http library.
 *
 * @param unknown1 - Memory pool size? Pass 20000
 * @return 0 on success, < 0 on error.
 */
int sceHttpInit(unsigned int unknown1);

/**
 * Terminate the http library.
 *
 * @return 0 on success, < 0 on error.
 */
int sceHttpEnd(void);

/**
 * Create a http template.
 *
 * @param agent - User agent
 * @param unknown1 - Pass 1
 * @param unknown2 - Pass 0
 * @return A template ID on success, < 0 on error.
 */
int sceHttpCreateTemplate(char *agent, int unknown1, int unknown2);

/**
 * Delete a http template.
 *
 * @param templateid - ID of the template created by sceHttpCreateTemplate
 * @return 0 on success, < 0 on error.
 */
int sceHttpDeleteTemplate(int templateid);

/**
 * Create a http connection.
 *
 * @param templateid - ID of the template created by sceHttpCreateTemplate
 * @param host - Host to connect to
 * @param unknown1 - Pass "http"
 * @param port - Port to connect on
 * @param unknown2 - Pass 0
 * @return A connection ID on success, < 0 on error.
 */
int sceHttpCreateConnection(int templateid, char *host, char *unknown1, unsigned short port, int unknown2);

/**
 * Create a http connection to a url.
 *
 * @param templateid - ID of the template created by sceHttpCreateTemplate
 * @param url - url to connect to
 * @param unknown1 - Pass 0
 * @return A connection ID on success, < 0 on error.
 */
int sceHttpCreateConnectionWithURL(int templateid, const char *url, int unknown1);

/**
 * Delete a http connection.
 *
 * @param connectionid - ID of the connection created by sceHttpCreateConnection or sceHttpCreateConnectionWithURL
 * @return 0 on success, < 0 on error.
 */
int sceHttpDeleteConnection(int connectionid);

/**
 * Create a http request.
 *
 * @param connectionid - ID of the connection created by sceHttpCreateConnection or sceHttpCreateConnectionWithURL
 * @param method - One of ::PspHttpMethod
 * @param path - Path to access
 * @param contentlength - Length of the content (POST method only)
 * @return A request ID on success, < 0 on error.
 */
int sceHttpCreateRequest(int connectionid, PspHttpMethod method, char *path, SceULong64 contentlength);

/**
 * Create a http request with url.
 *
 * @param connectionid - ID of the connection created by sceHttpCreateConnection or sceHttpCreateConnectionWithURL
 * @param method - One of ::PspHttpMethod
 * @param url - url to access
 * @param contentlength - Length of the content (POST method only)
 * @return A request ID on success, < 0 on error.
 */
int sceHttpCreateRequestWithURL(int connectionid, PspHttpMethod method, char *url, SceULong64 contentlength);

/**
 * Delete a http request.
 *
 * @param requestid - ID of the request created by sceHttpCreateRequest or sceHttpCreateRequestWithURL
 * @return 0 on success, < 0 on error.
 */
int sceHttpDeleteRequest(int requestid);

/**
 * Send a http request.
 *
 * @param requestid - ID of the request created by sceHttpCreateRequest or sceHttpCreateRequestWithURL
 * @param data - For POST methods specify a pointer to the post data, otherwise pass NULL
 * @param datasize - For POST methods specify the size of the post data, otherwise pass 0
 * @return 0 on success, < 0 on error.
 */
int sceHttpSendRequest(int requestid, void *data, unsigned int datasize);

/**
 * Abort a http request.
 *
 * @param requestid - ID of the request created by sceHttpCreateRequest or sceHttpCreateRequestWithURL
 * @return 0 on success, < 0 on error.
 */
int sceHttpAbortRequest(int requestid);

/**
 * Read a http request response.
 *
 * @param requestid - ID of the request created by sceHttpCreateRequest or sceHttpCreateRequestWithURL
 * @param data - Buffer for the response data to be stored
 * @param datasize - Size of the buffer 
 * @return The size read into the data buffer, 0 if there is no more data, < 0 on error.
 */
int sceHttpReadData(int requestid, void *data, unsigned int datasize);

/**
 * Get http request response length.
 *
 * @param requestid - ID of the request created by sceHttpCreateRequest or sceHttpCreateRequestWithURL
 * @param contentlength - The size of the content
 * @return 0 on success, < 0 on error.
 */
int sceHttpGetContentLength(int requestid, SceULong64 *contentlength);

/**
 * Get http request status code.
 *
 * @param requestid - ID of the request created by sceHttpCreateRequest or sceHttpCreateRequestWithURL
 * @param statuscode - The status code from the host (200 is ok, 404 is not found etc)
 * @return 0 on success, < 0 on error.
 */
int sceHttpGetStatusCode(int requestid, int *statuscode);

/**
 * Set resolver timeout
 *
 * @param id - ID of the template or connection 
 * @param timeout - Timeout value in microseconds
 * @return 0 on success, < 0 on error.
 */
int sceHttpSetResolveTimeOut(int id, unsigned int timeout);

/**
 * Set resolver retry
 *
 * @param id - ID of the template or connection 
 * @param count - Number of retries
 * @return 0 on success, < 0 on error.
 */
int sceHttpSetResolveRetry(int id, int count);

/**
 * Set connect timeout
 *
 * @param id - ID of the template, connection or request 
 * @param timeout - Timeout value in microseconds
 * @return 0 on success, < 0 on error.
 */
int sceHttpSetConnectTimeOut(int id, unsigned int timeout);

/**
 * Set send timeout
 *
 * @param id - ID of the template, connection or request 
 * @param timeout - Timeout value in microseconds
 * @return 0 on success, < 0 on error.
 */
int sceHttpSetSendTimeOut(int id, unsigned int timeout);

/**
 * Set receive timeout
 *
 * @param id - ID of the template or connection 
 * @param timeout - Timeout value in microseconds
 * @return 0 on success, < 0 on error.
 */
int sceHttpSetRecvTimeOut(int id, unsigned int timeout);

/**
 * Enable keep alive
 *
 * @param id - ID of the template or connection 
 * @return 0 on success, < 0 on error.
 */
int sceHttpEnableKeepAlive(int id);

/**
 * Disable keep alive
 *
 * @param id - ID of the template or connection 
 * @return 0 on success, < 0 on error.
 */
int sceHttpDisableKeepAlive(int id);

/**
 * Enable redirect
 *
 * @param id - ID of the template or connection 
 * @return 0 on success, < 0 on error.
 */
int sceHttpEnableRedirect(int id);

/**
 * Disable redirect
 *
 * @param id - ID of the template or connection 
 * @return 0 on success, < 0 on error.
 */
int sceHttpDisableRedirect(int id);

/**
 * Enable cookie
 *
 * @param id - ID of the template or connection 
 * @return 0 on success, < 0 on error.
 */
int sceHttpEnableCookie(int id);

/**
 * Disable cookie
 *
 * @param id - ID of the template or connection 
 * @return 0 on success, < 0 on error.
 */
int sceHttpDisableCookie(int id);

/**
 * Save cookie
 *
 * @return 0 on success, < 0 on error.
 */
int sceHttpSaveSystemCookie(void);

/**
 * Load cookie
 *
 * @return 0 on success, < 0 on error.
 */
int sceHttpLoadSystemCookie(void);

/**
 * Add content header
 *
 * @param id - ID of the template, connection or request 
 * @param name - Name of the content
 * @param value - Value of the content
 * @param unknown1 - Pass 0
 * @return 0 on success, < 0 on error.
 */
int sceHttpAddExtraHeader(int id, char *name, char *value, int unknown1);

/**
 * Delete content header
 *
 * @param id - ID of the template, connection or request 
 * @param name - Name of the content
 * @return 0 on success, < 0 on error.
 */
int sceHttpDeleteHeader(int id, const char *name);

/**
 * Init the https library.
 *
 * @param unknown1 - Pass 0
 * @param unknown2 - Pass 0
 * @param unknown3 - Pass 0
 * @param unknown4 - Pass 0
 *
 * @return 0 on success, < 0 on error.
*/
int sceHttpsInit(int unknown1, int unknown2, int unknown3, int unknown4);

/**
 * Terminate the https library
 *
 * @return 0 on success, < 0 on error.
*/
int sceHttpsEnd(void);

/**
 * Load default certificate
 *
 * @param unknown1 - Pass 0
 * @param unknown2 - Pass 0
 * @return 0 on success, < 0 on error.
*/
int sceHttpsLoadDefaultCert(int unknown1, int unknown2);

int sceHttpDisableAuth(int id);

int sceHttpDisableCache(int id);

int sceHttpEnableAuth(int id);

int sceHttpEnableCache(int id);

int sceHttpEndCache(void);

int sceHttpGetAllHeader(int request, unsigned char **header, unsigned int *header_size);

int sceHttpGetNetworkErrno(int request, int *err_num);

int sceHttpGetProxy(int id, int *activate_flag, int *mode, unsigned char *proxy_host, SceSize len, unsigned short *proxy_port);

int sceHttpInitCache(SceSize max_size);

int sceHttpSetAuthInfoCB(int id, PspHttpPasswordCB cbfunc);

int sceHttpSetProxy(int id, int activate_flag, int mode, const unsigned char *new_proxy_host, unsigned short new_proxy_port);

int sceHttpSetResHeaderMaxSize(int id, unsigned int header_size);

int sceHttpSetMallocFunction(PspHttpMallocFunction malloc_func, PspHttpFreeFunction free_func, PspHttpReallocFunction realloc_func);

#if defined(__cplusplus)
};
#endif

#endif
