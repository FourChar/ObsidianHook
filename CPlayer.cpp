#include "stdafx.h"

void CPlayerManager::BeginUpdate( )
{
	for( int i = 0; i < Game.Structs.cgs->maxclients; i++ )
	{
		centity_t			*		Entity		= SubGame::getEntityIndex( i );
		clientInfo_t		*		Player		= SubGame::getClientIndex( i );

		if( Entity->clientNum == SubGame::getLocalPlayerID( ) )
			continue;
		if( !Entity->isAlive || !Entity->currentValid || !Player->infoValid )
			continue;
		if( Player->Team == TEAM_SPECTATOR )
			continue;

		this->AddPlayer( Entity );
	}
}
void CPlayerManager::EndUpdate( )
{
	this->Players.clear( );
}

bool CPlayerManager::AddPlayer( centity_t *Entity )
{
	CPlayer			CurrentPlayer;

	if( !Entity )
		return( false );

	if( !Players.empty( ) )
	{
		for( int i = 0; i < Players.size( ); i++ )
		{
			if( Entity == Players[ i ].Entity )
				return( false );
		}
	}

	CurrentPlayer.Client			= SubGame::getClientIndex( Entity->clientNum );
	CurrentPlayer.Entity			= Entity;
	CurrentPlayer.Weapon			= Math::GetWeaponIndex( Entity->weapon );
	CurrentPlayer.isAlive			= Entity->isAlive;
	CurrentPlayer.currentValid		= Entity->currentValid;
	CurrentPlayer.infoValid			= CurrentPlayer.Client->infoValid;
	CurrentPlayer.entityType		= Entity->eType;
	CurrentPlayer.entityFlags		= Entity->eFlags;
	CurrentPlayer.Name				= std::string( CurrentPlayer.Client->Name );
	CurrentPlayer.WeaponName		= std::string( CurrentPlayer.Weapon->Name );
	CurrentPlayer.clientNum			= Entity->clientNum;
	CurrentPlayer.Team				= CurrentPlayer.Client->Team;
	CurrentPlayer.WeaponID			= Entity->weapon;
	CurrentPlayer.Distance			= Math::GetDistance( Entity->lerpOrigin, Game.Structs.refdef->Vieworg );
	CurrentPlayer.Enemy				= ( (CurrentPlayer.Client->Team != SubGame::getLocalPlayerClient( )->Team) || \
										(CurrentPlayer.Client->Team == TEAM_FFA) );
	CurrentPlayer.Friend			= ( strstr( CurrentPlayer.Client->Name, "CyberDwak" ) || \
										strstr( CurrentPlayer.Client->Name, "bot27" ) );

	VectorCopy( Entity->lerpOrigin, CurrentPlayer.lerpOrigin );
	VectorCopy( Entity->oldOrigin, CurrentPlayer.oldOrigin );
	VectorCopy( Entity->newOrigin, CurrentPlayer.newOrigin );
	VectorSubtract( Entity->oldOrigin, Entity->newOrigin, CurrentPlayer.Velocity );

	CurrentPlayer.headOrigin[ 0 ] = Entity->lerpOrigin[ 0 ];
	CurrentPlayer.headOrigin[ 1 ] = Entity->lerpOrigin[ 1 ];
	CurrentPlayer.headOrigin[ 2 ] = Entity->lerpOrigin[ 2 ];

	if( Entity->eFlags & FLAGS_PRONE || Entity->eFlags & FLAGS_PRONE_FORWARD || Entity->eFlags & FLAGS_PRONE_BACKWARD )
		CurrentPlayer.headOrigin[ 2 ]		+= 20;
	else if( Entity->eFlags & FLAGS_CROUCH || Entity->eFlags & FLAGS_CROUCH_FORWARD || Entity->eFlags & FLAGS_CROUCH_BACKWARD )
		CurrentPlayer.headOrigin[ 2 ]		+= 40;
	else
		CurrentPlayer.headOrigin[ 2 ]		+= 55;

	CurrentPlayer.isVisible			= SubGame::SubMath::SubTrace::IsVisible( CurrentPlayer.headOrigin, true );

	if( CurrentPlayer.Enemy )
	{
		CurrentPlayer.DrawingColor = ( Settings.Options.General_VisibleChecks->Value._bool ? ( CurrentPlayer.isVisible ? D3DColors::Easy_Yellow : D3DColors::Easy_Red ) : D3DColors::Easy_Red );
	}
	else if( CurrentPlayer.Friend )
	{
		CurrentPlayer.DrawingColor = ( Settings.Options.General_VisibleChecks->Value._bool ? ( CurrentPlayer.isVisible ? D3DColors::LightPink : D3DColors::Easy_Pink ) : D3DColors::Easy_Pink );
	}
	else
	{
		CurrentPlayer.DrawingColor = ( Settings.Options.General_VisibleChecks->Value._bool ? ( CurrentPlayer.isVisible ? D3DColors::Cyan : D3DColors::Easy_Blue ) : D3DColors::Easy_Blue );
	}

	Players.push_back( CurrentPlayer );
	return( true );
}

CPlayer *CPlayerManager::GetPlayer( int clientNum )
{
	if( !Players.empty( ) )
	{
		return &Players[ clientNum ];
	}

	return( NULL );
}

UINT CPlayerManager::GetPlayerCount( )
{
	return( Players.size( ) );
}