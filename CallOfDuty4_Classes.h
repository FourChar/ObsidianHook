#pragma once

#define Q_COLOR_ESCAPE				'^'
#define Q_IsColorString( p )		( p && *(p) == Q_COLOR_ESCAPE && *((p)+1) && *((p)+1) != Q_COLOR_ESCAPE )
#define NullVec3(a)					((a)[0][0]=(a)[0][1]=(a)[0][2]=(a)[1][0]=(a)[1][1]=(a)[1][2]=(a)[2][0]=(a)[2][1]=(a)[2][2]=0)

#define FLAGS_STANDING 				0x02     // standing, still
#define FLAGS_CROUCH 				0x04     // crouch, still
#define FLAGS_PRONE 				0x08     // prone, still
#define FLAGS_PRONE_FORWARD 		0x100    // prone, moving forwards
#define FLAGS_PRONE_BACKWARD 		0x200    // prone, moving backwards
#define FLAGS_STANDING_FORWARD 		0x400    // standing, moving forwards
#define FLAGS_STANDING_BACKWARD		0x800    // standing, moving backwards
#define FLAGS_CROUCH_FORWARD 		0x1000   // crouched, moving forwards
#define FLAGS_CROUCH_BACKWARD 		0x2000   // crouched, moving backwards
#define FLAGS_CLIMBING 				0x40000	 // climbing a ladder
#define FLAGS_SPRINTING 			0x100000 // sprinting
#define FLAGS_SCALING 				0x800000 // the player is using the object to hop over/onto it

#define	CVAR_ARCHIVE				1	// set to cause it to be saved to vars.rc
										// used for system variables, not for player
										// specific configurations
#define	CVAR_USERINFO				2	// sent to server on connect or change
#define	CVAR_SERVERINFO				4	// sent in response to front end requests
#define	CVAR_SYSTEMINFO				8	// these cvars will be duplicated on all clients
#define	CVAR_INIT					16	// don't allow change from console at all,
										// but can be set from the command line
#define	CVAR_LATCH					32	// will only change when C code next does
										// a Cvar_Get(), so it can't be changed
										// without proper initialization.  modified
										// will be set, even though the value hasn't
										// changed yet
#define	CVAR_ROM					64	// display only, cannot be set by user at all
#define	CVAR_USER_CREATED			128	// created by a set command
#define	CVAR_TEMP					256	// can be set even when cheats are disabled, but is not archived
#define CVAR_CHEAT					512	// can not be changed if cheats are disabled
#define CVAR_NORESTART				1024// do not clear when a cvar_restart is issued

#define CVAR_SERVER_CREATED			2048// cvar was created by a server the client connected to.
#define CVAR_NONEXISTENT			0xFFFFFFFF	// Cvar doesn't exist.

#define IsFriend( a )				( Structs.clientinfo[a].Team == Structs.clientinfo[Structs.cg->clientNum].Team )

#define MAX_CLIENTS					64
#define GENTITYNUM_BITS				10
#define MAX_GENTITIES				( 1 << GENTITYNUM_BITS )
#define ENTITYNUM_NONE				( MAX_GENTITIES - 1 )
#define ENTITYNUM_WORLD				( MAX_GENTITIES - 2 )
#define ENTITYNUM_MAX_NORMAL		( MAX_GENTITIES - 2 )

#define TYPE_SMOKEGRENADE			0
#define TYPE_HUMAN					1
#define TYPE_HUMANCORPSE			2
#define TYPE_WEAPON					3
#define TYPE_EXPLOSIVE				4
#define TYPE_VEHICLE				6
#define TYPE_CLAYMORELASER			8
#define TYPE_TURRET					11			//Check for eFlag == 0x2
#define TYPE_HELICOPTER				12
#define TYPE_AIRSTRIKE				13
#define TYPE_BROKEN_PART			20			//Broken Part from a Car. E.G. Window, Light	|		Alive must be 0
#define TYPE_KNIFE_CONTACT			58			//After you've hit something with a knife		|		Alive must be 0
#define TYPE_BLOWN_UP_CAR			60			//Blown Up Car									|		Alive must be 1
#define TYPE_OLD_EXPLOSION			78			//Grenade, Car, Claymore						|		Alive must be 0
#define FLAG_OLD_EXPLOSIVE			0x20		//Like Flashbang or Claymore but not Grenade	|		Alive must be 0

typedef float Vector;
typedef Vector Vector2[2];
typedef Vector Vector3[3];
typedef Vector Vector4[4];
typedef Vector Vector5[5];

typedef int	 clipHandle_t;
typedef int	 sfxHandle_t;
typedef int	 qhandle_t;
typedef void fontInfo_t;

typedef enum
{
	STEREO_CENTER,
	STEREO_LEFT,
	STEREO_RIGHT
} stereoFrame_t;

typedef enum 
{
	qfalse, 
	qtrue
} qboolean;

enum eTypes
{
	ET_GENERAL,//0
	ET_PLAYER,//1
	ET_PLAYER_CORPSE,//2
	ET_ITEM,//3
	ET_MISSILE,//4
	ET_INVISIBLE,//5
	ET_SCRIPTMOVER,//6
	ET_SOUND_BLEND,//7
	ET_FX,//8
	ET_LOOP_FX,//9
	ET_PRIMARY_LIGHT,//10
	ET_MG42,//11
	ET_HELICOPTER,//12
	ET_PLANE,//13
	ET_VEHICLE,//14
	ET_VEHICLE_COLLMAP,//15
	ET_VEHICLE_CORPSE,//16
	ET_KNIFE_CONTACT = 58,//58
};

typedef enum 
{
    TEAM_FFA,
    TEAM_ALLIES,
    TEAM_ENEMIES,
    TEAM_SPECTATOR,

    TEAM_TEAMS
} team_t;

