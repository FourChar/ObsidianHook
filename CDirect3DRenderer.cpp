#include "stdafx.h"

tEndScene			oEndScene;
void				( *oSwapChain_Present )		( );

DWORD				ClassManagerPointer					= NULL;
BYTE				OriginalEndSceneBytes	[10];
BYTE				WhitePixel				[58]		= 
{
	0x42, 0x4D, 0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 
	0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xFF, 0xFF, 0xFF, 0x00
};

DWORD WINAPI InitiateDirect3DThread( LPVOID )
{
	DWORD	VTableAddress		= NULL;
	DWORD	PresentAddress		= NULL;

	char	VTable_bMask[]				= "\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86";
	char	Present_bMask[]				= "\x8B\xFF\x55\x8B\xEC\x83\xEC\x7C\x53\x56\x8B\xF1\x8B\x46\x0C\x85\xC0\x0F\x84\x00\x00\x00\x00\x8D\x58\x04\x83\x7B\x00\x00\x89\x5D\xF0\x89\x5D\xE8\xC7\x45\x00\x00\x00\x00\x00\x0F\x85\x00\x00\x00\x00\x8B\x46\x0C\xF6\x40\x00\x00\x0F\x85\x00\x00\x00\x00\x57\xBF\x00\x00\x00\x00\x39\xB8\x00\x00\x00\x00\x0F\x84\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x0B\x05\x00\x00\x00\x00\xC7\x45\x00\x00\x00\x00\x00\x0F\x85\x00\x00\x00\x00\x8B\x5D\x18\xF6\xC3\x40\x0F\x85\x00\x00\x00\x00\xF6\xC3\xA0\x0F\x85\x00\x00\x00\x00\x8B\x46\x0C\xF6\x40\x00\x00\x0F\x85\x00\x00\x00\x00\x8B\x80\x00\x00\x00\x00\x50\xE8\x00\x00\x00\x00\x85\xC0\x0F\x85\x00\x00\x00\x00\x83\x7E\x00\x00\x8B\x46\x0C\x0F\x84\x00\x00\x00\x00\xF6\x40\x00\x00\x0F\x85\x00\x00\x00\x00\x83\xB8\x00\x00\x00\x00\x00\x0F\x85\x00\x00\x00\x00\x8B\x56\x0C\xF6\x82\x00\x00\x00\x00\x00\x0F\x85\x00\x00\x00\x00\x8B\x8E\x00\x00\x00\x00\x8B\x7D\x14\x8B\x55\x0C\x8B\x45\x08\x83\xF9\x02";

	char	VTable_szMask[]				= "xx????xx????xx";
	char	Present_szMask[]			= "xxxxxxxxxxxxxxxxxxx????xxxxx??xxxxxxxx?????xx????xxxxx??xx????xx????xx????xx????x????xx????xx?????xx????xxxxxxxx????xxxxx????xxxxx??xx????xx????xx????xxxx????xx??xxxxx????xx??xx????xx?????xx????xxxxx?????xx????xx????xxxxxxxxxxxx";

	char	d3d9[]						= "d3d9.dll";

	while( !Direct3D_ModuleBase )
	{
		Direct3D_ModuleBase = (DWORD)GetModuleHandle( d3d9 );
		Sleep( 250 );
	}
	while( !Direct3D_ModuleSize )
	{
		Direct3D_ModuleSize = (DWORD)D3DRenderer.Hooks.GetModuleSize( d3d9 );
		Sleep( 250 );
	}

	VTableAddress						= D3DRenderer.Hooks.FindPattern(Direct3D_ModuleBase, Direct3D_ModuleSize, \
										(PBYTE)VTable_bMask, \
										VTable_szMask) + 2;
	PresentAddress						= D3DRenderer.Hooks.FindPattern(Direct3D_ModuleBase, Direct3D_ModuleSize, \
										(PBYTE)Present_bMask, \
										 Present_szMask) + 23; // 8, 16, 23

	CopyMemory( &D3DRenderer.VTable, (PVOID)VTableAddress, 4 );

	ReadProcessMemory( GetCurrentProcess(), (LPCVOID)D3DRenderer.VTable[42], OriginalEndSceneBytes, sizeof( OriginalEndSceneBytes ), NULL );

	*(void**)&oSwapChain_Present		= (void*)DetourFunction( (PBYTE)PresentAddress,					(PBYTE)hkSwapChain_Present );
	*(void**)&oEndScene					= (void*)DetourFunction( (PBYTE)D3DRenderer.VTable[42],			(PBYTE)hkEndScene );

	ZeroMemory( VTable_bMask, sizeof( VTable_bMask ) );
	ZeroMemory( Present_bMask, sizeof( Present_bMask ) );
	ZeroMemory( VTable_szMask, sizeof( VTable_szMask ) );
	ZeroMemory( Present_szMask, sizeof( Present_szMask ) );
	ZeroMemory( d3d9, sizeof( d3d9 ) );

	ExitThread( 0 );
};
void CDirect3DRenderer::InitiateDirect3D( )
{
	MakeThread( InitiateDirect3DThread );
}
void CDirect3DRenderer::InitiateDirect3DObjects( )
{
	static bool AfterOne = false;
	if( AfterOne == true )
	{
		TextWriter.UnloadFont( TextWriter.GetFontByName("Normal") );
		TextWriter.UnloadFont( TextWriter.GetFontByName("Bold") );
		TextWriter.UnloadFont( TextWriter.GetFontByName("Big") );
		TextWriter.UnloadFont( TextWriter.GetFontByName("Objective") );

		ShapeDrawer.GetDrawingLine( )->Release( );
		ShapeDrawer.GetDrawingPrimitive( )->Release( );
	}
	else
	{
		AfterOne = true;
	}

	TextWriter.LoadFont( TextWriter.GetFontByName("Normal"),		15, FW_NORMAL,	0, "Verdana" );
	TextWriter.LoadFont( TextWriter.GetFontByName("Bold"),			15, FW_BOLD,	0, "Verdana" );
	TextWriter.LoadFont( TextWriter.GetFontByName("Big"),			23, FW_NORMAL,	0, "Verdana" );
	TextWriter.LoadFont( TextWriter.GetFontByName("Objective"),		35, FW_BOLD,	0, "Verdana" );

	ShapeDrawer.LoadLine( ShapeDrawer.GetDrawingLine( ) );

	D3DXCreateTextureFromFileInMemory( this->RenderDevice, (LPCVOID)&WhitePixel, sizeof(WhitePixel), &ShapeDrawer.GetDrawingPrimitive( ) );
}

