#pragma once

class CPlayer
{
public:
	int								isAlive;
	int								infoValid;
	BYTE							currentValid;

	DWORD							entityType;   
	DWORD							entityFlags;

	std::string						Name;
	std::string						WeaponName;
	int								clientNum;
	int								Team;
	int								WeaponID;

	Vector3							headOrigin;
	Vector3							lerpOrigin;
	Vector3							oldOrigin;
	Vector3							newOrigin;

	centity_t			*			Entity;
	clientInfo_t		*			Client;
	weapon_t			*			Weapon;

	float							Distance;
	bool							isVisible;
	bool							Enemy;
	bool							Friend;

	DWORD							DrawingColor;
	Vector3							Velocity;
};

class CPlayerManager
{
public:
	void							BeginUpdate									( );
	void							EndUpdate									( );

	bool							AddPlayer									( centity_t *Entity );
	CPlayer				*			GetPlayer									( int clientNum );

	UINT							GetPlayerCount								( );

private:
	std::vector< CPlayer >			Players;
};