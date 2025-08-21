#include "stdafx.h"

bool CTextWriter::SetDrawingFont( ID3DXFont *Font )
{
	if( !IsFontLoaded( Font ) )
		return false;

	this->DrawingFont				= Font;
	return true;
}

void CTextWriter::SetDrawingColor( DWORD Color )
{
	this->DrawingColor = Color;
}

ID3DXFont *&CTextWriter::GetDrawingFont( )
{
	return this->DrawingFont;
}

DWORD CTextWriter::GetDrawingColor( )
{
	return this->DrawingColor;
}

int CTextWriter::GetTextLength( const std::string TextString )
{
	const char *	TempString		= TextString.c_str( );
	int				TextCount		= 0;

	while( *TempString )
	{
		if( ( TempString && *(TempString) == '^' && *((TempString)+1) && *((TempString)+1) != '^' ) )
		{
			TempString += 2;
		}
		else
		{
			TextCount++;
			TempString++;
		}
	}

	return TextCount;
}

bool CTextWriter::IsFontLoaded( ID3DXFont *Font )
{
	if( !Font )
		return false;

	return true;
}

ID3DXFont *&CTextWriter::GetFontByName( const std::string FontName )
{
	if( strcmp( FontName.c_str( ), "Normal" ) == 0 )
		return this->Fonts.Normal;
	else if( strcmp( FontName.c_str( ), "Bold" ) == 0 )
		return this->Fonts.Bold;
	else if( strcmp( FontName.c_str( ), "Big" ) == 0 )
		return this->Fonts.Big;
	else if( strcmp( FontName.c_str( ), "Objective" ) == 0 )
		return this->Fonts.Objective;

	return this->Fonts.Normal;
}

void CTextWriter::LoadFont( ID3DXFont *&Font, int Height, UINT Weight, BOOL Italic, std::string FontName )
{
	D3DXCreateFontW(D3DRenderer.GetRenderDevice( ), Height, 0, Weight, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, (wchar_t *)FontName.c_str( ), &Font);
}

void CTextWriter::UnloadFont( ID3DXFont *&Font )
{
	if( IsFontLoaded( Font ) )
		Font = NULL;
}

void CTextWriter::DrawTextString( float X, float Y, std::string TextString, ... )
{
	char			TextBuffer[512]		= { 0 };
	va_list			vaList;

	va_start(vaList, TextString);
		vsprintf(TextBuffer, TextString.c_str( ), vaList);
	va_end(vaList);
	
	DrawTextFromEngine( X, Y, this->DrawingFont, TextBuffer, this->DrawingColor );
}
void CTextWriter::DrawTextStringEx( float X, float Y, ID3DXFont *Font, DWORD Color, std::string TextString, ... )
{
	char			TextBuffer[512]		= { 0 };
	va_list			vaList;

	va_start(vaList, TextString);
		vsprintf(TextBuffer, TextString.c_str( ), vaList);
	va_end(vaList);
	
	DrawTextFromEngine( X, Y, Font, TextBuffer, Color );
}

void CTextWriter::DrawTextStringCentered( float X, float Y, std::string TextString, ... )
{
	char			TextBuffer[512]		= { 0 };
	int				TextLength			= 0;
	int				CenterMultiple		= 0;
	va_list			vaList;

	va_start(vaList, TextString);
		vsprintf(TextBuffer, TextString.c_str( ), vaList);
	va_end(vaList);

	TextLength = GetTextLength( TextBuffer );

	if( DrawingFont == Fonts.Normal )
	{
		CenterMultiple = 6;
	}
	else
	{
		CenterMultiple = 12;
	}

	float FinalPositionX = X - ( (TextLength * CenterMultiple) / 2.0f );
	
	DrawTextFromEngine( FinalPositionX, Y, this->DrawingFont, TextBuffer, this->DrawingColor );
}
void CTextWriter::DrawTextStringCenteredEx( float X, float Y, ID3DXFont *Font, DWORD Color, std::string TextString, ... )
{
	char			TextBuffer[512]		= { 0 };
	int				TextLength			= 0;
	int				CenterMultiple		= 0;
	va_list			vaList;

	va_start(vaList, TextString);
		vsprintf(TextBuffer, TextString.c_str( ), vaList);
	va_end(vaList);

	TextLength = GetTextLength( TextBuffer );

	if( Font == Fonts.Normal )
	{
		CenterMultiple = 6;
	}
	else
	{
		CenterMultiple = 12;
	}

	float FinalPositionX = X - ( (TextLength * CenterMultiple) / 2.0f );
	
	DrawTextFromEngine( FinalPositionX, Y, Font, TextBuffer, Color );
}

void CTextWriter::DrawTextFromEngine( float X, float Y, ID3DXFont *Font, std::string TextString, DWORD TextColor )
{
	RECT		FontPos					= { X, Y, X + 120, Y + 16 };

	Font->DrawTextA( NULL, TextString.c_str( ), -1, &FontPos, DT_NOCLIP, TextColor );
}