IDirect3DDevice9 *&CDirect3DRenderer::GetRenderDevice( )
{
	return this->RenderDevice;
}
void CDirect3DRenderer::SetRenderDevice( IDirect3DDevice9 *pDevice )
{
	this->RenderDevice = pDevice;
}

D3DVIEWPORT9 &CDirect3DRenderer::GetViewPort( )
{
	return this->pViewport;
}
void CDirect3DRenderer::SetViewPort( D3DVIEWPORT9 pViewPort )
{
	this->pViewport = pViewPort;
}

//=================================================================================================================

#pragma code_seg( ".qrdata" )
long __stdcall hkEndScene( IDirect3DDevice9 *pDevice )
{
	D3DRenderer.SetRenderDevice( pDevice );
	D3DRenderer.InitiateDirect3DObjects( );
	
	pDevice->GetViewport( &D3DRenderer.GetViewPort( ) );

	DetourRemove( (PBYTE)oEndScene, (PBYTE)hkEndScene );
	WriteProcessMemory( GetCurrentProcess(), (LPVOID)D3DRenderer.VTable[42], OriginalEndSceneBytes, sizeof( OriginalEndSceneBytes ), NULL );

	return oEndScene( pDevice );
}

//=================================================================================================================

// hkSwapChain_Present( )
//
// This is the Hooked SwapChain_Present( ) function's jump location.
// Basicly main Direct3D9 Rendering location.
// Calls the CDirect3DRenderer::Direct3DPreRenderThread( ) then 
// calls the CDirect3DRenderer::Direct3DRenderThread( ) to render everything.
//
// Function is stored in ".qrdata" section.
//
//
#pragma code_seg( ".qrdata" )
void __declspec( naked ) hkSwapChain_Present( )
{
	__asm PUSHAD
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

	D3DRenderer.Direct3DPreRenderThread		( );
	D3DRenderer.Direct3DRenderThread		( );

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+	
	__asm POPAD
	__asm JMP [ oSwapChain_Present ]
}

