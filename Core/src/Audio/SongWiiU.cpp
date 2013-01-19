#include <Audio/Song.h>

#include <cafe/mem.h>

#include <Content/File.h>
#include <Content/Filesystem.h>

#include "SongInternalWiiU.h"

Song::Song() :
	internal_( new SongInternal )
{
	Duration.TotalSeconds = 0;

	internal_->Data = 0;
	internal_->Length = 0;
}

Song::~Song() 
{
	MEMFreeToDefaultHeap( internal_->Data );

	delete internal_;
}

void Song::Load( const std::string &path )
{
	std::string temp = path;

	std::string extension = temp.substr( temp.length() - 3, 3 );
	if( extension == "wma" )
	{
		temp[ temp.length() - 3 ] = 'a';
		temp[ temp.length() - 2 ] = 'a';
		temp[ temp.length() - 1 ] = 'c';
	}

	boost::shared_ptr< File > file = FILESYSTEM.Open( temp );

	internal_->Data = MEMAllocFromDefaultHeapEx( file->Size(), 64 );
	internal_->Length = file->Size();

	file->Read( reinterpret_cast< char * >( internal_->Data ), internal_->Length );
}