enum EntityEvent
{
    EV_NONE,//0
    EV_FOLIAGE_SOUND,//1
    EV_STOP_WEAPON_SOUND,//2
    EV_SOUND_ALIAS,//3
    EV_SOUND_ALIAS_AS_MASTER,//4
    EV_STOPSOUNDS,//5
    EV_STANCE_FORCE_STAND,//6
    EV_STANCE_FORCE_CROUCH,//7
    EV_STANCE_FORCE_PRONE,//8
    EV_ITEM_PICKUP,//9
    EV_AMMO_PICKUP,//10
    EV_NOAMMO,//11
    EV_EMPTYCLIP,//12
    EV_EMPTY_OFFHAND,//13
    EV_RESET_ADS,//14
    EV_RELOAD,//15
    EV_RELOAD_FROM_EMPTY,//16
    EV_RELOAD_START,//17
    EV_RELOAD_END,//18
    EV_RELOAD_START_NOTIFY,//19
    EV_RELOAD_ADDAMMO,//20
    EV_RAISE_WEAPON,//21
    EV_FIRST_RAISE_WEAPON,//22
    EV_PUTAWAY_WEAPON,//23
    EV_WEAPON_ALT,//24
    EV_PULLBACK_WEAPON,//25
    EV_FIRE_WEAPON,//26
    EV_FIRE_WEAPON_LASTSHOT,//27
    EV_RECHAMBER_WEAPON,//28
    EV_EJECT_BRASS,//29
    EV_MELEE_SWIPE,//30
    EV_FIRE_MELEE,//31
    EV_PREP_OFFHAND,//32
    EV_USE_OFFHAND,//33
    EV_SWITCH_OFFHAND,//34
    EV_MELEE_HIT,//35
    EV_MELEE_MISS,//36
    EV_MELEE_BLOOD,//37
    EV_FIRE_WEAPON_MG42,//38
    EV_FIRE_QUADBARREL_1,//39
    EV_FIRE_QUADBARREL_2,//40
    EV_BULLET_HIT,//41
    EV_BULLET_HIT_CLIENT_SMALL,//42
    EV_BULLET_HIT_CLIENT_LARGE,//43
    EV_GRENADE_BOUNCE,//44
    EV_GRENADE_EXPLODE,//45
    EV_ROCKET_EXPLODE,//46
    EV_ROCKET_EXPLODE_NOMARKS,//47
    EV_FLASHBANG_EXPLODE,//48
    EV_CUSTOM_EXPLODE,//49
    EV_CUSTOM_EXPLODE_NOMARKS,//50
    EV_CHANGE_TO_DUD,//51
    EV_DUD_EXPLODE,//52
    EV_DUD_IMPACT,//53
    EV_BULLET,//54
    EV_PLAY_FX,//55
    EV_PLAY_FX_ON_TAG,//56
    EV_PHYS_EXPLOSION_SPHERE,//57
    EV_PHYS_EXPLOSION_CYLINDER,//58
    EV_PHYS_EXPLOSION_JOLT,//59
    EV_PHYS_JITTER,//60
    EV_EARTHQUAKE,//61
    EV_GRENADE_SUICIDE,//62
    EV_DETONATE,//63
    EV_NIGHTVISION_WEAR,//64
    EV_NIGHTVISION_REMOVE,//65
    EV_OBITUARY,//66
    EV_NO_FRAG_GRENADE_HINT,//67
    EV_NO_SPECIAL_GRENADE_HINT,//68
    EV_TARGET_TOO_CLOSE_HINT,//69
    EV_TARGET_NOT_ENOUGH_CLEARANCE,//70
    EV_LOCKON_REQUIRED_HINT,//71
    EV_FOOTSTEP_SPRINT,//72
    EV_FOOTSTEP_RUN,//73
    EV_FOOTSTEP_WALK,//74
    EV_FOOTSTEP_PRONE,//75
    EV_JUMP,//76
    EV_LANDING_DEFAULT,//77
    EV_LANDING_BARK,//78
    EV_LANDING_BRICK,//79
    EV_LANDING_CARPET,//80
    EV_LANDING_CLOTH,//81
    EV_LANDING_CONCRETE,//82
    EV_LANDING_DIRT,//83
    EV_LANDING_FLESH,//84
    EV_LANDING_FOLIAGE,//85
    EV_LANDING_GLASS,//86
    EV_LANDING_GRASS,//87
    EV_LANDING_GRAVEL,//88
    EV_LANDING_ICE,//89
    EV_LANDING_METAL,//90
    EV_LANDING_MUD,//91
    EV_LANDING_PAPER,//92
    EV_LANDING_PLASTER,//93
    EV_LANDING_ROCK,//94
    EV_LANDING_SAND,//95
    EV_LANDING_SNOW,//96
    EV_LANDING_WATER,//97
    EV_LANDING_WOOD,//98
    EV_LANDING_ASPHALT,//99
    EV_LANDING_CERAMIC,//100
    EV_LANDING_PLASTIC,//101
    EV_LANDING_RUBBER,//102
    EV_LANDING_CUSHION,//103
    EV_LANDING_FRUIT,//104
    EV_LANDING_PAINTEDMETAL,//105
    EV_LANDING_PAIN_DEFAULT,//106
    EV_LANDING_PAIN_BARK,//107
    EV_LANDING_PAIN_BRICK,//108
    EV_LANDING_PAIN_CARPET,//109
    EV_LANDING_PAIN_CLOTH,//110
    EV_LANDING_PAIN_CONCRETE,//111
    EV_LANDING_PAIN_DIRT,//112
    EV_LANDING_PAIN_FLESH,//113
    EV_LANDING_PAIN_FOLIAGE,//114
    EV_LANDING_PAIN_GLASS,//115
    EV_LANDING_PAIN_GRASS,//116
    EV_LANDING_PAIN_GRAVEL,//117
    EV_LANDING_PAIN_ICE,//118
    EV_LANDING_PAIN_METAL,//119
    EV_LANDING_PAIN_MUD,//120
    EV_LANDING_PAIN_PAPER,//121
    EV_LANDING_PAIN_PLASTER,//122
    EV_LANDING_PAIN_ROCK,//123
    EV_LANDING_PAIN_SAND,//124
    EV_LANDING_PAIN_SNOW,//125
    EV_LANDING_PAIN_WATER,//126
    EV_LANDING_PAIN_WOOD,//127
    EV_LANDING_PAIN_ASPHALT,//128
    EV_LANDING_PAIN_CERAMIC,//129
    EV_LANDING_PAIN_PLASTIC,//130
    EV_LANDING_PAIN_RUBBER,//131
    EV_LANDING_PAIN_CUSHION,//132
    EV_LANDING_PAIN_FRUIT,//133
    EV_LANDING_PAIN_PAINTEDMETAL//134
};

typedef struct
{
	int					commandTime;
	int					pm_type; 
	int					bobCycle;
	int					pm_flags; 
	int					holdAtem;
	int					old_pmType;
	int					pmTime;
	Vector3				origin;
	Vector3				velocity;
	char				unknown52[8];
	int					WeaponTime;
	int					WeaponReloadTime;
	int					GrenadeTimeLeft;
	char				unknown72[16];
	int					Gravity;
	float				leanf;
	int					speed;
	int					delta_angles[3];
	int					loll2;
	char				unknown116[12];
	int					IncreasesWhileJumping;
	float				Jump_Y; 
	char				unknown136[4];
	int					movementDir;
	int					eFlags;
	int					ID0F7CD498;
	int					ID0F7CD491;
	int					ID0F7CD492;
	int					DamageFeedback;
	int					MaxDamageFeedback;
	int					DamageSide;
	int					strafe_dir;
	int					ShootingRate;
	int					legsTimer;
	int					events0;
	int					events1;
	int					events2;
	int					events3;
	int					eventParms0;
	int					eventParms1;
	int					eventParms2;
	int					eventParms3;
	int					torsoTimer;
	int					clientNumSpec;
	char				unknown224[8];
	int					Weapon; 
	int					weaponState;
	char				unknown240[4];
	int					zoomTimer;
	char				unknown248[12];
	int					Item;
	Vector3				viewangles;
	int					viewHeight;
	float				viewHeightF;
	char				unknown284[28]; 
	int					damageCount;	 //0x0138 <--- how many times you have been damaged
	int					damagePitch;
	int					damage_Yaw;
	int					DamageAmount;	//0x0144 <--- amount of current damage
	int					health;			//0x0148 <--- player current health
	int					_p01[13];
	int					PrimaryClip;
	int					SecondaryClip;
} entityState_t;

typedef struct {
	char        z_crap[64];
	int			contents;
}Trace_pointer_t;

typedef struct {
	float             Fraction;   
	Vector3	          HitLocation;
	int               SurfaceType;   
	int               SurfaceFlags; 
    int               allSolid;
	Trace_pointer_t * Pointer;   
	int	      		  MyHideFunction;
	char              z_crap[68]; 
} trace_t;

typedef struct
{
    int health;
    char z_crap[624];
} actor_t;

typedef struct
{
	DWORD		*		ToDefinitionTable;  
	char		*		CmdName; 
	char			z_crap[8]; 
	DWORD		*		CmdAddress; 
} CmdTable_t;

