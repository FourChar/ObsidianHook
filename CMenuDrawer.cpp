#include "stdafx.h"
 
void CMenuDrawer::BeginUpdate( )
{
	static bool UpdateOnce		= false;
	if( UpdateOnce == false )
	{
		//Update or Register Objects once here.
		this->SelectedObject	= 0;
 
		UpdateOnce				= true;
	}
 
	if( (GetAsyncKeyState( VK_DOWN )&1) )
	{
		if( (this->SelectedObject < this->MenuObjectAmount - 1) )
			this->SelectedObject++;
		else if( (this->SelectedObject == this->MenuObjectAmount - 1) )
			this->SelectedObject = 0;
	}
	else if( (GetAsyncKeyState( VK_UP )&1) )
	{
		if( (this->SelectedObject > 0) )
			this->SelectedObject--;
		else if( (this->SelectedObject == 0) )
			this->SelectedObject = this->MenuObjectAmount - 1;
	}
}
void CMenuDrawer::EndUpdate( )
{
	this->MenuObjectAmount		= this->MenuObjects.size( );
	this->MenuObjects.clear( );
}
 
void CMenuDrawer::DrawMenu( )
{
	if( !this->MenuActive )
		return;
	this->BeginUpdate( );
//____________________________________________________________
//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯

	BorderSettings_t BorderSettings;

	//Menu 1
	this->AddMenuCategory( 60, 80, "Aimbot:" );
	this->AddMenuObject( 60, 80 + (25 * 1),		&Settings.Options.Aim_Aimbot->Value._bool,						"Auto Aim" );
	this->AddMenuObject( 60, 80 + (25 * 2),		&Settings.Options.Aim_AutoKnife->Value._bool,					"Auto Knife" );
	this->AddMenuObject( 60, 80 + (25 * 3),		&Settings.Options.Aim_AutoShoot->Value._bool,					"Auto Shoot" );
	this->AddMenuObject( 60, 80 + (25 * 4),		&Settings.Options.Aim_AutoZoom->Value._bool,					"Auto Zoom" );
	this->AddMenuObject( 60, 80 + (25 * 5),		&Settings.Options.Aim_ManualPrediction->Value._float, 0.10f,	"Manual Prediction" );
	this->AddMenuObject( 60, 80 + (25 * 6),		&Settings.Options.Aim_LimitFov->Value._int, 1,					"Limit Aim FOV" );

	this->AddMenuCategory( 60, 80 + (25 * 7), "Extra-Sensory Perception:" );
	this->AddMenuObject( 60, 80 + (25 * 8),		&Settings.Options.ESP_Name->Value._bool,						"Name" );
	this->AddMenuObject( 60, 80 + (25 * 9),		&Settings.Options.ESP_Distance->Value._bool,					"Distance" );
	this->AddMenuObject( 60, 80 + (25 * 10),	&Settings.Options.ESP_Weapon->Value._bool,						"Weapon" );
	this->AddMenuObject( 60, 80 + (25 * 11),	&Settings.Options.ESP_Box->Value._bool,							"Box" );
	this->AddMenuObject( 60, 80 + (25 * 12),	&Settings.Options.ESP_HeadBox->Value._bool,						"Head" );
	this->AddMenuObject( 60, 80 + (25 * 13),	&Settings.Options.ESP_Barrel->Value._bool,						"Barrel" );
	this->AddMenuObject( 60, 80 + (25 * 14),	&Settings.Options.ESP_Helicopter->Value._bool,					"Helicopter" );

	//Menu 2
	this->AddMenuCategory( 380, 80, "Miscellaneous:" );
	this->AddMenuObject( 380, 80 + (25 * 1),	&Settings.Options.Misc_NoRecoil->Value._bool,					"No Recoil" );
	this->AddMenuObject( 380, 80 + (25 * 2),	&Settings.Options.Misc_CrossHair->Value._bool,					"CrossHair" );
	this->AddMenuObject( 380, 80 + (25 * 3),	&Settings.Options.Misc_AutoShoot->Value._bool,					"AutoShoot" );
	this->AddMenuObject( 380, 80 + (25 * 4),	&Settings.Options.Misc_AutoVote->Value._bool,					"AutoVote" );
	this->AddMenuObject( 380, 80 + (25 * 5),	&Settings.Options.Misc_NameStealer->Value._bool,				"NameStealer" );

	this->AddMenuCategory( 380, 80 + (25 * 6), "Render:" );
	this->AddMenuObject( 380, 80 + (25 * 7),	&Settings.Options.Render_WeaponInfo->Value._bool,				"Weapon Info" );
	this->AddMenuObject( 380, 80 + (25 * 8),	&Settings.Options.Render_Radar->Value._bool,					"Radar" );
	this->AddMenuObject( 380, 80 + (25 * 9),	&Settings.Options.Render_FullBright->Value._bool,				"FullBright" );
	this->AddMenuObject( 380, 80 + (25 * 10),	&Settings.Options.Render_NoShellShock->Value._bool,				"No ShellShock" );

	this->AddMenuCategory( 380, 80 + (25 * 11), "General:" );
	this->AddMenuObject( 380, 80 + (25 * 12),	&Settings.Options.General_VisibleChecks->Value._bool,			"Visible Checks" );

	this->AddMenuCategory( 380, 80 + (25 * 13), "Beta Stages:" );
	this->AddMenuObject( 380, 80 + (25 * 14),	&Settings.Options.Beta_FixESPJump->Value._bool,					"Fix ESP Jumping" );

	this->AddMenuObject( 380, 80 + (25 * 16),	&Settings.Options.LoadSettings,									"Load Settings" );
	this->AddMenuObject( 380, 80 + (25 * 17),	&Settings.Options.SaveSettings,									"Save Settings" );

	static int MenuSize_1		= ( 30 + (14 * 25 + 25) );
	static int MenuSize_2		= ( 30 + (17 * 25 + 25) );
 
	this->SetBorderSettings( &BorderSettings, D3DColors::Green, D3DColors::Black, D3DColors::DarkGreen, true, true, true, true, 20 );
	this->DrawWindow( 50, 50, 310, MenuSize_1, &BorderSettings, &cdstl::Mathematics::Vector2( 11, 0 ), "ObsidianHook Menu" );

	this->SetBorderSettings( &BorderSettings, D3DColors::Green, D3DColors::Black, D3DColors::DarkGreen, true, true, true, true, 20 );
	this->DrawWindow( 370, 50, 310, MenuSize_2, &BorderSettings, &cdstl::Mathematics::Vector2( 11, 0 ), "ObsidianHook Menu" );

//____________________________________________________________
//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
	this->DrawMenuObjects( );
	this->DrawCursor( );
	this->EndUpdate( );
}
void CMenuDrawer::DrawCursor( )
{
	if( !this->isMouseMenu( ) )
		return;
 
	D3DRenderer.ShapeDrawer.SetDrawingColor( D3DCOLOR_RGBA(3, 6, 26, 215) );
	D3DRenderer.ShapeDrawer.DrawSolidSquare( this->CursorPositionX + 1, this->CursorPositionY, 1, 17 );
	for( int i = 0; i < 11; i++ )
	{
		D3DRenderer.ShapeDrawer.DrawSolidSquare( this->CursorPositionX + 2 + i, this->CursorPositionY + 1 + i, 1, 1 );
	}
	D3DRenderer.ShapeDrawer.DrawSolidSquare( this->CursorPositionX + 8, this->CursorPositionY + 12, 5, 1 );
	D3DRenderer.ShapeDrawer.DrawSolidSquare( this->CursorPositionX + 8, this->CursorPositionY + 13, 1, 1 );
	D3DRenderer.ShapeDrawer.DrawSolidSquare( this->CursorPositionX + 9, this->CursorPositionY + 14, 1, 2 );
	D3DRenderer.ShapeDrawer.DrawSolidSquare( this->CursorPositionX + 10, this->CursorPositionY +16, 1, 2 );
	D3DRenderer.ShapeDrawer.DrawSolidSquare( this->CursorPositionX + 8, this->CursorPositionY + 18, 2, 1 );
	D3DRenderer.ShapeDrawer.DrawSolidSquare( this->CursorPositionX + 7, this->CursorPositionY + 16, 1, 2 );
	D3DRenderer.ShapeDrawer.DrawSolidSquare( this->CursorPositionX + 6, this->CursorPositionY + 14, 1, 2 );
	D3DRenderer.ShapeDrawer.DrawSolidSquare( this->CursorPositionX + 5, this->CursorPositionY + 13, 1, 1 );
	D3DRenderer.ShapeDrawer.DrawSolidSquare( this->CursorPositionX + 4, this->CursorPositionY + 14, 1, 1 );
	D3DRenderer.ShapeDrawer.DrawSolidSquare( this->CursorPositionX + 3, this->CursorPositionY + 15, 1, 1 );
	D3DRenderer.ShapeDrawer.DrawSolidSquare( this->CursorPositionX + 2, this->CursorPositionY + 16, 1, 1 );
	for( int i = 0; i < 4; i++ )
	{
		D3DRenderer.ShapeDrawer.DrawSolidSquareEx( this->CursorPositionX + 2 + i, this->CursorPositionY + 2 + i, 1, 14 - (i * 2),
			D3DCOLOR_RGBA( 255 - (i * 4), 255 - (i * 4), 255 - (i * 4), 255 ) );
    }
	D3DRenderer.ShapeDrawer.DrawSolidSquareEx( this->CursorPositionX + 6, this->CursorPositionY + 6, 1, 8, D3DCOLOR_RGBA( 235, 235, 235, 255 ) );
	D3DRenderer.ShapeDrawer.DrawSolidSquareEx( this->CursorPositionX + 7, this->CursorPositionY + 7, 1, 9, D3DCOLOR_RGBA( 231, 231, 231, 255 ) );
	for( int i = 0; i < 4; i++ )
	{
		D3DRenderer.ShapeDrawer.DrawSolidSquareEx( this->CursorPositionX + 8 + i, this->CursorPositionY + 8 + i, 1, 4 - i,
			D3DCOLOR_RGBA( 227 - (i * 4), 227 - (i * 4), 227 - (i * 4), 255 ) );
	}
	D3DRenderer.ShapeDrawer.DrawSolidSquareEx( this->CursorPositionX + 8, this->CursorPositionY + 14, 1, 4, D3DCOLOR_RGBA( 207, 207, 207, 255 ) );
	D3DRenderer.ShapeDrawer.DrawSolidSquareEx( this->CursorPositionX + 9, this->CursorPositionY + 16, 1, 2, D3DCOLOR_RGBA( 203, 203, 203, 255 ) );
}
void CMenuDrawer::DrawMenuObjects( )
{
	BorderSettings_t BorderSettings;

	for( int i = 0; i < this->MenuObjects.size( ); i++ )
	{
		int						C_I				= this->MenuObjects[ i ].Index;
		float					C_X				= this->MenuObjects[ i ].X;
		float					C_Y				= this->MenuObjects[ i ].Y;
		bool			*		C_BS			= &(*this->MenuObjects[ i ].Object_State.bool_State);
		float			*		C_FS			= &(*this->MenuObjects[ i ].Object_State.float_State);
		int				*		C_IS			= &(*this->MenuObjects[ i ].Object_State.int_State);
		float					C_FD			= this->MenuObjects[ i ].Diffrence_Value.float_Value;
		float					C_ID			= this->MenuObjects[ i ].Diffrence_Value.int_Value;
		Menu_ObjectType			C_OT			= this->MenuObjects[ i ].Object_Type;
		std::string				C_S				= this->MenuObjects[ i ].Object_String;
 
		if( this->SelectedObject == C_I )
		{
			D3DRenderer.ShapeDrawer.SaveUsePrimitives( );
			D3DRenderer.ShapeDrawer.GetUsePrimitives( ) = true;
 
			D3DRenderer.ShapeDrawer.DrawSolidSquareEx( C_X - 5, C_Y - 5, 300, 23, D3DCOLOR_ARGB( 200, 255,141,66 ) );
 
			D3DRenderer.ShapeDrawer.RestoreUsePrimitives( );
		}
 
		if( C_OT == OBJECT_BOOL )
		{
			bool ClickState_1    = ( this->MouseMenu ?
									( MenuManager.IsCursorInsideSpace( C_X + 00, C_Y, 25, 15 ) && GetAsyncKeyState( VK_LBUTTON ) ) :
									( this->SelectedObject == C_I && GetAsyncKeyState( VK_LEFT )&1 ) );
			bool ClickState_2    = ( this->MouseMenu ?
									( MenuManager.IsCursorInsideSpace( C_X + 00, C_Y, 25, 15 ) && GetAsyncKeyState( VK_LBUTTON ) ) :
									( this->SelectedObject == C_I && GetAsyncKeyState( VK_RIGHT )&1 ) );
 
			if( ClickState_1 )
				(*C_BS) = false;
			else if( ClickState_2 )
				(*C_BS) = true;
 
			D3DRenderer.ShapeDrawer.DrawCheckBox( C_X, C_Y, (*C_BS), D3DColors::Easy_Grey, D3DColors::Easy_Green );
			D3DRenderer.TextWriter.DrawTextStringEx( C_X + 166, C_Y + 1, D3DRenderer.TextWriter.GetFontByName("Bold"), D3DColors::Black, C_S );
			D3DRenderer.TextWriter.DrawTextStringEx( C_X + 165, C_Y + 0, D3DRenderer.TextWriter.GetFontByName("Bold"), D3DColors::White, C_S );
		}
		else if( C_OT == OBJECT_FLOAT )
		{
			bool ClickState_1    = ( this->MouseMenu ?
									( MenuManager.IsCursorInsideSpace( C_X + 00, C_Y, 25, 15 ) && GetAsyncKeyState( VK_LBUTTON ) ) :
									( this->SelectedObject == C_I && GetAsyncKeyState( VK_LEFT )&1 ) );
			bool ClickState_2    = ( this->MouseMenu ?
									( MenuManager.IsCursorInsideSpace( C_X + 85, C_Y, 25, 15 ) && GetAsyncKeyState( VK_LBUTTON ) ) :
									( this->SelectedObject == C_I && GetAsyncKeyState( VK_RIGHT )&1 ) );
 
			if( ClickState_1 )
				(*C_FS) -= C_FD;
			else if( ClickState_2 )
				(*C_FS) += C_FD;
 
			this->SetBorderSettings( &BorderSettings, D3DColors::White, ( ( ClickState_1 ) ? D3DColors::Red : D3DColors::Green ), NULL, true, true, true, false, NULL );
			this->DrawBorder( C_X + 00, C_Y - 1, 25, 15, &BorderSettings );
			this->SetBorderSettings( &BorderSettings, D3DColors::White, ( ( ClickState_2 ) ? D3DColors::Red : D3DColors::Green ), NULL, true, true, true, false, NULL );
			this->DrawBorder( C_X + 85, C_Y - 1, 25, 15, &BorderSettings );
 
			D3DRenderer.TextWriter.DrawTextStringEx( C_X + 3.5, C_Y - 1, D3DRenderer.TextWriter.GetFontByName("Bold"), D3DColors::White, "<<" );
			D3DRenderer.TextWriter.DrawTextStringEx( C_X + 90, C_Y - 1, D3DRenderer.TextWriter.GetFontByName("Bold"), D3DColors::White, ">>" );
 
			D3DRenderer.TextWriter.DrawTextStringEx( C_X + 42, C_Y - 0, D3DRenderer.TextWriter.GetFontByName("Bold"), D3DColors::White, "%.2f", (*C_FS) );
 
			D3DRenderer.TextWriter.DrawTextStringEx( C_X + 166, C_Y + 1, D3DRenderer.TextWriter.GetFontByName("Bold"), D3DColors::Black, C_S );
			D3DRenderer.TextWriter.DrawTextStringEx( C_X + 165, C_Y + 0, D3DRenderer.TextWriter.GetFontByName("Bold"), D3DColors::White, C_S );
		}
		else if( C_OT == OBJECT_INT )
		{
			bool ClickState_1    = ( this->MouseMenu ?
									( MenuManager.IsCursorInsideSpace( C_X + 00, C_Y, 25, 15 ) && GetAsyncKeyState( VK_LBUTTON ) ) :
									( this->SelectedObject == C_I && GetAsyncKeyState( VK_LEFT )&1 ) );
			bool ClickState_2    = ( this->MouseMenu ?
									( MenuManager.IsCursorInsideSpace( C_X + 85, C_Y, 25, 15 ) && GetAsyncKeyState( VK_LBUTTON ) ) :
									( this->SelectedObject == C_I && GetAsyncKeyState( VK_RIGHT )&1 ) );
			if( ClickState_1 )
				(*C_IS) -= C_ID;
			else if( ClickState_2 )
				(*C_IS) += C_ID;
 
			this->SetBorderSettings( &BorderSettings, D3DColors::White, ( ( ClickState_1 ) ? D3DColors::Red : D3DColors::Green ), NULL, true, true, true, false, NULL );
			this->DrawBorder( C_X + 00, C_Y - 1, 25, 15, &BorderSettings );
			this->SetBorderSettings( &BorderSettings, D3DColors::White, ( ( ClickState_2 ) ? D3DColors::Red : D3DColors::Green ), NULL, true, true, true, false, NULL );
			this->DrawBorder( C_X + 85, C_Y - 1, 25, 15, &BorderSettings );
 
			D3DRenderer.TextWriter.DrawTextStringEx( C_X + 3.5, C_Y - 1, D3DRenderer.TextWriter.GetFontByName("Bold"), D3DColors::White, "<<" );
			D3DRenderer.TextWriter.DrawTextStringEx( C_X + 90, C_Y - 1, D3DRenderer.TextWriter.GetFontByName("Bold"), D3DColors::White, ">>" );
 
			D3DRenderer.TextWriter.DrawTextStringEx( C_X + 42, C_Y - 0, D3DRenderer.TextWriter.GetFontByName("Bold"), D3DColors::White, "%.1i", (*C_IS) );
 
			D3DRenderer.TextWriter.DrawTextStringEx( C_X + 166, C_Y + 1, D3DRenderer.TextWriter.GetFontByName("Bold"), D3DColors::Black, C_S );
			D3DRenderer.TextWriter.DrawTextStringEx( C_X + 165, C_Y + 0, D3DRenderer.TextWriter.GetFontByName("Bold"), D3DColors::White, C_S );
		}
		else if( C_OT == OBJECT_NONE )
		{
			D3DRenderer.TextWriter.DrawTextStringEx( C_X - 1, C_Y - 0, D3DRenderer.TextWriter.GetFontByName("Bold"), D3DColors::Black, C_S );
			D3DRenderer.TextWriter.DrawTextStringEx( C_X - 0, C_Y - 1, D3DRenderer.TextWriter.GetFontByName("Bold"), D3DColors::Black, C_S );
			D3DRenderer.TextWriter.DrawTextStringEx( C_X + 1, C_Y + 0, D3DRenderer.TextWriter.GetFontByName("Bold"), D3DColors::Black, C_S );
			D3DRenderer.TextWriter.DrawTextStringEx( C_X + 0, C_Y + 1, D3DRenderer.TextWriter.GetFontByName("Bold"), D3DColors::Black, C_S );
			D3DRenderer.TextWriter.DrawTextStringEx( C_X + 0, C_Y + 0, D3DRenderer.TextWriter.GetFontByName("Bold"), D3DColors::White, C_S );
		}
	}
}
 
