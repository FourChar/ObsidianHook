#include "stdafx.h"

// CheckDebugFunctionsChecker( bool Crash )
//
// Simply does the exact same as the CheckDebugFunctions function exept it 
// checks the CheckDebugFunctions function ( 5 times for confusion ),
// instead of the DebugThread's.
//
// Function is stored in ".DllMain" section.
//
//
#pragma code_seg(".DllMain")
void __fastcall CheckDebugFunctionsChecker( bool Crash )
{
	static BYTE CheckFunctions1_Original[ 0x90 ];
	static BYTE CheckFunctions2_Original[ 0x90 ];
	static BYTE CheckFunctions3_Original[ 0x90 ];
	static BYTE CheckFunctions4_Original[ 0x90 ];
	static BYTE CheckFunctions5_Original[ 0x90 ];

	BYTE CheckFunctions1_Current[ 0x90 ];
	BYTE CheckFunctions2_Current[ 0x90 ];
	BYTE CheckFunctions3_Current[ 0x90 ];
	BYTE CheckFunctions4_Current[ 0x90 ];
	BYTE CheckFunctions5_Current[ 0x90 ];

	static bool CopyOnce = false;
	if( CopyOnce == false )
	{
		memcpy( CheckFunctions1_Original, &CheckDebugFunctions, sizeof( CheckFunctions1_Original ) );
		memcpy( CheckFunctions2_Original, &CheckDebugFunctions, sizeof( CheckFunctions2_Original ) );
		memcpy( CheckFunctions3_Original, &CheckDebugFunctions, sizeof( CheckFunctions3_Original ) );
		memcpy( CheckFunctions4_Original, &CheckDebugFunctions, sizeof( CheckFunctions4_Original ) );
		memcpy( CheckFunctions5_Original, &CheckDebugFunctions, sizeof( CheckFunctions5_Original ) );

		CopyOnce = true;
	}

	memcpy( CheckFunctions1_Current, &CheckDebugFunctions, sizeof( CheckFunctions1_Current ) );
	memcpy( CheckFunctions2_Current, &CheckDebugFunctions, sizeof( CheckFunctions2_Current ) );
	memcpy( CheckFunctions3_Current, &CheckDebugFunctions, sizeof( CheckFunctions3_Current ) );
	memcpy( CheckFunctions4_Current, &CheckDebugFunctions, sizeof( CheckFunctions4_Current ) );
	memcpy( CheckFunctions5_Current, &CheckDebugFunctions, sizeof( CheckFunctions5_Current ) );

	AddRandomNops( Nop_5 );
	DWORD dwOld, dwOld2;
	for( int i = 1; i < 5; i++ )
	{
		AddRandomNops( Nop_5 );
		switch( i )
		{
		case 1:
			{
				AddRandomNops( Nop_5 );
				if( _memicmp( CheckFunctions1_Original, CheckFunctions1_Current, sizeof( CheckFunctions1_Original ) ) != 0 )
				{
					AddRandomNops( Nop_5 );
					if( Crash )
					{
						AddRandomNops( Nop_5 );
						TerminateProcess( GetCurrentProcess(), 0 );
						AddRandomNops( Nop_5 );
					}
					else
					{
						AddRandomNops( Nop_5 );
						VirtualProtectEx( INVALID_HANDLE_VALUE, &CheckDebugFunctions, sizeof( CheckFunctions1_Original ), PAGE_EXECUTE_READWRITE, &dwOld );
						AddRandomNops( Nop_5 );
						memcpy( &CheckDebugFunctions, CheckFunctions1_Original, sizeof( CheckFunctions1_Original ) );
						AddRandomNops( Nop_5 );
						VirtualProtectEx( INVALID_HANDLE_VALUE, &CheckDebugFunctions, sizeof( CheckFunctions1_Original ), dwOld, &dwOld2 );
						AddRandomNops( Nop_5 );
					}
					AddRandomNops( Nop_5 );
				}
				AddRandomNops( Nop_5 );
			}
			break;

		case 2:
			{
				AddRandomNops( Nop_5 );
				if( _memicmp( CheckFunctions2_Original, CheckFunctions2_Current, sizeof( CheckFunctions2_Original ) ) != 0 )
				{
					AddRandomNops( Nop_5 );
					if( Crash )
					{
						AddRandomNops( Nop_5 );
						TerminateProcess( GetCurrentProcess(), 0 );
						AddRandomNops( Nop_5 );
					}
					else
					{
						AddRandomNops( Nop_5 );
						VirtualProtectEx( INVALID_HANDLE_VALUE, &CheckDebugFunctions, sizeof( CheckFunctions2_Original ), PAGE_EXECUTE_READWRITE, &dwOld );
						AddRandomNops( Nop_5 );
						memcpy( &CheckDebugFunctions, CheckFunctions2_Original, sizeof( CheckFunctions2_Original ) );
						AddRandomNops( Nop_5 );
						VirtualProtectEx( INVALID_HANDLE_VALUE, &CheckDebugFunctions, sizeof( CheckFunctions2_Original ), dwOld, &dwOld2 );
						AddRandomNops( Nop_5 );
					}
					AddRandomNops( Nop_5 );
				}
				AddRandomNops( Nop_5 );
			}
			break;

		case 3:
			{
				AddRandomNops( Nop_5 );
				if( _memicmp( CheckFunctions3_Original, CheckFunctions3_Current, sizeof( CheckFunctions3_Original ) ) != 0 )
				{
					AddRandomNops( Nop_5 );
					if( Crash )
					{
						AddRandomNops( Nop_5 );
						TerminateProcess( GetCurrentProcess(), 0 );
						AddRandomNops( Nop_5 );
					}
					else
					{
						AddRandomNops( Nop_5 );
						VirtualProtectEx( INVALID_HANDLE_VALUE, &CheckDebugFunctions, sizeof( CheckFunctions3_Original ), PAGE_EXECUTE_READWRITE, &dwOld );
						AddRandomNops( Nop_5 );
						memcpy( &CheckDebugFunctions, CheckFunctions3_Original, sizeof( CheckFunctions3_Original ) );
						AddRandomNops( Nop_5 );
						VirtualProtectEx( INVALID_HANDLE_VALUE, &CheckDebugFunctions, sizeof( CheckFunctions3_Original ), dwOld, &dwOld2 );
						AddRandomNops( Nop_5 );
					}
					AddRandomNops( Nop_5 );
				}
				AddRandomNops( Nop_5 );
			}
			break;

		case 4:
			{
				AddRandomNops( Nop_5 );
				if( _memicmp( CheckFunctions4_Original, CheckFunctions4_Current, sizeof( CheckFunctions4_Original ) ) != 0 )
				{
					AddRandomNops( Nop_5 );
					if( Crash )
					{
						AddRandomNops( Nop_5 );
						TerminateProcess( GetCurrentProcess(), 0 );
						AddRandomNops( Nop_5 );
					}
					else
					{
						AddRandomNops( Nop_5 );
						VirtualProtectEx( INVALID_HANDLE_VALUE, &CheckDebugFunctions, sizeof( CheckFunctions4_Original ), PAGE_EXECUTE_READWRITE, &dwOld );
						AddRandomNops( Nop_5 );
						memcpy( &CheckDebugFunctions, CheckFunctions4_Original, sizeof( CheckFunctions4_Original ) );
						AddRandomNops( Nop_5 );
						VirtualProtectEx( INVALID_HANDLE_VALUE, &CheckDebugFunctions, sizeof( CheckFunctions4_Original ), dwOld, &dwOld2 );
						AddRandomNops( Nop_5 );
					}
					AddRandomNops( Nop_5 );
				}
				AddRandomNops( Nop_5 );
			}
			break;

		case 5:
			{
				AddRandomNops( Nop_5 );
				if( _memicmp( CheckFunctions5_Original, CheckFunctions5_Current, sizeof( CheckFunctions5_Original ) ) != 0 )
				{
					AddRandomNops( Nop_5 );
					if( Crash )
					{
						AddRandomNops( Nop_5 );
						TerminateProcess( GetCurrentProcess(), 0 );
						AddRandomNops( Nop_5 );
					}
					else
					{
						AddRandomNops( Nop_5 );
						VirtualProtectEx( INVALID_HANDLE_VALUE, &CheckDebugFunctions, sizeof( CheckFunctions5_Original ), PAGE_EXECUTE_READWRITE, &dwOld );
						AddRandomNops( Nop_5 );
						memcpy( &CheckDebugFunctions, CheckFunctions5_Original, sizeof( CheckFunctions5_Original ) );
						AddRandomNops( Nop_5 );
						VirtualProtectEx( INVALID_HANDLE_VALUE, &CheckDebugFunctions, sizeof( CheckFunctions5_Original ), dwOld, &dwOld2 );
						AddRandomNops( Nop_5 );
					}
					AddRandomNops( Nop_5 );
				}
				AddRandomNops( Nop_5 );
			}
			break;

		default:
			{
				AddRandomNops( Nop_5 );
				FatalExit( 0 );
				AddRandomNops( Nop_5 );
			}
			break;
		}
		AddRandomNops( Nop_5 );
	}
	AddRandomNops( Nop_5 );
}

