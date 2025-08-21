#include "stdafx.h"

namespace Math
{
	void AngleVectors(float *angles, float *forward, float *right, float *up)
	{
		float			angle;
		static float	sr, sp, sy, cr, cp, cy;
		
		angle = radian(angles[0]);
		sp= sin(angle);
		cp= cos(angle);
		
		angle = radian(angles[1]);
		sy = sin(angle);
		cy = cos(angle);
		
		angle = radian(angles[2]);
		sr = sin(angle);
		cr = cos(angle);
		
		if (forward)
		{
			forward[0] = cp*cy;
			forward[1] = cp*sy;
			forward[2] = -sp;
		}
		if (right)
		{
			right[0] = (-1*sr*sp*cy+-1*cr*-sy);
			right[1] = (-1*sr*sp*sy+-1*cr*cy);
			right[2] = -1*sr*cp;
		}
		if (up)
		{
			up[0] = (cr*sp*cy+-sr*-sy);
			up[1] = (cr*sp*sy+-sr*cy);
			up[2] = cr*cp;
		}
	}

	//---------------------------------------------------

	float AngleNormalize360 ( float angle ) 
	{
		return ((float)(360.0 / 65536) * ((int)(angle * (65536 / 360.0)) & 65535));
	}

	//---------------------------------------------------

	float AngleNormalize180 ( float angle ) 
	{
		angle = AngleNormalize360( angle );
		if( angle > 180.0 )
		{
			angle -= 360.0;
		}
		return angle;
	}

	//---------------------------------------------------

	bool WorldToScreen( Vector3 WorldLocation, float *ScreenX, float *ScreenY )
	{
		int ScreenCenterX = D3DRenderer.GetViewPort( ).Width / 2;
		int ScreenCenterY = D3DRenderer.GetViewPort( ).Height / 2;

		D3DXVECTOR3 Local;
		D3DXVECTOR3 TransForm;
		D3DXVECTOR3 Right			= Game.Structs.refdef->Viewaxis[1];
		D3DXVECTOR3 Up				= Game.Structs.refdef->Viewaxis[2];
		D3DXVECTOR3 Forward			= Game.Structs.refdef->Viewaxis[0];

		VectorSubtract( WorldLocation, Game.Structs.refdef->Vieworg, Local );
		            
		TransForm[0]				= ( Local[0] * Right[0] + Local[1] * Right[1] + Local[2] * Right[2] );
		TransForm[1]				= ( Local[0] * Up[0] + Local[1] * Up[1] + Local[2] * Up[2] );
		TransForm[2]				= ( Local[0] * Forward[0] + Local[1] * Forward[1] + Local[2] * Forward[2] );

		if( TransForm.z < 0.01 )
			return 0;

		if( ScreenX && ScreenY )
		{
			*ScreenX = ScreenCenterX * ( 1 - ( TransForm.x / Game.Structs.refdef->Fovx / TransForm.z ) );
			*ScreenY = ScreenCenterY * ( 1 - ( TransForm.y / Game.Structs.refdef->Fovy / TransForm.z ) );
		}

		return( TransForm.z > 0 );
	}

	//---------------------------------------------------

	bool GetRadarPoint( Vector3 origin, float& screenx, float& screeny, float Size, float x, float y )
	{
		Vector3 vec,rot;
		float distance;
	 
		VectorSubtract( origin, Game.Structs.refdef->Vieworg, vec );
		vec[2] = 0.0f;
		distance = Math::GetDistance( origin, Game.Structs.refdef->Vieworg ) / 48.0f;

		VectorAngles( vec, rot );
		rot[1] = AngleNormalize180( rot[1] - Game.Structs.refdef->refdefViewAngles[1] );
		AngleVectors( rot, vec, 0, 0 );
		VectorScale( vec, distance, vec );
	 
		if( vec[0] > ( Size / 2.f ) )
		   VectorScale( vec,( Size / 2.f ) / vec[0], vec );
		else if( vec[0] < -( Size / 2.f ) )
		   VectorScale( vec, -( Size / 2.f ) / vec[0], vec );

		if( vec[1] > ( Size / 2.f ) )
		   VectorScale( vec, ( Size / 2.f ) / vec[1], vec);
		else if( vec[1] < -( Size / 2.f ) )
		   VectorScale( vec, -( Size / 2.f ) / vec[1], vec );
		
		if( ( ( (int) -vec[1] ) > ( Size / 2.f ) )  || 
			( ( (int) -vec[0] ) > ( Size / 2.f ) ) ) 
				return false;
		
		if( ( ( (int) -vec[1] ) < -( Size / 2.f ) ) || 
			( ( (int) -vec[0] ) < -(Size / 2.f ) ) ) 
				return false;
		
		screenx = (int) -vec[1] + ( (int)x + ( Size / 2.f ) );
		screeny = (int) -vec[0] + ( (int)y + ( Size / 2.f ) );

		return true;
	}

