#pragma once

#define GetRandomNumber( Return, LimitInHex )			__asm pushad \
														__asm rdtsc \
														__asm and eax, LimitInHex \
														__asm mov Return, eax \
														__asm popad

#define MakeThread( a )				CreateThread(0,0,(LPTHREAD_START_ROUTINE)a,0,0,0)

//========================================== For HideModule Function ==========================================

#define UNLINK(x)										(x).Blink->Flink = (x).Flink; (x).Flink->Blink = (x).Blink;

typedef struct _ModuleInfoNode
{
   LIST_ENTRY LoadOrder;
   LIST_ENTRY InitOrder;
   LIST_ENTRY MemoryOrder;
   HMODULE baseAddress;
   unsigned long entryPoint;
   unsigned int size;
   UNICODE_STRING fullPath;
   UNICODE_STRING name;
   unsigned long flags;
   unsigned short LoadCount;
   unsigned short TlsIndex;
   LIST_ENTRY HashTable;
   unsigned long timestamp;
} ModuleInfoNode, *pModuleInfoNode;

typedef struct _ProcessModuleInfo
{
   unsigned int size;
   unsigned int initialized;
   HANDLE SsHandle;
   LIST_ENTRY LoadOrder;
   LIST_ENTRY InitOrder;
   LIST_ENTRY MemoryOrder;
} ProcessModuleInfo, *pProcessModuleInfo;

//=============================================================================================================

////////////////////
//Functions
int				HideModule			( HMODULE hMod );
std::string		GetDirectoryFile	( std::string FileName );
void __fastcall	Log					( const std::string String, ... );
std::string		ReturnTime			( const std::string Format );

////////////////////
//Extern shit
extern HINSTANCE			hMod;
extern char					DllDirectory[320];

////////////////////
//CHook Class(Makes it easier)
class CHook
{
public:
	void				StartInit					( HINSTANCE hinstModule );
	void				EndInit						( );
	void				StartThread					( );
	void				EndThread					( );
};
extern CHook	*	 Hook;