// CheckDebugFunctions( bool Crash )
//
// Gets all the DebugThread's Original Code on Startup and stores it in static values.
// Then checks those values against the current Code on Execution and if it differs,
// it checks the 'Crash' bool. If it's true, it runs the TerminateProcess function to 
// exit the process, and if it's false, it will simply restore the function to the original state.
//
// Function is stored in ".acdata" section.
//
//
#pragma code_seg(".acdata")
void __fastcall CheckDebugFunctions( bool Crash )
{
	static BYTE DebugThread1_Original[ 0x90 ];
	static BYTE DebugThread2_Original[ 0x90 ];
	static BYTE DebugThread3_Original[ 0x90 ];
	static BYTE DebugThread4_Original[ 0x90 ];
	static BYTE DebugThread5_Original[ 0x90 ];

	BYTE DebugThread1_Current[ 0x90 ];
	BYTE DebugThread2_Current[ 0x90 ];
	BYTE DebugThread3_Current[ 0x90 ];
	BYTE DebugThread4_Current[ 0x90 ];
	BYTE DebugThread5_Current[ 0x90 ];

	static bool CopyOnce = false;
	if( CopyOnce == false )
	{
		memcpy( DebugThread1_Original, &DebugThread1, sizeof( DebugThread1_Original ) );
		memcpy( DebugThread2_Original, &DebugThread2, sizeof( DebugThread2_Original ) );
		memcpy( DebugThread3_Original, &DebugThread3, sizeof( DebugThread3_Original ) );
		memcpy( DebugThread4_Original, &DebugThread4, sizeof( DebugThread4_Original ) );
		memcpy( DebugThread5_Original, &DebugThread5, sizeof( DebugThread5_Original ) );

		CopyOnce = true;
	}

	memcpy( DebugThread1_Current, &DebugThread1, sizeof( DebugThread1_Current ) );
	memcpy( DebugThread2_Current, &DebugThread2, sizeof( DebugThread2_Current ) );
	memcpy( DebugThread3_Current, &DebugThread3, sizeof( DebugThread3_Current ) );
	memcpy( DebugThread4_Current, &DebugThread4, sizeof( DebugThread4_Current ) );
	memcpy( DebugThread5_Current, &DebugThread5, sizeof( DebugThread5_Current ) );

	AddRandomNops( Nop_5 );
	DWORD dwOld, dwOld2;
	for( int i = 1; i < 5; i++ )
	{
		AddRandomNops( Nop_5 );
		switch( i )
		{
		case 1:
			{
				AddRandomNops( Nop_5 );
				if( _memicmp( DebugThread1_Original, DebugThread1_Current, sizeof( DebugThread1_Original ) ) != 0 )
				{
					AddRandomNops( Nop_5 );
					if( Crash )
					{
						AddRandomNops( Nop_5 );
						TerminateProcess( GetCurrentProcess(), 0 );
						AddRandomNops( Nop_5 );
					}
					else
					{
						AddRandomNops( Nop_5 );
						VirtualProtectEx( INVALID_HANDLE_VALUE, &DebugThread1, sizeof( DebugThread1_Original ), PAGE_EXECUTE_READWRITE, &dwOld );
						AddRandomNops( Nop_5 );
						memcpy( &DebugThread1, DebugThread1_Original, sizeof( DebugThread1_Original ) );
						AddRandomNops( Nop_5 );
						VirtualProtectEx( INVALID_HANDLE_VALUE, &DebugThread1, sizeof( DebugThread1_Original ), dwOld, &dwOld2 );
						AddRandomNops( Nop_5 );
					}
					AddRandomNops( Nop_5 );
				}
				AddRandomNops( Nop_5 );
			}
			break;

		case 2:
			{
				AddRandomNops( Nop_5 );
				if( _memicmp( DebugThread2_Original, DebugThread2_Current, sizeof( DebugThread2_Original ) ) != 0 )
				{
					AddRandomNops( Nop_5 );
					if( Crash )
					{
						AddRandomNops( Nop_5 );
						TerminateProcess( GetCurrentProcess(), 0 );
						AddRandomNops( Nop_5 );
					}
					else
					{
						AddRandomNops( Nop_5 );
						VirtualProtectEx( INVALID_HANDLE_VALUE, &DebugThread2, sizeof( DebugThread2_Original ), PAGE_EXECUTE_READWRITE, &dwOld );
						AddRandomNops( Nop_5 );
						memcpy( &DebugThread2, DebugThread2_Original, sizeof( DebugThread2_Original ) );
						AddRandomNops( Nop_5 );
						VirtualProtectEx( INVALID_HANDLE_VALUE, &DebugThread2, sizeof( DebugThread2_Original ), dwOld, &dwOld2 );
						AddRandomNops( Nop_5 );
					}
					AddRandomNops( Nop_5 );
				}
				AddRandomNops( Nop_5 );
			}
			break;

		case 3:
			{
				AddRandomNops( Nop_5 );
				if( _memicmp( DebugThread3_Original, DebugThread3_Current, sizeof( DebugThread3_Original ) ) != 0 )
				{
					AddRandomNops( Nop_5 );
					if( Crash )
					{
						AddRandomNops( Nop_5 );
						TerminateProcess( GetCurrentProcess(), 0 );
						AddRandomNops( Nop_5 );
					}
					else
					{
						AddRandomNops( Nop_5 );
						VirtualProtectEx( INVALID_HANDLE_VALUE, &DebugThread3, sizeof( DebugThread3_Original ), PAGE_EXECUTE_READWRITE, &dwOld );
						AddRandomNops( Nop_5 );
						memcpy( &DebugThread3, DebugThread3_Original, sizeof( DebugThread3_Original ) );
						AddRandomNops( Nop_5 );
						VirtualProtectEx( INVALID_HANDLE_VALUE, &DebugThread2, sizeof( DebugThread3_Original ), dwOld, &dwOld2 );
						AddRandomNops( Nop_5 );
					}
					AddRandomNops( Nop_5 );
				}
				AddRandomNops( Nop_5 );
			}
			break;

		case 4:
			{
				AddRandomNops( Nop_5 );
				if( _memicmp( DebugThread4_Original, DebugThread4_Current, sizeof( DebugThread4_Original ) ) != 0 )
				{
					AddRandomNops( Nop_5 );
					if( Crash )
					{
						AddRandomNops( Nop_5 );
						TerminateProcess( GetCurrentProcess(), 0 );
						AddRandomNops( Nop_5 );
					}
					else
					{
						AddRandomNops( Nop_5 );
						VirtualProtectEx( INVALID_HANDLE_VALUE, &DebugThread4, sizeof( DebugThread4_Original ), PAGE_EXECUTE_READWRITE, &dwOld );
						AddRandomNops( Nop_5 );
						memcpy( &DebugThread4, DebugThread4_Original, sizeof( DebugThread4_Original ) );
						AddRandomNops( Nop_5 );
						VirtualProtectEx( INVALID_HANDLE_VALUE, &DebugThread4, sizeof( DebugThread4_Original ), dwOld, &dwOld2 );
						AddRandomNops( Nop_5 );
					}
					AddRandomNops( Nop_5 );
				}
				AddRandomNops( Nop_5 );
			}
			break;

		case 5:
			{
				AddRandomNops( Nop_5 );
				if( _memicmp( DebugThread5_Original, DebugThread5_Current, sizeof( DebugThread5_Original ) ) != 0 )
				{
					AddRandomNops( Nop_5 );
					if( Crash )
					{
						AddRandomNops( Nop_5 );
						TerminateProcess( GetCurrentProcess(), 0 );
						AddRandomNops( Nop_5 );
					}
					else
					{
						AddRandomNops( Nop_5 );
						VirtualProtectEx( INVALID_HANDLE_VALUE, &DebugThread5, sizeof( DebugThread5_Original ), PAGE_EXECUTE_READWRITE, &dwOld );
						AddRandomNops( Nop_5 );
						memcpy( &DebugThread2, DebugThread5_Original, sizeof( DebugThread5_Original ) );
						AddRandomNops( Nop_5 );
						VirtualProtectEx( INVALID_HANDLE_VALUE, &DebugThread5, sizeof( DebugThread5_Original ), dwOld, &dwOld2 );
						AddRandomNops( Nop_5 );
					}
					AddRandomNops( Nop_5 );
				}
				AddRandomNops( Nop_5 );
			}
			break;

		default:
			{
				AddRandomNops( Nop_5 );
				FatalExit( 0 );
				AddRandomNops( Nop_5 );
			}
			break;
		}
		AddRandomNops( Nop_5 );
	}
	AddRandomNops( Nop_5 );
}