typedef struct
{
	char _pad0[0x4]; // 0000
	char* displayName; // 0004
	char* AIOverlayDescription; // 0008
	void* gunModel; // 000C, XModel*
	void* gunModel2; // 0010, XModel*
	void* gunModel3; // 0014, XModel*
	void* gunModel4; // 0018, XModel*
	void* gunModel5; // 001C, XModel*
	void* gunModel6; // 0020, XModel*
	void* gunModel7; // 0024, XModel*
	void* gunModel8; // 0028, XModel*
	void* gunModel9; // 002C, XModel*
	void* gunModel10; // 0030, XModel*
	void* gunModel11; // 0034, XModel*
	void* gunModel12; // 0038, XModel*
	void* gunModel13; // 003C, XModel*
	void* gunModel14; // 0040, XModel*
	void* gunModel15; // 0044, XModel*
	void* gunModel16; // 0048, XModel*
	void* handModel; // 004C, XModel*
	char _pad1[0x4]; // 0050
	char* idleAnim; // 0054
	char* emptyIdleAnim; // 0058
	char* fireAnim; // 005C
	char* holdFireAnim; // 0060
	char* lastShotAnim; // 0064
	char* rechamberAnim; // 0068
	char* meleeAnim; // 006C
	char* meleeChargeAnim; // 0070
	char* reloadAnim; // 0074
	char* reloadEmptyAnim; // 0078
	char* reloadStartAnim; // 007C
	char* reloadEndAnim; // 0080
	char* raiseAnim; // 0084
	char* firstRaiseAnim; // 0088
	char* dropAnim; // 008C
	char* altRaiseAnim; // 0090
	char* altDropAnim; // 0094
	char* quickRaiseAnim; // 0098
	char* quickDropAnim; // 009C
	char* emptyRaiseAnim; // 00A0
	char* emptyDropAnim; // 00A4
	char* sprintInAnim; // 00A8
	char* sprintLoopAnim; // 00AC
	char* sprintOutAnim; // 00B0
	char* detonateAnim; // 00B4
	char* nightVisionWearAnim; // 00B8
	char* nightVisionRemoveAnim; // 00BC
	char* adsFireAnim; // 00C0
	char* adsLastShotAnim; // 00C4
	char* adsRechamberAnim; // 00C8
	char* adsUpAnim; // 00CC
	char* adsDownAnim; // 00D0
	char* modeName; // 00D4
	int hideTags; // 00D8, Type 33
	char _pad2[0xC]; // 00DC
	int notetrackSoundMap; // 00E8, Type 34
	char _pad3[0x3C]; // 00EC
	int playerAnimType; // 0128, Type 20
	int weaponType; // 012C, Type 12
	int weaponClass; // 0130, Type 13
	int penetrateType; // 0134, Type 15
	int impactType; // 0138, Type 16
	int inventoryType; // 013C, Type 26
	int fireType; // 0140, Type 27
	int offhandClass; // 0144, Type 19
	int stance; // 0148, Type 17
	int viewFlashEffect; // 014C, Type 8
	int worldFlashEffect; // 0150, Type 8
	int pickupSound; // 0154, Type 11
	int pickupSoundPlayer; // 0158, Type 11
	int ammoPickupSound; // 015C, Type 11
	int ammoPickupSoundPlayer; // 0160, Type 11
	int projectileSound; // 0164, Type 11
	int pullbackSound; // 0168, Type 11
	int pullbackSoundPlayer; // 016C, Type 11
	int fireSound; // 0170, Type 11
	int fireSoundPlayer; // 0174, Type 11
	int loopFireSound; // 0178, Type 11
	int loopFireSoundPlayer; // 017C, Type 11
	int stopFireSound; // 0180, Type 11
	int stopFireSoundPlayer; // 0184, Type 11
	int lastShotSound; // 0188, Type 11
	int lastShotSoundPlayer; // 018C, Type 11
	int emptyFireSound; // 0190, Type 11
	int emptyFireSoundPlayer; // 0194, Type 11
	int meleeSwipeSound; // 0198, Type 11
	int meleeSwipeSoundPlayer; // 019C, Type 11
	int meleeHitSound; // 01A0, Type 11
	int meleeMissSound; // 01A4, Type 11
	int rechamberSound; // 01A8, Type 11
	int rechamberSoundPlayer; // 01AC, Type 11
	int reloadSound; // 01B0, Type 11
	int reloadSoundPlayer; // 01B4, Type 11
	int reloadEmptySound; // 01B8, Type 11
	int reloadEmptySoundPlayer; // 01BC, Type 11
	int reloadStartSound; // 01C0, Type 11
	int reloadStartSoundPlayer; // 01C4, Type 11
	int reloadEndSound; // 01C8, Type 11
	int reloadEndSoundPlayer; // 01CC, Type 11
	int detonateSound; // 01D0, Type 11
	int detonateSoundPlayer; // 01D4, Type 11
	int nightVisionWearSound; // 01D8, Type 11
	int nightVisionWearSoundPlayer; // 01DC, Type 11
	int nightVisionRemoveSound; // 01E0, Type 11
	int nightVisionRemoveSoundPlayer; // 01E4, Type 11
	int altSwitchSound; // 01E8, Type 11
	int altSwitchSoundPlayer; // 01EC, Type 11
	int raiseSound; // 01F0, Type 11
	int raiseSoundPlayer; // 01F4, Type 11
	int firstRaiseSound; // 01F8, Type 11
	int firstRaiseSoundPlayer; // 01FC, Type 11
	int putawaySound; // 0200, Type 11
	int putawaySoundPlayer; // 0204, Type 11
	int bounceSound; // 0208, Type 23
	int viewShellEjectEffect; // 020C, Type 8
	int worldShellEjectEffect; // 0210, Type 8
	int viewLastShotEjectEffect; // 0214, Type 8
	int worldLastShotEjectEffect; // 0218, Type 8
	int reticleCenter; // 021C, Type 10
	int reticleSide; // 0220, Type 10
	int reticleCenterSize; // 0224
	int reticleSideSize; // 0228
	int reticleMinOfs; // 022C
	int activeReticleType; // 0230, Type 21
	float standMoveF; // 0234
	float standMoveR; // 0238
	float standMoveU; // 023C
	float standRotP; // 0240
	float standRotY; // 0244
	float standRotR; // 0248
	float duckedOfsF; // 024C
	float duckedOfsR; // 0250
	float duckedOfsU; // 0254
	float duckedMoveF; // 0258
	float duckedMoveR; // 025C
	float duckedMoveU; // 0260
	float duckedRotP; // 0264
	float duckedRotY; // 0268
	float duckedRotR; // 026C
	float proneOfsF; // 0270
	float proneOfsR; // 0274
	float proneOfsU; // 0278
	float proneMoveF; // 027C
	float proneMoveR; // 0280
	float proneMoveU; // 0284
	float proneRotP; // 0288
	float proneRotY; // 028C
	float proneRotR; // 0290
	float posMoveRate; // 0294
	float posProneMoveRate; // 0298
	float standMoveMinSpeed; // 029C
	float duckedMoveMinSpeed; // 02A0
	float proneMoveMinSpeed; // 02A4
	float posRotRate; // 02A8
	float posProneRotRate; // 02AC
	float standRotMinSpeed; // 02B0
	float duckedRotMinSpeed; // 02B4
	float proneRotMinSpeed; // 02B8
	void* worldModel; // 02BC, XModel*
	void* worldModel2; // 02C0, XModel*
	void* worldModel3; // 02C4, XModel*
	void* worldModel4; // 02C8, XModel*
	void* worldModel5; // 02CC, XModel*
	void* worldModel6; // 02D0, XModel*
	void* worldModel7; // 02D4, XModel*
	void* worldModel8; // 02D8, XModel*
	void* worldModel9; // 02DC, XModel*
	void* worldModel10; // 02E0, XModel*
	void* worldModel11; // 02E4, XModel*
	void* worldModel12; // 02E8, XModel*
	void* worldModel13; // 02EC, XModel*
	void* worldModel14; // 02F0, XModel*
	void* worldModel15; // 02F4, XModel*
	void* worldModel16; // 02F8, XModel*
	void* worldClipModel; // 02FC, XModel*
	void* rocketModel; // 0300, XModel*
	void* knifeModel; // 0304, XModel*
	void* worldKnifeModel; // 0308, XModel*
	int hudIcon; // 030C, Type 10
	int hudIconRatio; // 0310, Type 29
	int ammoCounterIcon; // 0314, Type 10
	int ammoCounterIconRatio; // 0318, Type 30
	int ammoCounterClip; // 031C, Type 28
	int startAmmo; // 0320
	char* ammoName; // 0324
	char _pad4[0x4]; // 0328
	char* clipName; // 032C
	char _pad5[0x4]; // 0330
	int maxAmmo; // 0334
	int clipSize; // 0338
	int shotCount; // 033C
	char* sharedAmmoCapName; // 0340
	char _pad6[0x4]; // 0344
	int sharedAmmoCap; // 0348
	int damage; // 034C
	int playerDamage; // 0350
	int meleeDamage; // 0354
	char _pad7[0x4]; // 0358
	int fireDelay; // 035C, Type 7
	int meleeDelay; // 0360, Type 7
	int meleeChargeDelay; // 0364, Type 7
	int detonateDelay; // 0368, Type 7
	int fireTime; // 036C, Type 7
	int rechamberTime; // 0370, Type 7
	int rechamberBoltTime; // 0374, Type 7
	int holdFireTime; // 0378, Type 7
	int detonateTime; // 037C, Type 7
	int meleeTime; // 0380, Type 7
	int meleeChargeTime; // 0384, Type 7
	int reloadTime; // 0388, Type 7
	int reloadShowRocketTime; // 038C, Type 7
	int reloadEmptyTime; // 0390, Type 7
	int reloadAddTime; // 0394, Type 7
	int reloadStartTime; // 0398, Type 7
	int reloadStartAddTime; // 039C, Type 7
	int reloadEndTime; // 03A0, Type 7
	int dropTime; // 03A4, Type 7
	int raiseTime; // 03A8, Type 7
	int altDropTime; // 03AC, Type 7
	int altRaiseTime; // 03B0, Type 7
	int quickDropTime; // 03B4, Type 7
	int quickRaiseTime; // 03B8, Type 7
	int firstRaiseTime; // 03BC, Type 7
	int emptyRaiseTime; // 03C0, Type 7
	int emptyDropTime; // 03C4, Type 7
	int sprintInTime; // 03C8, Type 7
	int sprintLoopTime; // 03CC, Type 7
	int sprintOutTime; // 03D0, Type 7
	int nightVisionWearTime; // 03D4, Type 7
	int nightVisionWearTimeFadeOutEnd; // 03D8, Type 7
	int nightVisionWearTimePowerUp; // 03DC, Type 7
	int nightVisionRemoveTime; // 03E0, Type 7
	int nightVisionRemoveTimePowerDown; // 03E4, Type 7
	int nightVisionRemoveTimeFadeInStart; // 03E8, Type 7
	int fuseTime; // 03EC, Type 7
	int aifuseTime; // 03F0, Type 7
	BOOL requireLockonToFire; // 03F4
	BOOL noAdsWhenMagEmpty; // 03F8
	BOOL avoidDropCleanup; // 03FC
	float autoAimRange; // 0400
	float aimAssistRange; // 0404
	float aimAssistRangeAds; // 0408
	float aimPadding; // 040C
	float enemyCrosshairRange; // 0410
	BOOL crosshairColorChange; // 0414
	float moveSpeedScale; // 0418
	float adsMoveSpeedScale; // 041C
	float sprintDurationScale; // 0420
	float adsZoomFov; // 0424
	float adsZoomInFrac; // 0428
	float adsZoomOutFrac; // 042C
	int adsOverlayShader; // 0430, Type 10
	int adsOverlayShaderLowRes; // 0434, Type 10
	int adsOverlayReticle; // 0438, Type 14
	int adsOverlayInterface; // 043C, Type 25
	float adsOverlayWidth; // 0440
	float adsOverlayHeight; // 0444
	float adsBobFactor; // 0448
	float adsViewBobMult; // 044C
	float hipSpreadStandMin; // 0450
	float hipSpreadDuckedMin; // 0454
	float hipSpreadProneMin; // 0458
	float hipSpreadMax; // 045C
	float hipSpreadDuckedMax; // 0460
	float hipSpreadProneMax; // 0464
	float hipSpreadDecayRate; // 0468
	float hipSpreadFireAdd; // 046C
	float hipSpreadTurnAdd; // 0470
	float hipSpreadMoveAdd; // 0474
	float hipSpreadDuckedDecay; // 0478
	float hipSpreadProneDecay; // 047C
	float hipReticleSidePos; // 0480
	int adsTransInTime; // 0484, Type 7
	int adsTransOutTime; // 0488, Type 7
	float adsIdleAmount; // 048C
	float hipIdleAmount; // 0490
	float adsIdleSpeed; // 0494
	float hipIdleSpeed; // 0498
	float idleCrouchFactor; // 049C
	float idleProneFactor; // 04A0
	float gunMaxPitch; // 04A4
	float gunMaxYaw; // 04A8
	float swayMaxAngle; // 04AC
	float swayLerpSpeed; // 04B0
	float swayPitchScale; // 04B4
	float swayYawScale; // 04B8
	float swayHorizScale; // 04BC
	float swayVertScale; // 04C0
	float swayShellShockScale; // 04C4
	float adsSwayMaxAngle; // 04C8
	float adsSwayLerpSpeed; // 04CC
	float adsSwayPitchScale; // 04D0
	float adsSwayYawScale; // 04D4
	float adsSwayHorizScale; // 04D8
	float adsSwayVertScale; // 04DC
	BOOL rifleBullet; // 04E0
	BOOL armorPiercing; // 04E4
	BOOL boltAction; // 04E8
	BOOL aimDownSight; // 04EC
	BOOL rechamberWhileAds; // 04F0
	float adsViewErrorMin; // 04F4
	float adsViewErrorMax; // 04F8
	BOOL cookOffHold; // 04FC
	BOOL clipOnly; // 0500
	BOOL adsFire; // 0504
	BOOL cancelAutoHolsterWhenEmpty; // 0508
	BOOL suppressAmmoReserveDisplay; // 050C
	BOOL enhanced; // 0510
	BOOL laserSightDuringNightvision; // 0514
	int killIcon; // 0518, Type 10
	int killIconRatio; // 051C, Type 31
	BOOL flipKillIcon; // 0520
	int dpadIcon; // 0524, Type 10
	int dpadIconRatio; // 0528, Type 32
	BOOL noPartialReload; // 052C
	BOOL segmentedReload; // 0530
	int reloadAmmoAdd; // 0534
	int reloadStartAdd; // 0538
	char* altWeapon; // 053C
	char _pad8[0x4]; // 0540
	int dropAmmoMin; // 0544
	int dropAmmoMax; // 0548
	BOOL blocksProne; // 054C
	BOOL silenced; // 0550
	int explosionRadius; // 0554
	int explosionRadiusMin; // 0558
	int explosionInnerDamage; // 055C
	int explosionOuterDamage; // 0560
	float damageConeAngle; // 0564
	int projectileSpeed; // 0568
	int projectileSpeedUp; // 056C
	int projectileSpeedForward; // 0570
	int projectileActivateDist; // 0574
	float projectileLifetime; // 0578
	float timeToAccelerate; // 057C
	float projectileCurvature; // 0580
	void* projectileModel; // 0584, XModel*
	int projExplosionType; // 0588, Type 18
	int projExplosionEffect; // 058C, Type 8
	BOOL projExplosionEffectForceNormalUp; // 0590
	int projDudEffect; // 0594, Type 8
	int projExplosionSound; // 0598, Type 11
	int projDudSound; // 059C, Type 11
	BOOL projImpactExplode; // 05A0
	int stickiness; // 05A4, Type 24
	BOOL hasDetonator; // 05A8
	BOOL timedDetonation; // 05AC
	BOOL rotate; // 05B0
	BOOL holdButtonToThrow; // 05B4
	BOOL freezeMovementWhenFiring; // 05B8
	float lowAmmoWarningThreshold; // 05BC
	float parallelDefaultBounce; // 05C0
	float parallelBarkBounce; // 05C4
	float parallelBrickBounce; // 05C8
	float parallelCarpetBounce; // 05CC
	float parallelClothBounce; // 05D0
	float parallelConcreteBounce; // 05D4
	float parallelDirtBounce; // 05D8
	float parallelFleshBounce; // 05DC
	float parallelFoliageBounce; // 05E0
	float parallelGlassBounce; // 05E4
	float parallelGrassBounce; // 05E8
	float parallelGravelBounce; // 05EC
	float parallelIceBounce; // 05F0
	float parallelMetalBounce; // 05F4
	float parallelMudBounce; // 05F8
	float parallelPaperBounce; // 05FC
	float parallelPlasterBounce; // 0600
	float parallelRockBounce; // 0604
	float parallelSandBounce; // 0608
	float parallelSnowBounce; // 060C
	float parallelWaterBounce; // 0610
	float parallelWoodBounce; // 0614
	float parallelAsphaltBounce; // 0618
	float parallelCeramicBounce; // 061C
	float perpendicularCeramicBounce; // 061C
	float parallelPlasticBounce; // 0620
	float perpendicularPlasticBounce; // 0620
	float parallelRubberBounce; // 0624
	float perpendicularRubberBounce; // 0624
	float parallelCushionBounce; // 0628
	float parallelFruitBounce; // 062C
	float parallelPaintedMetalBounce; // 0630
	float perpendicularDefaultBounce; // 0634
	float perpendicularBarkBounce; // 0638
	float perpendicularBrickBounce; // 063C
	float perpendicularCarpetBounce; // 0640
	float perpendicularClothBounce; // 0644
	float perpendicularConcreteBounce; // 0648
	float perpendicularDirtBounce; // 064C
	float perpendicularFleshBounce; // 0650
	float perpendicularFoliageBounce; // 0654
	float perpendicularGlassBounce; // 0658
	float perpendicularGrassBounce; // 065C
	float perpendicularGravelBounce; // 0660
	float perpendicularIceBounce; // 0664
	float perpendicularMetalBounce; // 0668
	float perpendicularMudBounce; // 066C
	float perpendicularPaperBounce; // 0670
	float perpendicularPlasterBounce; // 0674
	float perpendicularRockBounce; // 0678
	float perpendicularSandBounce; // 067C
	float perpendicularSnowBounce; // 0680
	float perpendicularWaterBounce; // 0684
	float perpendicularWoodBounce; // 0688
	float perpendicularAsphaltBounce; // 068C
	char _pad9[0xC]; // 0690
	float perpendicularCushionBounce; // 069C
	float perpendicularFruitBounce; // 06A0
	float perpendicularPaintedMetalBounce; // 06A4
	int projTrailEffect; // 06A8, Type 8
	float projectileRed; // 06AC
	float projectileGreen; // 06B0
	float projectileBlue; // 06B4
	int guidedMissileType; // 06B8, Type 22
	float maxSteeringAccel; // 06BC
	int projIgnitionDelay; // 06C0
	int projIgnitionEffect; // 06C4, Type 8
	int projIgnitionSound; // 06C8, Type 11
	float adsAimPitch; // 06CC
	float adsCrosshairInFrac; // 06D0
	float adsCrosshairOutFrac; // 06D4
	int adsGunKickReducedKickBullets; // 06D8
	float adsGunKickReducedKickPercent; // 06DC
	float adsGunKickPitchMin; // 06E0
	float adsGunKickPitchMax; // 06E4
	float adsGunKickYawMin; // 06E8
	float adsGunKickYawMax; // 06EC
	float adsGunKickAccel; // 06F0
	float adsGunKickSpeedMax; // 06F4
	float adsGunKickSpeedDecay; // 06F8
	float adsGunKickStaticDecay; // 06FC
	float adsViewKickPitchMin; // 0700
	float adsViewKickPitchMax; // 0704
	float adsViewKickYawMin; // 0708
	float adsViewKickYawMax; // 070C
	float adsViewKickCenterSpeed; // 0710
	char _pad10[0x8]; // 0714
	float adsSpread; // 071C
	int hipGunKickReducedKickBullets; // 0720
	float hipGunKickReducedKickPercent; // 0724
	float hipGunKickPitchMin; // 0728
	float hipGunKickPitchMax; // 072C
	float hipGunKickYawMin; // 0730
	float hipGunKickYawMax; // 0734
	float hipGunKickAccel; // 0738
	float hipGunKickSpeedMax; // 073C
	float hipGunKickSpeedDecay; // 0740
	float hipGunKickStaticDecay; // 0744
	float hipViewKickPitchMin; // 0748
	float hipViewKickPitchMax; // 074C
	float hipViewKickYawMin; // 0750
	float hipViewKickYawMax; // 0754
	float hipViewKickCenterSpeed; // 0758
	char _pad11[0x8]; // 075C
	float fightDist; // 0764
	float maxDist; // 0768
	char* aiVsAiAccuracyGraph; // 076C
	char* aiVsPlayerAccuracyGraph; // 0770
	char _pad12[0x20]; // 0774
	int adsReloadTransTime; // 0794, Type 7
	float leftArc; // 0798
	float rightArc; // 079C
	float topArc; // 07A0
	float bottomArc; // 07A4
	float accuracy; // 07A8
	float aiSpread; // 07AC
	float playerSpread; // 07B0
	float minVertTurnSpeed; // 07B4
	float minHorTurnSpeed; // 07B8
	float maxVertTurnSpeed; // 07BC
	float maxHorTurnSpeed; // 07C0
	float pitchConvergenceTime; // 07C4
	float yawConvergenceTime; // 07C8
	float suppressionTime; // 07CC
	float maxRange; // 07D0
	float animHorRotateInc; // 07D4
	float playerPositionDist; // 07D8
	char* useHintString; // 07DC
	char* dropHintString; // 07E0
	char _pad13[0x8]; // 07E4
	float horizViewJitter; // 07EC
	float vertViewJitter; // 07F0
	char* script; // 07F4
	char _pad14[0x8]; // 07F8
	int minDamage; // 0800
	int minPlayerDamage; // 0804
	float maxDamageRange; // 0808
	float minDamageRange; // 080C
	float destabilizationRateTime; // 0810
	float destabilizationCurvatureMax; // 0814
	int destabilizeDistance; // 0818
	float locNone; // 081C
	float locHelmet; // 0820
	float locHead; // 0824
	float locNeck; // 0828
	float locTorsoUpper; // 082C
	float locTorsoLower; // 0830
	float locRightArmUpper; // 0834
	float locLeftArmUpper; // 0838
	float locRightArmLower; // 083C
	float locLeftArmLower; // 0840
	float locRightHand; // 0844
	float locLeftHand; // 0848
	float locRightLegUpper; // 084C
	float locLeftLegUpper; // 0850
	float locRightLegLower; // 0854
	float locLeftLegLower; // 0858
	float locRightFoot; // 085C
	float locLeftFoot; // 0860
	float locGun; // 0864
	char* fireRumble; // 0868
	char* meleeImpactRumble; // 086C
	float adsDofStart; // 0870
	float adsDofEnd; // 0874
}weaponInfos_t;

