#include "stdafx.h"

#define LIMIT_VALUE(val,min,max)		if( (val) > (max) ) \
										{ \
											(val) = (max); \
										} \
										else if( (val) < (min) ) \
										{ \
											(val) = (min); \
										}

void CSettings::InitiateSettings( )
{
	memset( this->Config, 0, sizeof( Config_t ) );
	ConfigSize = 0;

	this->Options.Aim_Aimbot				=	AddOptionToSettings( "Aimbot", "Auto_Aim", false );
	this->Options.Aim_AutoKnife				=	AddOptionToSettings( "Aimbot", "Auto_Knife", false );
	this->Options.Aim_AutoShoot				=	AddOptionToSettings( "Aimbot", "Auto_Shoot", false );
	this->Options.Aim_AutoZoom				=	AddOptionToSettings( "Aimbot", "Auto_Zoom", false );
	this->Options.Aim_ManualPrediction		=	AddOptionToSettings( "Aimbot", "ManualPrediction", 1.0f, 0.0f, 50.0f );
	this->Options.Aim_LimitFov				=	AddOptionToSettings( "Aimbot", "LimitFov", 360, 10, 360 );

	this->Options.ESP_Name					=	AddOptionToSettings( "Extra-Sensory Perception", "Name", false );
	this->Options.ESP_Distance				=	AddOptionToSettings( "Extra-Sensory Perception", "Distance", false );
	this->Options.ESP_Box					=	AddOptionToSettings( "Extra-Sensory Perception", "Box", false );
	this->Options.ESP_Weapon				=	AddOptionToSettings( "Extra-Sensory Perception", "Weapon", false );
	this->Options.ESP_HeadBox				=	AddOptionToSettings( "Extra-Sensory Perception", "Head_Box", false );
	this->Options.ESP_Barrel				=	AddOptionToSettings( "Extra-Sensory Perception", "Barrel", false );
	this->Options.ESP_Helicopter			=	AddOptionToSettings( "Extra-Sensory Perception", "Helicopter", false );

	this->Options.Misc_NoRecoil				=	AddOptionToSettings( "Miscellaneous", "No_Recoil", false );
	this->Options.Misc_CrossHair			=	AddOptionToSettings( "Miscellaneous", "CrossHair", false );
	this->Options.Misc_AutoShoot			=	AddOptionToSettings( "Miscellaneous", "AutoShoot", false );
	this->Options.Misc_AutoVote				=	AddOptionToSettings( "Miscellaneous", "AutoVote", false );
	this->Options.Misc_NameStealer			=	AddOptionToSettings( "Miscellaneous", "NameStealer", false );

	this->Options.Render_WeaponInfo			=	AddOptionToSettings( "Render", "Weapon_Info", false );
	this->Options.Render_Radar				=	AddOptionToSettings( "Render", "Radar", false );
	this->Options.Render_FullBright			=	AddOptionToSettings( "Render", "FullBright", false );
	this->Options.Render_NoShellShock		=	AddOptionToSettings( "Render", "No_Shellshock", false );

	this->Options.General_VisibleChecks		=	AddOptionToSettings( "General", "VisibleChecks", false );

	this->Options.Beta_FixESPJump			=	AddOptionToSettings( "Beta Stage", "Fix_ESP_Jumping", false );
}

void CSettings::UpdateAll( )
{
	if( this->Options.LoadSettings )
	{
		this->LoadSettingsFromFile( );
		this->Options.LoadSettings = false;
	}
	if( this->Options.SaveSettings )
	{
		this->SaveSettingsToFile( );
		this->Options.SaveSettings = false;
	}
}