#pragma code_seg(".cddata")
char *CAntiDebug::Encrypt( const char *String )
{
	int		StringLength			= strlen( String );
	char	*EncryptedString		= new char[ StringLength + 1 ];

	for( int i = 0; i < StringLength; i++ )
	{
		AddRandomNops( Nop_20 );
		EncryptedString[i] = ( String[i] + 1 ) ^ 9 ^ 8;
		AddRandomNops( Nop_5 );
		EncryptedString[i] = ( EncryptedString[i] ^ 7 ^ 4 ^ 6 ^ 5 ^ 2 ^ 3 ^ 1 );
		AddRandomNops( Nop_5 );
		EncryptedString[i] = ( EncryptedString[i] - 2 );
		AddRandomNops( Nop_10 );
		EncryptedString[i] = ( EncryptedString[i] ^ 3 ^ 8 ^ 5 ^ 6 ^ 6 ^ 4 ^ 3 );
		AddRandomNops( Nop_20 );
	}

	AddRandomNops( Nop_20 );
	EncryptedString[StringLength]	= NULL;

	return EncryptedString;
}

#pragma code_seg(".cddata")
char *CAntiDebug::Decrypt( const char *String )
{
	int		StringLength			= strlen( String );
	char	*EncryptedString		= new char[ StringLength + 1 ];

	for( int i = 0; i < StringLength; i++ )
	{
		AddRandomNops( Nop_20 );
		EncryptedString[i] = ( String[i] ^ 3 ^ 4 ^ 6 ^ 6 ^ 5 ^ 8 ^ 3 );
		AddRandomNops( Nop_20 );
		EncryptedString[i] = ( EncryptedString[i] + 2 );
		AddRandomNops( Nop_5 );
		EncryptedString[i] = ( EncryptedString[i] ^ 1 ^ 3 ^ 2 ^ 5 ^ 6 ^ 4 ^ 7 );
		AddRandomNops( Nop_10 );
		EncryptedString[i] = ( EncryptedString[i] ^ 8 ^ 9 ) - 1;
		AddRandomNops( Nop_20 );
	}

	AddRandomNops( Nop_20 );
	EncryptedString[StringLength]	= NULL;

	return EncryptedString;
}

