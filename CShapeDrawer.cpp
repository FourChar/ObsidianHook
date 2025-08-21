#include "stdafx.h"

void CShapeDrawer::SetDrawingColor( DWORD Color )
{
	this->DrawingColor = Color;
}

void CShapeDrawer::SaveUsePrimitives( )
{
	this->SavedUsePrimitives	= this->UsePrimitives;
}
void CShapeDrawer::RestoreUsePrimitives( )
{
	this->UsePrimitives			= this->SavedUsePrimitives;
}
bool &CShapeDrawer::GetUsePrimitives( )
{
	return this->UsePrimitives;
}

IDirect3DTexture9 *&CShapeDrawer::GetDrawingPrimitive( )
{
	return this->pPrimitive;
}

ID3DXLine *&CShapeDrawer::GetDrawingLine( )
{
	return this->pLine;
}

DWORD CShapeDrawer::GetDrawingColor( )
{
	return this->DrawingColor;
}

void CShapeDrawer::LoadLine( ID3DXLine *&Line )
{
	D3DXCreateLine( D3DRenderer.GetRenderDevice( ), &Line );
}

void CShapeDrawer::UnloadLine( ID3DXLine *&Line )
{
	Line = NULL;
}

//-----------------------------------------------------------------------------------------

void CShapeDrawer::DrawSolidSquare( float X, float Y, float Width, float Height )
{
	if( this->UsePrimitives )
	{
		struct Vertex
		{
			float X;
			float Y;
			float Z;
			float RHW;
			DWORD COLOR;
		};

		Vertex qV[4] =
		{
			{ (float)X, (float)Y+Height,		0.0f, 1.0f, this->DrawingColor },
			{ (float)X, (float)Y,				0.0f, 1.0f, this->DrawingColor },
			{ (float)X+Width, (float)Y+Height,	0.0f, 1.0f, this->DrawingColor },
			{ (float)X+Width, (float)Y,			0.0f, 1.0f, this->DrawingColor }
		};

		const DWORD D3DFVF_TL = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX5;
		D3DRenderer.GetRenderDevice( )->SetFVF( D3DFVF_TL );
		D3DRenderer.GetRenderDevice( )->SetTexture( 0, this->pPrimitive );
		D3DRenderer.GetRenderDevice( )->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, qV, sizeof(Vertex) );
	}
	else
	{
		D3DRECT Rect = { X, Y, X + Width, Y + Height };
		D3DRenderer.GetRenderDevice( )->Clear( 1, &Rect, D3DCLEAR_TARGET, this->DrawingColor, 0, 0 );
	}
}
void CShapeDrawer::DrawSolidSquareEx( float X, float Y, float Width, float Height, DWORD Color )
{
	if( this->UsePrimitives )
	{
		struct Vertex
		{
			float X;
			float Y;
			float Z;
			float RHW;
			DWORD COLOR;
		};

		Vertex qV[4] =
		{
			{ (float)X, (float)Y+Height,		0.0f, 1.0f, Color },
			{ (float)X, (float)Y,				0.0f, 1.0f, Color },
			{ (float)X+Width, (float)Y+Height,	0.0f, 1.0f, Color },
			{ (float)X+Width, (float)Y,			0.0f, 1.0f, Color }
		};

		const DWORD D3DFVF_TL = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX5;
		D3DRenderer.GetRenderDevice( )->SetFVF( D3DFVF_TL );
		D3DRenderer.GetRenderDevice( )->SetTexture( 0, this->pPrimitive );
		D3DRenderer.GetRenderDevice( )->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, qV, sizeof(Vertex) );
	}
	else
	{
		D3DRECT Rect = { X, Y, X + Width, Y + Height };
		D3DRenderer.GetRenderDevice( )->Clear( 1, &Rect, D3DCLEAR_TARGET, Color, 0, 0 );
	}
}

void CShapeDrawer::DrawBorderSquare( float X, float Y, float Width, float Height, float LineThickness )
{
	DrawSolidSquare( X, Y, Width, LineThickness );								// Top
	DrawSolidSquare( X, Y, LineThickness, Height );								// Left
	DrawSolidSquare( X, Y + Height, Width + 1, LineThickness );					// Bottom
	DrawSolidSquare( X + Width, Y, LineThickness, Height + 1 );					// Right
}
void CShapeDrawer::DrawBorderSquareEx( float X, float Y, float Width, float Height, float LineThickness, DWORD Color )
{
	DrawSolidSquareEx( X, Y, Width, LineThickness, Color );						// Top
	DrawSolidSquareEx( X, Y, LineThickness, Height, Color );					// Left
	DrawSolidSquareEx( X, Y + Height, Width + 1, LineThickness, Color );		// Bottom
	DrawSolidSquareEx( X + Width, Y, LineThickness, Height + 1, Color );		// Right
}