// CDirect3DRenderer::Direct3DRenderThread( )
//
// Any Pre-Render calculations or shit goes in here.
//
// Function is stored in ".qrdata" section.
//
//
#pragma code_seg( ".qqdata" )
void CDirect3DRenderer::Direct3DPreRenderThread( )
{
	static bool DoOnce = false;
	if( DoOnce == false )
	{
		MenuManager.SetMouseMenu		( false );

		if( Settings.isNewFile )
		{
			Settings.SaveSettingsToFile( );
		}

		if( EngineHooks.CheckGame_Name( "Call of Duty: 4" ) )
		{
			// Sets all the localy defined structs/data to the correct address in the game.
			Game.SetOffsets				( );

			// Checks for the Game's RenderDevice, if found, set CDirect3DRenderer::RenderDevice to the Game's one.
			if( Game.Structs.Renderer->pDevice )
				D3DRenderer.SetRenderDevice( Game.Structs.Renderer->pDevice );
		}

		DoOnce = true;
	}

	// Resets the RenderDevice and Reinitiates the D3D Objects if The game's RenderDevice Changes
	// ( Means that its gone through IDirect3DDevice9::Reset so we also have to reset our shit to be able to draw again ).
	if( D3DRenderer.GetRenderDevice( ) != Game.Structs.Renderer->pDevice )
	{
		D3DRenderer.SetRenderDevice( Game.Structs.Renderer->pDevice );
		D3DRenderer.InitiateDirect3DObjects( );
	}
}

// CDirect3DRenderer::Direct3DRenderThread( )
//
// This is where you would do your main Rendering or Calculation calling. 
// ESP, Crosshair, Aimbot, AutoVote, Radar, Menu, ect...
//
// Function is stored in ".qrdata" section.
//
//
#pragma code_seg( ".qrdata" )
void CDirect3DRenderer::Direct3DRenderThread( )
{
	D3DRenderer.ShapeDrawer.GetUsePrimitives( ) = true;

	if( Game.Structs.cg->snap )
	{
		Game.AutoVote			( );
		Game.NameStealer		( );

		Game.DrawPlayerESP		( );
		Game.DrawHelicopterESP	( );
		//Game.DrawEntityESP	( );

		if( SubGame::isPlayerValid( SubGame::getLocalPlayerID( ) ) )
		{
			if( Settings.Options.Misc_CrossHair->Value._bool )
			{
				D3DRenderer.ShapeDrawer.DrawBorderSquareEx( D3DRenderer.GetViewPort( ).Width/2-8.5, D3DRenderer.GetViewPort( ).Height/2-8.5, 16, 16, 1, D3DColors::Easy_Green );
				D3DRenderer.ShapeDrawer.DrawSolidSquareEx( D3DRenderer.GetViewPort( ).Width/2-2.5,D3DRenderer.GetViewPort( ).Height/2-2.5, 5, 5, D3DColors::Easy_Green );
			}

			Game.AutoWeapons			( );
			Game.DrawLocalWeaponInfo	( );
			Game.DrawRadar				( );
			Game.DoAimbot				( );
		}
	}

	D3DRenderer.ESPDrawer.DrawPlayerText( D3DRenderer.GetViewPort( ).Width/2, D3DRenderer.GetViewPort( ).Height - 25, true, D3DColors::Easy_Green, "%s - ObsidianHook v%s (By CyberDwak)", EngineHooks.GetGame_Name( ), EngineHooks.GetHack_Version( ) );
	D3DRenderer.ESPDrawer.DrawPlayerText( D3DRenderer.GetViewPort( ).Width/2, D3DRenderer.GetViewPort( ).Height - 45, true, D3DColors::Easy_Green, ReturnTime( "[ %a %b %d %Y %H:%M:%S %p ]" ) );

	Game.UpdateAll						( );
	Settings.UpdateAll					( );
	MenuManager.UpdateAll				( );
	MenuManager.MenuDrawer.DrawMenu		( );

	if( GetAsyncKeyState( VK_F7 ) & 1 )
	{
		MenuManager.ChangeMenuState		( !MenuManager.MenuDrawer.GetMenuActive( ) );
		MenuManager.ChangeCursorState	( MenuManager.MenuDrawer.GetMenuActive( ) );
	}
}