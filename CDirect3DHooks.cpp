#include "stdafx.h"

DWORD							Direct3D_ModuleBase;
DWORD							RenderDx9_ModuleBase;
DWORD							initDll_ModuleBase;

DWORD							Direct3D_ModuleSize;
DWORD							RenderDx9_ModuleSize;


DWORD CDirect3DHooks::GetModuleSize( char* module )
{
	HMODULE hMod = GetModuleHandle(module);

    if( !hMod )
        return 0;

    MODULEENTRY32 lpme = { 0 };
    DWORD dwSize = 0;
    DWORD PID = GetProcessId(hMod);
    BOOL isMod = 0;

    HANDLE hSnapshotModule = CreateToolhelp32Snapshot( 0x8, PID );
    if( hSnapshotModule )
    {
        lpme.dwSize = sizeof( lpme );
        isMod = Module32First( hSnapshotModule, &lpme );
        while( isMod )
        {
            if( lpme.hModule == hMod )
            {
                dwSize = lpme.modBaseSize;
                CloseHandle( hSnapshotModule );
                return dwSize;
            }
            isMod = Module32Next( hSnapshotModule, &lpme );
        }
    }
    CloseHandle( hSnapshotModule );

    return 0;
}

DWORD CDirect3DHooks::GetProperBase( const char *Module )
{
	DWORD ProperBase	= NULL;

	if( ProperBase = (DWORD)GetModuleHandleA( Module ) )
		return ProperBase;
	else if( ProperBase = (DWORD)LoadLibraryA( Module ) )
		return ProperBase;

	return NULL;
}

DWORD CDirect3DHooks::GetProperSize( const char *Module )
{
	HMODULE				hMod				= GetModuleHandleA( Module );
	MODULEENTRY32		lpme				= { 0 };
	DWORD				dwSize				= 0;
	DWORD				PID					= GetProcessId(hMod);
	BOOL				isMod				= 0;
	HANDLE				hSnapshotModule		= NULL;

	if( !hMod )
		return NULL;

	hSnapshotModule = CreateToolhelp32Snapshot( 0x8, PID );
    if( hSnapshotModule )
    {
        lpme.dwSize = sizeof( lpme );
        isMod = Module32First( hSnapshotModule, &lpme );
        while( isMod )
        {
            if( lpme.hModule == hMod )
            {
                dwSize = lpme.modBaseSize;
                CloseHandle( hSnapshotModule );
                return dwSize;
            }
            isMod = Module32Next( hSnapshotModule, &lpme );
        }
    }
    CloseHandle( hSnapshotModule );

	return NULL;
}

BOOL CDirect3DHooks::DataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
    for(;*szMask;++szMask,++pData,++bMask)
        if(*szMask=='x' && *pData!=*bMask)   return 0;
    return (*szMask) == NULL;
}

DWORD CDirect3DHooks::FindPattern(DWORD dwdwAdd,DWORD dwLen,BYTE *bMask,char * szMask)
{
    for(DWORD i=0; i<dwLen; i++)
        if (this->DataCompare((BYTE*)(dwdwAdd+i),bMask,szMask))  return (DWORD)(dwdwAdd+i);
    return 0;
}

PBYTE CDirect3DHooks::HookVTableFunction( PDWORD* dwVTable, PBYTE dwHook, int Index )
{
	DWORD dwOld = 0;
	VirtualProtect((void*)((*dwVTable) + Index), 4, PAGE_EXECUTE_READWRITE, &dwOld);

	PBYTE pOrig = ((PBYTE)(*dwVTable)[Index]); 
	(*dwVTable)[Index] = (DWORD)dwHook;

	VirtualProtect((void*)((*dwVTable) + Index), 4, dwOld, &dwOld);

	return pOrig;
}