typedef struct
{
	int					snapFlags;
	int					Ping;
	int					ServerTime;
	char				unknown12[28];
	Vector3				lerpOrigin;
	Vector3				newOrigin;
	char				z_crap2[168];
	DWORD				clientNum;
	char				z_crap3[8];	
	int					curWeapon;
	int					weaponState;			//5: Shooting, 7: Reloading, 4: Changing to Secondary, 3: Changing to Primary
	char				z_crap4[4];
	float				Zoom;
	char				z_crap5[16];
	float				Pitch;
	float				Yaw;
	char				z_crap6[8];
	float				viewHeight;
	char				z_crap7[576];
	char				z_crap8[24];
	int					Grenade_Ammo;
	int					RPG_Ammo;
	char				z_crap9[4];
	int					M9_Ammo;
	char				z_crap10[4];
	int					USP45_Ammo;
	char				z_crap11[8];
	int					MP5_Ammo;
	char				z_crap12[48];
	int					M16A4_Ammo;
	int					M16A4Grenade_Ammo;
	char				z_crap13[4];
	int					M40A3_Ammo;
	char				z_crap14[12];
	int					W1200_Ammo;
	char				z_crap15[4];
	int					M249Saw_Ammo;
	char				z_crap16[12];
	int					FlashBang_Ammo;
	int					SmokeGrenade_Ammo;
	int					StunGrenade_Ammo;
	int					M9Sliencer_Ammo;
	char				z_crap17[4];
	int					USP45Sliencer_Ammo;
	char				z_crap18[11084];
	DWORD				numEntities;
	entityState_t		ID0248F620;
	entityState_t		ID024A70F0;
	entityState_t		ID0246CAE8;
	char				z_crap19[8];
} snapshot_t;

