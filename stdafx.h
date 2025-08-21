#pragma once

/*************************************/

#ifndef WINVER				
#define WINVER 0x0400		
#endif

#ifndef _WIN32_WINNT		                  
#define _WIN32_WINNT 0x0501	
#endif						

#ifndef _WIN32_WINDOWS		
#define _WIN32_WINDOWS 0x0410 
#endif

#ifndef _WIN32_IE			
#define _WIN32_IE 0x0600	
#endif

#ifndef _cplusplus			
#define _cplusplus
#endif

#ifndef PC32BIT			
#define PC32BIT
#endif

#ifndef WIN32_LEAN_AND_MEAN			
#define WIN32_LEAN_AND_MEAN
#endif
		
#define PublicModeNo

/*************************************/

#pragma comment ( lib, "Detours.lib" )
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib" )
#pragma comment ( lib, "Gdi32.lib" )
#pragma comment ( lib, "Shlwapi.lib" )
#pragma comment ( lib, "delayimp" )
#pragma comment ( lib, "WinMM.lib" )
#pragma comment ( lib, "wininet.lib" )
#pragma comment ( lib, "Ws2_32.lib" )
#pragma comment ( lib, "iphlpapi.lib" )
#pragma comment ( lib, "Psapi.lib" )
#pragma comment ( lib, "winmm.lib" )
#pragma comment ( lib, "Urlmon.lib" )

#pragma warning ( disable : 4244 4700 4101 4996 4800 4405 4311 4312 4305 4018 )

/*************************************/

#include <windows.h>
#include <Windowsx.h>
#include <detours.h>
#include <Urlmon.h>
#include <tlhelp32.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <sys/stat.h> 
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <D3D9Types.h>
#include <assert.h>
#include <vector>
#include <intrin.h>
#include <vector>
#include <time.h>
#include <sstream>
#include <process.h>
#include <ddraw.h>
#include <Shlwapi.h>
#include <string>
#include <deque>
#include <intrin.h>
#include <Winsock2.h>
#include <Psapi.h>
#include <delayimp.h>
#include <Mmsystem.h>
#include <algorithm>
#include <map>
#include <sys/stat.h>
#include <winternl.h>
#include <Wininet.h>
#include <shellapi.h>
#include <Iphlpapi.h>
#include <Assert.h>
#include <Ddeml.h>
#include <Dde.h>

/*************************************/

///////////////////////
// Local Includes
#include "CallOfDuty4_Classes.h"
#include "CCore.h"
#include "Math.h"
#include "Main.h"
#include "CGameAim.h"
#include "CSettings.h"
#include "CDirect3DHooks.h"
#include "CEngineHooks.h"
#include "CTextWriter.h"
#include "CShapeDrawer.h"
#include "CESPDrawer.h"
#include "CMenuDrawer.h"
#include "CMenuManager.h"
#include "CGame.h"
#include "CDirect3DRenderer.h"
///////////////////////

#pragma intrinsic(_ReturnAddress)

using namespace std;