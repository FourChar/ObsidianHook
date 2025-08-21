#include "stdafx.h"

namespace EngineFunctions
{
	void RenderScene( )
	{
		
	}
};

namespace SubGame
{
	int getLocalPlayerID( )
	{
		return Game.Structs.cg->clientNum;
	}
	clientInfo_t *getLocalPlayerClient( )
	{
		return ( clientInfo_t* )( 0x00839270 + (0x4CC * Game.Structs.cg->clientNum) );
	}
	centity_t *getLocalPlayerEntity( )
	{
		return ( centity_t* )( 0x0084F2D8 + (0x1DC * Game.Structs.cg->clientNum) );
	}

	clientInfo_t *getClientIndex( int Index )
	{
		return ( clientInfo_t* )( 0x00839270 + (0x4CC * Index) );
	}
	centity_t *getEntityIndex( int Index )
	{
		return ( centity_t* )( 0x0084F2D8 + (0x1DC * Index) );
	}
	weapon_t *getWeaponIndex( int Index )
	{
		return ( weapon_t* )( 0x00748658 + (0x44 * Index) );
	}
	weaponInfos_t *getWeaponInfoIndex( int Index )
	{
		return ( weaponInfos_t* )( *(DWORD*)( 0x00736DB8 + (Index * 4) ) );
	}
	helicopter_t *getHelicopterIndex( int Index )
	{
		return ( helicopter_t* )( 0x00742A40 + (0x001C * Index) );
	}

	bool isPlayerValid( int PlayerID )
	{
		if( Game.Structs.cg_entities[ PlayerID ].isAlive && \
			Game.Structs.cg_entities[ PlayerID ].currentValid && \
			Game.Structs.clientinfo[ PlayerID ].infoValid )
		{
			return true;
		}

		return false;
	}

	namespace SubMath
	{
		float *getPlayerViewDirection( float LineLength, float *PlayerAngle, float *PlayerLocation )
		{
			float	*ForwardDirection,
					*ReturnPosition; 
		     
			Math::AngleVectors( PlayerAngle, ForwardDirection, NULL, NULL );
			VectorCopy( PlayerLocation, ReturnPosition );

			ForwardDirection[2] = -ForwardDirection[2];
			ReturnPosition[0] += ( ForwardDirection[0] * LineLength );
			ReturnPosition[1] += ( ForwardDirection[1] * LineLength );
			ReturnPosition[2] += ( ForwardDirection[2] * LineLength );

			return ReturnPosition;
		}

		int getLocalAmmo( )
		{
			DWORD Weapon		= *(DWORD*)( 0x00736DB8 + ( Game.Structs.cg->snap->curWeapon * 4 ) );
			DWORD WeaponInfo	= *(DWORD*)( Weapon + 0x330 );
			return				  *(DWORD*)( (DWORD)Game.Structs.cg->snap + 0x368 + ( WeaponInfo * 4 ) );
		}

		int GetPlayerTag( WORD TagName, centity_t *Entity, PFLOAT Origin )
		{
			int iReturn		= NULL;
			__asm
			{
				PUSH	Origin
				MOVZX	ESI, TagName
				MOV		ECX, Entity
				MOVZX	EAX, BYTE PTR [ECX+4]
				MOV		EDI, 0x004024B0
				CALL	EDI
				ADD		ESP, 4
				MOV		iReturn, EAX
			}
			return iReturn;
		}

		WORD RegisterTag( char* TagName )
		{
			return ( ( WORD (*)( const char *, int, size_t, int ) )0x004024B0 )( TagName, 1, strlen( TagName ) + 1, 6 );
		}

		namespace SubTrace
		{
			float	*	TraceMin			= ( float* )0x0070B7D0; 
			float		vec3_origin[3]		= { 0, 0, 0 };

			bool IsVisible( float *CheckingPoint, bool forAimbot )
			{
				trace_t t;

				DWORD	Mask				= 0x00803003;
				if( !forAimbot )
				{
					Mask					= 0x02806831;
				}

				(( void (__cdecl *)(trace_t *, const Vector3, const Vector3, const Vector3, const Vector3, int, DWORD, int, int ) )0x0045A230) \
					( &t, Game.Structs.refdef->Vieworg, TraceMin, vec3_origin, CheckingPoint, SubGame::getLocalPlayerID( ), Mask, 1, 1 );

				return( t.Fraction >= 0.89f );
			}

