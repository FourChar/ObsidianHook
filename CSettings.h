#pragma once

typedef enum
{
	SETTING_BOOL,
	SETTING_INT,
	SETTING_DWORD,
	SETTING_FLOAT,
	SETTING_VEC2,
	SETTING_VEC3,
	SETTING_VEC4,
	SETTING_STRING,
	
	SETTING_NONE
} SettingType_t;

typedef struct
{
	SettingType_t			eType;
	std::string				OptionCategory;
	std::string				OptionName;
	char					szDefault[256];

	union
	{
		bool				_bool;
		int					_int;
		float				_float;
		Vector2				_vec2;
		Vector3				_vec3;
		Vector4				_vec4;
		char				_char[256];
	} Value;

	union
	{
		float				_float;
		int					_int;
	} MinValue;

	union
	{
		float				_float;
		int					_int;
	} MaxValue;
} Config_t;

typedef struct
{
	Config_t			*			Aim_Aimbot;
	Config_t			*			Aim_AutoKnife;
	Config_t			*			Aim_AutoShoot;
	Config_t			*			Aim_AutoZoom;
	Config_t			*			Aim_ManualPrediction;
	Config_t			*			Aim_LimitFov;

	Config_t			*			ESP_Name;
	Config_t			*			ESP_Distance;
	Config_t			*			ESP_Box;
	Config_t			*			ESP_Weapon;
	Config_t			*			ESP_HeadBox;
	Config_t			*			ESP_Barrel;
	Config_t			*			ESP_Helicopter;

	Config_t			*			Misc_NoRecoil;
	Config_t			*			Misc_CrossHair;
	Config_t			*			Misc_AutoShoot;
	Config_t			*			Misc_AutoVote;
	Config_t			*			Misc_NameStealer;

	Config_t			*			Render_WeaponInfo;
	Config_t			*			Render_Radar;
	Config_t			*			Render_FullBright;
	Config_t			*			Render_NoShellShock;

	Config_t			*			General_VisibleChecks;

	Config_t			*			Beta_FixESPJump;

	bool							LoadSettings;
	bool							SaveSettings;
} Settings_t;

class CSettings
{
public:
	void							InitiateSettings							( );
	void							UpdateAll									( );

	void							LoadSettingsFromFile						( );
	void							LoadSettingsFromFileEx						( const std::string FileLocation );

	void							SaveSettingsToFile							( );
	void							SaveSettingsToFileEx						( const std::string FileLocation );

	void							SetSettingsFileLocation						( const std::string FileLocation );
	const std::string				GetSettingsFileLocation						( );

	Config_t			*			AddOptionToSettings							( const std::string OptionCategory, const std::string OptionName, const bool DefaultState );
	Config_t			*			AddOptionToSettings							( const std::string OptionCategory, const std::string OptionName, const std::string DefaultState );
	Config_t			*			AddOptionToSettings							( const std::string OptionCategory, const std::string OptionName, const int DefaultState, const int Minimum, const int Maximum );
	Config_t			*			AddOptionToSettings							( const std::string OptionCategory, const std::string OptionName, const float DefaultState, const float Minimum, const float Maximum );
	Config_t			*			AddOptionToSettings_DWORD					( const std::string OptionCategory, const std::string OptionName, const DWORD DefaultState );
	Config_t			*			AddOptionToSettings_Vec2					( const std::string OptionCategory, const std::string OptionName, const float DefaultState[2], const float Minimum, const float Maximum );
	Config_t			*			AddOptionToSettings_Vec3					( const std::string OptionCategory, const std::string OptionName, const float DefaultState[3], const float Minimum, const float Maximum );
	Config_t			*			AddOptionToSettings_Vec4					( const std::string OptionCategory, const std::string OptionName, const float DefaultState[4], const float Minimum, const float Maximum );

	Settings_t						Options;
	bool							isNewFile;
private:
	std::string						FileLocation;
	Config_t						Config[ 1024 ];
	size_t							ConfigSize;
	
};
extern CSettings Settings;