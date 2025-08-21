#pragma once

extern DWORD							Direct3D_ModuleBase;
extern DWORD							RenderDx9_ModuleBase;
extern DWORD							initDll_ModuleBase;

extern DWORD							Direct3D_ModuleSize;
extern DWORD							RenderDx9_ModuleSize;


class CDirect3DHooks
{
public:
	DWORD							FindPattern									( DWORD dwAddress, DWORD dwLen, PBYTE ByteMask, char *StringMask );
	DWORD							GetModuleSize								( char* module );
	PBYTE							HookVTableFunction							( PDWORD* dwVTable, PBYTE dwHook, int Index );

private:
	DWORD							GetProperBase								( const char *Module );
	DWORD							GetProperSize								( const char *Module );
	BOOL							DataCompare									(const BYTE* pData, const BYTE* bMask, const char* szMask);
};