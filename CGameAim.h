#pragma once

class CGameAim
{
public:
	bool							CheckAimState								( DWORD localState );
	bool							IsInFov										( float *Angles, float Fov );
	bool							GetVisibleBone								( centity_t *Entity, float *AimingPoint );
};


class CPlayerBones
{
public:
	WORD							Helmet;						// 0x001406E96
	WORD							Head;						// 0x001406E98
	WORD							Neck;						// 0x001406FC6
	WORD							Spine4;						// 0x001406E94
	WORD							Pelvis;						// 0x001406FC8	
};

class CEntityBones
{
public:
	WORD							Smoke;						// 0x001406F62
	WORD							Flash;						// 0x001406F60
	WORD							Flashbang;					// 0x001406F5E
	WORD							Grenade;					// 0x001406ECE
};

class CAllBones
{
public:
	CPlayerBones					PlayerBones;
	CEntityBones					EntityBones;
};