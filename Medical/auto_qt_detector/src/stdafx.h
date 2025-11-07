// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
//#pragma warning(disable : 4996)


#include <iostream>
//#include <fstream>

// #define STDC_WANT_LIB_EXT1 1

// TODO: reference additional headers your program requires here
#ifdef _WIN32
  #include "./mman/mman.h"
#else
  #include <sys/mman.h>
#endif
#include <stdio.h>
#include <math.h>
#include <limits.h>
//#include <string.h>
//#include <wchar.h>
#include <stdlib.h>
// #include <fcntl.h>
#include <unistd.h>

#include <vector>
using namespace std;

typedef void *LPVOID;
typedef void *PVOID;
typedef PVOID HANDLE;

#ifndef _WIN32
  #define _MAX_PATH PATH_MAX
#endif

// Stuff from Windows headers:
typedef unsigned long       DWORD;
typedef unsigned long       ULONG_PTR;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef ULONG_PTR           DWORD_PTR;
#define MAKEWORD(a, b)      ((WORD)(((BYTE)((DWORD_PTR)(a) & 0xff)) | ((WORD)((BYTE)((DWORD_PTR)(b) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)((DWORD_PTR)(a) & 0xffff)) | ((DWORD)((WORD)((DWORD_PTR)(b) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)((DWORD_PTR)(l) & 0xffff))
#define HIWORD(l)           ((WORD)((DWORD_PTR)(l) >> 16))
#define LOBYTE(w)           ((BYTE)((DWORD_PTR)(w) & 0xff))
#define HIBYTE(w)           ((BYTE)((DWORD_PTR)(w) >> 8))

// typedef union _LARGE_INTEGER {
//   struct {
//     DWORD LowPart;
//     LONG  HighPart;
//   };
//   struct {
//     DWORD LowPart;
//     LONG  HighPart;
//   } u;
//   LONGLONG QuadPart;
// } LARGE_INTEGER, *PLARGE_INTEGER;
