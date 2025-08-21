#pragma once

typedef struct
{
	cg_t				*			cg;
	cgs_t				*			cgs;
	centity_t			*			cg_entities;
	clientInfo_t		*			clientinfo;
	refdef_t			*			refdef;
	Prediction_t		*			Predict;
	viewMatrix_t		*			viewmatrix;
	d3dRenderer_t		*			Renderer;
	shock_t				*			ShellShock;
} CallOfDuty_Structs;

namespace EngineFunctions
{
	void							RenderScene									( );
	void							SRC_Unknown									( );
	void							CG_Init										( );
};

namespace SubGame
{
	int								getLocalPlayerID							( );
	clientInfo_t		*			getLocalPlayerClient						( );
	centity_t			*			getLocalPlayerEntity						( );

	clientInfo_t		*			getClientIndex								( int Index );
	centity_t			*			getEntityIndex								( int Index );
	weaponInfos_t		*			getWeaponInfoIndex							( int Index );
	helicopter_t		*			getHelicopterIndex							( int Index );

	bool							isPlayerValid								( int PlayerID );

	namespace SubMath
	{
		float			*			getPlayerViewDirection						( float LineLength, float *PlayerAngle, float *PlayerLocation );
		int							getLocalAmmo								( );
		int							GetPlayerTag								( WORD TagName, centity_t *Entity, float *Origin );
		WORD						RegisterTag									( char* TagName );

		namespace SubTrace
		{
			bool					IsVisible									( float *CheckingPoint, bool forAimbot );
			void					GetTraceHitLocation							( float *StartingPoint, float *CheckingPoint, int SkipID, DWORD Mask, Vector3 &ReturnHitLocation );
		};
	};
	namespace SubDrawing
	{
		float			*			D3DColor_To_FloatColor						( DWORD D3DColor );
	};
};

class CGame
{
public:
	void							SetOffsets									( );
	DWORD							GetLocalState								( );
	void							UpdateAll									( );

	void							DrawPlayerESP								( );
	void							DrawEntityESP								( );
	void							DrawHelicopterESP							( );
	void							DrawLocalWeaponInfo							( );
	void							DrawRadar									( );

	void							DoAimbot									( );
	bool							Aim											( );

	void							AutoWeapons									( );
	void							ZeroRecoil									( );
	void							NameStealer									( );
	void							AutoVote									( );

	CallOfDuty_Structs				Structs;
	CGameAim						GameAim;
	CAllBones						AllBones;
private:
	float				*			ViewAngleX;
	float				*			ViewAngleY;
	DWORD				*			PlayerState;

	void							AutoZoom									( bool Toggle );
	void							AutoShoot									( bool Toggle );
};
extern CGame Game;