#include <Audio/Song.h>

#include <Content/File.h>
#include <Content/Filesystem.h>

#include "SongInternalPS3.h"

Song::Song() :
	internal_( new SongInternal )
{
}

Song::~Song() 
{
	delete internal_;
}

void Song::Load( const std::string &path )
{
}
