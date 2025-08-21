#include "stdafx.h"

char *AimTags[] =
{
	"j_head",
	"neck",
	"j_clavicle_ri",
	"j_clavicle_le",
	"j_shoulder_le",
	"j_shoulder_ri",
	"j_elbow_le",
	"j_elbow_ri",
	"j_wrist_le",
	"j_wrist_ri",
	"j_mainroot",
	"j_spineupper",
	"j_spinelower",
	"j_spine4",
	"j_hip_le",
	"j_hip_ri",
	"j_knee_ri",
	"j_knee_le",
	"j_ankle_ri",
	"j_ankle_le",
	"j_ball_ri",
	"j_ball_le",
};

bool CGameAim::CheckAimState( DWORD localState ) 
{ 
    switch( localState )
    {
    case 1:			//Weapons Switch
    case 4:			//Going Something
    case 7:			//Reloading
    case 16:		//Throwing Grenade
    case 18:		//Throwing Grenade
    case 19:		//Throwing Grenade
    case 20:		//Throwing Grenade
    case 21:		//Throwing C4
    case 22:		//Sprinting
    case 23:		//Sprinting
        return false;
    }

    return true;
}

bool CGameAim::IsInFov( float *Angles, float Fov )
{
	if( Angles[ 2 ] < Fov && \
		Angles[ 2 ] > -(Fov) )
		return true;

	return false;
}

bool CGameAim::GetVisibleBone( centity_t *Entity, float *AimingPoint )
{
	static WORD LoadedTags[ sizeof( AimTags ) ];
	static bool LoadTags = false;
	if( LoadTags == false )
	{
		for( int BoneCount = 0; BoneCount < ( sizeof( AimTags ) / sizeof( char * ) ); BoneCount++ )
		{
			char	*	TagName		= AimTags[ BoneCount ];

			LoadedTags[ BoneCount ]	= SubGame::SubMath::RegisterTag( TagName );
		}

		LoadTags = true;
	}

	for( int BoneCount = 0; BoneCount < ( sizeof( AimTags ) / sizeof( char * ) ); BoneCount++ )
	{
		if( !SubGame::SubMath::GetPlayerTag( LoadedTags[ BoneCount ], Entity, AimingPoint ) )
			return false;

		if( SubGame::SubMath::SubTrace::IsVisible( AimingPoint, true ) )
			return true;
	}
	
	return false;
}