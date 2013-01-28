#include <Audio/Song.h>

#include <Utility/Log.h>

#include "SongInternalWiiU.h"

Song::Song() :
	internal_( new SongInternal )
{
	Duration.TotalSeconds = 0;

	internal_->Song = NULL;
}

Song::~Song() 
{
	if( internal_->Song )
		internal_->Song->release();

	delete internal_;
}

void Song::Load( const std::string &path )
{
	std::string internalPath = "/vol/content/" + path;
	size_t pathLength = internalPath.size();

	internalPath[ pathLength - 3 ] = 'm';
	internalPath[ pathLength - 2 ] = 'p';
	internalPath[ pathLength - 1 ] = '3';

	FMOD_RESULT result;
	result = FMODSystem->createStream( internalPath.c_str(), FMOD_NONBLOCKING, 0, &internal_->Song );
	if( result != FMOD_OK )
	{
		LOG.Write( "Failed to load song: %s\n", internalPath.c_str() );
		internal_->Song = NULL;
		return;
	}

	unsigned int length;
	internal_->Song->getLength( &length, FMOD_TIMEUNIT_MS );

	Duration.TotalSeconds = static_cast< float >( length ) / 1000.f;
}