void CShapeDrawer::DrawCross( float X, float Y, float Width, float Height, float LineThickness, DWORD Color )
{
	DrawSolidSquareEx( X + (Width/2), Y, LineThickness, Height+1, Color );
	DrawSolidSquareEx( X, Y + (Height/2), Width+1, LineThickness, Color );
}
void CShapeDrawer::DrawGradientSquare( float X, float Y, float Width, float Height, int R, int G, int B, int A )
{ 
	for(int i = 0; i < Height; i++) 
	{ 
		int iR, iG, iB, iA; 

		iR = (int)((float)i / Height * R); 
		iG = (int)((float)i / Height * G); 
		iB = (int)((float)i / Height * B); 
		if(A < 255) 
		{ 
			iA = (int)((float)i / Height * A); 
		} 
		else iA = 0;
		DrawSolidSquareEx( X, Y+i, Width, 1, D3DCOLOR_RGBA( R-iR, G-iG, B-iB, A-iA ) );
	} 
}
void CShapeDrawer::DrawLine( float X1, float Y1, float X2, float Y2, DWORD Color )
{
	D3DXVECTOR2 vLine[ 2 ];
 
	this->pLine->SetWidth( 1 );
	this->pLine->SetAntialias( true );
	this->pLine->Begin( );
 
		vLine[ 0 ][ 0 ] = X1;
		vLine[ 0 ][ 1 ] = Y1;
		vLine[ 1 ][ 0 ] = X2;
		vLine[ 1 ][ 1 ] = Y2;
 
	this->pLine->Draw( vLine, 2, Color );
	this->pLine->End( );
}
void CShapeDrawer::DrawCheckBox( float X, float Y, bool On, DWORD Background_Color, DWORD Forground_Color )
{
	this->DrawSolidSquareEx( X, Y, 13, 13, D3DColors::White );
	this->DrawBorderSquareEx( X, Y, 13, 13, 1, D3DCOLOR_ARGB( 255, 142,143,143 ) );

	if( On )
	{
		for( int i = 0; i < 3; i++ )
			this->DrawSolidSquareEx( X + i + 4, Y + i + 6, 1, 2, D3DColors::DarkGrey );
		for( int i = 0; i < 5; i++ )
			this->DrawSolidSquareEx( X + i + 6, Y - i + 8, 1, 2, D3DColors::DarkGrey );
	}
}

