#include "stdafx.h"

tGetWindowThreadProcessId		oGetWindowThreadProcessId;
tGetThreadContext				oGetThreadContext;

//========================================================================================================

#ifndef PublicMode
void hkBreakPoint1( )
{
	__asm PUSHAD

	if( Game.Structs.cg->snap )
	{
		Game.AutoVote			( );
		Game.NameStealer		( );

		if( SubGame::isPlayerValid( SubGame::getLocalPlayerID( ) ) )
		{
			Game.AutoWeapons			( );
			Game.DoAimbot				( );
		}
	}

	Game.ZeroRecoil( );

	__asm POPAD
	( (void (__cdecl*)( ))EngineHooks.GetBreakPointReturn( 1 ) )( );
}

void hkBreakPoint2( )
{
	__asm PUSHAD

	//lolhai

	__asm POPAD
	( (void (__cdecl*)( ))EngineHooks.GetBreakPointReturn( 2 ) )( );
}

void hkBreakPoint3( )
{
	__asm PUSHAD

	//lolhai

	__asm POPAD
	( (void (__cdecl*)( ))EngineHooks.GetBreakPointReturn( 3 ) )( );
}

void hkBreakPoint4( )
{
	__asm PUSHAD

	//lolhai

	__asm POPAD
	( (void (__cdecl*)( ))EngineHooks.GetBreakPointReturn( 4 ) )( );
}
#endif

//========================================================================================================

DWORD WINAPI hkGetWindowThreadProcessId( HWND hWnd, LPDWORD lpdwProcessId )
{
	DWORD dwReturnAddress	= (DWORD)_ReturnAddress();

	if( dwReturnAddress > EngineHooks.GetAntiCheat_ModuleBase( ) && \
		dwReturnAddress < ( EngineHooks.GetAntiCheat_ModuleBase( ) + EngineHooks.GetAntiCheat_ModuleSize( ) ) )
	{
		return oGetWindowThreadProcessId( GetDesktopWindow( ), lpdwProcessId );
	}

	return oGetWindowThreadProcessId( hWnd, lpdwProcessId );
}

DWORD WINAPI CheckForAntiCheat( LPVOID AntiCheat_Module )
{
	char *AntiCheat_ModuleName		= (char *)AntiCheat_Module;

	while( !EngineHooks.GetAntiCheat_ModuleBase( ) )
	{
		EngineHooks.GetAntiCheat_ModuleBase( ) = (DWORD)GetModuleHandle( AntiCheat_ModuleName );
		Sleep( 250 );
	}
	while( !EngineHooks.GetAntiCheat_ModuleSize( ) )
	{
		EngineHooks.GetAntiCheat_ModuleSize( ) = (DWORD)D3DRenderer.Hooks.GetModuleSize( AntiCheat_ModuleName );
		Sleep( 250 );
	}

#ifndef PublicMode
	Log( "this->AntiCheat_ModuleBase: ------ 0x%.8X", EngineHooks.GetAntiCheat_ModuleBase( ) );
	Log( "this->AntiCheat_ModuleSize: ------ 0x%.8X", EngineHooks.GetAntiCheat_ModuleSize( ) );

	if( strcmp( EngineHooks.GetAntiCheat_Name( ), "PunkBuster" ) == 0 )
	{
		*(void**)&oGetWindowThreadProcessId	= (void*)DetourFunction( (PBYTE)GetWindowThreadProcessId,	(PBYTE)hkGetWindowThreadProcessId );
	}
#else
	*(void**)&oGetWindowThreadProcessId	= (void*)DetourFunction( (PBYTE)GetWindowThreadProcessId,	(PBYTE)hkGetWindowThreadProcessId );
#endif

	ExitThread( 0 );
}

//========================================================================================================

DETOUR_TRAMPOLINE(LPTOP_LEVEL_EXCEPTION_FILTER oSetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER), SetUnhandledExceptionFilter);
BYTE OriginalGetTickCountBytes[6];

//----------------------------------------------------------------

#ifndef PublicMode
DWORD WINAPI hkGetTickCount( )
{
	EngineHooks.BreakpointSetup( );

	WriteProcessMemory(GetCurrentProcess(),		(LPVOID)GetTickCount, &OriginalGetTickCountBytes, 5, 0);
	return GetTickCount( );
}

//----------------------------------------------------------------

