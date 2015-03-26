#ifndef _BASE
#define _BASE

#if !defined(_WIN32_WINNT)
#define _WIN32_WINNT 0x0501 	
#elif (_WIN32_WINNT < 0x0501)
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#pragma once

#include <Winsock2.h>
#include <Windows.h>
#include <stdlib.h>

// NULL define
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

// memory safe delete
#if !defined(SAFE_DELETE)
#define SAFE_DELETE(p)			if(p) { delete p; p = 0; }
#endif
#define SAFE_DELETE_ARRAY(p)	if(p) { delete[] p; p = 0; }
#define SAFE_FREE(p)			if(p) { free(p); p = 0; }

// macro sleep
#define SleepSec(s) Sleep( (s) * 1000 )

#define INVALID_HSESSION		0xFFFFFFFF

#pragma warning(disable:4819)

#endif