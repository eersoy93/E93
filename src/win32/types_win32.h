/* DESCRIPTION: E93 Win32 Data Type Definitions File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: MIT license. See README.md file for deatils.
 */

#ifndef TYPES_WIN32_H
#define TYPES_WIN32_H

#include <stdint.h>

#define UNICODE  // Unicode are default in Windows Mode.

#define APIENTRY WINAPI
#define CALLBACK __stdcall
#define CONST const
#define POINTER_SIGNED __sptr
#define POINTER_UNSIGNED __uptr
#define VOID void
#define WINAPI __stdcall

#define POINTER_32
#define POINTER_64

// They are Win32 data types for 32-bit x86.

typedef int32_t BOOL;
typedef uint8_t BYTE;
typedef char CCHAR;
typedef char CHAR;
typedef uint32_t DWORD;
typedef uint32_t DWORD32;
typedef uint64_t DWORD64;
typedef uint64_t DWORDLONG;
typedef float FLOAT;
typedef int16_t HALF_PTR;
typedef int32_t HFILE;
typedef int32_t INT;
typedef int32_t INT_PTR;
typedef int8_t INT8;
typedef int16_t INT16;
typedef int32_t INT32;
typedef int64_t INT64;
typedef int64_t LONG;
typedef double LONGLONG;  // X86
typedef int32_t LONG32;
typedef int64_t LONG64;
typedef int64_t LONG_PTR;
typedef int32_t * LPINT;
typedef int64_t * LPLONG;
typedef void * LPVOID;
typedef void * PVOID;
typedef uint64_t QWORD;
typedef int16_t SHORT;
typedef unsigned char UCHAR;
typedef uint16_t UHALF_PTR;
typedef uint32_t UINT;
typedef uint8_t UINT8;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint64_t UINT64;
typedef uint32_t UINT_PTR;
typedef uint64_t ULONG;
typedef uint64_t ULONG_PTR;
typedef double ULONGLONG;  // X86
typedef uint32_t ULONG32;
typedef uint64_t ULONG64;
typedef uint32_t USHORT;
typedef uint16_t WORD;
typedef int32_t WCHAR;  // Hacky WCHAR definition beacuse no wchar_t.

typedef BYTE BOOLEAN;
typedef CHAR * LPSTR;
typedef DWORD COLORREF;
typedef DWORD LCID;
typedef DWORD LCTYPE;
typedef DWORD LGRPID;
typedef PVOID HANDLE;
typedef HANDLE HACCEL;
typedef HANDLE HBITMAP;
typedef HANDLE HBRUSH;
typedef HANDLE HCOLOR_SPACE;
typedef HANDLE HCONV;
typedef HANDLE HCONV_LIST;
typedef HANDLE HDC;
typedef HANDLE HDDEDATA;
typedef HANDLE HDESK;
typedef HANDLE HDROP;
typedef HANDLE HDWP;
typedef HANDLE HENHMETAFILE;
typedef HANDLE HFONT;
typedef HANDLE HGDIOBJ;
typedef HANDLE HGLOBAL;
typedef HANDLE HHOOK;
typedef HANDLE HICON;
typedef HANDLE HINSTANCE;
typedef HANDLE HKEY;
typedef HANDLE HKL;
typedef HANDLE HLOCAL;
typedef HANDLE HMENU;
typedef HANDLE HMETAFILE;
typedef HINSTANCE HMODULE;
typedef HANDLE HMONITOR;
typedef HANDLE HPALETTE;
typedef HANDLE HPEN;
typedef HANDLE HRGN;
typedef HANDLE HRSRC;
typedef HANDLE HSZ;
typedef HANDLE HWINSTA;
typedef HANDLE HWND;
typedef WORD LANGID;
typedef DWORD LCID;
typedef LONG_PTR LPARAM;
typedef BOOL * LPBOOL;
typedef BYTE * LPBYTE;
typedef DWORD * LPCOLORREF;
typedef CONST CHAR * LPCSTR;
typedef CONST WCHAR * LPCWSTR;  // UNICODE
typedef HANDLE * LPHANDLE;
typedef LONG_PTR LRESULT;
typedef DWORD * LPWORD;
typedef LPSTR LPWSTR;
typedef BOOL * PBOOL;
typedef BOOLEAN * PBOOLEAN;
typedef BYTE * PBYTE;
typedef CHAR * PCHAR;
typedef CONST CHAR * PCSTR;
typedef LPCSTR PCTSTR;  // UNICODE
typedef CONST WCHAR * PCWSTR;
typedef DWORD * PDWORD;
typedef DWORDLONG * PDWORDLONG;
typedef DWORD_PTR * PDWORD_PTR;
typedef DWORD32 * PDWORD32;
typedef DWORD64 * PDWORD64;
typedef FLOAT * PFLOAT;
typedef HALF_PTR PHALF_PTR;
typedef HANDLE * PHANDLE;
typedef HKEY * PHKEY;
typedef INT * PINT;
typedef INT_PTR * PINT_PTR;
typedef INT8 * PINT8;
typedef INT16 * PINT16;
typedef INT32 * PINT32;
typedef INT64 * PINT64;
typedef LONG * PLONG;
typedef LONGLONG * PLONGLONG;
typedef LONG_PTR * PLONG_PTR;
typedef LONG32 * PLONG32;
typedef LONG64 * PLONG64;
typedef SHORT * PSHORT;
typedef CHAR * PSTR;
typedef UCHAR * PUCHAR;
typedef UHALF_PTR * PUHALF_PTR;
typedef UINT * PUINT;
typedef UINT_PTR * PUINT_PTR;
typedef UINT8 * PUINT8;
typedef UINT16 * PUINT16;
typedef UINT32 * PUINT32;
typedef UINT64 * PUINT64;
typedef ULONG * PULONG;
typedef ULONGLONG * PULONGLONG;
typedef ULONG_PTR * PULONG_PTR;
typedef ULONG32 * PULONG32;
typedef ULONG64 * PULONG64;
typedef USHORT * PUSHORT;
typedef WCHAR PWSTR;
typedef HANDLE SC_HANDLE;
typedef LPVOID SC_LOCK;
typedef HANDLE SERVICE_STATUS_HANDLE;
typedef ULONG_PTR SIZE_T;
typedef LONG_PTR SSIZE_T;
typedef WCHAR TBYTE;  // UNICODE
typedef WCHAR TCHAR;  // UNICODE
typedef LONGLONG USN;
typedef UINT_PTR WPARAM;

typedef WORD ATOM;
typedef ULONG_PTR DWORD_PTR;
typedef LPCSTR LPCTSTR;  // UNICODE
typedef SIZE_T * PSIZE_T;
typedef SSIZE_T * PSSIZE_T;
typedef TBYTE * PTBYTE;
typedef TCHAR * PTCHAR;
typedef TCHAR * LPTCH;
typedef TCHAR * LPTSTR;
typedef LPWSTR PTSTR;  // UNICODE
typedef CHAR *LPCH;
typedef WCHAR *LPWCH;

typedef HICON HCURSOR;
typedef LONG HRESULT;

typedef struct _UNICODE_STRING
{
  USHORT  Length;
  USHORT  MaximumLength;
  PWSTR  Buffer;
} UNICODE_STRING;
typedef UNICODE_STRING * PUNICODE_STRING;
typedef const UNICODE_STRING * PCUNICODE_STRING;

#endif
