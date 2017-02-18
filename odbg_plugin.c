// Created by John AAkerblom 2015-10-02

#include <windows.h>
#include "version.h"

#ifdef _MSC_VER
    #pragma warning(disable:4996) // CRT_SECURE_NO_WARNINGS
#endif

// defines from plugin.h from the plugin SDK
#ifndef __ODBG_PLUGIN_H // plugin.h from plugin SDK
    #ifdef _MSC_VER
        #define _export      __declspec(dllexport)
    #endif
    // Put other compilers here...
    #ifdef __cplusplus
        #define extc         extern "C" _export
    #else
        #define extc         extern     _export
    #endif
    #define SHORTNAME      32              // Max length of short or module name
    typedef unsigned long  ulong;          // Unsigned long
#endif

#define PLUGINNAME  L"LosweiterOlly"
#define VERSION     L"2.00.01"

static void _PatchEnumProcessModules();

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	return TRUE;
}

extc int __cdecl ODBG2_Plugininit(void) 
{
    OutputDebugStringA("LosweiterOlly " ___VERSION_STRING___ " loaded");
	_PatchEnumProcessModules();
    return 0;
}

extc int __cdecl ODBG2_Pluginquery(int ollydbgversion, ulong *features,
    wchar_t pluginname[SHORTNAME], wchar_t pluginversion[SHORTNAME]) 
{
    // Report name and version to OllyDbg.
    wcscpy(pluginname, PLUGINNAME);
    wcscpy(pluginversion, VERSION);
    
    return 0x02010001;
};

// Patches EnumProcessModules() to just immediately return 0
static void _PatchEnumProcessModules(void)
{
	DWORD dwOldProtect = 0;
	HANDLE hPsapi = GetModuleHandleA("PSAPI.DLL");
	FARPROC addr_epm = GetProcAddress(hPsapi, "EnumProcessModules");
	unsigned char patch_epm[] = {
		0x31, 0xC0,         // XOR EAX, EAX
		0xC2, 0x10, 0x00    // RETN 10
	};
	static unsigned char orig_epm[(sizeof(patch_epm))];

	memcpy(orig_epm, addr_epm, sizeof(orig_epm));
	VirtualProtect(addr_epm, sizeof(orig_epm), PAGE_EXECUTE_READWRITE, &dwOldProtect);
	memcpy(addr_epm, patch_epm, sizeof(patch_epm));
	VirtualProtect(addr_epm, sizeof(orig_epm), dwOldProtect, &dwOldProtect);
}