LPTOP_LEVEL_EXCEPTION_FILTER hkSetUnhandledExceptionFilter( LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter )
{
	return oSetUnhandledExceptionFilter( MyExeptionHandler );
}

//----------------------------------------------------------------

BOOL WINAPI hkGetThreadContext( HANDLE hThread,LPCONTEXT lpContext )
{
	BOOL iReturn = oGetThreadContext( hThread, lpContext );

	if(lpContext->ContextFlags & CONTEXT_DEBUG_REGISTERS)
	{
		LPCONTEXT CleanContext	= lpContext;

		CleanContext->Dr0		= 0;
		CleanContext->Dr1		= 0;
		CleanContext->Dr2		= 0;
		CleanContext->Dr3		= 0;
		CleanContext->Dr6		= 0;
		CleanContext->Dr7		= 0;

		iReturn = oGetThreadContext( hThread, CleanContext );
	}

	return iReturn;
}

//----------------------------------------------------------------

void CEngineHooks::HookBreakPoints( )
{
	if( strcmp( this->AntiCheat_Name, "PunkBuster" ) == 0 )
	{
		if( this->dwBreakPoints[ 0 ] == NULL &&\
			this->dwBreakPoints[ 1 ] == NULL &&\
			this->dwBreakPoints[ 2 ] == NULL &&\
			this->dwBreakPoints[ 3 ] == NULL )
			return;

		ReadProcessMemory(GetCurrentProcess(),		(LPVOID)GetTickCount, &OriginalGetTickCountBytes, 5, 0);

		*(void**)&oGetThreadContext = (tGetThreadContext)DetourFunction( (PBYTE)GetThreadContext, (PBYTE)hkGetThreadContext );

		DetourFunction(					(PBYTE)GetTickCount,					(PBYTE)hkGetTickCount );
		DetourFunctionWithTrampoline(	(PBYTE)oSetUnhandledExceptionFilter,	(PBYTE)hkSetUnhandledExceptionFilter );
	}
}

//----------------------------------------------------------------

void CEngineHooks::BreakpointSetup( )
{
	OldExeptionHandler	= SetUnhandledExceptionFilter( MyExeptionHandler );

	CONTEXT Context		= {CONTEXT_DEBUG_REGISTERS};
	Context.Dr6			= 0x00000000;

	Context.Dr0			= this->dwBreakPoints[ 0 ];
	Context.Dr1			= this->dwBreakPoints[ 1 ];
	Context.Dr2			= this->dwBreakPoints[ 2 ];
	Context.Dr3			= this->dwBreakPoints[ 3 ];

	if( this->dwBreakPoints[ 0 ] != NULL )
	{
		Context.Dr7 = ( 1 << 0 );
		if( this->dwBreakPoints[ 1 ] != NULL )
		{
			Context.Dr7 |= ( 1 << 2 );
			if( this->dwBreakPoints[ 2 ] != NULL )
			{
				Context.Dr7 |= ( 1 << 4 );
				if( this->dwBreakPoints[ 3 ] != NULL )
				{
					Context.Dr7 |= ( 1 << 6 );
				}
			}
		}
	}
	else
	{
		Context.Dr7 = NULL;
	}

	SetThreadContext( GetCurrentThread(), &Context );
}

//----------------------------------------------------------------

