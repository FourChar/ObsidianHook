#pragma once

class CMenuManager
{
public:
	void							SetMouseMenu							( bool MouseMenu );
	void							InitiateMenu							( const std::string WindowName );

	void							ChangeCursorState						( bool Active );
	void							ChangeMenuState							( bool Active );

	void							UpdateAll								( );

	bool							IsCursorInsideSpace						( int X, int Y, int Width, int Height );
	bool							IsCursorInCorrectWindow					( );

	CMenuDrawer						MenuDrawer;

private:
	std::string						MainWindowName;
	HWND							MainWindowHWND;

	float							CursorPositionX;
	float							CursorPositionY;
};
extern CMenuManager			MenuManager;