			void GetTraceHitLocation( float *StartingPoint, float *CheckingPoint, int SkipID, DWORD Mask, Vector3 &ReturnHitLocation )
			{
				trace_t		t;

				(( void (__cdecl *)(trace_t *, const Vector3, const Vector3, const Vector3, const Vector3, int, DWORD, int, int ) )0x0045A230) \
					( &t, StartingPoint, TraceMin, vec3_origin, CheckingPoint, SkipID, Mask, 1, 1 );

				ReturnHitLocation[0]	= StartingPoint[0] + ( ( CheckingPoint[0] - StartingPoint[0] ) * t.Fraction );
				ReturnHitLocation[1]	= StartingPoint[1] + ( ( CheckingPoint[1] - StartingPoint[1] ) * t.Fraction );
				ReturnHitLocation[2]	= StartingPoint[2] + ( ( CheckingPoint[2] - StartingPoint[2] ) * t.Fraction );
			}
		};
	};

	namespace SubDrawing
	{
		float *D3DColor_To_FloatColor( DWORD D3DColor )
		{
			float	*Return;

			Return[0]		= D3DColor & 0xFF; D3DColor >>= 8;
			Return[1]		= D3DColor & 0xFF; D3DColor >>= 8;
			Return[2]		= D3DColor & 0xFF; D3DColor >>= 8;
			Return[3]		= D3DColor & 0xFF;

			return Return;
		}
	};
};

void CGame::SetOffsets( )
{
	this->ViewAngleX				= ( float * )			0x00C84FDC;
	this->ViewAngleY				= ( float * )			0x00C84FD8;
	this->PlayerState				= ( DWORD * )			0x00794560;

	this->Structs.cg				= ( cg_t* )				0x0074E338;
	this->Structs.cgs				= ( cgs_t* )			0x0074A908;
	this->Structs.cg_entities		= ( centity_t* )		0x0084F2D8;
	this->Structs.clientinfo		= ( clientInfo_t* )		0x00839270;
	this->Structs.refdef			= ( refdef_t* )			0x00797600;
	this->Structs.Predict			= ( Prediction_t* )		0x0084F2D8;
	this->Structs.viewmatrix		= ( viewMatrix_t* )		0x0079E700;
	this->Structs.Renderer			= ( d3dRenderer_t* )	0x0CC9A404;
	this->Structs.ShellShock		= ( shock_t* )			0x00732658;
}

DWORD CGame::GetLocalState( )
{
	return *this->PlayerState;
}

void CGame::UpdateAll( )
{
	this->AllBones.PlayerBones.Helmet			= *( WORD *)0x001406E96;
	this->AllBones.PlayerBones.Head				= *( WORD *)0x001406E98;
	this->AllBones.PlayerBones.Neck				= *( WORD *)0x001406FC6;
	this->AllBones.PlayerBones.Spine4			= *( WORD *)0x001406E94;
	this->AllBones.PlayerBones.Pelvis			= *( WORD *)0x001406FC8;

	this->AllBones.EntityBones.Smoke			= *( WORD *)0x001406F62;
	this->AllBones.EntityBones.Flash			= *( WORD *)0x001406F60;
	this->AllBones.EntityBones.Flashbang		= *( WORD *)0x001406F5E;
	this->AllBones.EntityBones.Grenade			= *( WORD *)0x001406ECE;

	if( this->Structs.cg->snap )
	{
		//FullBright
		static bool FullBright_Switch		= false;
		if( !Settings.Options.Render_FullBright->Value._bool && FullBright_Switch )
		{
			DWORD DeactivateFullBright		= 0x0063326C;
            __asm CALL DeactivateFullBright

			FullBright_Switch = false;
		}
		else if( Settings.Options.Render_FullBright->Value._bool && !FullBright_Switch )
		{
			DWORD ActivateFullBright		= 0x0063325B;
            __asm CALL ActivateFullBright

			FullBright_Switch = true;
		}

		//ShellShock
		static float OriginalShellShock_1		= *( float * )0x007276D0;
		static float OriginalShellShock_2		= *( float * )0x007276D4;
		static float OriginalShellShock_3		= *( float * )0x007276D8;
		static float OriginalShellShock_4		= *( float * )0x007276DC;
		if( Settings.Options.Render_NoShellShock->Value._bool )
		{
			*( float * )0x007276D0 = 0.0f;
			*( float * )0x007276D4 = 0.0f;
			*( float * )0x007276D8 = 0.0f;
			*( float * )0x007276DC = 0.0f;
		}
		else
		{
			*( float * )0x007276D0 = OriginalShellShock_1;
			*( float * )0x007276D4 = OriginalShellShock_2;
			*( float * )0x007276D8 = OriginalShellShock_3;
			*( float * )0x007276DC = OriginalShellShock_4;
		}
	}
}