typedef struct 
{
	int					infoValid; 
	char				unknown4[4]; 
	int					clientNum;   
	char				Name[16];   
	int					Team;   
	int					Team2;   
	int					Rank;  
	char				unknown40[20]; 
	char				bodyModel[64];   
	char				headModel[64];   
	char				unknown188[1040]; 
} clientInfo_t;

typedef struct
{
	char				unknown0[2];
	BYTE				currentValid;  
	char				unknown3[25]; 
	Vector3				lerpOrigin; 
	Vector3				lerpAngles; 
	char				unknown52[64]; 
	Vector3				newOrigin; 
	char				unknown128[76]; 
	int					clientNum;   
	DWORD				eType;   
	DWORD				eFlags;   
	char				unknown216[12]; 
	Vector3				oldOrigin; 
	char				unknown240[160];
	int					weapon;  
	char				unknown404[44]; 
	int					isAlive;   
	char				unknown452[24];
} centity_t;

typedef struct {
	int					x; 
    int					y; 
    int					Width; 
    int					Height; 
    float				Fovx; 
    float				Fovy; 
    Vector3				Vieworg; 
    Vector3				Viewaxis[3]; 
	char				unknown142[0x4050];
    Vector3				refdefViewAngles;
} refdef_t;

typedef struct
{
    __int32				time;  
		char			z_crap1[8];
    __int32				PlayerState;  
		char			z_crap2[36];
    __int32				oldTime;
    __int32				newTime;
	  char				z_crap3[116];
    __int32				ID025B8700;
    __int32				ID025BA6C0;
		char			z_crap4[32];
    __int32				ID025B8C70;
	   char				z_crap5[16];
    __int32				State;
		char			z_crap6[24];
    float				WeaponViewX;
    float				WeaponViewY;
		char			z_crap7[28];
} PlayerStates_t;