	//---------------------------------------------------

	float GetDistance( Vector3 LocationA, Vector3 LocationB )
	{
		float DistanceX		= LocationA[0] - LocationB[0];
		float DistanceY		= LocationA[1] - LocationB[1];
		float DistanceZ		= LocationA[2] - LocationB[2];

		return (float)sqrt( ( DistanceX * DistanceX ) + ( DistanceY * DistanceY ) + ( DistanceZ * DistanceZ ) );
	}

	//---------------------------------------------------

	float radian( float Angle )
	{ 
		return Angle * ( 3.14159265358979323846f / 180 ); 
	}

	//---------------------------------------------------

	void VectorAngles( const Vector3 value1, Vector3 angles )
	{
		float    forward;
		float    yaw, pitch;
	    
		if ( value1[1] == 0 && value1[0] == 0 ) 
		{
			yaw = 0;
			if ( value1[2] > 0 )         pitch = 90;
			else                         pitch = 270;
		}
		else
		{
			if ( value1[0] )             yaw = (FLOAT) ( atan2 ( value1[1], value1[0] ) * 180 / M_PI );
			else if ( value1[1] > 0 )    yaw = 90;
			else                        yaw = 270;
			if ( yaw < 0 )                yaw += 360;
			forward = (FLOAT) sqrt ( value1[0]*value1[0] + value1[1]*value1[1] );
			pitch = (FLOAT) ( atan2(value1[2], forward) * 180 / M_PI );
			if ( pitch < 0 )             pitch += 360;
		}

		angles[0] = -pitch;
		angles[1] = yaw;
		angles[2] = 0;
	}

	//---------------------------------------------------

	void AnglesToAxis( const Vector3 Angles, Vector3 Axis[3] )
	{
		float *Right, *NullVector3;

		AngleVectors( (float *)Angles, Axis[0], Right, Axis[2] );
		VectorSubtract( NullVector3, Right, Axis[1] );
	}

	//---------------------------------------------------

	void GetOrigin( Vector3 origin, Vector3 angles )
	{
		Vector3 entity;
		VectorSubtract( origin, Game.Structs.refdef->Vieworg, entity );
		VectorAngles( entity, angles );

		if( angles[0] > 180.0f)					angles[0] -= 360.0f;
		else if( angles[0] < -180.0f )			angles[0] += 360.0f;
		if( angles[1] > 180.0f )				angles[1] -= 360.0f;
		else if( angles[1] < -180.0f )			angles[1] += 360.0f;
												angles[0] -= Game.Structs.refdef->refdefViewAngles[0];
												angles[1] -= Game.Structs.refdef->refdefViewAngles[1];
		if( angles[0] > 180.0f )				angles[0] -= 360.0f;
		else if( angles[0] < -180.0f )			angles[0] += 360.0f;
		if( angles[1] > 180.0f )				angles[1] -= 360.0f;
		else if( angles[1] < -180.0f )			angles[1] += 360.0f;
	}

	//---------------------------------------------------

	weapon_t* GetWeaponIndex( int Index )
	{
		return ( weapon_t* )( 0x00748658 + (Index * 0x44) );
	}

	//---------------------------------------------------

	centity_t * GetEntityIndex( int Index )
	{
		return ( centity_t* )( 0x84F2D8 + 0x1DC * Index );
	}

	//---------------------------------------------------

	clientInfo_t * GetClientIndex( int Index )
	{
		return ( clientInfo_t* )( 0x839270 + 0x4CC * Index );
	}
};