int		Exception1 = NULL;
int		Exception2 = NULL;
int		Exception3 = NULL;
int		Exception4 = NULL;
LONG WINAPI MyExeptionHandler( struct _EXCEPTION_POINTERS* ExceptionInfo )
{
	if(ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP)
	{
		if( EngineHooks.GetBreakPointAddress( 1 ) != NULL )
		{
			if( (DWORD)ExceptionInfo->ExceptionRecord->ExceptionAddress == EngineHooks.GetBreakPointAddress( 1 ) )
			{
				if( Exception1 == 0 )
				{
					EngineHooks.GetBreakPointReturn( 1 ) = \
						DetourFunction(	(PBYTE)EngineHooks.GetBreakPointAddress( 1 ), EngineHooks.GetBreakPointFunction( 1 ) );

					ExceptionInfo->ContextRecord->Eip = (DWORD)EngineHooks.GetBreakPointFunction( 1 );
					DetourRemove( (PBYTE)EngineHooks.GetBreakPointReturn( 1 ), (PBYTE)EngineHooks.GetBreakPointFunction( 1 ) );
					Exception1 = 1;
				}
				else
				{
					ExceptionInfo->ContextRecord->Eip = (DWORD)EngineHooks.GetBreakPointFunction( 1 );
				}

				return EXCEPTION_CONTINUE_EXECUTION;
			}
			else
			{
				if( EngineHooks.GetBreakPointAddress( 2 ) != NULL )
				{
					if( (DWORD)ExceptionInfo->ExceptionRecord->ExceptionAddress == EngineHooks.GetBreakPointAddress( 2 ) )
					{
						if( Exception2 == 0 )
						{
							EngineHooks.GetBreakPointReturn( 2 ) = \
								DetourFunction(	(PBYTE)EngineHooks.GetBreakPointAddress( 2 ), EngineHooks.GetBreakPointFunction( 2 ) );

							ExceptionInfo->ContextRecord->Eip = (DWORD)EngineHooks.GetBreakPointFunction( 2 );
							DetourRemove( (PBYTE)EngineHooks.GetBreakPointReturn( 2 ), (PBYTE)EngineHooks.GetBreakPointFunction( 2 ) );
							Exception2 = 1;
						}
						else
						{
							ExceptionInfo->ContextRecord->Eip = (DWORD)EngineHooks.GetBreakPointFunction( 2 );
						}

						return EXCEPTION_CONTINUE_EXECUTION;
					}
					else
					{
						if( EngineHooks.GetBreakPointAddress( 3 ) != NULL )
						{
							if( (DWORD)ExceptionInfo->ExceptionRecord->ExceptionAddress == EngineHooks.GetBreakPointAddress( 3 ) )
							{
								if( Exception3 == 0 )
								{
									EngineHooks.GetBreakPointReturn( 3 ) = \
										DetourFunction(	(PBYTE)EngineHooks.GetBreakPointAddress( 3 ), EngineHooks.GetBreakPointFunction( 3 ) );

									ExceptionInfo->ContextRecord->Eip = (DWORD)EngineHooks.GetBreakPointFunction( 3 );
									DetourRemove( (PBYTE)EngineHooks.GetBreakPointReturn( 3 ), (PBYTE)EngineHooks.GetBreakPointFunction( 3 ) );
									Exception3 = 1;
								}
								else
								{
									ExceptionInfo->ContextRecord->Eip = (DWORD)EngineHooks.GetBreakPointFunction( 3 );
								}

								return EXCEPTION_CONTINUE_EXECUTION;
							}
							else
							{
								if( EngineHooks.GetBreakPointAddress( 4 ) != NULL )
								{
									if( (DWORD)ExceptionInfo->ExceptionRecord->ExceptionAddress == EngineHooks.GetBreakPointAddress( 4 ) )
									{
										if( Exception4 == 0 )
										{
											EngineHooks.GetBreakPointReturn( 4 ) = \
												DetourFunction(	(PBYTE)EngineHooks.GetBreakPointAddress( 4 ), EngineHooks.GetBreakPointFunction( 4 ) );

											ExceptionInfo->ContextRecord->Eip = (DWORD)EngineHooks.GetBreakPointFunction( 4 );
											DetourRemove( (PBYTE)EngineHooks.GetBreakPointReturn( 4 ), (PBYTE)EngineHooks.GetBreakPointFunction( 4 ) );
											Exception4 = 1;
										}
										else
										{
											ExceptionInfo->ContextRecord->Eip = (DWORD)EngineHooks.GetBreakPointFunction( 4 );
										}

										return EXCEPTION_CONTINUE_EXECUTION;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return EXCEPTION_CONTINUE_SEARCH;
}

void CEngineHooks::SetBreakPointAddress( int BreakPointNumber, DWORD Address, PBYTE Function )
{
	if( BreakPointNumber > 4 )
	{
		MessageBoxA( NULL, "Hardware Breakpoint Limit Reached.\nHardware Breakpoint will not be added.", "Error", NULL );
		return;
	}

	this->dwBreakPoints[ BreakPointNumber - 1 ]				= Address;
	this->pbBreakPointFunctions[ BreakPointNumber - 1 ]		= Function;
}
DWORD &CEngineHooks::GetBreakPointAddress( int BreakPointNumber )
{
	if( BreakPointNumber > 4 )
		return this->NULLDword;

	return this->dwBreakPoints[ BreakPointNumber - 1 ];
}
PBYTE &CEngineHooks::GetBreakPointReturn( int BreakPointNumber )
{
	if( BreakPointNumber > 4 )
		return this->NULLPByte;

	return this->pbBreakPointReturns[ BreakPointNumber - 1 ];
}
PBYTE &CEngineHooks::GetBreakPointFunction( int BreakPointNumber )
{
	if( BreakPointNumber > 4 )
		return this->NULLPByte;

	return this->pbBreakPointFunctions[ BreakPointNumber - 1 ];
}
#endif

//========================================================================================================

bool CEngineHooks::InitiateAntiCheatProtection( )
{
	while( !this->Game_ModuleBase )
	{
		this->Game_ModuleBase = (DWORD)GetModuleHandleA( this->Game_Module );
		Sleep( 250 );
	}
	while( !this->Game_ModuleSize )
	{
		this->Game_ModuleSize = (DWORD)D3DRenderer.Hooks.GetModuleSize( this->Game_Module );
		Sleep( 250 );
	}

#ifndef PublicMode
	if( strcmp( this->Game_Name, "Call of Duty: 4" ) == 0 )
	{
		EngineHooks.SetBreakPointAddress( 1, 0x005FAF00, (PBYTE)hkBreakPoint1 );		//RenderScene
	}
#endif

	D3DRenderer.InitiateDirect3D( );

	if( this->AntiCheat_Name == NULL )
		return false;

#ifndef PublicMode
	Log( "this->Game_Name: ----------------- %s", this->Game_Name );
	Log( "this->Game_Module: --------------- %s", this->Game_Module );
	Log( "this->Game_ModuleBase: ----------- 0x%.8X", this->Game_ModuleBase );
	Log( "this->Game_ModuleSize: ----------- 0x%.8X", this->Game_ModuleSize );
	Log( "this->AntiCheat_Name: ------------ %s", this->AntiCheat_Name );
#endif

	if( strcmp( this->AntiCheat_Name, "PunkBuster" ) == 0 )
	{
		this->AntiCheat_Module = "pbcl.dll";
#ifndef PublicMode
		Log( "this->AntiCheat_Module: ---------- %s", this->AntiCheat_Module );
#endif
		CreateThread( 0,0, CheckForAntiCheat, this->AntiCheat_Module, 0,0 );

		return true;
	}

	return false;
}

void CEngineHooks::SetGame_Name( const char *Name )
{
	this->Game_Name = const_cast<char *>( Name );
}
void CEngineHooks::SetGame_Module( const char *Module )
{
	this->Game_Module = const_cast<char *>( Module );
}
void CEngineHooks::SetHack_Version( const char *Version )
{
	this->Hack_Version = const_cast<char *>( Version );
}

char *&CEngineHooks::GetGame_Name( )
{
	return this->Game_Name;
}
char *&CEngineHooks::GetGame_Module( )
{
	return this->Game_Module;
}
char *&CEngineHooks::GetHack_Version( )
{
	return this->Hack_Version;
}
DWORD &CEngineHooks::GetGame_ModuleBase( )
{
	return this->Game_ModuleBase;
}
DWORD &CEngineHooks::GetGame_ModuleSize( )
{
	return this->Game_ModuleSize;
}

bool CEngineHooks::CheckGame_Name( const char *Name )
{
	if( strcmp( this->Game_Name, Name ) == 0 )
		return true;
	
	return false;
}

void CEngineHooks::SetAntiCheat_Name( const char *Name )
{
	this->AntiCheat_Name = const_cast<char *>( Name );
}
bool CEngineHooks::CheckAntiCheat_Name( const char *Name )
{
	if( strcmp( this->AntiCheat_Name, Name ) == 0 )
		return true;
	
	return false;
}
char *&CEngineHooks::GetAntiCheat_Name( )
{
	return this->AntiCheat_Name;
}
char *&CEngineHooks::GetAntiCheat_Module( )
{
	return this->AntiCheat_Module;
}
DWORD &CEngineHooks::GetAntiCheat_ModuleBase( )
{
	return this->AntiCheat_ModuleBase;
}
DWORD &CEngineHooks::GetAntiCheat_ModuleSize( )
{
	return this->AntiCheat_ModuleSize;
}