void CSettings::LoadSettingsFromFile( )
{
	char			OptionValue[ 1024 ];
	Config_t	*	tempConfig;

	for( size_t i = 0; i < this->ConfigSize; i++ )
	{
		tempConfig = &this->Config[ i ];

		GetPrivateProfileString( tempConfig->OptionCategory.c_str( ), tempConfig->OptionName.c_str( ), (LPCSTR)tempConfig->szDefault, OptionValue, 1024, this->FileLocation.c_str( ) );

		switch( tempConfig->eType )
		{
		case SETTING_BOOL:
			{
				tempConfig->Value._bool = ( _stricmp( OptionValue, "true" ) == 0 );
			}
			break;

		case SETTING_INT:
			{
				tempConfig->Value._int = atoi( OptionValue );

				LIMIT_VALUE( tempConfig->Value._int, tempConfig->MinValue._int, tempConfig->MaxValue._int );
			}
			break;

		case SETTING_DWORD:
			{
				tempConfig->Value._int = atoi( OptionValue );
			}
			break;

		case SETTING_FLOAT:
			{
				tempConfig->Value._float = atof( OptionValue );

				LIMIT_VALUE( tempConfig->Value._float, tempConfig->MinValue._float, tempConfig->MaxValue._float );
			}
			break;

		case SETTING_VEC2:
			{
				sscanf_s( OptionValue, "%f %f", &tempConfig->Value._vec2[0], &tempConfig->Value._vec2[1] );

				LIMIT_VALUE( tempConfig->Value._vec2[0], tempConfig->MinValue._float, tempConfig->MaxValue._float );
				LIMIT_VALUE( tempConfig->Value._vec2[1], tempConfig->MinValue._float, tempConfig->MaxValue._float );
			}
			break;


		case SETTING_VEC3:
			{
				sscanf_s( OptionValue, "%f %f %f", &tempConfig->Value._vec3[0], &tempConfig->Value._vec3[1], &tempConfig->Value._vec3[2] );

				LIMIT_VALUE( tempConfig->Value._vec3[0], tempConfig->MinValue._float, tempConfig->MaxValue._float );
				LIMIT_VALUE( tempConfig->Value._vec3[1], tempConfig->MinValue._float, tempConfig->MaxValue._float );
				LIMIT_VALUE( tempConfig->Value._vec3[2], tempConfig->MinValue._float, tempConfig->MaxValue._float );
			}
			break;

		case SETTING_VEC4:
			{
				sscanf_s( OptionValue, "%f %f %f %f", &tempConfig->Value._vec4[0], &tempConfig->Value._vec4[1], &tempConfig->Value._vec4[2], &tempConfig->Value._vec4[3] );
			
				LIMIT_VALUE( tempConfig->Value._vec4[0], tempConfig->MinValue._float, tempConfig->MaxValue._float );
				LIMIT_VALUE( tempConfig->Value._vec4[1], tempConfig->MinValue._float, tempConfig->MaxValue._float );
				LIMIT_VALUE( tempConfig->Value._vec4[2], tempConfig->MinValue._float, tempConfig->MaxValue._float );
				LIMIT_VALUE( tempConfig->Value._vec4[3], tempConfig->MinValue._float, tempConfig->MaxValue._float );
			}
			break;

		case SETTING_STRING:
			{
				strncpy_s< 256 >( tempConfig->Value._char, OptionValue, 255 );
			}
			break;

		default:
			break;
		}
	}
}
void CSettings::LoadSettingsFromFileEx( const std::string FileLocation )
{
	std::string temp_FileLocation		= this->FileLocation;
	this->SetSettingsFileLocation( FileLocation );

	this->LoadSettingsFromFile( );

	this->SetSettingsFileLocation( temp_FileLocation );
}

