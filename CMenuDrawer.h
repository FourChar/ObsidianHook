#pragma once
 
typedef enum
{
	OBJECT_BOOL,
	OBJECT_FLOAT,
	OBJECT_INT,
	OBJECT_NONE
} Menu_ObjectType;
 
typedef struct
{
	int								Index;
	float							X;
	float							Y;
	std::string						Object_String;
	Menu_ObjectType					Object_Type;
	union
	{
		bool			*			bool_State;
		int				*			int_State;
		float			*			float_State;
	} Object_State;
	union
	{
		int							int_Value;
		float						float_Value;
	} Diffrence_Value;
 
} Menu_Object;
 
class CMenuDrawer
{
public:
	void							BeginUpdate								( );
	void							EndUpdate								( );
 
	void							DrawMenu								( );
	void							DrawCursor								( );
	void							DrawMenuObjects							( );
	void							DrawBorder								( float X, float Y, float Width, float Height, BorderSettings_t *BorderSettings );
	void							DrawWindow								( float X, float Y, float Width, float Height, BorderSettings_t *BorderSettings, cdstl::Mathematics::Vector2 *TitleOffset, std::string Title );
 
	void							SetBorderSettings						( BorderSettings_t *BorderSettings,
																				DWORD MainColor, DWORD WindowFillColor, DWORD TopBoarderColor,
																				bool InSet, bool FillCorners, bool FillWindow, bool UseTopBorder, int TopBorderHight );
   
	void							AddMenuCategory							( float X, float Y, std::string Object_String );

	void							AddMenuObject							( float X, float Y, bool  *Object_State, std::string Object_String );
	void							AddMenuObject							( float X, float Y, float *Object_State, float DiffrenceValue, std::string Object_String );
	void							AddMenuObject							( float X, float Y, int   *Object_State, int DiffrenceValue, std::string Object_String );
 
	float				&			GetCursorPosition						( bool X );
	bool				&			GetMenuActive							( );
	bool				&			isMouseMenu								( );
 
private:
	float							CursorPositionX;
	float							CursorPositionY;
 
	bool							MenuActive;
	bool							MouseMenu;
 
	std::vector< Menu_Object >		MenuObjects;
	int								MenuObjectAmount;
	int								SelectedObject;
};