int CAntiDebug::GenerateRandomNumber( int Minimum, int Mamimum )
{
	UINT iReturn		= NULL;

	__asm PUSH EDX
	__asm RDTSC
	__asm POP EDX
	__asm MOV iReturn, EAX

	iReturn				%= ( Mamimum - Minimum );

	return iReturn + Minimum;
}

#pragma code_seg(".acdata")
void *CAntiDebug::GetRandomThread( )
{
	AddRandomNops( Nop_5 );
	int RandomThread = AntiDebug.GenerateRandomNumber( 1, 5 );

	AddRandomNops( Nop_5 );
	switch( RandomThread )
	{
	case 1:
		{
			AddRandomNops( Nop_5 );
			return &DebugThread1;
		}
	case 2:
		{
			AddRandomNops( Nop_5 );
			return &DebugThread2;
		}
	case 3:
		{
			AddRandomNops( Nop_5 );
			return &DebugThread3;
		}
	case 4:
		{
			AddRandomNops( Nop_5 );
			return &DebugThread4;
		}
	case 5:
		{
			AddRandomNops( Nop_5 );
			return &DebugThread5;
		}

	default:
		break;
	}

	AddRandomNops( Nop_5 );
	return &DebugThread2;
}

#pragma code_seg(".acdata")
void *CAntiDebug::GetRandomThread2( )
{
	AddRandomNops( Nop_5 );
	int RandomThread = AntiDebug.GenerateRandomNumber( 1, 5 );

	AddRandomNops( Nop_5 );
	if( RandomThread == 1 )
	{
		AddRandomNops( Nop_5 );
		return &DebugThread1;
	}

	AddRandomNops( Nop_5 );
	if( RandomThread == 2 )
	{
		AddRandomNops( Nop_5 );
		return &DebugThread2;
	}

	AddRandomNops( Nop_5 );
	if( RandomThread == 3 )
	{
		AddRandomNops( Nop_5 );
		return &DebugThread3;
	}

	AddRandomNops( Nop_5 );
	if( RandomThread == 4 )
	{
		AddRandomNops( Nop_5 );
		return &DebugThread4;
	}

	AddRandomNops( Nop_5 );
	if( RandomThread == 5 )
	{
		AddRandomNops( Nop_5 );
		return &DebugThread5;
	}

	AddRandomNops( Nop_5 );
	return &DebugThread2;
}

