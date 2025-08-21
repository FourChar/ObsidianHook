#include "stdafx.h"

void CESPDrawer::DrawPlayerSquare( float X, float Y, float Width, float Height, DWORD Color )
{
	D3DRenderer.ShapeDrawer.DrawBorderSquareEx(X - 1, Y - 1, Width + 2, Height + 2, 1, Color);
	D3DRenderer.ShapeDrawer.DrawBorderSquareEx(X + 1, Y + 1, Width - 2, Height - 2, 1, D3DColors::Black );
	D3DRenderer.ShapeDrawer.DrawBorderSquareEx(X - 2, Y - 2, Width + 4, Height + 4, 1, D3DColors::Black );
	D3DRenderer.ShapeDrawer.DrawBorderSquareEx(X - 0, Y - 0, Width + 0, Height + 0, 1, Color);
}

void CESPDrawer::DrawPlayerText( float X, float Y, bool Centered, DWORD Color, const std::string TextString, ... )
{
	char			TextBuffer[512]		= { 0 };
	va_list			vaList;

	va_start(vaList, TextString);
		vsprintf(TextBuffer, TextString.c_str( ), vaList);
	va_end(vaList);

	if( Centered )
	{
		D3DRenderer.TextWriter.DrawTextStringCenteredEx( X - 1, Y - 0, D3DRenderer.TextWriter.GetFontByName("Normal"), \
														D3DColors::Black, TextBuffer );
		D3DRenderer.TextWriter.DrawTextStringCenteredEx( X - 0, Y - 1, D3DRenderer.TextWriter.GetFontByName("Normal"), \
														D3DColors::Black, TextBuffer );
		D3DRenderer.TextWriter.DrawTextStringCenteredEx( X + 1, Y + 0, D3DRenderer.TextWriter.GetFontByName("Normal"), \
														D3DColors::Black, TextBuffer );
		D3DRenderer.TextWriter.DrawTextStringCenteredEx( X + 0, Y + 1, D3DRenderer.TextWriter.GetFontByName("Normal"), \
														D3DColors::Black, TextBuffer );
		D3DRenderer.TextWriter.DrawTextStringCenteredEx( X + 0, Y + 0, D3DRenderer.TextWriter.GetFontByName("Normal"), \
														Color, TextBuffer );
	}
	else
	{
		D3DRenderer.TextWriter.DrawTextStringEx( X - 1, Y - 0, D3DRenderer.TextWriter.GetFontByName("Normal"), \
														D3DColors::Black, TextBuffer );
		D3DRenderer.TextWriter.DrawTextStringEx( X - 0, Y - 1, D3DRenderer.TextWriter.GetFontByName("Normal"), \
														D3DColors::Black, TextBuffer );
		D3DRenderer.TextWriter.DrawTextStringEx( X + 1, Y + 0, D3DRenderer.TextWriter.GetFontByName("Normal"), \
														D3DColors::Black, TextBuffer );
		D3DRenderer.TextWriter.DrawTextStringEx( X + 0, Y + 1, D3DRenderer.TextWriter.GetFontByName("Normal"), \
														D3DColors::Black, TextBuffer );
		D3DRenderer.TextWriter.DrawTextStringEx( X + 0, Y + 0, D3DRenderer.TextWriter.GetFontByName("Normal"), \
														Color, TextBuffer );
	}
}