typedef struct
{
		char			z_crap1[8];
	float				screenXScale;
	float				screenYScale;
	float				screenXBias;
	DWORD				serverCommandSequence;
	DWORD				processedSnapshotNum;
	__int32				localServer;
	char				gametype[4];
		char			z_crap2[28];
	char				servername[256];
	__int32				maxclients;
	char				mapname[64];
}cgs_t;

typedef struct
{
	int					clientNum;
	qboolean			demoPlayback;
	char				z_crap1[24];
    snapshot_t			*snap;
    snapshot_t			*nextSnap;
	snapshot_t			activeSnapshots[2];
	char				z_crap2[286152];
    float				frameInterpolation;
    qboolean			thisFrameTeleport;
    qboolean			nextFrameTeleport;
    int					frametime;        
    int					Time;					//0x794460
    int					oldTime;    
    int					physicsTime;    
    int					timelimitWarnings;    
    int					fraglimitWarnings;
    int					teleportTime;            
    int					cameraState;    
    int					runningTime;            
    int					clientState;        
    int					targetuseState;       
    int					menuEvent;        
    int					JumpTime;        
    float				TeleportPosition_x;        
    float				TeleportPosition_y;        
    float				TeleportPosition_z;        
    float				MapPosition_x;        
    float				MapPosition_y;        
    float				MapPosition_z;        
    float				StepTimePosition_YAW;        
    float				StepTimePosition_PITCH;        
    float				StepTimePosition_ROLL;        
    int					WerfTime;     
    float				ExplodeTime;
	int					CoD2_ZCRAP;
	char				z_crap3[12320];
    Vector3				refdefViewAngles;
	char				z_crap4[276];
    refdef_t			Refdef;					//0x797600
    float				AnglePos_x;    
    float				AnglePos_y;    
    float				AnglePos_z;    
	char				z_crap5[12160];
    int					crosshairClientNum;
    int					crosshairClientTime;
}cg_t;

typedef struct
{
	char				unknown0[72];
	Vector3				Recoil[3]; 
	Vector3				ViewAngles;
	char				unknown1[32];
	Vector3				ViewAxis[3]; 
	Vector3				vOrigin;
}viewMatrix_t;

typedef struct
{
    __int32				EntityNum;
    __int32				SnapShot;
    Vector3				lerpOrigin; 
    __int32				Team; 
} helicopter_t;

typedef struct
{
	char*				ViewMode;				
	char				z_crap1[216];
	char*				WeaponFx;				
} weaponInfo_t; 

typedef struct
{
	char				z_crap1[4];
	weaponInfo_t*		WeaponInfo;				
	char				z_crap2[48];
	char*				Name;					
} weapon_t;

typedef struct
{
	char			z_crap1[4]; 
	float				SpreadValue0;
	float				SpreadValue1;
	float				SpreadValue2;
	char			z_crap2[52]; 
	float				SpreadValue3;
	float				SpreadValue4;
	float				SpreadValue5;
	char			z_crap4[12]; 
	Vector3				lerpOrigin0;  
	char			z_crap5[28]; 
	float				SpreadValue6;
	float				SpreadValue7;
	float				SpreadValue8;
	char			z_crap6[12]; 
	Vector3				lerpOrigin1;
	char			z_crap7[24];
	float				SpreadValue9;
	float				SpreadValue10;
	float				SpreadValue11;
	char			z_crap8[12];
	Vector3				lerpOrigin2;
	char			z_crap9[28];
	float				SpreadValue12;
	float				SpreadValue13;
	float				SpreadValue14;
	char			z_crap10[12];
	Vector3				lerpOrigin3;
	char			z_crap11[28];
	float				SpreadValue15;
	float				SpreadValue16;
	float				SpreadValue17;
	char			z_crap12[12];
	Vector3				lerpOrigin4;
	char			z_crap13[28];
	float				SpreadValue18;
	float				SpreadValue19;
	float				SpreadValue20;
	char			z_crap14[12];
	Vector3				lerpOrigin5;
	char			z_crap15[28];
	float				SpreadValue21;
	float				SpreadValue22;
	float				SpreadValue23;
	char			z_crap16[12];
	Vector3				lerpOrigin6;
	char			z_crap17[28];
	float				SpreadValue24;
	float				SpreadValue25;
	float				SpreadValue26;
	char			z_crap18[12];
	Vector3				lerpOrigin7;
	char			z_crap19[28];
	float				SpreadValue27;
	float				SpreadValue28;
	float				SpreadValue29;
	char			z_crap20[12];
	Vector3				lerpOrigin8;
	char			z_crap21[28];
	float				SpreadValue30;
	float				SpreadValue31;
	float				SpreadValue32;
	char			z_crap22[12];
	Vector3				lerpOrigin9;
	char			z_crap23[28];
	float				SpreadValue33;
	float				SpreadValue34;
	float				SpreadValue35;
	char			z_crap24[12];
	Vector3				lerpOrigin10;
	char			z_crap25[28];
	float				SpreadValue36;
	float				SpreadValue37;
	float				SpreadValue38;
	char			z_crap26[12];
	Vector3				lerpOrigin11;
	char			z_crap27[28];
	float				SpreadValue39;
	float				SpreadValue40;
	float				SpreadValue41;
	char			z_crap28[12];
	Vector3				lerpOrigin12;
	char			z_crap29[28];
	float				SpreadValue42;
	float				SpreadValue43;
	float				SpreadValue44;
	char			z_crap30[12];
	Vector3				lerpOrigin13;
} bullets_t;

typedef struct
{
	float Recoil1; //0x0000  
    float Recoil2; //0x0004  
    float Recoil3; //0x0008  
    float Recoil4; //0x000C  
    float Recoil5; //0x0010  
    float Recoil6; //0x0014  
    float Recoil7; //0x0018  
    float Recoil8; //0x001C  
    float Recoil9; //0x0020  
    float ViewAngleX; //0x0024  
    float ViewAngleY; //0x0028  
    float Spread1; //0x002C  
    float Spread2; //0x0030  
    float Spread3; //0x0034  
    float Spread4; //0x0038  
    float Spread5; //0x003C  
    float Spread6; //0x0040  
    float Spread7; //0x0044  
    float Spread8; //0x0048  
    float Spread9; //0x004C  
    float Spread10; //0x0050  
    float Spread11; //0x0054  
    float Spread12; //0x0058  
    float Spread13; //0x005C  
    float Spread14; //0x0060  
    float Spread15; //0x0064  
    float Spread16; //0x0068  
    float Spread17; //0x006C  
    float Spread18; //0x0070  
    float Timer1; //0x0074  
    float Timer2; //0x0078  
    float Timer3; //0x007C  
    float Timer4; //0x0080  
    float Timer5; //0x0084  
    float Timer6; //0x0088  
        char unknown140[24]; //0x008C
    __int32 Time; //0x00A4  
        char unknown168[4]; //0x00A8
    __int32 RecoilTimer1; //0x00AC  
        char unknown176[8]; //0x00B0
    __int32 RecoilTimer2; //0x00B8  
        char unknown188[4]; //0x00BC
    __int32 RecoilTimer3; //0x00C0  
        char unknown196[16]; //0x00C4
} WeaponGun_t;