void CSettings::SaveSettingsToFile( )
{
	char			OptionValue[ 1024 ];
	Config_t	*	tempConfig;

	for( size_t i = 0; i < this->ConfigSize; i++ )
	{
		tempConfig = &this->Config[ i ];

		switch( tempConfig->eType )
		{
		case SETTING_BOOL:
			{
				strcpy_s< 1024 >( OptionValue, ( tempConfig->Value._bool ) ? "true" : "false" );
			}
			break;

		case SETTING_INT:
			{
				LIMIT_VALUE( tempConfig->Value._int, tempConfig->MinValue._int, tempConfig->MaxValue._int );

				sprintf_s< 1024 >( OptionValue, "%i", tempConfig->Value._int );
			}
			break;

		case SETTING_DWORD:
			{
				sprintf_s< 1024 >( OptionValue, "%i", tempConfig->Value._float );
			}
			break;

		case SETTING_FLOAT:
			{
				LIMIT_VALUE( tempConfig->Value._float, tempConfig->MinValue._float, tempConfig->MaxValue._float );

				sprintf_s< 1024 >( OptionValue, "%.3f", tempConfig->Value._float );
			}
			break;

		case SETTING_VEC2:
			{
				LIMIT_VALUE( tempConfig->Value._vec2[0], tempConfig->MinValue._float, tempConfig->MaxValue._float );
				LIMIT_VALUE( tempConfig->Value._vec2[1], tempConfig->MinValue._float, tempConfig->MaxValue._float );

				sprintf_s< 1024 >( OptionValue, "%.3f %.3f", tempConfig->Value._vec2[0], tempConfig->Value._vec2[1] );
			}
			break;

		case SETTING_VEC3:
			{
				LIMIT_VALUE( tempConfig->Value._vec3[0], tempConfig->MinValue._float, tempConfig->MaxValue._float );
				LIMIT_VALUE( tempConfig->Value._vec3[1], tempConfig->MinValue._float, tempConfig->MaxValue._float );
				LIMIT_VALUE( tempConfig->Value._vec3[2], tempConfig->MinValue._float, tempConfig->MaxValue._float );

				sprintf_s< 1024 >( OptionValue, "%.3f %.3f %.3f", tempConfig->Value._vec3[0], tempConfig->Value._vec3[1], tempConfig->Value._vec3[2] );
			}
			break;

		case SETTING_VEC4:
			{
				LIMIT_VALUE( tempConfig->Value._vec3[0], tempConfig->MinValue._float, tempConfig->MaxValue._float );
				LIMIT_VALUE( tempConfig->Value._vec3[1], tempConfig->MinValue._float, tempConfig->MaxValue._float );
				LIMIT_VALUE( tempConfig->Value._vec3[2], tempConfig->MinValue._float, tempConfig->MaxValue._float );
				LIMIT_VALUE( tempConfig->Value._vec3[3], tempConfig->MinValue._float, tempConfig->MaxValue._float );

				sprintf_s< 1024 >( OptionValue, "%.3f %.3f %.3f %.3f", tempConfig->Value._vec4[0], tempConfig->Value._vec4[1], tempConfig->Value._vec4[2], tempConfig->Value._vec4[3] );
			}
			break;

		case SETTING_STRING:
			{
				strcpy_s< 1024 >( OptionValue, tempConfig->Value._char );
			}
			break;

		default:
			break;
		}

		WritePrivateProfileString( tempConfig->OptionCategory.c_str( ), tempConfig->OptionName.c_str( ), OptionValue, this->FileLocation.c_str( ) );
	}
}
void CSettings::SaveSettingsToFileEx( const std::string FileLocation )
{
	std::string temp_FileLocation		= this->FileLocation;
	this->SetSettingsFileLocation( FileLocation );

	this->SaveSettingsToFile( );

	this->SetSettingsFileLocation( temp_FileLocation );
}

void CSettings::SetSettingsFileLocation( const std::string FileLocation )
{
	//Create The file here if it doesn't exist.
	ifstream		temp_iFile( FileLocation.c_str( ) );
	if( !temp_iFile )
	{
		temp_iFile.close( );

		ofstream	temp_oFile( FileLocation.c_str( ) );
		temp_oFile.open( FileLocation.c_str( ) );
		temp_oFile.close( );

		this->isNewFile = true;
	}

	this->FileLocation = FileLocation;
}
const std::string CSettings::GetSettingsFileLocation( )
{
	return this->FileLocation;
}

Config_t *CSettings::AddOptionToSettings( const std::string OptionCategory, const std::string OptionName, const bool DefaultState )
{
	if( this->ConfigSize >= 1024 )
		return NULL;

	Config_t *tempConfig = &this->Config[ this->ConfigSize ];
	memset( tempConfig, 0, sizeof( Config_t ) );

	tempConfig->eType				= SETTING_BOOL;
	tempConfig->OptionCategory		= OptionCategory;
	tempConfig->OptionName			= OptionName;
	sprintf_s< 256 >( tempConfig->szDefault, "%s", ( DefaultState ) ? "True" : "False" );

	this->ConfigSize++;

	return tempConfig;
}

Config_t *CSettings::AddOptionToSettings( const std::string OptionCategory, const std::string OptionName, const std::string DefaultState )
{
	if( this->ConfigSize >= 1024 )
		return NULL;

	Config_t *tempConfig = &this->Config[ this->ConfigSize ];
	memset( tempConfig, 0, sizeof( Config_t ) );

	tempConfig->eType				= SETTING_STRING;
	tempConfig->OptionCategory		= OptionCategory;
	tempConfig->OptionName			= OptionName;
	strncpy_s< 256 >( tempConfig->szDefault, DefaultState.c_str( ), 256 );

	this->ConfigSize++;

	return tempConfig;
}

