#pragma once

namespace cdstl
{
	namespace Mathematics
	{
		static const DWORD M_PI		= 3.14159265358979323846f;
		static const DWORD M_E		= 2.71828182845904523536f;

		class Color32
		{
		public:
			Color32( ){ }
			Color32( float Red, float Green, float Blue, float Alpha )
			{
				this->Red		= Red;
				this->Green		= Green;
				this->Blue		= Blue;
				this->Alpha		= Alpha;
			}

			float	Red;
			float	Green;
			float	Blue;
			float	Alpha;
		};
			
		class Rect
		{
		public:
			Rect( ){ }
			Rect( float X, float Y, float Width, float Height )
			{
				this->X			= X;
				this->Y			= Y;
				this->Width		= Width;
				this->Height	= Height;
			}
			
			float	X;
			float	Y;
			float	Width;
			float	Height;
		};
		class Vector2
		{
		public:
			Vector2( ){ }
			Vector2( float One, float Two )
			{
				this->Vec1	= One;
				this->Vec2	= Two;
			}

			Vector2 & operator = ( Vector2 & From )
			{
				this->Vec1	= From.Vec1;
				this->Vec2	= From.Vec2;

				return (*this);
			}

			float DistanceFrom( Vector2 One )
			{
				Vector2 Distance( 
					One.Vec1 - this->Vec1, 
					One.Vec2 - this->Vec2 );

				return sqrt( ( Distance.Vec1 * Distance.Vec1 ) + ( Distance.Vec2 * Distance.Vec2 ) );
			}

			float	Vec1;
			float	Vec2;
		};
		class Vector3
		{
		public:
			Vector3( ){ }
			Vector3( float One, float Two, float Three )
			{
				this->Vec1	= One;
				this->Vec2	= Two;
				this->Vec3	= Three;
			}

			Vector3 & operator = ( Vector3 & From )
			{
				this->Vec1	= From.Vec1;
				this->Vec2	= From.Vec2;
				this->Vec3	= From.Vec3;

				return (*this);
			}

			float Dot( Vector3 Vec )
			{
				return( (this->Vec1 * Vec.Vec1) + 
						(this->Vec2 * Vec.Vec2) + 
						(this->Vec3 * Vec.Vec3) );
			}

			float DistanceFrom( Vector3 One )
			{
				Vector3 Distance(
					One.Vec1 - this->Vec1,
					One.Vec2 - this->Vec2,
					One.Vec3 - this->Vec3 );

				return sqrt( ( Distance.Vec1 * Distance.Vec1 ) + ( Distance.Vec2 * Distance.Vec2 ) + ( Distance.Vec3 * Distance.Vec3 ) );
			}

			float	Vec1;
			float	Vec2;
			float	Vec3;
		};
		class Vector4
		{
		public:
			Vector4( ){ }
			Vector4( float One, float Two, float Three, float Four )
			{
				this->Vec1	= One;
				this->Vec2	= Two;
				this->Vec3	= Three;
				this->Vec4	= Four;
			}

			Vector4 & operator = ( Vector4 & From )
			{
				this->Vec1	= From.Vec1;
				this->Vec2	= From.Vec2;
				this->Vec3	= From.Vec3;
				this->Vec4	= From.Vec4;

				return (*this);
			}

			float Dot( Vector4 Vec )
			{
				return( (this->Vec1 * Vec.Vec1) + 
						(this->Vec2 * Vec.Vec2) + 
						(this->Vec3 * Vec.Vec3) + 
						(this->Vec4 * Vec.Vec4) );
			}

			float DistanceFrom( Vector4 One )
			{
				Vector4 Distance(
					One.Vec1 - this->Vec1,
					One.Vec2 - this->Vec2,
					One.Vec3 - this->Vec3,
					One.Vec4 - this->Vec4 );

				return sqrt( ( Distance.Vec1 * Distance.Vec1 ) 
					+ ( Distance.Vec2 * Distance.Vec2 ) 
					+ ( Distance.Vec3 * Distance.Vec3 ) 
					+ ( Distance.Vec4 * Distance.Vec4 ) );
			}

			float	Vec1;
			float	Vec2;
			float	Vec3;
			float	Vec4;
		};

		class Player
		{
		public:
			Player( ){ }
			Player( std::string Name, Vector3 Location, DWORD EntityFlags )
			{
				this->Name				= Name;
				this->Location			= Location;
				this->EntityFlags		= EntityFlags;
			}

			/*bool DrawBoxAroundPlayer( Color32 Color )
			{
				Vector3 tempLocation( this->Location.Vec1, this->Location.Vec2, this->Location.Vec3 );

				if( EntityFlags & FLAGS_PRONE || 
					EntityFlags & FLAGS_PRONE_FORWARD || 
					EntityFlags & FLAGS_PRONE_BACKWARD )
				{
					tempLocation.Vec3 += 20;
				}
				else if( EntityFlags & FLAGS_CROUCH || 
						 EntityFlags & FLAGS_CROUCH_FORWARD || 
						 EntityFlags & FLAGS_CROUCH_BACKWARD )
				{
					tempLocation.Vec3 += 40;
				}
				else
				{
					tempLocation.Vec3 += 55;
				}

				float FootX, FootY, HeadX, HeadY;
				if( Math::WorldToScreen( vOut, &HeadX, &HeadY ) )
				{
					if( Math::WorldToScreen( this->Location, &FootX, &FootY ) )
					{
						float BoxLength = ((FootY+10) - HeadY);
						float BoxWidth  = (BoxLength/2.2);
						float BoxFlow   = (HeadX - (BoxWidth/2));

						if(BoxWidth > 240)
							BoxWidth = 240;
						if(BoxLength > 518)
							BoxLength = 518;

						D3DRenderer.ESPDrawer.DrawPlayerSquare( BoxFlow, FootY - BoxLength, BoxWidth, BoxLength, D3DCOLOR_RGBA( Color.Red, Color.Green, Color.Blue, Color.Alpha ) );
					}
				}
			}*/

			std::string					Name;
			Vector3						Location;
			DWORD						EntityFlags;
		};
	};

	class Allocator
	{
	public:
		Allocator( )
		{
			this->Name = "CDSTL";
		}
		Allocator( std::string Name )
		{
			this->Name = Name;
		}

		void						Set_Name								( std::string Name );
		std::string			*		Get_Name								( );
		void				*		Allocate								( size_t Size );
		void						Deallocate								( void *AllocatedSpace );

	private:
		std::string					Name;
	};

	size_t							getStringLength							( std::string String );
};