#include <Audio/Song.h>

#include <Content/File.h>
#include <Content/Filesystem.h>
#include <Utility/Log.h>

#include "SongInternalVita.h"

float GetMP3Length( const std::string &path )
{
	return 0;
}

Song::Song() :
	internal_( new SongInternal )
{
	Duration.TotalSeconds = 0.f;
}

Song::~Song() 
{
	delete internal_;
}

extern std::string VITA_PATH_PREFIX;

void Song::Load( const std::string &path )
{
	internal_->Path = VITA_PATH_PREFIX + "ContentVita/" + path;
	Duration.TotalSeconds = GetMP3Length( internal_->Path );
}
