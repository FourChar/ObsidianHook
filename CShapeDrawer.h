#pragma once

typedef struct
{
	static const DWORD			Black				= D3DCOLOR_ARGB( 255, 0,0,0 );
	static const DWORD			White				= D3DCOLOR_ARGB( 255, 255,255,255 );
	static const DWORD			Red					= D3DCOLOR_ARGB( 255, 255,0,0 );
	static const DWORD			Green				= D3DCOLOR_ARGB( 255, 0,255,0 );
	static const DWORD			Blue				= D3DCOLOR_ARGB( 255, 0,0,255 );
	static const DWORD			Pink				= D3DCOLOR_ARGB( 255, 255,0,255 );
	static const DWORD			Orange				= D3DCOLOR_ARGB( 255, 255,106,0 );
	static const DWORD			Yellow				= D3DCOLOR_ARGB( 255, 255,255,0 );
	static const DWORD			Cyan				= D3DCOLOR_ARGB( 255, 0,255,255 );
	static const DWORD			Lime				= D3DCOLOR_ARGB( 255, 182,255,0 );
	static const DWORD			LightGreen			= D3DCOLOR_ARGB( 255, 76,255,0 );
	static const DWORD			DarkGreen			= D3DCOLOR_ARGB( 255, 0,127,14 );
	static const DWORD			LightBlue			= D3DCOLOR_ARGB( 255, 0,148,255 );
	static const DWORD			DarkBlue			= D3DCOLOR_ARGB( 255, 0,19,127 );
	static const DWORD			LightPink			= D3DCOLOR_ARGB( 255, 178,0,255 );
	static const DWORD			DarkPink			= D3DCOLOR_ARGB( 255, 255,0,110 );
	static const DWORD			DarkGrey			= D3DCOLOR_ARGB( 255, 51,51,51 );
	static const DWORD			Grey				= D3DCOLOR_ARGB( 255, 64,64,64 );

	static const DWORD			Easy_Red			= D3DCOLOR_ARGB( 255, 255,127,127 );
	static const DWORD			Easy_Green			= D3DCOLOR_ARGB( 255, 127,255,127 );
	static const DWORD			Easy_Blue			= D3DCOLOR_ARGB( 255, 127,127,255 );
	static const DWORD			Easy_Pink			= D3DCOLOR_ARGB( 255, 255,127,255 );
	static const DWORD			Easy_Orange			= D3DCOLOR_ARGB( 255, 255,141,66 );
	static const DWORD			Easy_Yellow			= D3DCOLOR_ARGB( 255, 255,255,127 );
	static const DWORD			Easy_Cyan			= D3DCOLOR_ARGB( 255, 127,255,255 );
	static const DWORD			Easy_Lime			= D3DCOLOR_ARGB( 255, 182,255,127 );
	static const DWORD			Easy_Grey			= D3DCOLOR_ARGB( 255, 84,84,84 );

} D3DColors;

typedef struct
{
	DWORD							MainColor;
	DWORD							WindowFillColor;
	DWORD							TopBoarderColor;
	bool							InSet;
	bool							FillCorners;
	bool							FillWindow;
	bool							UseTopBorder;
	int								TopBorderHight;
 
} BorderSettings_t;

class CShapeDrawer
{
public:
	void							SetDrawingColor						( DWORD Color );

	void							SaveUsePrimitives					( );
	void							RestoreUsePrimitives				( );

	bool				&			GetUsePrimitives					( );
	IDirect3DTexture9	*&			GetDrawingPrimitive					( );
	ID3DXLine			*&			GetDrawingLine						( );
	DWORD							GetDrawingColor						( );

	void							LoadLine							( ID3DXLine *&Line );
	void							UnloadLine							( ID3DXLine *&Line );

	void							DrawSolidSquare						( float X, float Y, float Width, float Height );
	void							DrawSolidSquareEx					( float X, float Y, float Width, float Height, DWORD Color );

	void							DrawBorderSquare					( float X, float Y, float Width, float Height, float LineThickness );
	void							DrawBorderSquareEx					( float X, float Y, float Width, float Height, float LineThickness, DWORD Color );

	void							DrawGradientSquare					( float X, float Y, float Width, float Height, int R, int G, int B, int A );
	void							DrawCross							( float X, float Y, float Width, float Height, float LineThickness, DWORD Color );
	void							DrawLine							( float X1, float Y1, float X2, float Y2, DWORD Color );
	void							DrawCheckBox						( float X, float Y, bool On, DWORD Background_Color, DWORD Forground_Color );

	void							DrawBorder							( float X, float Y, float Width, float Height, BorderSettings_t *BorderSettings );
	void							DrawWindow							( float X, float Y, float Width, float Height, BorderSettings_t *BorderSettings, cdstl::Mathematics::Vector2 *TitleOffset, std::string Title );
 
	void							SetBorderSettings					( BorderSettings_t *BorderSettings,
																			DWORD MainColor, DWORD WindowFillColor, DWORD TopBoarderColor,
																			bool InSet, bool FillCorners, bool FillWindow, bool UseTopBorder, 
																			int TopBorderHight );
private:
	IDirect3DTexture9	*			pPrimitive;
	ID3DXLine			*			pLine;
	DWORD							DrawingColor;

	bool							UsePrimitives;
	bool							SavedUsePrimitives;
};