void CGame::DrawHelicopterESP( )
{
	if( !Settings.Options.ESP_Helicopter->Value._bool )
		return;

	float	ScreenX,
			ScreenY;
	for( int i = 0; i < 8; i++ )
	{
		helicopter_t	*		Helicopter	= SubGame::getHelicopterIndex( i );
		centity_t		*		Entity		= SubGame::getEntityIndex( Helicopter->EntityNum );

		if( !Entity->isAlive )
			continue;
		if( Entity->eType != ET_HELICOPTER )
			continue;
		if( Entity->isAlive != 257 || !Entity->currentValid )
			continue;

		float Distance	= Math::GetDistance( Structs.refdef->Vieworg, Entity->lerpOrigin ) / 48;
		DWORD UrColor	= D3DColors::Cyan;

		if( Helicopter->Team != SubGame::getLocalPlayerClient( )->Team || Helicopter->Team == TEAM_FFA )
		{
			UrColor		= ( Settings.Options.General_VisibleChecks->Value._bool ? ( SubGame::SubMath::SubTrace::IsVisible( Entity->lerpOrigin, true ) ? D3DColors::Easy_Yellow : D3DColors::Easy_Red ) : D3DColors::Easy_Red );
		}
		else
		{
			UrColor		= ( Settings.Options.General_VisibleChecks->Value._bool ? ( SubGame::SubMath::SubTrace::IsVisible( Entity->lerpOrigin, true ) ? D3DColors::Cyan : D3DColors::Easy_Blue ) : D3DColors::Easy_Blue );
		}

		if( Math::WorldToScreen( Entity->lerpOrigin, &ScreenX, &ScreenY ) )
		{
			D3DRenderer.ESPDrawer.DrawPlayerText( ScreenX, ScreenY, true, UrColor, "Helicopter" );
			D3DRenderer.ESPDrawer.DrawPlayerText( ScreenX, ScreenY + 15, true, UrColor, "%.2f", Distance );
		}
    }
}

/*void CGame::DrawEntityESP( )
{
	float	ScreenX,
			ScreenY;
	for( int i = 64; i < MAX_GENTITIES; i++ )
	{
		centity_t		*		Entity		= SubGame::getEntityIndex( i );
		weapon_t		*		Weapon		= Math::GetWeaponIndex( Entity->weapon );

		if( (Entity->currentValid == 1) && Entity->eType == ET_MISSILE )
		{
			DWORD GColor = ( Settings.Options.General_VisibleChecks->Value._bool ? ( SubGame::SubMath::SubTrace::IsVisible( Entity->lerpOrigin, true ) ? D3DColors::Pink : D3DColors::Easy_Pink ) : D3DColors::Easy_Pink );
					
			if( Math::WorldToScreen( Entity->lerpOrigin, &ScreenX, &ScreenY ) )
			{
				D3DRenderer.ESPDrawer.DrawPlayerText( ScreenX, ScreenY, false, GColor, "%s", Weapon->Name );
			}
		}
    }
}*/