typedef struct
{
	DWORD				dword0;
	DWORD				dword4;
	DWORD				dword8;
	DWORD				dwordC;
	DWORD				dword10;
	DWORD				dword14;
	float				float18;
	float				float1C;
	BYTE				byte20;
	char				char21;
	BYTE			z_crap0[63];
	char				char61;
	BYTE			z_crap1[63];
	char				charA1;
	BYTE			z_crap2[63];
	char				charE1;
	BYTE			z_crap3[66];
	DWORD				dword124;
	DWORD				dword128;
	float				float12C;
	float				float130;
	char				char134;
	BYTE			z_crap4[14];
	BYTE				byte143;
	BYTE			z_crap5[256];
	DWORD				dword244;
	DWORD				dword248;
	DWORD				dword24C;
	BYTE				byte250;
	char			z_crap6[3];
	DWORD				dword254;
	float				float258;
	float				float25C;
	float				float260;
	BYTE				byte264;
} shock_t;

typedef struct
{
    IDirect3D9 *		pD3D9;
    IDirect3DDevice9 *	pDevice;
    byte				Unknown001[0x8];
    int					ScreenSizeX;
    int					ScreenSizeY;
    int					CurrentSizeX;
    int					CurrentSizeY;
} d3dRenderer_t;

typedef struct
{
	int					XP;
	int					Score;
	int					Kills;
	int					Deaths;
	int					Suicides;
	int					HeadShots;
	int					KillStreak;
	int					Assists;
	int					Hits;
	int					Knifes;

	int					XPHolder;
	int					ScoreHolder;
	int					KillsHolder;
	int					DeathsHolder;
	int					SuicidesHolder;
	int					HeadShotsHolder;
	int					KillStreakHolder;
	int					AssistsHolder;
	int					HitsHolder;
	int					KnifeHolder;

	float				KillToDeathRatio;
	float				HeadshotRatio;
} statsHolder_t;
extern statsHolder_t playerStats;

class RealStats_t
{
public:
	__int32 XP; //0x0000
	__int32 Score; //0x0004
	__int32 Kills; //0x0008
	__int32 KillStreak; //0x000C
	__int32 Deaths; //0x0010
	__int32 Unknown0; //0x0014
	__int32 Assists; //0x0018
	__int32 HeadShots; //0x001C
	__int32 Unknown1; //0x0020  
	__int32 Suicides; //0x0024  
	__int32 Time0; //0x0028  
	__int32 Unknown2; //0x002C  
	__int32 Unknown3; //0x0030  
	__int32 Time1; //0x0034  
	__int32 KillToDeathRatio; //0x0038  
	__int32 Wins; //0x003C  
	__int32 Rounds; //0x0040  
	__int32 Unknown6; //0x0044  
	__int32 Unknown7; //0x0048  
	__int32 Unknown8; //0x004C  
	__int32 Unknown9; //0x0050  
	__int32 Hits; //0x0054  
	__int32 Shots; //0x0058  
	__int32 Shots1; //0x005C  
	__int32 Shots2; //0x0060 lowest value 
	char pad0[96]; //0x0064  
	__int32 Rank; //0x00C4  
	__int32 StartXpCurrentRank; //0x00C8  
	__int32 XPAtNextRank; //0x00CC  
	__int32 XpAtLastRank; //0x00D0  
	char pad1[588]; //0x00D4  
	__int32 M16_Marksman; //0x0320 Start soldier guns 
	__int32 M16_Expert; //0x0324  
	__int32 AK47_Expert; //0x0328  
	__int32 AK47_Marksman; //0x032C  
	__int32 G3_Marksman; //0x0330  
	__int32 G3_Expert; //0x0334  
	__int32 M4Karabine_Marksman; //0x0338  
	__int32 M4Karabine_Expert; //0x033C  
	__int32 M14_Marksman; //0x0340  
	__int32 M14_Expert; //0x0344  
	__int32 G63C_Marksman; //0x0348  
	__int32 G63C_Expert; //0x034C  
	__int32 MP44_Expert; //0x0350 End 
	char pad2[28]; //0x0354  
	__int32 MP5_Marksman; //0x0370 Start MP's 
	__int32 MP5_Expert; //0x0374  
	__int32 Skorpion_Marksman; //0x0378  
	__int32 Skorpion_Expert; //0x037C  
	__int32 MiniUzi_Marksman; //0x0380  
	__int32 MiniUzi_Expert; //0x0384  
	__int32 AK74u_Marksman; //0x0388  
	__int32 AK74u_Expert; //0x038C  
	__int32 P90_Marksman; //0x0390  
	__int32 P90_Expert; //0x0394 End 
	char pad3[40]; //0x0398  
	__int32 M249SAW_Marksman; //0x03C0 Start MG's 
	__int32 M249SAW_Expert; //0x03C4  
	__int32 RPD_Marksman; //0x03C8  
	__int32 RPD_Expert; //0x03CC  
	__int32 M60E4_Marksman; //0x03D0  
	__int32 M60E4_Expert; //0x03D4 End 
	char pad4[56]; //0x03D8  
	__int32 W1200_Marksman; //0x0410 Start shotguns 
	__int32 W1200_Expert; //0x0414  
	__int32 M4_Marksman; //0x0418  
	__int32 M4_Expert; //0x041C End 
	char pad5[64]; //0x0420  
	__int32 M21_Marksman; //0x0460 Start Snipers 
	__int32 M21_Expert; //0x0464  
	__int32 M40A3_Marksman; //0x0468  
	__int32 M40A3_Expert; //0x046C  
	__int32 Drawgunow_Marksman; //0x0470  
	__int32 Dragunow_Expert; //0x0474  
	__int32 R700_Marksman; //0x0478  
	__int32 R700_Expert; //0x047C  
	__int32 Barrett_kal50_Marksman; //0x0480  
	__int32 Barrett_kal50_Expert; //0x0484 End 
	char pad6[40]; //0x0488  
	__int32 Radar_Started; //0x04B0 Start Trainingslager 
	__int32 LuftAngriff_Started; //0x04B4  
	__int32 HeliNaehrtSich; //0x04B8  
	__int32 FliegenKlatsche; //0x04BC  
	__int32 Marathon_Miles; //0x04C0  
	__int32 Wiedersehen; //0x04C4  
	__int32 GebaeudeSprung; //0x04C8  
	__int32 GeduckterSchuss; //0x04CC  
	__int32 LiegenderSchuss; //0x04D0  
	__int32 GranatenAbschuss; //0x04D4  
	__int32 AufbauSpieler; //0x04D8  
	__int32 Roentgenblick; //0x04DC  
	__int32 Vandalismus; //0x04E0  
	__int32 Ungeschuetzt; //0x04E4  
	__int32 RauchExplosion; //0x04E8  
	__int32 MesserVeteran; //0x04EC  
	char pad7[16]; //0x04F0  
	__int32 FreiFuerAlleSieger; //0x0500 Opertaion Herausforderungen Start 
	__int32 TeamSpieler; //0x0504  
	__int32 SuchenUndZerstoerenSieger; //0x0508  
	__int32 MVPTeamDeathmatch; //0x050C  
	__int32 HardcoreTeamspieler; //0x0510  
	__int32 SabotageSieger; //0x0514  
	__int32 MVPTeamHardCore; //0x0518  
	__int32 BombenTraeger; //0x051C  
	__int32 BombenVerteidiger; //0x0520  
	__int32 BombenLeger; //0x0524  
	__int32 Held; //0x0528  
	__int32 LastManStanding; //0x052C End 
	char pad8[32]; //0x0530  
	__int32 ClaymoreSchuetze; //0x0550 Killer Herausforderungen 
	__int32 SturmGewehr_Expert; //0x0554  
	__int32 MP_Expert; //0x0558  
	__int32 MG_Expert; //0x055C  
	__int32 EliminatorVeteran; //0x0560  
	__int32 Schaerf_Expert; //0x0564  
	__int32 LuftschlagVeteran; //0x0568  
	__int32 HeliVeteran; //0x056C  
	__int32 HandGranatenVeteran; //0x0570  
	__int32 MultiRaketenWerfer; //0x0574  
	__int32 MartyriumVeteran; //0x0578  
	__int32 ClayMore; //0x057C  
	__int32 Heimlich; //0x0580  
	__int32 Unsichtbar; //0x0584  
	__int32 KonterClaymore; //0x0588  
	__int32 KonterC4; //0x058C End 
	char pad9[16]; //0x0590  
	__int32 UeberFlieger; //0x05A0 Demuetigung Herausforderungen start 
	__int32 MultiFrag; //0x05A4  
	__int32 TeppichBombe; //0x05A8  
	__int32 MGMeister; //0x05AC  
	__int32 Schlitzer; //0x05B0  
	__int32 MultiC4; //0x05B4  
	__int32 HeisseKartoffel; //0x05B8  
	__int32 Autobombe; //0x05BC  
	__int32 Verraeter; //0x05C0  
	__int32 LangsamAberSicher; //0x05C4  
	__int32 BlendGranatenVeteran; //0x05C8  
	__int32 GeteiltesLeid; //0x05CC  
	__int32 Autsch; //0x05D0  
	__int32 Rivale; //0x05D4  
	__int32 Grausamkeit; //0x05D8  
	__int32 Schnelldenker; //0x05DC  
	__int32 SchnelldenkerHandgranate; //0x05E0  
	__int32 SchnelldenkerBlendgranate; //0x05E4  
	__int32 ZurueckAnDenAbsender; //0x05E8  
	__int32 BlindFeuer; //0x05EC End 
	__int32 DerRand; //0x05F0 Elite Herausforderungen 
	__int32 Kollateralschaden; //0x05F4  
	__int32 DieKante; //0x05F8  
	__int32 Makellos; //0x05FC  
	__int32 ZielErledigt; //0x0600  
	__int32 HarteLandung; //0x0604  
	__int32 ExtremeGrausamkeit; //0x0608  
	__int32 SchnellerWechsel; //0x060C  
	__int32 StarSpieler; //0x0610  
	__int32 WieZum; //0x0614  
	__int32 Domino; //0x0618  
	__int32 KeineGeheimnisse; //0x061C  
	__int32 Nachbrenner; //0x0620  
	__int32 Lufthoheit; //0x0624  
	__int32 Furchtlos; //0x0628  
	__int32 KonterMVP; //0x062C  
	__int32 Unbesiegbar; //0x0630  
	__int32 Lebenskuenstler; //0x0634 Ende 
	__int32 Unknown10; //0x0638  
};//Size=0x063C(1596)

