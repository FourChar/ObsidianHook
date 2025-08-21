#pragma once

class CESPDrawer
{
public:
	void							DrawPlayerSquare					( float X, float Y, float Width, float Height, DWORD Color );
	void							DrawPlayerText						( float X, float Y, bool Centered, DWORD Color, const std::string TextString, ... );
};