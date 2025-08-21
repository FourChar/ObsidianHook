#pragma once

#define M_PI					3.14159265358979323846f
#define M_E						2.71828182845904523536f
#define	ANGLE2SHORT(x)			((int)((x)*65536/360) & 65535)
#define	SHORT2ANGLE(x)			((x)*(360.0/65536))

#define DotProduct(x,y)			((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])
#define VectorSubtract(a,b,c)	((c)[0]=(a)[0]-(b)[0],(c)[1]=(a)[1]-(b)[1],(c)[2]=(a)[2]-(b)[2])
#define VectorAdd(a,b,c)		((c)[0]=(a)[0]+(b)[0],(c)[1]=(a)[1]+(b)[1],(c)[2]=(a)[2]+(b)[2])
#define VectorCopy(a,b)			((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2])
#define VectorCopy4(a,b)		((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2],(b)[3]=(a)[3])
#define	VectorScale(v, s, o)	((o)[0]=(v)[0]*(s),(o)[1]=(v)[1]*(s),(o)[2]=(v)[2]*(s))
#define	VectorMA(v, s, b, o)	((o)[0]=(v)[0]+(b)[0]*(s),(o)[1]=(v)[1]+(b)[1]*(s),(o)[2]=(v)[2]+(b)[2]*(s))
#define VectorCmp(a,b)			(((a)[0]==(b)[0])&&((a)[1]==(b)[1])&&((a)[2]==(b)[2]))
#define VectorClear(a)			((a)[0]=(a)[1]=(a)[2]=0)

namespace Math
{
	void				AngleVectors			( float *Angles, float *Forward, float *Right, float *Up );
	float				AngleNormalize360		( float Angle );
	float				AngleNormalize180		( float Angle );
	bool				WorldToScreen			( Vector3 WorldLocation, float *ScreenX, float *ScreenY );
	bool				GetRadarPoint			( Vector3 EntityOrigin, float &EntityScreenX, float &EntityScreenY, float RadarSize, float RadarX, float RadarY );
	float				GetDistance				( Vector3 LocationA, Vector3 LocationB );
	float				radian					( float Angle );
	void				VectorAngles			( const Vector3 value1, Vector3 Angles );
	void				AnglesToAxis			( const Vector3 Angles, Vector3 Axis[3] );
	void				GetOrigin				( Vector3 origin, Vector3 angles );

	weapon_t*			GetWeaponIndex			( int Index );
	centity_t*			GetEntityIndex			( int Index );
	clientInfo_t*		GetClientIndex			( int Index );
};