#pragma code_seg(".audata")
void *CAntiDebug::GetRandomThread3( )
{
	AddRandomNops( Nop_5 );
	int RandomThread = AntiDebug.GenerateRandomNumber( 1, 7 );

	AddRandomNops( Nop_5 );
	if( RandomThread == 4 )
	{
		AddRandomNops( Nop_5 );
		return &DebugThread4;
	}

	AddRandomNops( Nop_5 );
	if( RandomThread == 2 )
	{
		AddRandomNops( Nop_5 );
		return &DebugThread2;
	}

	AddRandomNops( Nop_5 );
	switch( RandomThread )
	{
	case 1:
		{
			AddRandomNops( Nop_5 );
			return &DebugThread1;
		}
	case 3:
		{
			AddRandomNops( Nop_5 );
			return &DebugThread3;
		}
	case 5:
		{
			AddRandomNops( Nop_5 );
			return &DebugThread5;
		}

	default:
		{
			AddRandomNops( Nop_5 );
			return &DebugThread2;
		}
	}

	AddRandomNops( Nop_5 );
	return NULL;
}

// Function pointer declaration. VERY IMPORTANT!
typedef NTSTATUS (NTAPI *ntip)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG);
typedef NTSTATUS (NTAPI *ntsit)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG );

DWORD BeingDebugged		= NULL;

