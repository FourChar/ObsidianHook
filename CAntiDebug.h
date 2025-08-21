#pragma once

#define CheckRandomThread( RandomThread )				RandomThread == DebugThread1 || \
														RandomThread == DebugThread2 || \
														RandomThread == DebugThread3 || \
														RandomThread == DebugThread4 || \
														RandomThread == DebugThread5

class CAntiDebug
{
public:
	char			*				Encrypt										( const char *String );
	char			*				Decrypt										( const char *String );
	int								GenerateRandomNumber						( int Minimum, int Mamimum );

	void			*				GetRandomThread								( );
	void			*				GetRandomThread2							( );
	void			*				GetRandomThread3							( );
};
extern CAntiDebug AntiDebug;

void			__fastcall			CheckDebugFunctionsChecker					( bool Crash );
void			__fastcall			CheckDebugFunctions							( bool Crash );
DWORD			__stdcall			DebugThread1								( LPVOID );
DWORD			__stdcall			DebugThread2								( LPVOID );
DWORD			__stdcall			DebugThread3								( LPVOID );
DWORD			__stdcall			DebugThread4								( LPVOID );
DWORD			__stdcall			DebugThread5								( LPVOID );