void CMenuDrawer::DrawBorder( float X, float Y, float Width, float Height, BorderSettings_t *BorderSettings )
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
 
void CMenuDrawer::SetBorderSettings( BorderSettings_t *BorderSettings, DWORD MainColor, DWORD WindowFillColor, DWORD TopBoarderColor,
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
 
void CMenuDrawer::DrawWindow( float X, float Y, float Width, float Height, BorderSettings_t *BorderSettings, cdstl::Mathematics::Vector2 *TitleOffset, std::string Title )
{
	this->DrawBorder( X, Y, Width, Height, BorderSettings );
	D3DRenderer.TextWriter.DrawTextStringCenteredEx( X + Width / 2 + 1 - TitleOffset->Vec1, Y + 5 - TitleOffset->Vec2, D3DRenderer.TextWriter.GetFontByName("Normal"), D3DColors::Black, Title );
	D3DRenderer.TextWriter.DrawTextStringCenteredEx( X + Width / 2 + 0 - TitleOffset->Vec1, Y + 4 - TitleOffset->Vec2, D3DRenderer.TextWriter.GetFontByName("Normal"), D3DColors::White, Title );
}

void CMenuDrawer::AddMenuCategory( float X, float Y, std::string Object_String )
{
	Menu_Object		tempObject;

	tempObject.Index							= this->MenuObjects.size( );
	tempObject.X								= X;
	tempObject.Y								= Y;
	tempObject.Object_Type						= OBJECT_NONE;
	tempObject.Object_String					= Object_String;
 
	this->MenuObjects.push_back( tempObject );
}
void CMenuDrawer::AddMenuObject( float X, float Y, bool *Object_State, std::string Object_String )
{
	Menu_Object		tempObject;

	tempObject.Index							= this->MenuObjects.size( );
	tempObject.X								= X;
	tempObject.Y								= Y;
	tempObject.Object_State.bool_State			= Object_State;
	tempObject.Object_Type						= OBJECT_BOOL;
	tempObject.Object_String					= Object_String;
 
	this->MenuObjects.push_back( tempObject );
}
void CMenuDrawer::AddMenuObject( float X, float Y, float *Object_State, float DiffrenceValue, std::string Object_String )
{
	Menu_Object		tempObject;

	tempObject.Index							= this->MenuObjects.size( );
	tempObject.X								= X;
	tempObject.Y								= Y;
	tempObject.Object_State.float_State			= Object_State;
	tempObject.Diffrence_Value.float_Value		= DiffrenceValue;
	tempObject.Object_Type						= OBJECT_FLOAT;
	tempObject.Object_String					= Object_String;
 
	this->MenuObjects.push_back( tempObject );
}
void CMenuDrawer::AddMenuObject( float X, float Y, int *Object_State, int DiffrenceValue, std::string Object_String )
{
	Menu_Object		tempObject;

	tempObject.Index							= this->MenuObjects.size( );
	tempObject.X								= X;
	tempObject.Y								= Y;
	tempObject.Object_State.int_State			= Object_State;
	tempObject.Diffrence_Value.int_Value		= DiffrenceValue;
	tempObject.Object_Type						= OBJECT_INT;
	tempObject.Object_String					= Object_String;

	this->MenuObjects.push_back( tempObject );
}
 
float &CMenuDrawer::GetCursorPosition( bool X )
{
	if( X )
		return this->CursorPositionX;
 
	return this->CursorPositionY;
}
bool &CMenuDrawer::GetMenuActive( )
{
	return this->MenuActive;
}
bool &CMenuDrawer::isMouseMenu( )
{
	return this->MouseMenu;
}