#pragma code_seg(".addata")
DWORD WINAPI DebugThread1( LPVOID )
{
	AddRandomNops( Nop_5 );
	if( IsDebuggerPresent() )
	{
		AddRandomNops( Nop_5 );
		TerminateProcess( GetCurrentProcess(), 0 );
		BeingDebugged = 1;
	}
	AddRandomNops( Nop_5 );

	DWORD dwValue		= NULL;

/*---------------PEB!NtGlobalFlags------------------*/
	__asm
	{
		mov eax, fs:[30h]
		mov eax, [eax+68h]
		and eax, 0x70
		mov dwValue, eax
	}
	if( dwValue )
	{
		AddRandomNops( Nop_5 );
		ExitProcess( -1 );
	}
/*----------------------------------------------*/

	AddRandomNops( Nop_5 );
	DebugActiveProcessStop( GetCurrentProcessId() );

/*----------------Heap flags--------------------*/
	__asm
	{
		mov eax, fs:[30h]
		mov eax, [eax+18h]		//process heap
		mov eax, [eax+10h]		//heap flags
		mov dwValue, eax
	}
	if( !dwValue )
	{
		AddRandomNops( Nop_5 );
		FatalExit( -1 );
	}
/*----------------------------------------------*/


/*----------NtQueryInformationProcess-----------*/
	ntip NTQIP = (ntip)GetProcAddress(LoadLibrary(TEXT("ntdll.dll")), "NtQueryInformationProcess");
	int isdebugged;
	__asm
	{
		push 0
		push 4
		push isdebugged
		push 7 ;ProcessDebugPort
		push -1
		call NTQIP
	}
	if( isdebugged == -1 )
	{
		AddRandomNops( Nop_5 );
		TerminateProcess( GetCurrentProcess(), 0 );
	}
/*----------------------------------------------*/


/*----------NtQueryInformationProcess-----------*/
	ntsit NTSIT = (ntsit)GetProcAddress(LoadLibrary(TEXT("ntdll.dll")), "NtSetInformationThread");
	__asm
	{
		push 0
		push 0
		push 11h
		push -2
		call NTSIT
	}
/*----------------------------------------------*/

	AddRandomNops( Nop_5 );
	DebugActiveProcessStop( GetCurrentProcessId() );

/*-------------------NtClose--------------------*/
	AddRandomNops( Nop_5 );
	CloseHandle( (HANDLE)0x1234 );
/*----------------------------------------------*/

	ExitThread( -1 );
}