void CShapeDrawer::DrawBorder( float X, float Y, float Width, float Height, BorderSettings_t *BorderSettings )
{
	if( BorderSettings->FillWindow )
	{
		D3DRenderer.ShapeDrawer.DrawSolidSquareEx( X + 1, Y + 1, Width - 1, Height - 1, BorderSettings->WindowFillColor );
		D3DRenderer.ShapeDrawer.SetDrawingColor( D3DColors::Black );
 
		if( BorderSettings->InSet )
		{
			D3DRenderer.ShapeDrawer.DrawSolidSquare( X + 1, Y + 1, 1, 1 );
			D3DRenderer.ShapeDrawer.DrawSolidSquare( X + 1, Y + 0, 1, 1 );
			D3DRenderer.ShapeDrawer.DrawSolidSquare( X + Width - 1, Y + Height - 1, 1, 1 );
		}
		else
		{
            D3DRenderer.ShapeDrawer.DrawSolidSquare( X, Y, Width, 1 );
            D3DRenderer.ShapeDrawer.DrawSolidSquare( X, Y + 1, 1, Height - 1 );
            D3DRenderer.ShapeDrawer.DrawSolidSquare( X + Width, Y, 1, Height );
            D3DRenderer.ShapeDrawer.DrawSolidSquare( X, Y + Height, Width + 1, 1 );
 
			if( BorderSettings->FillCorners )
			{
				D3DRenderer.ShapeDrawer.DrawSolidSquare( X + 1, Y, Width - 1, 1 );
				D3DRenderer.ShapeDrawer.DrawSolidSquare( X, Y + 1, 1, Height - 1 );
				D3DRenderer.ShapeDrawer.DrawSolidSquare( X + Width, Y + 1, 1, Height - 1 );
				D3DRenderer.ShapeDrawer.DrawSolidSquare( X + 1, Y + Height, Width - 1, 1 );
			}
			else
			{
				D3DRenderer.ShapeDrawer.DrawSolidSquare( X + 2, Y, Width - 3, 1 );
				D3DRenderer.ShapeDrawer.DrawSolidSquare( X, Y + 2, 1, Height - 3 );
				D3DRenderer.ShapeDrawer.DrawSolidSquare( X + Width, Y + 2, 1, Height - 3 );
				D3DRenderer.ShapeDrawer.DrawSolidSquare( X + 2, Y + Height, Width - 3, 1 );
			}
		}
	}
 
	if( BorderSettings->UseTopBorder )
	{
		D3DRenderer.ShapeDrawer.DrawSolidSquareEx( X + 1, Y + 1, Width - 1, BorderSettings->TopBorderHight, BorderSettings->TopBoarderColor );
		D3DRenderer.ShapeDrawer.DrawSolidSquareEx( X + 0, Y + 1, 1, BorderSettings->TopBorderHight - 1, BorderSettings->TopBoarderColor );
		D3DRenderer.ShapeDrawer.DrawSolidSquareEx( X + 1, Y + 0, Width - 1, 1, BorderSettings->TopBoarderColor );
		D3DRenderer.ShapeDrawer.DrawSolidSquareEx( X + Width, Y + 1, 1, BorderSettings->TopBorderHight - 1, BorderSettings->TopBoarderColor );
		D3DRenderer.ShapeDrawer.DrawSolidSquare( X + 0, Y + BorderSettings->TopBorderHight, Width, 1.5 );
	}
 
	D3DRenderer.ShapeDrawer.SetDrawingColor( BorderSettings->MainColor );
	if( !BorderSettings->InSet )
	{
		D3DRenderer.ShapeDrawer.DrawSolidSquare( X, Y, Width, 1 );
		D3DRenderer.ShapeDrawer.DrawSolidSquare( X, Y + 1, 1, Height - 1 );
		D3DRenderer.ShapeDrawer.DrawSolidSquare( X + Width, Y, 1, Height );
		D3DRenderer.ShapeDrawer.DrawSolidSquare( X, Y + Height, Width + 1, 1 );
	}
	else
	{
		if( BorderSettings->FillCorners )
		{
			D3DRenderer.ShapeDrawer.DrawSolidSquare( X + 1, Y, Width - 1, 1 );
			D3DRenderer.ShapeDrawer.DrawSolidSquare( X, Y + 1, 1, Height - 1 );
			D3DRenderer.ShapeDrawer.DrawSolidSquare( X + Width, Y + 1, 1, Height - 1 );
			D3DRenderer.ShapeDrawer.DrawSolidSquare( X + 1, Y + Height, Width - 1, 1 );
		}
		else
		{
			D3DRenderer.ShapeDrawer.DrawSolidSquare( X + 2, Y, Width - 3, 1 );
			D3DRenderer.ShapeDrawer.DrawSolidSquare( X, Y + 2, 1, Height - 3 );
			D3DRenderer.ShapeDrawer.DrawSolidSquare( X + Width, Y + 2, 1, Height - 3 );
			D3DRenderer.ShapeDrawer.DrawSolidSquare( X + 2, Y + Height, Width - 3, 1 );
		}
		D3DRenderer.ShapeDrawer.DrawSolidSquare( X + 1, Y + 1, 1, 1 );
		D3DRenderer.ShapeDrawer.DrawSolidSquare( X + Width - 1, Y + 1, 1, 1 );
		D3DRenderer.ShapeDrawer.DrawSolidSquare( X + 1, Y + Height - 1, 1, 1 );
		D3DRenderer.ShapeDrawer.DrawSolidSquare( X + Width - 1, Y + Height - 1, 1, 1 );
	}
}
 
void CShapeDrawer::SetBorderSettings( BorderSettings_t *BorderSettings, DWORD MainColor, DWORD WindowFillColor, DWORD TopBoarderColor,
									 bool InSet, bool FillCorners, bool FillWindow, bool UseTopBorder, int TopBorderHight )
{
	BorderSettings->MainColor					= MainColor;
	BorderSettings->InSet						= InSet;
	BorderSettings->FillCorners					= FillCorners;
	BorderSettings->FillWindow					= FillWindow;
	BorderSettings->WindowFillColor				= WindowFillColor;
	BorderSettings->UseTopBorder				= UseTopBorder;
	BorderSettings->TopBorderHight				= TopBorderHight;
	BorderSettings->TopBoarderColor				= TopBoarderColor;
}
 
void CShapeDrawer::DrawWindow( float X, float Y, float Width, float Height, BorderSettings_t *BorderSettings, cdstl::Mathematics::Vector2 *TitleOffset, std::string Title )
{
	this->DrawBorder( X, Y, Width, Height, BorderSettings );
	D3DRenderer.TextWriter.DrawTextStringCenteredEx( X + Width / 2 + 1 - TitleOffset->Vec1, Y + 5 - TitleOffset->Vec2, D3DRenderer.TextWriter.GetFontByName("Normal"), D3DColors::Black, Title );
	D3DRenderer.TextWriter.DrawTextStringCenteredEx( X + Width / 2 + 0 - TitleOffset->Vec1, Y + 4 - TitleOffset->Vec2, D3DRenderer.TextWriter.GetFontByName("Normal"), D3DColors::White, Title );
}