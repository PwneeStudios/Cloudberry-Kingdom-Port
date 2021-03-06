#include <Audio/Song.h>

#include <Architecture/Job.h>
#include <Architecture/Scheduler.h>
#include <Core.h>
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
	// FIXME: Do we still need to clean up even when we release the system?
	/*
	if( internal_->Song )
		internal_->Song->release();
	*/

	delete internal_;
}

class SongLoaderJob : public Job
{

	SongInternal *internal_;

	std::string path_;

	Song *song_;

public:

	SongLoaderJob( Song *song, SongInternal *internal, const std::string &path )
		: song_( song )
		, internal_( internal )
		, path_( path )
	{
	}

	void Do()
	{
		std::string internalPath = "/vol/content/0010/" + path_;

		FMOD_RESULT result;
		//result = FMODSystem->createStream( internalPath.c_str(), FMOD_OPENONLY, 0, &internal_->Song );
		result = FMOD_System_CreateStream( FMODSystem, internalPath.c_str(), FMOD_OPENONLY, 0, &internal_->Song );
		if( result != FMOD_OK )
		{
			LOG_WRITE( "Failed to load song: %s\n", internalPath.c_str() );
			internal_->Song = NULL;
			return;
		}

		// I cry a little bit inside.
		if( path_.find( "140_Mph_in_the_Fog^Blind_Digital" ) != std::string::npos )
			song_->Duration.TotalSeconds = 245.f;
		else if( path_.find( "Blue_Chair^Blind_Digital" ) != std::string::npos )
			song_->Duration.TotalSeconds = 318.f;
		else if( path_.find( "Evidence^Blind_Digital" ) != std::string::npos )
			song_->Duration.TotalSeconds = 173.f;
		else if( path_.find( "Get_a_Grip^Peacemaker" ) != std::string::npos )
			song_->Duration.TotalSeconds = 119.f;
		else if( path_.find( "Happy^James_Stant" ) != std::string::npos )
			song_->Duration.TotalSeconds = 128.f;
		else if( path_.find( "House^Blind_Digital" ) != std::string::npos )
			song_->Duration.TotalSeconds = 345.f;
		else if( path_.find( "Nero's_Law^Peacemaker" ) != std::string::npos )
			song_->Duration.TotalSeconds = 217.f;
		else if( path_.find( "Ripcurl^Blind_Digital" ) != std::string::npos )
			song_->Duration.TotalSeconds = 351.f;
		else if( path_.find( "The_Fat_is_in_the_Fire^Peacemaker" ) != std::string::npos )
			song_->Duration.TotalSeconds = 167.f;
		else if( path_.find( "The_Heavens_Opened^Peacemaker" ) != std::string::npos )
			song_->Duration.TotalSeconds = 223.f;
		else if( path_.find( "Tidy_Up^Peacemaker" ) != std::string::npos )
			song_->Duration.TotalSeconds = 135.f;
		else if( path_.find( "Writer's_Block^Peacemaker" ) != std::string::npos )
			song_->Duration.TotalSeconds = 145.f;
	}
};

void Song::Load( const std::string &path )
{
	// Load screensaver and main menu songs first.
	/*if( path.find( "Ripcurl^Blind_Digital" ) != std::string::npos
		|| path.find( "Ripcurl^Blind_Digital" ) != std::string::npos )
	{
		SCHEDULER->RunJobASAP( new SongLoaderJob( this, internal_, path ) );
	}
	else
	{
		SCHEDULER->RunJob( new SongLoaderJob( this, internal_, path ) );
	}*/

	std::string internalPath = "/vol/content/0010/" + path;

	FMOD_RESULT result;
	//result = FMODSystem->createStream( internalPath.c_str(), FMOD_NONBLOCKING, 0, &internal_->Song );
	result = FMOD_System_CreateStream( FMODSystem, internalPath.c_str(), FMOD_NONBLOCKING, 0, &internal_->Song );
	if( result != FMOD_OK )
	{
		LOG_WRITE( "Failed to load song: %s\n", internalPath.c_str() );
		internal_->Song = NULL;
		return;
	}

	// I cry a little bit inside.
	if( path.find( "140_Mph_in_the_Fog^Blind_Digital" ) != std::string::npos )
		Duration.TotalSeconds = 245.f;
	else if( path.find( "Blue_Chair^Blind_Digital" ) != std::string::npos )
		Duration.TotalSeconds = 318.f;
	else if( path.find( "Evidence^Blind_Digital" ) != std::string::npos )
		Duration.TotalSeconds = 173.f;
	else if( path.find( "Get_a_Grip^Peacemaker" ) != std::string::npos )
		Duration.TotalSeconds = 119.f;
	else if( path.find( "Happy^James_Stant" ) != std::string::npos )
		Duration.TotalSeconds = 128.f;
	else if( path.find( "House^Blind_Digital" ) != std::string::npos )
		Duration.TotalSeconds = 345.f;
	else if( path.find( "Nero's_Law^Peacemaker" ) != std::string::npos )
		Duration.TotalSeconds = 217.f;
	else if( path.find( "Ripcurl^Blind_Digital" ) != std::string::npos )
		Duration.TotalSeconds = 351.f;
	else if( path.find( "The_Fat_is_in_the_Fire^Peacemaker" ) != std::string::npos )
		Duration.TotalSeconds = 167.f;
	else if( path.find( "The_Heavens_Opened^Peacemaker" ) != std::string::npos )
		Duration.TotalSeconds = 223.f;
	else if( path.find( "Tidy_Up^Peacemaker" ) != std::string::npos )
		Duration.TotalSeconds = 135.f;
	else if( path.find( "Writer's_Block^Peacemaker" ) != std::string::npos )
		Duration.TotalSeconds = 145.f;
}