#pragma code_seg(".addata")
DWORD WINAPI DebugThread2( LPVOID )
{
	AddRandomNops( Nop_5 );
	if( IsDebuggerPresent() )
	{
		AddRandomNops( Nop_5 );
		TerminateProcess( GetCurrentProcess(), 0 );
		BeingDebugged = 1;
	}

	DWORD dwValue		= NULL;

/*---------------PEB!NtGlobalFlags------------------*/
	__asm
	{
		mov eax, fs:[30h]
		mov eax, [eax+68h]
		and eax, 0x70
		mov dwValue, eax
	}
	if( dwValue )
	{
		ExitProcess( -1 );
	}
/*----------------------------------------------*/

	AddRandomNops( Nop_5 );
	DebugActiveProcessStop( GetCurrentProcessId() );

/*----------------Heap flags--------------------*/
	__asm
	{
		mov eax, fs:[30h]
		mov eax, [eax+18h]		//process heap
		mov eax, [eax+10h]		//heap flags
		mov dwValue, eax
	}
	if( !dwValue )
	{
		AddRandomNops( Nop_5 );
		FatalExit( -1 );
	}
/*----------------------------------------------*/

	AddRandomNops( Nop_5 );
	DebugActiveProcessStop( GetCurrentProcessId() );

/*----------NtQueryInformationProcess-----------*/
	ntip NTQIP = (ntip)GetProcAddress(LoadLibrary(TEXT("ntdll.dll")), "NtQueryInformationProcess");
	int isdebugged;
	__asm
	{
		push 0
		push 4
		push isdebugged
		push 7 ;ProcessDebugPort
		push -1
		call NTQIP
	}
	if( isdebugged == -1 )
	{
		AddRandomNops( Nop_5 );
		TerminateProcess( GetCurrentProcess(), 0 );
	}
/*----------------------------------------------*/


/*----------NtQueryInformationProcess-----------*/
	ntsit NTSIT = (ntsit)GetProcAddress(LoadLibrary(TEXT("ntdll.dll")), "NtSetInformationThread");
	__asm
	{
		push 0
		push 0
		push 11h
		push -2
		call NTSIT
	}
/*----------------------------------------------*/


/*-------------------NtClose--------------------*/
	AddRandomNops( Nop_5 );
	CloseHandle( (HANDLE)0x1234 );
/*----------------------------------------------*/

	AddRandomNops( Nop_5 );
	ExitThread( -1 );
}

#pragma code_seg(".ecdata")
DWORD WINAPI DebugThread3( LPVOID )
{
	AddRandomNops( Nop_5 );
	if( IsDebuggerPresent() )
	{
		AddRandomNops( Nop_5 );
		TerminateProcess( GetCurrentProcess(), 0 );
		BeingDebugged = 1;
	}

	DWORD dwValue		= NULL;

/*---------------PEB!NtGlobalFlags------------------*/
	__asm
	{
		mov eax, fs:[30h]
		mov eax, [eax+68h]
		and eax, 0x70
		mov dwValue, eax
	}
	if( dwValue )
	{
		AddRandomNops( Nop_5 );
		ExitProcess( -1 );
	}
/*----------------------------------------------*/

	AddRandomNops( Nop_5 );
	DebugActiveProcessStop( GetCurrentProcessId() );

/*----------------Heap flags--------------------*/
	__asm
	{
		mov eax, fs:[30h]
		mov eax, [eax+18h]		//process heap
		mov eax, [eax+10h]		//heap flags
		mov dwValue, eax
	}
	if( !dwValue )
	{
		AddRandomNops( Nop_5 );
		FatalExit( -1 );
	}
/*----------------------------------------------*/


/*----------NtQueryInformationProcess-----------*/
	ntip NTQIP = (ntip)GetProcAddress(LoadLibrary(TEXT("ntdll.dll")), "NtQueryInformationProcess");
	int isdebugged;
	__asm
	{
		push 0
		push 4
		push isdebugged
		push 7 ;ProcessDebugPort
		push -1
		call NTQIP
	}
	if( isdebugged == -1 )
	{
		AddRandomNops( Nop_5 );
		TerminateProcess( GetCurrentProcess(), 0 );
	}
/*----------------------------------------------*/

	AddRandomNops( Nop_5 );
	DebugActiveProcessStop( GetCurrentProcessId() );

/*----------NtQueryInformationProcess-----------*/
	ntsit NTSIT = (ntsit)GetProcAddress(LoadLibrary(TEXT("ntdll.dll")), "NtSetInformationThread");
	__asm
	{
		push 0
		push 0
		push 11h
		push -2
		call NTSIT
	}
/*----------------------------------------------*/


/*-------------------NtClose--------------------*/
	AddRandomNops( Nop_5 );
	CloseHandle( (HANDLE)0x1234 );
/*----------------------------------------------*/

	AddRandomNops( Nop_5 );
	ExitThread( -1 );
}