void CGame::DrawPlayerESP( )
{
	if( !(Settings.Options.ESP_Name->Value._bool) && \
		!(Settings.Options.ESP_Distance->Value._bool) && \
		!(Settings.Options.ESP_Box->Value._bool) && \
		!(Settings.Options.ESP_HeadBox->Value._bool) && \
		!(Settings.Options.ESP_Barrel->Value._bool) )
		return;

	D3DRenderer.ShapeDrawer.SaveUsePrimitives( );
	D3DRenderer.ShapeDrawer.GetUsePrimitives( ) = true;

	for( int i = 0; i < this->Structs.cgs->maxclients; i++ )
	{
		centity_t		*	Entity			= SubGame::getEntityIndex( i );
		clientInfo_t	*	Player			= SubGame::getClientIndex( i );
		weapon_t		*	pWeapon			= SubGame::getWeaponIndex( Entity->weapon );
		
		if( !SubGame::isPlayerValid( i ) )
			continue;

		DWORD				DrawingColor;
		Vector3				HeadOrigin;
		VectorCopy( Entity->lerpOrigin, HeadOrigin );

		if( Entity->eFlags & FLAGS_PRONE || Entity->eFlags & FLAGS_PRONE_FORWARD || Entity->eFlags & FLAGS_PRONE_BACKWARD )
			HeadOrigin[ 2 ]		+= 20;
		else if( Entity->eFlags & FLAGS_CROUCH || Entity->eFlags & FLAGS_CROUCH_FORWARD || Entity->eFlags & FLAGS_CROUCH_BACKWARD )
			HeadOrigin[ 2 ]		+= 40;
		else
			HeadOrigin[ 2 ]		+= 55;

		float FootX, FootY, HeadX, HeadY;
		if( !Math::WorldToScreen( HeadOrigin, &HeadX, &HeadY ) )
			continue;
		if( !Math::WorldToScreen( Entity->lerpOrigin, &FootX, &FootY ) )
			continue;

		bool isVisible				= SubGame::SubMath::SubTrace::IsVisible( HeadOrigin, true );
		float Distance				= Math::GetDistance( Entity->lerpOrigin, Game.Structs.refdef->Vieworg );
		float BoxLength				= ((FootY+10) - HeadY);
		float BoxWidth				= (BoxLength/2.2);
		float BoxFlow				= (HeadX - (BoxWidth/2));
		if(BoxWidth > 240)			BoxWidth = 240;
		if(BoxLength > 518)			BoxLength = 518;

		if( !IsFriend( i ) || Player->Team == TEAM_FFA )
		{
			DrawingColor			= ( Settings.Options.General_VisibleChecks->Value._bool ? ( isVisible ? D3DColors::Easy_Yellow : D3DColors::Easy_Red ) : D3DColors::Easy_Red );
		}
		else if( !( Player->Team == TEAM_FFA || Player->Team != this->Structs.clientinfo[ Structs.cg->clientNum ].Team ) )
		{
			DrawingColor			= ( Settings.Options.General_VisibleChecks->Value._bool ? ( isVisible ? D3DColors::LightPink : D3DColors::Easy_Pink ) : D3DColors::Easy_Pink );
		}

		if( Settings.Options.ESP_HeadBox->Value._bool )			// Head Box
		{
			D3DRenderer.ShapeDrawer.DrawBorderSquareEx( HeadX - 2.5, HeadY - 5, 5, 5, 1, DrawingColor );
		}
		if( Settings.Options.ESP_Barrel->Value._bool )			// Barrel
		{
			D3DRenderer.ShapeDrawer.DrawLine( D3DRenderer.GetViewPort( ).Width/2, D3DRenderer.GetViewPort( ).Height, FootX, FootY, DrawingColor );
		}
		if( Settings.Options.ESP_Box->Value._bool )				// Box
		{
			D3DRenderer.ESPDrawer.DrawPlayerSquare( BoxFlow, FootY - BoxLength, BoxWidth, BoxLength, DrawingColor );
		}
		if( Settings.Options.ESP_Name->Value._bool )			// Name
		{
			D3DRenderer.ESPDrawer.DrawPlayerText( BoxFlow + BoxWidth + 3, FootY - BoxLength, false, DrawingColor, "%s", Player->Name );
		}
		if( Settings.Options.ESP_Distance->Value._bool )		// Distance
		{
			D3DRenderer.ESPDrawer.DrawPlayerText( BoxFlow + BoxWidth + 3, FootY - BoxLength + 15, false, DrawingColor, "%.2f", Distance / 42.0f );
		}
		if( Settings.Options.ESP_Weapon->Value._bool )			// Weapon
		{
			D3DRenderer.ESPDrawer.DrawPlayerText( BoxFlow + BoxWidth + 3, FootY - BoxLength + 30, false, DrawingColor, "%s", pWeapon->Name );
		}
	}
	D3DRenderer.ShapeDrawer.RestoreUsePrimitives( );
}

