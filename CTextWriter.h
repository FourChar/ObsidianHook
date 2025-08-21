#pragma once

typedef struct
{
	ID3DXFont			*		Normal;
	ID3DXFont			*		Bold;
	ID3DXFont			*		Big;
	ID3DXFont			*		Objective;
} CDirect3DFonts;

class CTextWriter
{
public:
	bool							SetDrawingFont						( ID3DXFont *Font );
	void							SetDrawingColor						( DWORD Color );

	ID3DXFont			*&			GetDrawingFont						( );
	DWORD							GetDrawingColor						( );
	int								GetTextLength						( const std::string TextString );

	bool							IsFontLoaded						( ID3DXFont *Font );
	ID3DXFont			*&			GetFontByName						( const std::string FontName );
	void							LoadFont							( ID3DXFont *&Font, int Height, UINT Weight, BOOL Italic, std::string FontName );
	void							UnloadFont							( ID3DXFont *&Font );

	void							DrawTextString						( float X, float Y, std::string TextString, ... );
	void							DrawTextStringEx					( float X, float Y, ID3DXFont *Font, DWORD Color, std::string TextString, ... );

	void							DrawTextStringCentered				( float X, float Y, std::string TextString, ... );
	void							DrawTextStringCenteredEx			( float X, float Y, ID3DXFont *Font, DWORD Color, std::string TextString, ... );

private:
	CDirect3DFonts					Fonts;
	ID3DXFont			*			DrawingFont;
	DWORD							DrawingColor;

	void							DrawTextFromEngine					( float X, float Y, ID3DXFont *Font, std::string TextString, DWORD TextColor );
};