#pragma code_seg(".etdata")
DWORD WINAPI DebugThread4( LPVOID )
{
	AddRandomNops( Nop_5 );
	if( IsDebuggerPresent() )
	{
		AddRandomNops( Nop_5 );
		TerminateProcess( GetCurrentProcess(), 0 );
		BeingDebugged = 1;
	}

	DWORD dwValue		= NULL;

/*---------------PEB!NtGlobalFlags------------------*/
	__asm
	{
		mov eax, fs:[30h]
		mov eax, [eax+68h]
		and eax, 0x70
		mov dwValue, eax
	}
	if( dwValue )
	{
		AddRandomNops( Nop_5 );
		ExitProcess( -1 );
	}
/*----------------------------------------------*/


/*----------------Heap flags--------------------*/
	__asm
	{
		mov eax, fs:[30h]
		mov eax, [eax+18h]		//process heap
		mov eax, [eax+10h]		//heap flags
		mov dwValue, eax
	}
	if( !dwValue )
	{
		AddRandomNops( Nop_5 );
		FatalExit( -1 );
	}
/*----------------------------------------------*/

	AddRandomNops( Nop_5 );
	DebugActiveProcessStop( GetCurrentProcessId() );

/*----------NtQueryInformationProcess-----------*/
	ntip NTQIP = (ntip)GetProcAddress(LoadLibrary(TEXT("ntdll.dll")), "NtQueryInformationProcess");
	int isdebugged;
	__asm
	{
		push 0
		push 4
		push isdebugged
		push 7 ;ProcessDebugPort
		push -1
		call NTQIP
	}
	if( isdebugged == -1 )
	{
		AddRandomNops( Nop_5 );
		TerminateProcess( GetCurrentProcess(), 0 );
	}
/*----------------------------------------------*/

	AddRandomNops( Nop_5 );
	DebugActiveProcessStop( GetCurrentProcessId() );

/*----------NtQueryInformationProcess-----------*/
	ntsit NTSIT = (ntsit)GetProcAddress(LoadLibrary(TEXT("ntdll.dll")), "NtSetInformationThread");
	__asm
	{
		push 0
		push 0
		push 11h
		push -2
		call NTSIT
	}
/*----------------------------------------------*/


/*-------------------NtClose--------------------*/
	AddRandomNops( Nop_5 );
	CloseHandle( (HANDLE)0x1234 );
/*----------------------------------------------*/

	AddRandomNops( Nop_5 );
	DebugActiveProcessStop( GetCurrentProcessId() );
	AddRandomNops( Nop_5 );
	ExitThread( -1 );
}

#pragma code_seg(".cddata")
DWORD WINAPI DebugThread5( LPVOID )
{
	AddRandomNops( Nop_5 );
	DebugActiveProcessStop( GetCurrentProcessId() );
	AddRandomNops( Nop_5 );
	if( IsDebuggerPresent() )
	{
		AddRandomNops( Nop_5 );
		TerminateProcess( GetCurrentProcess(), 0 );
		BeingDebugged = 1;
	}

	DWORD dwValue		= NULL;

/*---------------PEB!NtGlobalFlags------------------*/
	__asm
	{
		mov eax, fs:[30h]
		mov eax, [eax+68h]
		and eax, 0x70
		mov dwValue, eax
	}
	AddRandomNops( Nop_5 );
	if( dwValue )
	{
		AddRandomNops( Nop_5 );
		ExitProcess( -1 );
	}
/*----------------------------------------------*/


/*----------------Heap flags--------------------*/
	__asm
	{
		mov eax, fs:[30h]
		mov eax, [eax+18h]		//process heap
		mov eax, [eax+10h]		//heap flags
		mov dwValue, eax
	}
	AddRandomNops( Nop_5 );
	if( !dwValue )
	{
		AddRandomNops( Nop_5 );
		FatalExit( -1 );
	}
/*----------------------------------------------*/

	AddRandomNops( Nop_5 );
	DebugActiveProcessStop( GetCurrentProcessId() );

/*----------NtQueryInformationProcess-----------*/
	ntip NTQIP = (ntip)GetProcAddress(LoadLibrary(TEXT("ntdll.dll")), "NtQueryInformationProcess");
	int isdebugged;
	__asm
	{
		push 0
		push 4
		push isdebugged
		push 7 ;ProcessDebugPort
		push -1
		call NTQIP
	}
	if( isdebugged == -1 )
	{
		AddRandomNops( Nop_5 );
		TerminateProcess( GetCurrentProcess(), 0 );
	}
/*----------------------------------------------*/


/*----------NtQueryInformationProcess-----------*/
	ntsit NTSIT = (ntsit)GetProcAddress(LoadLibrary(TEXT("ntdll.dll")), "NtSetInformationThread");
	__asm
	{
		push 0
		push 0
		push 11h
		push -2
		call NTSIT
	}
/*----------------------------------------------*/


/*-------------------NtClose--------------------*/
	AddRandomNops( Nop_5 );
	CloseHandle( (HANDLE)0x1234 );
/*----------------------------------------------*/

	AddRandomNops( Nop_5 );
	DebugActiveProcessStop( GetCurrentProcessId() );

	AddRandomNops( Nop_5 );
	ExitThread( -1 );

	AddRandomNops( Nop_5 );
}