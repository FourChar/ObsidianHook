#pragma once

class CEngineHooks
{
public:
	bool							InitiateAntiCheatProtection					( );

	void							SetGame_Name								( const char *Name );
	void							SetGame_Module								( const char *Module );
	void							SetHack_Version								( const char *Version );

	char				*&			GetGame_Name								( );
	char				*&			GetGame_Module								( );
	char				*&			GetHack_Version								( );
	DWORD				&			GetGame_ModuleBase							( );
	DWORD				&			GetGame_ModuleSize							( );

	bool							CheckGame_Name								( const char *Name );

	void							SetAntiCheat_Name							( const char *Name );
	bool							CheckAntiCheat_Name							( const char *Name );
	char				*&			GetAntiCheat_Name							( );
	char				*&			GetAntiCheat_Module							( );
	DWORD				&			GetAntiCheat_ModuleBase						( );
	DWORD				&			GetAntiCheat_ModuleSize						( );

	void							HookBreakPoints								( );
	void							BreakpointSetup								( );

	void							SetBreakPointAddress						( int BreakPointNumber, DWORD Address, PBYTE Function );
	DWORD				&			GetBreakPointAddress						( int BreakPointNumber );
	PBYTE				&			GetBreakPointReturn							( int BreakPointNumber );
	PBYTE				&			GetBreakPointFunction						( int BreakPointNumber );

private:
	char				*			Hack_Version;

	char				*			Game_Name;
	char				*			Game_Module;
	DWORD							Game_ModuleBase;
	DWORD							Game_ModuleSize;

	char				*			AntiCheat_Name;
	char				*			AntiCheat_Module;
	DWORD							AntiCheat_ModuleBase;
	DWORD							AntiCheat_ModuleSize;

	LPTOP_LEVEL_EXCEPTION_FILTER	OldExeptionHandler;

	DWORD							dwBreakPoints[3];
	PBYTE							pbBreakPointReturns[3];
	PBYTE							pbBreakPointFunctions[3];

	DWORD							NULLDword;
	PBYTE							NULLPByte;
};
extern CEngineHooks EngineHooks;

typedef DWORD	(WINAPI		* tGetWindowThreadProcessId)							( HWND, LPDWORD );
typedef DWORD	(WINAPI		* tGetThreadContext)									( HANDLE, LPCONTEXT );

LONG	__stdcall						MyExeptionHandler					( struct _EXCEPTION_POINTERS* ExceptionInfo );
LPTOP_LEVEL_EXCEPTION_FILTER			hkSetUnhandledExceptionFilter		( LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter );
DWORD	__stdcall						hkGetTickCount						( void );
BOOL	__stdcall						hkGetThreadContext					( HANDLE hThread, LPCONTEXT lpContext );

extern tGetWindowThreadProcessId		oGetWindowThreadProcessId;
extern tGetThreadContext				oGetThreadContext;