void CGame::DrawLocalWeaponInfo( )
{
	if( !Settings.Options.Render_WeaponInfo->Value._bool )
		return;

	static float xpos, ypos, width, height;
	static bool WeaponPlaced = false;

	if( !WeaponPlaced )
	{
		width		= 213;
		height		= 65;
		xpos		= 15;
		ypos		= D3DRenderer.GetViewPort( ).Height - 85;
		WeaponPlaced = true;
	}

	BorderSettings_t BorderSettings;
	MenuManager.MenuDrawer.SetBorderSettings( &BorderSettings, D3DColors::Green, D3DColors::Black, D3DColors::DarkGreen, true, true, true, true, 20 );
	MenuManager.MenuDrawer.DrawWindow( xpos, ypos, width, height, &BorderSettings, &cdstl::Mathematics::Vector2( 7.5, 0 ), "Weapon Info" );

	//------------------------------------------------------------------

	weapon_t*	Weapon		= Math::GetWeaponIndex( Game.Structs.cg->snap->curWeapon );
	char* WeaponName		= NULL;
	if(Weapon->Name == NULL)
		WeaponName = "None";
	else
		WeaponName = Weapon->Name;

	D3DRenderer.TextWriter.DrawTextStringEx( xpos + 14, ypos + 26, D3DRenderer.TextWriter.GetFontByName("Normal"), D3DColors::Black, "Current Ammo:" );
	D3DRenderer.TextWriter.DrawTextStringEx( xpos + 13, ypos + 25, D3DRenderer.TextWriter.GetFontByName("Normal"), D3DColors::White, "Current Ammo:" );
	D3DRenderer.TextWriter.DrawTextStringEx( xpos + 14, ypos + 41, D3DRenderer.TextWriter.GetFontByName("Normal"), D3DColors::Black, "Current Weapon:" );
	D3DRenderer.TextWriter.DrawTextStringEx( xpos + 13, ypos + 40, D3DRenderer.TextWriter.GetFontByName("Normal"), D3DColors::White, "Current Weapon:" );

	D3DRenderer.TextWriter.DrawTextStringEx( xpos + 113, ypos + 25, D3DRenderer.TextWriter.GetFontByName("Bold"), D3DColors::Red, "%i", SubGame::SubMath::getLocalAmmo( ) );
	D3DRenderer.TextWriter.DrawTextStringEx( xpos + 127, ypos + 40, D3DRenderer.TextWriter.GetFontByName("Bold"), D3DColors::Red, "%s", WeaponName );
}