Config_t *CSettings::AddOptionToSettings( const std::string OptionCategory, const std::string OptionName, const int DefaultState, const int Minimum, const int Maximum )
{
	if( this->ConfigSize >= 1024 )
		return NULL;

	Config_t *tempConfig = &this->Config[ this->ConfigSize ];
	memset( tempConfig, 0, sizeof( Config_t ) );

	tempConfig->eType				= SETTING_INT;
	tempConfig->OptionCategory		= OptionCategory;
	tempConfig->OptionName			= OptionName;
	tempConfig->MinValue._int		= Minimum;
	tempConfig->MaxValue._int		= Maximum;
	sprintf_s< 256 >( tempConfig->szDefault, "%i", DefaultState );

	this->ConfigSize++;

	return tempConfig;
}

Config_t *CSettings::AddOptionToSettings( const std::string OptionCategory, const std::string OptionName, const float DefaultState, const float Minimum, const float Maximum )
{
	if( this->ConfigSize >= 1024 )
		return NULL;

	Config_t *tempConfig = &this->Config[ this->ConfigSize ];
	memset( tempConfig, 0, sizeof( Config_t ) );

	tempConfig->eType				= SETTING_FLOAT;
	tempConfig->OptionCategory		= OptionCategory;
	tempConfig->OptionName			= OptionName;
	tempConfig->MinValue._float		= Minimum;
	tempConfig->MaxValue._float		= Maximum;
	sprintf_s< 256 >( tempConfig->szDefault, "%.3f", DefaultState );

	this->ConfigSize++;

	return tempConfig;
}

Config_t *CSettings::AddOptionToSettings_DWORD( const std::string OptionCategory, const std::string OptionName, const DWORD DefaultState )
{
	if( this->ConfigSize >= 1024 )
		return NULL;

	Config_t *tempConfig = &this->Config[ this->ConfigSize ];
	memset( tempConfig, 0, sizeof( Config_t ) );

	tempConfig->eType				= SETTING_DWORD;
	tempConfig->OptionCategory		= OptionCategory;
	tempConfig->OptionName			= OptionName;
	sprintf_s< 256 >( tempConfig->szDefault, "%i", DefaultState );

	this->ConfigSize++;

	return tempConfig;
}

Config_t *CSettings::AddOptionToSettings_Vec2( const std::string OptionCategory, const std::string OptionName, const float DefaultState[2], const float Minimum, const float Maximum )
{
	if( this->ConfigSize >= 1024 )
		return NULL;

	Config_t *tempConfig = &this->Config[ this->ConfigSize ];
	memset( tempConfig, 0, sizeof( Config_t ) );

	tempConfig->eType				= SETTING_VEC2;
	tempConfig->OptionCategory		= OptionCategory;
	tempConfig->OptionName			= OptionName;
	tempConfig->MinValue._float		= Minimum;
	tempConfig->MaxValue._float		= Maximum;
	sprintf_s< 256 >( tempConfig->szDefault, "%.3f %.3f", DefaultState[0], DefaultState[1] );

	this->ConfigSize++;

	return tempConfig;
}

Config_t *CSettings::AddOptionToSettings_Vec3( const std::string OptionCategory, const std::string OptionName, const float DefaultState[3], const float Minimum, const float Maximum )
{
	if( this->ConfigSize >= 1024 )
		return NULL;

	Config_t *tempConfig = &this->Config[ this->ConfigSize ];
	memset( tempConfig, 0, sizeof( Config_t ) );

	tempConfig->eType				= SETTING_VEC3;
	tempConfig->OptionCategory		= OptionCategory;
	tempConfig->OptionName			= OptionName;
	tempConfig->MinValue._float		= Minimum;
	tempConfig->MaxValue._float		= Maximum;
	sprintf_s< 256 >( tempConfig->szDefault, "%.3f %.3f %.3f", DefaultState[0], DefaultState[1], DefaultState[2] );

	this->ConfigSize++;

	return tempConfig;
}

Config_t *CSettings::AddOptionToSettings_Vec4( const std::string OptionCategory, const std::string OptionName, const float DefaultState[4], const float Minimum, const float Maximum )
{
	if( this->ConfigSize >= 1024 )
		return NULL;

	Config_t *tempConfig = &this->Config[ this->ConfigSize ];
	memset( tempConfig, 0, sizeof( Config_t ) );

	tempConfig->eType				= SETTING_VEC4;
	tempConfig->OptionCategory		= OptionCategory;
	tempConfig->OptionName			= OptionName;
	tempConfig->MinValue._float		= Minimum;
	tempConfig->MaxValue._float		= Maximum;
	sprintf_s< 256 >( tempConfig->szDefault, "%.3f %.3f %.3f %.3f", DefaultState[0], DefaultState[1], DefaultState[2], DefaultState[3] );

	this->ConfigSize++;

	return tempConfig;
}