#include "stdafx.h"

void CMenuManager::SetMouseMenu( bool isMouseMenu )
{
	this->MenuDrawer.isMouseMenu( )	= isMouseMenu;
}
void CMenuManager::InitiateMenu( const std::string WindowName )
{
	static bool InitiateOnce		= false;
	if( InitiateOnce == false )
	{
		this->MainWindowName		= WindowName;
		this->MainWindowHWND		= FindWindowA( 0, WindowName.c_str( ) );

		InitiateOnce = true;
	}

	tagPOINT			tempCursorPoint;

	GetCursorPos( &tempCursorPoint );

	this->CursorPositionX							= tempCursorPoint.x;
    this->CursorPositionY							= tempCursorPoint.y;
	this->MenuDrawer.GetCursorPosition( true )		= this->CursorPositionX;
    this->MenuDrawer.GetCursorPosition( false )		= this->CursorPositionY;
}

void CMenuManager::ChangeCursorState( bool Active )
{
	if( !this->MenuDrawer.isMouseMenu( ) )
		return;

	if( EngineHooks.CheckGame_Name( "Call of Duty: 4" ) )
	{
		static bool areValuesSet = false;
		static BYTE OriginalValue;
	 
		if( !areValuesSet && Active )
		{
			OriginalValue = *(BYTE*)0x0CC147D1; 
			*(BYTE*)0x0CC147D1 = 0;
			(( void (__cdecl *) ( int, int, char * ) )0x004F9AB0)( 0, 0, "unbind mouse1" );

			areValuesSet = true;
		}
		else if( areValuesSet && !Active )
		{
			*(BYTE*)0x0CC147D1 = OriginalValue;
			(( void (__cdecl *) ( int, int, char * ) )0x004F9AB0)( 0, 0, "bind mouse1 +attack" );

			areValuesSet = false;
		}
	}
}
void CMenuManager::ChangeMenuState( bool Active )
{
	this->MenuDrawer.GetMenuActive( )		= Active;
}

void CMenuManager::UpdateAll( )
{
	this->InitiateMenu( this->MainWindowName );
}

bool CMenuManager::IsCursorInsideSpace( int X, int Y, int Width, int Height )
{
	if( this->CursorPositionX > X && \
		this->CursorPositionX < X + Width && \
		this->CursorPositionY > Y && \
		this->CursorPositionY < Y + Height )
	{
		return true;
	}

	return false;
}
bool CMenuManager::IsCursorInCorrectWindow( )
{
	if( GetForegroundWindow( ) == FindWindowA( 0, this->MainWindowName.c_str( ) ) )
		return true;

	return false;
}