void CGame::DrawRadar( )
{
	if( !Settings.Options.Render_Radar->Value._bool )
		return;

	static float xpos, ypos, width, height;
	static bool RadarPlaced = false;

	if( !RadarPlaced )
	{
		width		= 175.0f;
		height		= 175.0f;
		xpos		= D3DRenderer.GetViewPort( ).Width - width - 20;
		ypos		= 41;
		RadarPlaced = true;
	}

	D3DRenderer.ShapeDrawer.SaveUsePrimitives( );
	D3DRenderer.ShapeDrawer.GetUsePrimitives( ) = true;

	BorderSettings_t BorderSettings;
	MenuManager.MenuDrawer.SetBorderSettings( &BorderSettings, D3DColors::Green, D3DColors::Black, D3DColors::DarkGreen, true, true, true, true, 20 );
	MenuManager.MenuDrawer.DrawWindow( xpos - 5, ypos - 23, width + 5, height + 23, &BorderSettings, &cdstl::Mathematics::Vector2( 3, 0 ), "Radar" );

	float 	ScreenX,
			ScreenY;
	for( int i = 0; i < this->Structs.cgs->maxclients; i++ )
	{
		centity_t		*	Entity			= SubGame::getEntityIndex( i );
		clientInfo_t	*	Player			= SubGame::getClientIndex( i );
		
		if( !SubGame::isPlayerValid( i ) )
			continue;

		DWORD DrawingColor;
		bool isVisible				= SubGame::SubMath::SubTrace::IsVisible( Entity->lerpOrigin, true );
		if( !IsFriend( i ) || Player->Team == TEAM_FFA )
		{
			DrawingColor			= ( Settings.Options.General_VisibleChecks->Value._bool ? ( isVisible ? D3DColors::Easy_Yellow : D3DColors::Easy_Red ) : D3DColors::Easy_Red );
		}
		else if( !( Player->Team == TEAM_FFA || Player->Team != this->Structs.clientinfo[ Structs.cg->clientNum ].Team ) )
		{
			DrawingColor			= ( Settings.Options.General_VisibleChecks->Value._bool ? ( isVisible ? D3DColors::LightPink : D3DColors::Easy_Pink ) : D3DColors::Easy_Pink );
		}

		if( Math::GetRadarPoint( Entity->lerpOrigin, ScreenX, ScreenY, width, xpos, ypos ) )
		{
			D3DRenderer.ShapeDrawer.DrawSolidSquareEx( ScreenX - 2, ScreenY - 2, 4, 4, DrawingColor );
			D3DRenderer.ShapeDrawer.DrawBorderSquareEx( ScreenX - 3, ScreenY - 3, 5, 5, 1, D3DColors::Black );
		}
	}
	D3DRenderer.ShapeDrawer.RestoreUsePrimitives( );
}

void CGame::DoAimbot( )
{
	if( !Settings.Options.Aim_Aimbot->Value._bool )
		return;

	if( this->Aim( ) )
	{
		if( Settings.Options.Aim_AutoShoot->Value._bool )
			this->AutoShoot( true );

		if( Settings.Options.Aim_AutoZoom->Value._bool )
			this->AutoZoom( true );
	}
	else
	{
		if( Settings.Options.Aim_AutoShoot->Value._bool )
			this->AutoShoot( false );

		if( Settings.Options.Aim_AutoZoom->Value._bool )
			this->AutoZoom( false );
	}
}
bool CGame::Aim( )
{
	if( !Settings.Options.Aim_Aimbot->Value._bool )
		return false;

	for( int i=0; i < this->Structs.cgs->maxclients; i++ )
	{
		centity_t		*	Entity			= SubGame::getEntityIndex( i );
		clientInfo_t	*	Player			= SubGame::getClientIndex( i );

		if( i == this->Structs.cg->clientNum )
			continue;

		if( !Player->infoValid || !Entity->currentValid || !Entity->isAlive )
			continue;

		if( !this->GameAim.CheckAimState( *this->PlayerState ) )
			continue;

		if( SubGame::SubMath::getLocalAmmo( ) <= 0 )
			continue;

		if( IsFriend( i ) )
			continue;

		Vector3 AimPoint, Aimangles, Velocity;

		if( !SubGame::SubMath::GetPlayerTag( this->AllBones.PlayerBones.Head, Entity, AimPoint ) )
			continue;

	//----------------- Prediction Start -----------------//
		VectorSubtract( Entity->oldOrigin, Entity->newOrigin, Velocity );
		VectorMA( AimPoint, 0.20f, Velocity, AimPoint );

		if( Settings.Options.Aim_ManualPrediction->Value._float )
		{
			VectorMA( AimPoint, Settings.Options.Aim_ManualPrediction->Value._float, Velocity, AimPoint );
		}
	//------------------ Prediction End ------------------//

		if( !SubGame::SubMath::SubTrace::IsVisible( AimPoint, true ) )
			continue;

		Math::GetOrigin( AimPoint, Aimangles );

		if( !GameAim.IsInFov( Aimangles, Settings.Options.Aim_LimitFov->Value._int ) )
			continue;

		if( Settings.Options.Aim_AutoKnife->Value._bool )
		{
			if( (Math::GetDistance( Entity->lerpOrigin, Game.Structs.refdef->Vieworg ) / 36.0f) <= 3.2f )
			{
				(( void (__cdecl *) ( int, int, char * ) )0x004F9AB0)( 0, 0, "+melee" );
				(( void (__cdecl *) ( int, int, char * ) )0x004F9AB0)( 0, 0, "-melee" );
			}
		}

		*(float *)0x00C84FD8					+= Aimangles[ 0 ];	//PITCH = 0
		*(float *)0x00C84FDC					+= Aimangles[ 1 ];	//YAW = 1

		return true;
	}

	return false;
}

