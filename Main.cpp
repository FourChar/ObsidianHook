#include "stdafx.h"

//////////////////////////////////

char				DllDirectory[320];
ofstream			LogFile;

bool				MayLog		= true;

HINSTANCE			hMod;

//----------------------

CHook				*		Hook				= NULL;
CDirect3DRenderer			D3DRenderer;
CEngineHooks				EngineHooks;
CMenuManager				MenuManager;
CSettings					Settings;

CGame						Game;

//////////////////////////////////

#pragma code_seg(".DllMain")
void CHook::StartInit( HINSTANCE hinstModule )
{
#ifndef PublicMode
	if( MayLog == true )
	{
		char	LogFile_Name[]		= "D3DFramework.log";

		remove( GetDirectoryFile( LogFile_Name ).c_str( ) );
		LogFile.open( GetDirectoryFile( LogFile_Name ).c_str( ), ios::app );

		ZeroMemory( LogFile_Name, sizeof( LogFile_Name ) );
	}
#endif

	hMod = hinstModule;
	HideModule						( hinstModule );
}

////////////////////////////////////////////////////////////////////

#pragma code_seg(".DllMain")
void CHook::StartThread( )
{
	EngineHooks.SetGame_Name			( "Call of Duty: 4" );
	EngineHooks.SetGame_Module			( "iw3mp.exe" );
	EngineHooks.SetHack_Version			( "1.32" );
	MenuManager.InitiateMenu			( "Call of Duty 4" );
	EngineHooks.SetAntiCheat_Name		( "PunkBuster" );

	if( !EngineHooks.InitiateAntiCheatProtection( ) )
	{
		MessageBoxA( NULL, "Failed to Protect Against Anti-Cheat", "FAIL", NULL );
		ExitProcess( -1 );
	}

#ifndef PublicMode
	EngineHooks.HookBreakPoints			( );
#endif
}

////////////////////////////////////////////////////////////////////

#pragma code_seg(".DllMain")
BOOL WINAPI DllMain( HMODULE hinstModule, DWORD dwReason, LPVOID lpvReserved )  
{
	switch( dwReason )
	{
		case DLL_PROCESS_ATTACH:
			{
				if( DisableThreadLibraryCalls(hinstModule) )
				{
					GetModuleFileNameA( hinstModule, DllDirectory, 512 );
					for( size_t i = strlen( DllDirectory ); i > 0; i-- )
					{
						if( DllDirectory[i] == '\\' )
						{
							DllDirectory[i+1] = 0;
							break;
						}
					}

					Settings.SetSettingsFileLocation	( ( std::string( DllDirectory ) + std::string( "ObsidianHook_Settings.cfg" ) ).c_str( ) );
					Settings.InitiateSettings			( );
					Settings.LoadSettingsFromFile		( );
					Settings.SaveSettingsToFile			( );

					Hook->StartInit		( hinstModule );
					Hook->StartThread	( );

					return TRUE;
				}
			}
	}

	return FALSE;
}

////////////////////////////////////////////////////////////////////

#pragma code_seg(".DllMain")
int HideModule( HMODULE hMod )
{
	ProcessModuleInfo *pmInfo;
	ModuleInfoNode *module;

	_asm
	{
		mov eax, fs:[18h]      // TEB
		mov eax, [eax + 30h]   // PEB
		mov eax, [eax + 0Ch]   // PROCESS_MODULE_INFO
		mov pmInfo, eax
	}

	module = (ModuleInfoNode *)(pmInfo->LoadOrder.Flink);
   
	while(module->baseAddress && module->baseAddress != hMod)
	{
		module = (ModuleInfoNode *)(module->LoadOrder.Flink);
	}

	if( !module->baseAddress )
		return 0;

	UNLINK(module->LoadOrder);
	UNLINK(module->InitOrder);
	UNLINK(module->MemoryOrder);
	UNLINK(module->HashTable);
	memset(module->fullPath.Buffer, 0, module->fullPath.Length);
	memset(module, 0, sizeof(ModuleInfoNode));

	return 1;
}

////////////////////////////////////////////////////////////////////

#pragma code_seg(".DllMain")
std::string GetDirectoryFile( std::string FileName )
{
	static char FilePath[320];
	strcpy( FilePath, DllDirectory );
	strcat( FilePath, FileName.c_str( ) );
	return std::string( FilePath );
}

////////////////////////////////////////////////////////////////////

#pragma code_seg(".DllMain")
void __fastcall Log( const std::string String, ... )
{
	if(MayLog == false)
		return;

	if(LogFile!=NULL)
	{
		va_list va_alist;
		char LogBuffer[256] = {0};

		va_start (va_alist, String);
		_vsnprintf (LogBuffer+strlen(LogBuffer), sizeof(LogBuffer) - strlen(LogBuffer), String.c_str( ), va_alist);
		va_end (va_alist);

		if( !LogBuffer )
			return;

		if( String == "" )
			LogFile /*<< ReturnTime("[%H:%M:%S]") << "  " */<< LogBuffer;
		else
			LogFile /*<< ReturnTime("[%H:%M:%S]") << "  " */<< LogBuffer << endl;
	}
}

////////////////////////////////////////////////////////////////////

#pragma code_seg(".DllMain")
std::string ReturnTime( const std::string Format )
{
	static char		TimeAndDate[MAX_PATH];
	time_t			TimeValue;

	TimeValue = time(NULL);
	strftime(TimeAndDate, MAX_PATH, Format.c_str( ), localtime(&TimeValue));

	return std::string( TimeAndDate );
}