typedef struct
{
    short UNKNOW; 
    short active; 
    short j_spine4; 
    short j_helmet;
    short j_head; 
    short UNKNOW_2; 
    short allies; 
    short axis; 
    short bad_path; 
    short begin_firing; 
    short cancel_location; 
    short confirm_location;
    short crouch; 
    short current; 
    short damage; 
    short dead; 
    short death;
    short detonate;
    short direct;
    short dlight; 
    short done; 
    short empty;
    short end_firing;
    short entity; 
    short explode; 
    short failed; 
    short fraction; 
    short free; 
    short goal; 
    short goal_changed; 
    short goal_yaw; 
    short grenade; 
    short grenade_danger; 
    short grenade_fire;
    short grenade_pullback; 
    short info_notnull;
    short invisible; 
    short key1; 
    short key2; 
    short killanimscript; 
    short left; 
    short light; 
    short movedone; 
    short noclass; 
    short none; 
    short normal; 
    char   z_crap[4];
    short projectile_impact; 
    short prone; 
    short right; 
    short reload; 
    short reload_start; 
    short rocket;
    short rotatedone;
    short script_brushmodel; 
    short script_model;
    short script_origin; 
    short snd_enveffectsprio_level;
    short snd_enveffectsprio_shellshock; 
    short snd_channelvolprio_holdbreath; 
    short snd_channelvolprio_pain; 
    short snd_channelvolprio_shellshock; 
    short stand; 
    short suppression; 
    short suppression_end; 
    short surfacetype; 
    short tag_aim; 
    short tag_aim_animated; 
    short tag_brass; 
    short tag_butt; 
    short tag_clip; 
    short tag_flash; 
    short tag_flash_11; 
    short tag_flash_2; 
    short tag_flash_22; 
    short tag_flash_3; 
    short tag_fx; 
    short tag_inhand;
    short tag_knife_attach;
    short tag_knife_fx; 
    short tag_laser; 
    short tag_origin; 
    short tag_weapon;
    short tag_player; 
    short tag_camera; 
    short tag_weapon_right; 
    short tag_gasmask; 
    short tag_gasmask2; 
    short tag_sync; 
    short target_script_trigger;
    short tempEntity; 
    short UNKNOW_3; 
    short touch; 
    short trigger; 
    short trigger_use; 
    short trigger_use_touch; 
    short trigger_damage; 
    short trigger_lookat;
    short truck_cam; 
    short weapon_change; 
    short weapon_fired; 
    short worldspawn; 
    short flashbang; 
    short flash; 
    short smoke; 
    short night_vision_on; 
    short night_vision_off; 
    short MOD_UNKNOWN; 
    short MOD_PISTOL_BULLET;
    short MOD_RIFLE_BULLET;
    short MOD_GRENADE;
    short MOD_GRENADE_SPLASH; 
    short MOD_PROJECTILE; 
    short MOD_PROJECTILE_SPLASH; 
    short MOD_MELEE; 
    short MOD_HEAD_SHOT;
    short MOD_CRUSH; 
    short MOD_TELEFRAG; 
    short MOD_FALLING; 
    short MOD_SUICIDE; 
    short MOD_TRIGGER_HURT;
    short MOD_EXPLOSIVE;
    short MOD_IMPACT; 
    short script_vehicle; 
    short script_vehicle_collision; 
    short script_vehicle_collmap; 
    short script_vehicle_corpse; 
    short turret_fire; 
    short turret_on_target; 
    short turret_not_on_target;
    short turret_on_vistarget; 
    short turret_no_vis; 
    short turret_rotate_stopped; 
    short turret_deactivate; 
    short turretstatechange; 
    short turretownerchange; 
    short reached_end_node; 
    short reached_wait_node; 
    short reached_wait_speed;
    short near_goal; 
    short veh_collision; 
    short veh_predictedcollision; 
    short auto_change; 
    short back_low; 
    short back_mid; 
    short back_up; 
    short begin; 
    short call_vote;
    short freelook;
    short head; 
    short intermission; 
    short j_head2; 
    short manual_change; 
    short menuresponse; 
    short neck;
    short pelvis; 
    short pistol; 
    short plane_waypoint; 
    short playing; 
    short spectator; 
    short vote; 
    short sprint_begin; 
    short sprint_end; 
    short tag_driver; 
    short tag_passenger;
    short tag_gunner; 
    short tag_wheel_front_left; 
    short tag_wheel_front_right; 
    short tag_wheel_back_left; 
    short tag_wheel_back_right; 
    short tag_wheel_middle_left; 
    short tag_wheel_middle_righ; 
    short tag_detach; 
    short tag_popout; 
    short tag_body; 
    short tag_turret; 
    short tag_turret_base; 
    short tag_barrel; 
    short tag_engine_left; 
    short tag_engine_right; 
    short front_left; 
    short front_right; 
    short back_left; 
    short back_right; 
    short tag_gunner_pov; 
} RE_Tags_t;//0x1406E90  size:174(DEZ.372)

typedef struct
{
    char			z_crap[180];
    int					lerpBase;
    char			z_crap2[292];
}Prediction_t;

/*==============================================================================================*/