void CGame::AutoZoom( bool Toggle )
{
	static bool bSighted = false;

	if( Toggle )
	{
		(( void (__cdecl *) ( int, int, char * ) )0x004F9AB0)( 0, 0, "+speed" );
		bSighted = true;
	}
	else if( bSighted )
	{
		(( void (__cdecl *) ( int, int, char * ) )0x004F9AB0)( 0, 0, "-speed" );
		bSighted = false;
	}
}

int iCount, iBurst = 1;
void CGame::AutoShoot( bool Toggle )
{
	if( Toggle )
    {
        if ( iCount != iBurst )
        {
            (( void (__cdecl *) ( int, int, char * ) )0x004F9AB0)( 0, 0, "+attack" );
			(( void (__cdecl *) ( int, int, char * ) )0x004F9AB0)( 0, 0, "-attack" );
            iCount++;
        }
        else
			iCount = 0;
    } 
}

void CGame::AutoWeapons( )
{
	if( !Settings.Options.Misc_AutoShoot->Value._bool )
		return;
	if( !MenuManager.IsCursorInCorrectWindow( ) )
		return;
	if( MenuManager.MenuDrawer.GetMenuActive( ) )
		return;

	static int isFiring = 0;
    if( isFiring )
    {
        isFiring = 0;
        (( void (__cdecl *) ( int, int, char * ) )0x004F9AB0)( 0, 0, "-attack" );
    }
    else if( GetAsyncKeyState( VK_LBUTTON ) && !isFiring )
    {
        isFiring = 1;
        (( void (__cdecl *) ( int, int, char * ) )0x004F9AB0)( 0, 0, "+attack" );
    }
}

void CGame::ZeroRecoil( )
{
	if( !Settings.Options.Misc_NoRecoil->Value._bool )
		return;

	memset( this->Structs.viewmatrix->Recoil, 0, 12 );		// No Recoil
}

void CGame::AutoVote( )
{
	if( !Settings.Options.Misc_AutoVote->Value._bool )
		return;

	int					isVoteActive		= *(int*)0x00C6291E;
	BYTE				isVoteAllowed		= *(BYTE*)(0x00115D0F0 + 12);
	static DWORD		LastTime			= NULL;
	int					clientNum			= -1;
	clientInfo_t	*	pInfo;
	char				Namez[256];

	if( ( isVoteActive == 0 ) )
	{

		DWORD		CurrentTime			= GetCurrentTime( );
		if( (CurrentTime - LastTime) > 1000 )
		{
			clientNum					= ( rand( ) % this->Structs.cgs->maxclients );
			pInfo						= SubGame::getClientIndex( clientNum );
			
			if( ( pInfo->infoValid ) && \
				( SubGame::getLocalPlayerID( ) != clientNum ) )
			{
				sprintf( Namez, "callvote kick \"%s\"\n", pInfo->Name );
				(( void (__cdecl *) ( int, int, char * ) )0x004F9AB0)( 0, 0, Namez );

				LastTime					= CurrentTime;
			}
		}
	}
}

void CGame::NameStealer( )
{
	if( !Settings.Options.Misc_NameStealer->Value._bool )
		return;

	static DWORD		LastTime			= NULL;
	int					clientNum			= -1;
	DWORD				CurrentTime			= GetCurrentTime( );
	clientInfo_t	*	pInfo;
	char				Namez[256];

	if( (CurrentTime - LastTime) > 1000 )
	{
		clientNum				= ( rand( ) % this->Structs.cgs->maxclients );
		pInfo					= SubGame::getClientIndex( clientNum );

		if( ( pInfo->infoValid ) && \
			( SubGame::getLocalPlayerID( ) != clientNum ) )
		{
			sprintf( Namez, "set name %s", pInfo->Name );
			(( void (__cdecl *) ( int, int, char * ) )0x004F9AB0)( 0, 0, Namez );

			LastTime					= CurrentTime;
		}
	}
}