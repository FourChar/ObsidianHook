#include "stdafx.h"

namespace cdstl
{
	void Allocator::Set_Name( std::string Name )
	{
		if( cdstl::getStringLength( Name ) > 0 )
			this->Name = Name;
		else
			this->Name = "CDSTL";
	}
	std::string *Allocator::Get_Name( )
	{
		if( cdstl::getStringLength( this->Name ) > 0 )
			return &this->Name;

		return &std::string( "CDSTL" );
	}
	void *Allocator::Allocate( unsigned int Size )
	{
		if( Size > 0 )
			return malloc( Size );

		return malloc( 0x2000 );
	}
	void Allocator::Deallocate( void *AllocatedSpace )
	{
		free( AllocatedSpace );
	}

	size_t getStringLength( std::string String )
	{
		const char		*		tempString			= String.c_str( );
		size_t					LetterCount			= NULL;

		while( *tempString )
		{
			LetterCount++;
			tempString++;
		}

		return LetterCount;
	}
};